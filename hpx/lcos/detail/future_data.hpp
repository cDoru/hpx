//  Copyright (c) 2007-2013 Hartmut Kaiser
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#if !defined(HPX_LCOS_DETAIL_FUTURE_DATA_MAR_06_2012_1055AM)
#define HPX_LCOS_DETAIL_FUTURE_DATA_MAR_06_2012_1055AM

#include <hpx/hpx_fwd.hpp>
#include <hpx/traits/get_remote_result.hpp>
#include <hpx/util/move.hpp>
#include <hpx/runtime/threads/thread_data.hpp>
#include <hpx/runtime/threads/thread_helpers.hpp>
#include <hpx/runtime/threads/thread_executor.hpp>
#include <hpx/lcos/detail/full_empty_memory.hpp>
#include <hpx/lcos/local/no_mutex.hpp>
#include <hpx/util/decay.hpp>
#include <hpx/util/unused.hpp>
#include <hpx/util/scoped_unlock.hpp>
#include <hpx/util/detail/value_or_error.hpp>

#include <boost/intrusive_ptr.hpp>
#include <boost/intrusive/slist.hpp>
#include <boost/mpl/if.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/detail/atomic_count.hpp>
#include <boost/detail/scoped_enum_emulation.hpp>
#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/repetition/enum.hpp>
#include <boost/preprocessor/repetition/repeat_from_to.hpp>

///////////////////////////////////////////////////////////////////////////////
namespace hpx { namespace lcos
{
    BOOST_SCOPED_ENUM_START(future_status)
    {
        ready, timeout, deferred, uninitialized
    };
    BOOST_SCOPED_ENUM_END

    // forward declaration
    template <typename Result>
    future<Result>
    make_error_future(boost::exception_ptr const& e);
}}

///////////////////////////////////////////////////////////////////////////////
namespace hpx { namespace lcos
{

namespace local { template <typename T> struct channel; }

namespace detail
{
    template <typename Result> struct future_data_base;

    ///////////////////////////////////////////////////////////////////////
    template <typename Result>
    inline lcos::future<Result> make_future_from_data(
        boost::intrusive_ptr<detail::future_data_base<Result> > const&);

    template <typename Result>
    inline lcos::future<Result> make_future_from_data(
        BOOST_RV_REF(boost::intrusive_ptr<detail::future_data_base<Result> >));

    template <typename Result>
    inline lcos::future<Result> make_future_from_data(
        detail::future_data_base<Result>* p);

    template <typename Result>
    inline detail::future_data_base<Result>*
        get_future_data(lcos::future<Result>&);

    template <typename Result>
    inline detail::future_data_base<Result> const*
        get_future_data(lcos::future<Result> const&);

    ///////////////////////////////////////////////////////////////////////
    struct future_data_refcnt_base;

    void intrusive_ptr_add_ref(future_data_refcnt_base* p);
    void intrusive_ptr_release(future_data_refcnt_base* p);

    ///////////////////////////////////////////////////////////////////////
    struct future_data_refcnt_base
    {
    public:
        typedef void has_future_data_refcnt_base;

        virtual ~future_data_refcnt_base() {}

    protected:
        future_data_refcnt_base() : count_(0) {}

        // reference counting
        friend void intrusive_ptr_add_ref(future_data_refcnt_base* p);
        friend void intrusive_ptr_release(future_data_refcnt_base* p);

        boost::detail::atomic_count count_;
    };

    /// support functions for boost::intrusive_ptr
    inline void intrusive_ptr_add_ref(future_data_refcnt_base* p)
    {
        ++p->count_;
    }
    inline void intrusive_ptr_release(future_data_refcnt_base* p)
    {
        if (0 == --p->count_)
            delete p;
    }

    ///////////////////////////////////////////////////////////////////////////
    template <typename Result>
    struct future_data_base : future_data_refcnt_base
    {
        typedef typename boost::mpl::if_<
            boost::is_same<void, Result>, util::unused_type, Result
        >::type result_type;
        typedef HPX_STD_FUNCTION<void()>
            completed_callback_type;
        typedef lcos::local::spinlock mutex_type;

        virtual void deleting_owner() {}

        virtual result_type get_data(error_code& ec = throws) = 0;
        virtual result_type move_data(error_code& ec = throws) = 0;
        virtual bool is_ready() const = 0;
        virtual bool is_ready_locked() const = 0;
        virtual bool has_value() const = 0;
        virtual bool has_exception() const = 0;
        virtual BOOST_SCOPED_ENUM(future_status) get_state() const = 0;

        // cancellation is disabled by default
        virtual bool cancelable() const
        {
            return false;
        }
        virtual void cancel()
        {
            HPX_THROW_EXCEPTION(future_does_not_support_cancellation,
                "future_data_base::cancel",
                "this future does not support cancellation");
        }

        // continuation support
        virtual completed_callback_type
            set_on_completed(BOOST_RV_REF(completed_callback_type)) = 0;
        virtual completed_callback_type
            set_on_completed_locked(BOOST_RV_REF(completed_callback_type),
            typename mutex_type::scoped_lock& l) = 0;
        virtual completed_callback_type reset_on_completed_locked() = 0;

        // wait support
        struct wake_me_up
        {
            explicit wake_me_up(threads::thread_id_type const& thread_id)
              : thread_id_(thread_id)
            {}

            void operator()() const
            {
                threads::set_thread_state(
                    thread_id_, threads::pending, threads::wait_timeout);
            }

            threads::thread_id_type thread_id_;
        };

        struct reset_cb
        {
            template <typename F>
            reset_cb(future_data_base& fb, BOOST_FWD_REF(F) f,
                    typename mutex_type::scoped_lock& l)
              : target_(fb),
                l_(l),
                oldcb_(fb.reset_on_completed_locked())
            {
                fb.set_on_completed_locked(boost::forward<F>(f), l);
            }
            ~reset_cb()
            {
                l_.lock();
                target_.set_on_completed_locked(boost::move(oldcb_), l_);
            }

            future_data_base& target_;
            typename mutex_type::scoped_lock& l_;
            completed_callback_type oldcb_;
        };

        void wait()
        {
            typename mutex_type::scoped_lock l(mtx_);
            if (!is_ready_locked()) {
                boost::intrusive_ptr<future_data_base> this_(this);
                wake_me_up callback(threads::get_self_id());
                set_on_completed_locked(boost::ref(callback), l);  // leaves 'l' unlocked

                this_thread::suspend(threads::suspended);
            }
        }

        BOOST_SCOPED_ENUM(future_status)
        wait_for(boost::posix_time::time_duration const& p)
        {
            typename mutex_type::scoped_lock l(mtx_);
            if (!is_ready_locked()) {
                boost::intrusive_ptr<future_data_base> this_(this);
                reset_cb r(*this, wake_me_up(threads::get_self_id()), l);  // leaves 'l' unlocked

                // if the timer has hit, the waiting period timed out
                return (this_thread::suspend(p) == threads::wait_signaled) ? //-V110
                    future_status::timeout : future_status::ready;
            }
            return future_status::ready; //-V110
        }

        BOOST_SCOPED_ENUM(future_status)
        wait_until(boost::posix_time::ptime const& at)
        {
            typename mutex_type::scoped_lock l(mtx_);
            if (!is_ready_locked()) {
                boost::intrusive_ptr<future_data_base> this_(this);
                reset_cb r(*this, wake_me_up(threads::get_self_id()), l);  // leaves 'l' unlocked

                // if the timer has hit, the waiting period timed out
                return (this_thread::suspend(at) == threads::wait_signaled) ? //-V110
                    future_status::timeout : future_status::ready;
            }
            return future_status::ready; //-V110
        }

    protected:
        mutable mutex_type mtx_;

    protected:
        future_data_base() {}
    };

    ///////////////////////////////////////////////////////////////////////////
    template <typename F1, typename F2>
    struct compose_cb_impl
    {
        template <typename A1, typename A2>
        compose_cb_impl(BOOST_FWD_REF(A1) f1, BOOST_FWD_REF(A2) f2)
          : f1_(boost::forward<A1>(f1))
          , f2_(boost::forward<A2>(f2))
        {}

        typedef void result_type;

        void operator()() const
        {
            if (!f1_.empty()) f1_();
            if (!f2_.empty()) f2_();
        }

        typename util::remove_reference<F1>::type f1_;
        typename util::remove_reference<F2>::type f2_;
    };

    ///////////////////////////////////////////////////////////////////////////
    template <typename Result>
    struct future_data : future_data_base<Result>
    {
    public:
        typedef future_data_base<Result> base_type;
        typedef typename base_type::result_type result_type;
        typedef typename base_type::mutex_type mutex_type;
        typedef boost::exception_ptr error_type;
        typedef util::detail::value_or_error<result_type> data_type;

        typedef typename base_type::completed_callback_type
            completed_callback_type;

    public:
        future_data()
          : data_(), state_(empty)
        {}

        future_data(completed_callback_type const& data_sink)
          : data_(), state_(empty)
          , on_completed_(data_sink)
        {}

        ~future_data()
        {
            if (!read_queue_.empty()) {
                LERR_(info) << "~full_empty_entry: read_queue is not empty";
                log_non_empty_queue("read_queue", read_queue_);
            }
        }

        static result_type handle_error(data_type const& d, error_code &ec)
        {
            // an error has been reported in the meantime, throw or set
            // the error code
            if (&ec == &throws) {
                boost::rethrow_exception(d.get_error());
                // never reached
            }
            else {
                ec = make_error_code(d.get_error());
            }
            return result_type();
        }

        /// Get the result of the requested action. This call blocks (yields
        /// control) if the result is not ready. As soon as the result has been
        /// returned and the waiting thread has been re-scheduled by the thread
        /// manager the function will return.
        ///
        /// \param ec     [in,out] this represents the error status on exit,
        ///               if this is pre-initialized to \a hpx#throws
        ///               the function will throw on error instead. If the
        ///               operation blocks and is aborted because the object
        ///               went out of scope, the code \a hpx#yield_aborted is
        ///               set or thrown.
        ///
        /// \note         If there has been an error reported (using the action
        ///               \a base_lco#set_exception), this function will throw an
        ///               exception encapsulating the reported error code and
        ///               error description if <code>&ec == &throws</code>.
        result_type get_data(error_code& ec = throws)
        {
            // yields control if needed
            data_type d;
            {
                typename mutex_type::scoped_lock l(this->mtx_);
                feb_read(d, l, ec);      // copies the data out of the store
                if (ec) return result_type();
            }

            if (d.is_empty()) {
                // the value has already been moved out of this future
                HPX_THROWS_IF(ec, no_state,
                    "future_data::get_data",
                    "this future has no valid shared state");
                return result_type();
            }

            // the thread has been re-activated by one of the actions
            // supported by this promise (see \a promise::set_event
            // and promise::set_exception).
            if (d.stores_error())
                return handle_error(d, ec);

            // no error has been reported, return the result
            return d.move_value();
        }

    public:
        result_type move_data(error_code& ec = throws)
        {
            // yields control if needed
            data_type d;
            {
                typename mutex_type::scoped_lock l(this->mtx_);
                feb_move(d, l, ec); // moves the data from the store
                if (ec) return result_type();
            }

            if (d.is_empty()) {
                // the value has already been moved out of this future
                HPX_THROWS_IF(ec, no_state,
                    "future_data::move_data",
                    "this future has no valid shared state");
                return result_type();
            }

            // the thread has been re-activated by one of the actions
            // supported by this promise (see \a promise::set_event
            // and promise::set_exception).
            if (d.stores_error())
                return handle_error(d, ec);

            // no error has been reported, return the result
            return d.move_value();
        }

        // helper functions for setting data (if successful) or the error (if
        // non-successful)
        template <typename T>
        void set_data(BOOST_FWD_REF(T) result)
        {
            // set the received result, reset error status
            try {
               typedef typename util::decay<T>::type naked_type;

                typedef traits::get_remote_result<
                    result_type, naked_type
                > get_remote_result_type;

                completed_callback_type on_completed;
                {
                    typename mutex_type::scoped_lock l(this->mtx_);

                    // check whether the data already has been set
                    if (!feb_is_empty()) {
                        HPX_THROW_EXCEPTION(promise_already_satisfied,
                            "packaged_task::set_data<Result>",
                            "data has already been set for this future");
                    }

                    on_completed = boost::move(on_completed_);

                    // store the value
                    feb_set(boost::move(get_remote_result_type::call(
                          boost::forward<T>(result))));
                }

                // invoke the callback (continuation) function
                if (!on_completed.empty())
                    on_completed();
            }
            catch (hpx::exception const&) {
                // store the error instead
                set_exception(boost::current_exception());
            }
        }

        // trigger the future with the given error condition
        void set_exception(boost::exception_ptr const& e)
        {
            completed_callback_type on_completed;
            {
                typename mutex_type::scoped_lock l(this->mtx_);

                // check whether the data already has been set
                if (!feb_is_empty()) {
                    HPX_THROW_EXCEPTION(promise_already_satisfied,
                        "packaged_task::set_data<Result>",
                        "data has already been set for this future");
                }

                on_completed = boost::move(on_completed_);

                // store the error code
                feb_set(e);
            }

            // invoke the callback (continuation) function
            if (!on_completed.empty())
                on_completed();
        }

        void set_error(error e, char const* f, char const* msg)
        {
            try {
                HPX_THROW_EXCEPTION(e, f, msg);
            }
            catch (hpx::exception const&) {
                // store the error code
                set_exception(boost::current_exception());
            }
        }

        /// Return whether or not the data is available for this
        /// \a promise.
        bool is_ready() const
        {
            typename mutex_type::scoped_lock l(this->mtx_);
            return is_ready_locked();
        }

        bool is_ready_locked() const
        {
            return !feb_is_empty();
        }

    private:
        static bool has_data_helper(data_type const& d)
        {
            return d.stores_value();
        }

    public:
        bool has_value() const
        {
            typename mutex_type::scoped_lock l(this->mtx_);
            return !feb_is_empty() && feb_peek(&has_data_helper);
        }

        bool has_exception() const
        {
            typename mutex_type::scoped_lock l(this->mtx_);
            return !feb_is_empty() && !feb_peek(&has_data_helper);
        }

        BOOST_SCOPED_ENUM(future_status) get_state() const
        {
            typename mutex_type::scoped_lock l(this->mtx_);
            return !feb_is_empty() ? future_status::ready : future_status::deferred; //-V110
        }

        /// Reset the promise to allow to restart an asynchronous
        /// operation. Allows any subsequent set_data operation to succeed.
        void reset(error_code& ec = throws)
        {
            typename mutex_type::scoped_lock l(this->mtx_);
            feb_set_empty(ec);
        }

        /// Set the callback which needs to be invoked when the future becomes
        /// ready. If the future is ready the function will be invoked
        /// immediately.
        completed_callback_type
        set_on_completed(BOOST_RV_REF(completed_callback_type) data_sink)
        {
            typename mutex_type::scoped_lock l(this->mtx_);
            return set_on_completed_locked(boost::move(data_sink), l);
        }

    private:
        template <typename F1, typename F2>
        static BOOST_FORCEINLINE completed_callback_type
        compose_cb(BOOST_FWD_REF(F1) f1, BOOST_FWD_REF(F2) f2)
        {
            // otherwise create a combined callback
            return completed_callback_type(boost::move(
                    compose_cb_impl<F1, F2>(
                        boost::forward<F1>(f1),
                        boost::forward<F2>(f2))
                ));
        }

    public:
        // note: leaves the given lock in unlocked state when returning
        completed_callback_type set_on_completed_locked(
            BOOST_RV_REF(completed_callback_type) data_sink,
            typename mutex_type::scoped_lock& l)
        {
            completed_callback_type retval = boost::move(on_completed_);

            if (!data_sink.empty() && !feb_is_empty()) {
                // invoke the callback (continuation) function right away
                l.unlock();

                if (!retval.empty())
                    retval();
                data_sink();
            }
            else if (!retval.empty()) {
                // store a combined callback wrapping the old and the new one
                on_completed_ = boost::move(
                    compose_cb(boost::move(data_sink), retval));

                l.unlock();
            }
            else {
                // store the new callback
                on_completed_ = boost::move(data_sink);

                l.unlock();
            }

            return boost::move(retval);
        }

        completed_callback_type reset_on_completed_locked()
        {
            return boost::move(on_completed_);
        }

    private:
        /// \brief  Waits for the memory to become full and then reads it,
        ///         leaves memory in full state. If the location is empty the
        ///         calling thread will wait (block) for another thread to call
        ///         either the function \a set or the function \a write.
        ///
        /// \param ec [in,out] this represents the error status on exit,
        ///           if this is pre-initialized to \a hpx#throws
        ///           the function will throw on error instead. If the operation
        ///           blocks and is aborted because the object went out of
        ///           scope, the code \a hpx#yield_aborted is set or thrown.
        ///
        /// \note   When memory becomes full, all \a threads waiting for it
        ///         to become full with a read will receive the value at once
        ///         and will be queued to run.
        template <typename Target, typename Lock>
        void feb_read(Target& dest, Lock& l, error_code& ec = throws)
        {
            // block if this entry is empty
            if (state_ == empty) {
                threads::thread_self* self = threads::get_self_ptr_checked(ec);
                if (0 == self || ec) return;

                // enqueue the request and block this thread
                queue_entry f(threads::get_self_id());
                read_queue_.push_back(f);

                reset_queue_entry r(f, read_queue_);

                {
                    // yield this thread
                    util::scoped_unlock<Lock> ul(l);
                    this_thread::suspend(threads::suspended,
                        "full_empty_entry::enqueue_full_full", ec);
                    if (ec) return;
                }
            }

            // copy the data to the destination
            dest = data_;

            if (&ec != &throws)
                ec = make_success_code();
        }

        /// \brief  Waits for the memory to become full and then reads (moves) it,
        ///         leaves memory in full state. If the location is empty the
        ///         calling thread will wait (block) for another thread to call
        ///         either the function \a set or the function \a write.
        ///
        /// \param ec [in,out] this represents the error status on exit,
        ///           if this is pre-initialized to \a hpx#throws
        ///           the function will throw on error instead. If the operation
        ///           blocks and is aborted because the object went out of
        ///           scope, the code \a hpx#yield_aborted is set or thrown.
        ///
        /// \note   When memory becomes full, all \a threads waiting for it
        ///         to become full with a read will receive the value at once
        ///         and will be queued to run.
        template <typename Target, typename Lock>
        void feb_move(Target& dest, Lock& l, error_code& ec = throws)
        {
            // block if this entry is empty
            if (state_ == empty) {
                threads::thread_self* self = threads::get_self_ptr_checked(ec);
                if (0 == self || ec) return;

                // enqueue the request and block this thread
                queue_entry f(threads::get_self_id());
                read_queue_.push_back(f);

                reset_queue_entry r(f, read_queue_);

                {
                    // yield this thread
                    util::scoped_unlock<Lock> ul(l);
                    this_thread::suspend(threads::suspended,
                        "full_empty_entry::enqueue_full_full", ec);
                    if (ec) return;
                }
            }

            // move the data to the destination
            dest = boost::move(data_);

            if (&ec != &throws)
                ec = make_success_code();
        }

        /// \brief  Writes memory and atomically sets its state to full without
        ///         waiting for it to become empty.
        ///
        /// \note   Even if the function itself doesn't block, setting the
        ///         location to full using \a set might re-activate threads
        ///         waiting on this in a \a read or \a read_and_empty function.
        template <typename Target>
        void feb_set(BOOST_FWD_REF(Target) data)
        {
            // set the data
            data_ = boost::forward<Target>(data);

            // make sure the entry is full
            feb_set_full();    // state_ = full
        }

        /// \brief  Calls the supplied function passing along the stored data
        ///         (if full)
        ///
        /// \param f [in] The function to be called
        ///
        /// \returns This function returns \a false if the FE memory is empty
        ///          otherwise it returns the return value of \p f.
        template <typename F>
        bool feb_peek(F f) const
        {
            if (state_ == empty)
                return false;
            return f(data_);      // pass the data to the provided function
        }
        // returns whether this entry is currently empty
        bool feb_is_empty() const
        {
            return state_ == empty;
        }

        // sets this entry to empty
        bool feb_set_empty(error_code& ec = throws)
        {
            state_ = empty;

            // return whether this block needs to be removed
            return state_ == full && !feb_is_used();
        }

        // sets this entry to full
        bool feb_set_full(error_code& ec = throws)
        {
            state_ = full;

            // handle all threads waiting for the block to become full
            while (!read_queue_.empty()) {
                threads::thread_id_type id = read_queue_.front().id_;
                read_queue_.front().id_ = threads::invalid_thread_id;
                read_queue_.pop_front();

                threads::set_thread_state(id, threads::pending,
                    threads::wait_timeout, threads::thread_priority_default, ec);
                if (ec) return false;
            }

            // return whether this block needs to be removed
            return state_ == full && !feb_is_used();
        }

        // returns whether this entry is still in use
        bool feb_is_used() const
        {
            return !read_queue_.empty();
        }

    private:
        enum full_empty_state
        {
            empty = false,
            full = true
        };

        // define data structures needed for intrusive slist container used for
        // the queues
        struct queue_entry
        {
            typedef boost::intrusive::slist_member_hook<
                boost::intrusive::link_mode<boost::intrusive::normal_link>
            > hook_type;

            queue_entry(threads::thread_id_type const& id)
              : id_(id)
            {}

            threads::thread_id_type id_;
            hook_type list_hook_;
        };

        typedef boost::intrusive::member_hook<
            queue_entry, typename queue_entry::hook_type,
            &queue_entry::list_hook_
        > list_option_type;

        typedef boost::intrusive::slist<
            queue_entry, list_option_type,
            boost::intrusive::cache_last<true>,
            boost::intrusive::constant_time_size<false>
        > queue_type;

        struct reset_queue_entry
        {
            reset_queue_entry(queue_entry& e, queue_type& q)
              : e_(e), q_(q), last_(q.last())
            {}

            ~reset_queue_entry()
            {
                if (e_.id_)
                    q_.erase(last_);     // remove entry from queue
            }

            queue_entry& e_;
            queue_type& q_;
            typename queue_type::const_iterator last_;
        };

        void log_non_empty_queue(char const* const desc, queue_type& queue)
        {
            while (!queue.empty()) {
                threads::thread_id_type id = queue.front().id_;
                queue.front().id_ = threads::invalid_thread_id;
                queue.pop_front();

                // we know that the id is actually the pointer to the thread
                LERR_(info) << "~full_empty_entry: aborting pending thread in "
                        << desc << ": "
                        << get_thread_state_name(id->get_state())
                        << "(" << id.get() << "): " << id->get_description();

                // forcefully abort thread, do not throw
                error_code ec(lightweight);
                threads::set_thread_state(id, threads::pending,
                    threads::wait_abort, threads::thread_priority_default, ec);
                if (ec) {
                    LERR_(error) << "~full_empty_entry: could not abort thread"
                        << get_thread_state_name(id->get_state())
                        << "(" << id.get() << "): " << id->get_description();
                }
            }
        }

        queue_type read_queue_;               // threads waiting in read
        data_type data_;                      // protected data
        full_empty_state state_;              // current full/empty state

    protected:
        completed_callback_type on_completed_;
    };

    ///////////////////////////////////////////////////////////////////////////
    template <typename Result>
    struct timed_future_data : future_data<Result>
    {
    public:
        typedef future_data<Result> base_type;
        typedef typename base_type::result_type result_type;
        typedef typename base_type::mutex_type mutex_type;
        typedef typename base_type::error_type error_type;
        typedef typename base_type::data_type data_type;

    public:
        timed_future_data() {}

        template <typename Result_>
        timed_future_data(boost::posix_time::ptime const& at,
            BOOST_FWD_REF(Result_) init)
        {
            at_time(at, boost::forward<Result_>(init));
        }

        template <typename Result_>
        timed_future_data(boost::posix_time::time_duration const& d,
            BOOST_RV_REF(Result_) init)
        {
            at_time(d, boost::forward<Result_>(init));
        }

        void set_data(result_type const& value)
        {
            this->base_type::set_data(value);
        }

        template <typename TimeSpec, typename Result_>
        void at_time(TimeSpec const& tpoint, BOOST_FWD_REF(Result_) init)
        {
            boost::intrusive_ptr<timed_future_data> this_(this);

            error_code ec;
            threads::thread_id_type id = threads::register_thread_nullary(
                HPX_STD_BIND(&timed_future_data::set_data, this_,
                    boost::forward<Result_>(init)),
                "timed_future_data<Result>::timed_future_data",
                threads::suspended, true, threads::thread_priority_normal,
                std::size_t(-1), threads::thread_stacksize_default, ec);
            if (ec) {
                // thread creation failed, report error to the new future
                this->base_type::set_exception(hpx::detail::access_exception(ec));
            }

            // start new thread at given point in time
            threads::set_thread_state(id, tpoint, threads::pending,
                threads::wait_timeout, threads::thread_priority_critical, ec);
            if (ec) {
                // thread scheduling failed, report error to the new future
                this->base_type::set_exception(hpx::detail::access_exception(ec));
            }
        }
    };

    ///////////////////////////////////////////////////////////////////////////
    template <typename Result>
    struct task_base : future_data<Result>
    {
    private:
        typedef typename future_data<Result>::mutex_type mutex_type;
        typedef boost::intrusive_ptr<task_base> future_base_type;

    protected:
        typedef typename future_data<Result>::result_type result_type;

        threads::thread_id_type get_id() const
        {
            typename mutex_type::scoped_lock l(this->mtx_);
            return id_;
        }
        void set_id(threads::thread_id_type id)
        {
            typename mutex_type::scoped_lock l(this->mtx_);
            id_ = id;
        }

    public:
        task_base()
          : started_(false), id_(threads::invalid_thread_id), sched_(0)
        {}

        task_base(threads::executor& sched)
          : started_(false), id_(threads::invalid_thread_id), sched_(&sched)
        {}

        // retrieving the value
        result_type get_data(error_code& ec = throws)
        {
            if (!was_started())
                this->do_run();
            return this->future_data<Result>::get_data(ec);
        }

        // moving out the value
        result_type move_data(error_code& ec = throws)
        {
            if (!was_started())
                this->do_run();
            return this->future_data<Result>::move_data(ec);
        }

    private:
        bool was_started()
        {
            typename mutex_type::scoped_lock l(this->mtx_);
            if (started_)
                return true;

            started_ = true;
            return false;
        }

        void check_started()
        {
            typename mutex_type::scoped_lock l(this->mtx_);
            if (started_) {
                HPX_THROW_EXCEPTION(task_already_started,
                    "task_base::check_started", "this task has already been started");
                return;
            }
            started_ = true;
        }

    public:
        // run synchronously
        void run()
        {
            check_started();
            this->do_run();       // always on this thread
        }

        // run in a separate thread
        void apply(threads::thread_priority priority,
            threads::thread_stacksize stacksize, error_code& ec)
        {
            check_started();

            future_base_type this_(this);

            if (sched_) {
                sched_->add(HPX_STD_BIND(&task_base::run_impl, this_),
                    "task_base::apply", threads::pending, false,
                    stacksize, ec);
            }
            else {
                threads::register_thread_plain(
                    HPX_STD_BIND(&task_base::run_impl, this_),
                    "task_base::apply", threads::pending, false,
                    priority, std::size_t(-1), stacksize, ec);
            }
        }

    private:
        struct reset_id
        {
            reset_id(task_base& target)
              : target_(target)
            {
                target.set_id(threads::get_self_id());
            }
            ~reset_id()
            {
                target_.set_id(threads::invalid_thread_id);
            }
            task_base& target_;
        };

    protected:
        threads::thread_state_enum run_impl()
        {
            reset_id r(*this);
            this->do_run();
            return threads::terminated;
        }

    public:
        void deleting_owner()
        {
            typename mutex_type::scoped_lock l(this->mtx_);
            if (!started_) {
                started_ = true;
                l.unlock();
                this->set_error(broken_task, "task_base::deleting_owner",
                    "deleting task owner before future has become ready");
            }
        }

        template <typename T>
        void set_data(BOOST_FWD_REF(T) result)
        {
            BOOST_ASSERT(started_);
            this->future_data<Result>::set_data(boost::forward<T>(result));
        }

        void set_exception(boost::exception_ptr const& e)
        {
            BOOST_ASSERT(started_);
            this->future_data<Result>::set_exception(e);
        }

        virtual void do_run() = 0;

        // cancellation support
        bool cancelable() const
        {
            return true;
        }

        void cancel()
        {
            typename mutex_type::scoped_lock l(this->mtx_);
            try {
                if (!this->started_) {
                    HPX_THROW_EXCEPTION(thread_interrupted,
                        "task_base<Result>::cancel",
                        "future has been canceled");
                    return;
                }

                if (this->is_ready_locked())
                    return;   // nothing we can do

                if (id_ != threads::invalid_thread_id) {
                    // interrupt the executing thread
                    threads::interrupt_thread(id_);

                    this->started_ = true;

                    l.unlock();
                    this->set_error(thread_interrupted,
                        "task_base<Result>::cancel",
                        "future has been canceled");
                }
                else {
                    HPX_THROW_EXCEPTION(future_can_not_be_cancelled,
                        "task_base<Result>::cancel",
                        "future can't be canceled at this time");
                }
            }
            catch (hpx::exception const&) {
                this->started_ = true;
                this->set_exception(boost::current_exception());
                throw;
            }
        }

    protected:
        bool started_;
        threads::thread_id_type id_;
        threads::executor* sched_;
    };
}}}

#endif
