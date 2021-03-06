// Copyright (c) 2007-2013 Hartmut Kaiser
// Copyright (c) 2012-2013 Thomas Heller
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

// This file has been automatically generated using the Boost.Wave tool.
// Do not edit manually.


namespace hpx { namespace actions
{
    
    
    template <
        typename Component, typename Result,
        typename T0,
        Result (Component::*F)(T0) const, typename Derived>
    class base_result_action1<
            Result (Component::*)(T0) const, F, Derived>
      : public action<
            Component const, Result,
            hpx::util::tuple<typename util::decay<T0>::type>,
            Derived>
    {
    public:
        typedef Result result_type;
        typedef typename detail::remote_action_result<Result>::type
            remote_result_type;
        typedef hpx::util::tuple<
            typename util::decay<T0>::type> arguments_type;
        typedef action<Component const, remote_result_type, arguments_type, Derived>
            base_type;
    protected:
        
        
        
        struct thread_function
        {
            typedef threads::thread_state_enum result_type;
            template <typename Arg0>
            BOOST_FORCEINLINE result_type operator()(
                naming::address::address_type lva,
                BOOST_FWD_REF(Arg0) arg0) const
            {
                try {
                    LTM_(debug) << "Executing component action("
                                << detail::get_action_name<Derived>()
                                << ") lva(" << reinterpret_cast<void const*>
                                    (get_lva<Component const>::call(lva)) << ")";
                    
                    
                    
                    
                    (get_lva<Component const>::call(lva)->*F)(
                        boost::move(arg0));
                }
                catch (hpx::thread_interrupted const&) {
                     
                }
                catch (hpx::exception const& e) {
                    LTM_(error)
                        << "Unhandled exception while executing component action("
                        << detail::get_action_name<Derived>()
                        << ") lva(" << reinterpret_cast<void const*>
                            (get_lva<Component const>::call(lva)) << "): " << e.what();
                    
                    hpx::report_error(boost::current_exception());
                }
                catch (...) {
                    LTM_(error)
                        << "Unhandled exception while executing component action("
                        << detail::get_action_name<Derived>()
                        << ") lva(" << reinterpret_cast<void const*>
                            (get_lva<Component const>::call(lva)) << ")";
                    
                    hpx::report_error(boost::current_exception());
                }
                
                
                
                util::force_error_on_lock();
                return threads::terminated;
            }
        };
    public:
        typedef boost::mpl::false_ direct_execution;
        
        
        
        
        template <typename Arguments>
        static HPX_STD_FUNCTION<threads::thread_function_type>
        construct_thread_function(naming::address::address_type lva,
            BOOST_FWD_REF(Arguments) args)
        {
            return Derived::decorate_action(
                HPX_STD_BIND(typename Derived::thread_function(),
                    lva, util::get< 0>(boost::forward<Arguments>( args))), lva);
        }
        
        
        
        
        template <typename Arguments>
        static HPX_STD_FUNCTION<threads::thread_function_type>
        construct_thread_function(continuation_type& cont,
            naming::address::address_type lva, BOOST_FWD_REF(Arguments) args)
        {
            return Derived::decorate_action(
                base_type::construct_continuation_thread_object_function(
                    cont, F, get_lva<Component const>::call(lva),
                    boost::forward<Arguments>(args)), lva);
        }
        
        template <typename Arguments>
        BOOST_FORCEINLINE static Result
        execute_function(naming::address::address_type lva,
            BOOST_FWD_REF(Arguments) args)
        {
            LTM_(debug)
                << "base_result_action" << 1
                << "::execute_function name("
                << detail::get_action_name<Derived>()
                << ") lva(" << reinterpret_cast<void const*>(
                    get_lva<Component const>::call(lva)) << ")";
            return (get_lva<Component const>::call(lva)->*F)(
                util::get< 0>(boost::forward<Arguments>( args)));
        }
    };
    
    
    template <
        typename Component, typename Result,
        typename T0,
        Result (Component::*F)(T0) const,
        typename Derived>
    struct result_action1<
            Result (Component::*)(T0) const, F, Derived>
      : base_result_action1<
            Result (Component::*)(T0) const, F,
            typename detail::action_type<
                result_action1<
                    Result (Component::*)(T0) const, F, Derived>,
                Derived
            >::type>
    {
        typedef typename detail::action_type<
            result_action1, Derived
        >::type derived_type;
        typedef boost::mpl::false_ direct_execution;
    };
    
    template <
        typename Component, typename Result, typename T0,
        Result (Component::*F)(T0) const, typename Derived>
    struct make_action<Result (Component::*)(T0) const,
            F, Derived, boost::mpl::false_>
      : result_action1<
            Result (Component::*)(T0) const, F, Derived>
    {
        typedef result_action1<
            Result (Component::*)(T0) const, F, Derived
        > type;
    };
    
    
    template <
        typename Component, typename Result,
        typename T0,
        Result (Component::*F)(T0) const,
        typename Derived>
    struct direct_result_action1<
            Result (Component::*)(T0) const, F, Derived>
      : base_result_action1<
            Result (Component::*)(T0) const, F,
            typename detail::action_type<
                direct_result_action1<
                    Result (Component::*)(T0) const, F, Derived>,
                    Derived
            >::type>
    {
        typedef typename detail::action_type<
            direct_result_action1, Derived
        >::type derived_type;
        typedef boost::mpl::true_ direct_execution;
        
        
        static base_action::action_type get_action_type()
        {
            return base_action::direct_action;
        }
    };
    
    template <
        typename Component, typename Result, typename T0,
        Result (Component::*F)(T0) const, typename Derived>
    struct make_action<Result (Component::*)(T0) const,
            F, Derived, boost::mpl::true_>
      : direct_result_action1<
            Result (Component::*)(T0) const, F, Derived>
    {
        typedef direct_result_action1<
            Result (Component::*)(T0) const, F, Derived
        > type;
    };
    
    
    template <
        typename Component, typename T0,
        void (Component::*F)(T0) const, typename Derived>
    class base_action1<
            void (Component::*)(T0) const, F, Derived>
      : public action<
            Component const, util::unused_type,
            hpx::util::tuple<typename util::decay<T0>::type>,
            Derived>
    {
    public:
        typedef util::unused_type result_type;
        typedef util::unused_type remote_result_type;
        typedef hpx::util::tuple<
            typename util::decay<T0>::type> arguments_type;
        typedef action<Component const, remote_result_type, arguments_type, Derived>
            base_type;
    protected:
        
        
        
        struct thread_function
        {
            typedef threads::thread_state_enum result_type;
            template <typename Arg0>
            BOOST_FORCEINLINE result_type operator()(
                naming::address::address_type lva,
                BOOST_FWD_REF(Arg0) arg0) const
            {
                try {
                    LTM_(debug) << "Executing component action("
                                << detail::get_action_name<Derived>()
                                << ") lva(" << reinterpret_cast<void const*>
                                    (get_lva<Component const>::call(lva)) << ")";
                    
                    
                    
                    
                    (get_lva<Component const>::call(lva)->*F)(
                        boost::move(arg0));
                }
                catch (hpx::thread_interrupted const&) {
                     
                }
                catch (hpx::exception const& e) {
                    LTM_(error)
                        << "Unhandled exception while executing component action("
                        << detail::get_action_name<Derived>()
                        << ") lva(" << reinterpret_cast<void const*>
                            (get_lva<Component const>::call(lva)) << "): " << e.what();
                    
                    hpx::report_error(boost::current_exception());
                }
                catch (...) {
                    LTM_(error)
                        << "Unhandled exception while executing component action("
                        << detail::get_action_name<Derived>()
                        << ") lva(" << reinterpret_cast<void const*>
                            (get_lva<Component const>::call(lva)) << ")";
                    
                    hpx::report_error(boost::current_exception());
                }
                
                
                
                util::force_error_on_lock();
                return threads::terminated;
            }
        };
    public:
        
        
        
        
        template <typename Arguments>
        static HPX_STD_FUNCTION<threads::thread_function_type>
        construct_thread_function(naming::address::address_type lva,
            BOOST_FWD_REF(Arguments) args)
        {
            
            
            return Derived::decorate_action(
                HPX_STD_BIND(typename Derived::thread_function(), lva,
                    util::get< 0>(boost::forward<Arguments>( args))), lva);
        }
        
        
        
        
        template <typename Arguments>
        static HPX_STD_FUNCTION<threads::thread_function_type>
        construct_thread_function(continuation_type& cont,
            naming::address::address_type lva, BOOST_FWD_REF(Arguments) args)
        {
            return Derived::decorate_action(
                base_type::construct_continuation_thread_object_function_void(
                    cont, F, get_lva<Component const>::call(lva),
                    boost::forward<Arguments>(args)), lva);
        }
        
        template <typename Arguments>
        BOOST_FORCEINLINE static util::unused_type
        execute_function(naming::address::address_type lva,
            BOOST_FWD_REF(Arguments) args)
        {
            LTM_(debug)
                << "base_action" << 1
                << "::execute_function name("
                << detail::get_action_name<Derived>()
                << ") lva(" << reinterpret_cast<void const*>(
                    get_lva<Component const>::call(lva)) << ")";
            (get_lva<Component const>::call(lva)->*F)(
                util::get< 0>(boost::forward<Arguments>( args)));
            return util::unused;
        }
    };
    
    template <
        typename Component, typename T0,
        void (Component::*F)(T0) const,
        typename Derived>
    struct action1<
            void (Component::*)(T0) const, F, Derived>
      : base_action1<
            void (Component::*)(T0) const, F,
            typename detail::action_type<
                action1<
                    void (Component::*)(T0) const, F, Derived>,
                Derived
            >::type>
    {
        typedef typename detail::action_type<
            action1, Derived
        >::type derived_type;
        typedef boost::mpl::false_ direct_execution;
    };
    
    template <typename Component, typename T0,
        void (Component::*F)(T0) const, typename Derived>
    struct make_action<void (Component::*)(T0) const,
            F, Derived, boost::mpl::false_>
      : action1<
            void (Component::*)(T0) const, F, Derived>
    {
        typedef action1<
            void (Component::*)(T0) const, F, Derived
        > type;
    };
    
    template <
        typename Component, typename T0,
        void (Component::*F)(T0) const,
        typename Derived>
    struct direct_action1<
            void (Component::*)(T0) const, F, Derived>
      : base_action1<
            void (Component::*)(T0) const, F,
            typename detail::action_type<
                direct_action1<
                    void (Component::*)(T0) const, F, Derived>,
                    Derived
            >::type>
    {
        typedef typename detail::action_type<
            direct_action1, Derived
        >::type derived_type;
        typedef boost::mpl::true_ direct_execution;
        
        
        static base_action::action_type get_action_type()
        {
            return base_action::direct_action;
        }
    };
    
    template <
        typename Component, typename T0,
        void (Component::*F)(T0) const, typename Derived>
    struct make_action<void (Component::*)(T0) const,
            F, Derived, boost::mpl::true_>
      : direct_action1<
            void (Component::*)(T0) const, F, Derived>
    {
        typedef direct_action1<
            void (Component::*)(T0) const, F, Derived
        > type;
    };
    
    
    template <
        typename Component,
        typename T0,
        void (Component::*F)(T0) const,
        typename Derived>
    struct result_action1<
            void (Component::*)(T0) const, F, Derived>
      : action1<
            void (Component::*)(T0) const, F, Derived>
    {};
}}
namespace hpx { namespace actions
{
    
    
    template <
        typename Component, typename Result,
        typename T0 , typename T1,
        Result (Component::*F)(T0 , T1) const, typename Derived>
    class base_result_action2<
            Result (Component::*)(T0 , T1) const, F, Derived>
      : public action<
            Component const, Result,
            hpx::util::tuple<typename util::decay<T0>::type , typename util::decay<T1>::type>,
            Derived>
    {
    public:
        typedef Result result_type;
        typedef typename detail::remote_action_result<Result>::type
            remote_result_type;
        typedef hpx::util::tuple<
            typename util::decay<T0>::type , typename util::decay<T1>::type> arguments_type;
        typedef action<Component const, remote_result_type, arguments_type, Derived>
            base_type;
    protected:
        
        
        
        struct thread_function
        {
            typedef threads::thread_state_enum result_type;
            template <typename Arg0 , typename Arg1>
            BOOST_FORCEINLINE result_type operator()(
                naming::address::address_type lva,
                BOOST_FWD_REF(Arg0) arg0 , BOOST_FWD_REF(Arg1) arg1) const
            {
                try {
                    LTM_(debug) << "Executing component action("
                                << detail::get_action_name<Derived>()
                                << ") lva(" << reinterpret_cast<void const*>
                                    (get_lva<Component const>::call(lva)) << ")";
                    
                    
                    
                    
                    (get_lva<Component const>::call(lva)->*F)(
                        boost::move(arg0) , boost::move(arg1));
                }
                catch (hpx::thread_interrupted const&) {
                     
                }
                catch (hpx::exception const& e) {
                    LTM_(error)
                        << "Unhandled exception while executing component action("
                        << detail::get_action_name<Derived>()
                        << ") lva(" << reinterpret_cast<void const*>
                            (get_lva<Component const>::call(lva)) << "): " << e.what();
                    
                    hpx::report_error(boost::current_exception());
                }
                catch (...) {
                    LTM_(error)
                        << "Unhandled exception while executing component action("
                        << detail::get_action_name<Derived>()
                        << ") lva(" << reinterpret_cast<void const*>
                            (get_lva<Component const>::call(lva)) << ")";
                    
                    hpx::report_error(boost::current_exception());
                }
                
                
                
                util::force_error_on_lock();
                return threads::terminated;
            }
        };
    public:
        typedef boost::mpl::false_ direct_execution;
        
        
        
        
        template <typename Arguments>
        static HPX_STD_FUNCTION<threads::thread_function_type>
        construct_thread_function(naming::address::address_type lva,
            BOOST_FWD_REF(Arguments) args)
        {
            return Derived::decorate_action(
                HPX_STD_BIND(typename Derived::thread_function(),
                    lva, util::get< 0>(boost::forward<Arguments>( args)) , util::get< 1>(boost::forward<Arguments>( args))), lva);
        }
        
        
        
        
        template <typename Arguments>
        static HPX_STD_FUNCTION<threads::thread_function_type>
        construct_thread_function(continuation_type& cont,
            naming::address::address_type lva, BOOST_FWD_REF(Arguments) args)
        {
            return Derived::decorate_action(
                base_type::construct_continuation_thread_object_function(
                    cont, F, get_lva<Component const>::call(lva),
                    boost::forward<Arguments>(args)), lva);
        }
        
        template <typename Arguments>
        BOOST_FORCEINLINE static Result
        execute_function(naming::address::address_type lva,
            BOOST_FWD_REF(Arguments) args)
        {
            LTM_(debug)
                << "base_result_action" << 2
                << "::execute_function name("
                << detail::get_action_name<Derived>()
                << ") lva(" << reinterpret_cast<void const*>(
                    get_lva<Component const>::call(lva)) << ")";
            return (get_lva<Component const>::call(lva)->*F)(
                util::get< 0>(boost::forward<Arguments>( args)) , util::get< 1>(boost::forward<Arguments>( args)));
        }
    };
    
    
    template <
        typename Component, typename Result,
        typename T0 , typename T1,
        Result (Component::*F)(T0 , T1) const,
        typename Derived>
    struct result_action2<
            Result (Component::*)(T0 , T1) const, F, Derived>
      : base_result_action2<
            Result (Component::*)(T0 , T1) const, F,
            typename detail::action_type<
                result_action2<
                    Result (Component::*)(T0 , T1) const, F, Derived>,
                Derived
            >::type>
    {
        typedef typename detail::action_type<
            result_action2, Derived
        >::type derived_type;
        typedef boost::mpl::false_ direct_execution;
    };
    
    template <
        typename Component, typename Result, typename T0 , typename T1,
        Result (Component::*F)(T0 , T1) const, typename Derived>
    struct make_action<Result (Component::*)(T0 , T1) const,
            F, Derived, boost::mpl::false_>
      : result_action2<
            Result (Component::*)(T0 , T1) const, F, Derived>
    {
        typedef result_action2<
            Result (Component::*)(T0 , T1) const, F, Derived
        > type;
    };
    
    
    template <
        typename Component, typename Result,
        typename T0 , typename T1,
        Result (Component::*F)(T0 , T1) const,
        typename Derived>
    struct direct_result_action2<
            Result (Component::*)(T0 , T1) const, F, Derived>
      : base_result_action2<
            Result (Component::*)(T0 , T1) const, F,
            typename detail::action_type<
                direct_result_action2<
                    Result (Component::*)(T0 , T1) const, F, Derived>,
                    Derived
            >::type>
    {
        typedef typename detail::action_type<
            direct_result_action2, Derived
        >::type derived_type;
        typedef boost::mpl::true_ direct_execution;
        
        
        static base_action::action_type get_action_type()
        {
            return base_action::direct_action;
        }
    };
    
    template <
        typename Component, typename Result, typename T0 , typename T1,
        Result (Component::*F)(T0 , T1) const, typename Derived>
    struct make_action<Result (Component::*)(T0 , T1) const,
            F, Derived, boost::mpl::true_>
      : direct_result_action2<
            Result (Component::*)(T0 , T1) const, F, Derived>
    {
        typedef direct_result_action2<
            Result (Component::*)(T0 , T1) const, F, Derived
        > type;
    };
    
    
    template <
        typename Component, typename T0 , typename T1,
        void (Component::*F)(T0 , T1) const, typename Derived>
    class base_action2<
            void (Component::*)(T0 , T1) const, F, Derived>
      : public action<
            Component const, util::unused_type,
            hpx::util::tuple<typename util::decay<T0>::type , typename util::decay<T1>::type>,
            Derived>
    {
    public:
        typedef util::unused_type result_type;
        typedef util::unused_type remote_result_type;
        typedef hpx::util::tuple<
            typename util::decay<T0>::type , typename util::decay<T1>::type> arguments_type;
        typedef action<Component const, remote_result_type, arguments_type, Derived>
            base_type;
    protected:
        
        
        
        struct thread_function
        {
            typedef threads::thread_state_enum result_type;
            template <typename Arg0 , typename Arg1>
            BOOST_FORCEINLINE result_type operator()(
                naming::address::address_type lva,
                BOOST_FWD_REF(Arg0) arg0 , BOOST_FWD_REF(Arg1) arg1) const
            {
                try {
                    LTM_(debug) << "Executing component action("
                                << detail::get_action_name<Derived>()
                                << ") lva(" << reinterpret_cast<void const*>
                                    (get_lva<Component const>::call(lva)) << ")";
                    
                    
                    
                    
                    (get_lva<Component const>::call(lva)->*F)(
                        boost::move(arg0) , boost::move(arg1));
                }
                catch (hpx::thread_interrupted const&) {
                     
                }
                catch (hpx::exception const& e) {
                    LTM_(error)
                        << "Unhandled exception while executing component action("
                        << detail::get_action_name<Derived>()
                        << ") lva(" << reinterpret_cast<void const*>
                            (get_lva<Component const>::call(lva)) << "): " << e.what();
                    
                    hpx::report_error(boost::current_exception());
                }
                catch (...) {
                    LTM_(error)
                        << "Unhandled exception while executing component action("
                        << detail::get_action_name<Derived>()
                        << ") lva(" << reinterpret_cast<void const*>
                            (get_lva<Component const>::call(lva)) << ")";
                    
                    hpx::report_error(boost::current_exception());
                }
                
                
                
                util::force_error_on_lock();
                return threads::terminated;
            }
        };
    public:
        
        
        
        
        template <typename Arguments>
        static HPX_STD_FUNCTION<threads::thread_function_type>
        construct_thread_function(naming::address::address_type lva,
            BOOST_FWD_REF(Arguments) args)
        {
            
            
            return Derived::decorate_action(
                HPX_STD_BIND(typename Derived::thread_function(), lva,
                    util::get< 0>(boost::forward<Arguments>( args)) , util::get< 1>(boost::forward<Arguments>( args))), lva);
        }
        
        
        
        
        template <typename Arguments>
        static HPX_STD_FUNCTION<threads::thread_function_type>
        construct_thread_function(continuation_type& cont,
            naming::address::address_type lva, BOOST_FWD_REF(Arguments) args)
        {
            return Derived::decorate_action(
                base_type::construct_continuation_thread_object_function_void(
                    cont, F, get_lva<Component const>::call(lva),
                    boost::forward<Arguments>(args)), lva);
        }
        
        template <typename Arguments>
        BOOST_FORCEINLINE static util::unused_type
        execute_function(naming::address::address_type lva,
            BOOST_FWD_REF(Arguments) args)
        {
            LTM_(debug)
                << "base_action" << 2
                << "::execute_function name("
                << detail::get_action_name<Derived>()
                << ") lva(" << reinterpret_cast<void const*>(
                    get_lva<Component const>::call(lva)) << ")";
            (get_lva<Component const>::call(lva)->*F)(
                util::get< 0>(boost::forward<Arguments>( args)) , util::get< 1>(boost::forward<Arguments>( args)));
            return util::unused;
        }
    };
    
    template <
        typename Component, typename T0 , typename T1,
        void (Component::*F)(T0 , T1) const,
        typename Derived>
    struct action2<
            void (Component::*)(T0 , T1) const, F, Derived>
      : base_action2<
            void (Component::*)(T0 , T1) const, F,
            typename detail::action_type<
                action2<
                    void (Component::*)(T0 , T1) const, F, Derived>,
                Derived
            >::type>
    {
        typedef typename detail::action_type<
            action2, Derived
        >::type derived_type;
        typedef boost::mpl::false_ direct_execution;
    };
    
    template <typename Component, typename T0 , typename T1,
        void (Component::*F)(T0 , T1) const, typename Derived>
    struct make_action<void (Component::*)(T0 , T1) const,
            F, Derived, boost::mpl::false_>
      : action2<
            void (Component::*)(T0 , T1) const, F, Derived>
    {
        typedef action2<
            void (Component::*)(T0 , T1) const, F, Derived
        > type;
    };
    
    template <
        typename Component, typename T0 , typename T1,
        void (Component::*F)(T0 , T1) const,
        typename Derived>
    struct direct_action2<
            void (Component::*)(T0 , T1) const, F, Derived>
      : base_action2<
            void (Component::*)(T0 , T1) const, F,
            typename detail::action_type<
                direct_action2<
                    void (Component::*)(T0 , T1) const, F, Derived>,
                    Derived
            >::type>
    {
        typedef typename detail::action_type<
            direct_action2, Derived
        >::type derived_type;
        typedef boost::mpl::true_ direct_execution;
        
        
        static base_action::action_type get_action_type()
        {
            return base_action::direct_action;
        }
    };
    
    template <
        typename Component, typename T0 , typename T1,
        void (Component::*F)(T0 , T1) const, typename Derived>
    struct make_action<void (Component::*)(T0 , T1) const,
            F, Derived, boost::mpl::true_>
      : direct_action2<
            void (Component::*)(T0 , T1) const, F, Derived>
    {
        typedef direct_action2<
            void (Component::*)(T0 , T1) const, F, Derived
        > type;
    };
    
    
    template <
        typename Component,
        typename T0 , typename T1,
        void (Component::*F)(T0 , T1) const,
        typename Derived>
    struct result_action2<
            void (Component::*)(T0 , T1) const, F, Derived>
      : action2<
            void (Component::*)(T0 , T1) const, F, Derived>
    {};
}}
namespace hpx { namespace actions
{
    
    
    template <
        typename Component, typename Result,
        typename T0 , typename T1 , typename T2,
        Result (Component::*F)(T0 , T1 , T2) const, typename Derived>
    class base_result_action3<
            Result (Component::*)(T0 , T1 , T2) const, F, Derived>
      : public action<
            Component const, Result,
            hpx::util::tuple<typename util::decay<T0>::type , typename util::decay<T1>::type , typename util::decay<T2>::type>,
            Derived>
    {
    public:
        typedef Result result_type;
        typedef typename detail::remote_action_result<Result>::type
            remote_result_type;
        typedef hpx::util::tuple<
            typename util::decay<T0>::type , typename util::decay<T1>::type , typename util::decay<T2>::type> arguments_type;
        typedef action<Component const, remote_result_type, arguments_type, Derived>
            base_type;
    protected:
        
        
        
        struct thread_function
        {
            typedef threads::thread_state_enum result_type;
            template <typename Arg0 , typename Arg1 , typename Arg2>
            BOOST_FORCEINLINE result_type operator()(
                naming::address::address_type lva,
                BOOST_FWD_REF(Arg0) arg0 , BOOST_FWD_REF(Arg1) arg1 , BOOST_FWD_REF(Arg2) arg2) const
            {
                try {
                    LTM_(debug) << "Executing component action("
                                << detail::get_action_name<Derived>()
                                << ") lva(" << reinterpret_cast<void const*>
                                    (get_lva<Component const>::call(lva)) << ")";
                    
                    
                    
                    
                    (get_lva<Component const>::call(lva)->*F)(
                        boost::move(arg0) , boost::move(arg1) , boost::move(arg2));
                }
                catch (hpx::thread_interrupted const&) {
                     
                }
                catch (hpx::exception const& e) {
                    LTM_(error)
                        << "Unhandled exception while executing component action("
                        << detail::get_action_name<Derived>()
                        << ") lva(" << reinterpret_cast<void const*>
                            (get_lva<Component const>::call(lva)) << "): " << e.what();
                    
                    hpx::report_error(boost::current_exception());
                }
                catch (...) {
                    LTM_(error)
                        << "Unhandled exception while executing component action("
                        << detail::get_action_name<Derived>()
                        << ") lva(" << reinterpret_cast<void const*>
                            (get_lva<Component const>::call(lva)) << ")";
                    
                    hpx::report_error(boost::current_exception());
                }
                
                
                
                util::force_error_on_lock();
                return threads::terminated;
            }
        };
    public:
        typedef boost::mpl::false_ direct_execution;
        
        
        
        
        template <typename Arguments>
        static HPX_STD_FUNCTION<threads::thread_function_type>
        construct_thread_function(naming::address::address_type lva,
            BOOST_FWD_REF(Arguments) args)
        {
            return Derived::decorate_action(
                HPX_STD_BIND(typename Derived::thread_function(),
                    lva, util::get< 0>(boost::forward<Arguments>( args)) , util::get< 1>(boost::forward<Arguments>( args)) , util::get< 2>(boost::forward<Arguments>( args))), lva);
        }
        
        
        
        
        template <typename Arguments>
        static HPX_STD_FUNCTION<threads::thread_function_type>
        construct_thread_function(continuation_type& cont,
            naming::address::address_type lva, BOOST_FWD_REF(Arguments) args)
        {
            return Derived::decorate_action(
                base_type::construct_continuation_thread_object_function(
                    cont, F, get_lva<Component const>::call(lva),
                    boost::forward<Arguments>(args)), lva);
        }
        
        template <typename Arguments>
        BOOST_FORCEINLINE static Result
        execute_function(naming::address::address_type lva,
            BOOST_FWD_REF(Arguments) args)
        {
            LTM_(debug)
                << "base_result_action" << 3
                << "::execute_function name("
                << detail::get_action_name<Derived>()
                << ") lva(" << reinterpret_cast<void const*>(
                    get_lva<Component const>::call(lva)) << ")";
            return (get_lva<Component const>::call(lva)->*F)(
                util::get< 0>(boost::forward<Arguments>( args)) , util::get< 1>(boost::forward<Arguments>( args)) , util::get< 2>(boost::forward<Arguments>( args)));
        }
    };
    
    
    template <
        typename Component, typename Result,
        typename T0 , typename T1 , typename T2,
        Result (Component::*F)(T0 , T1 , T2) const,
        typename Derived>
    struct result_action3<
            Result (Component::*)(T0 , T1 , T2) const, F, Derived>
      : base_result_action3<
            Result (Component::*)(T0 , T1 , T2) const, F,
            typename detail::action_type<
                result_action3<
                    Result (Component::*)(T0 , T1 , T2) const, F, Derived>,
                Derived
            >::type>
    {
        typedef typename detail::action_type<
            result_action3, Derived
        >::type derived_type;
        typedef boost::mpl::false_ direct_execution;
    };
    
    template <
        typename Component, typename Result, typename T0 , typename T1 , typename T2,
        Result (Component::*F)(T0 , T1 , T2) const, typename Derived>
    struct make_action<Result (Component::*)(T0 , T1 , T2) const,
            F, Derived, boost::mpl::false_>
      : result_action3<
            Result (Component::*)(T0 , T1 , T2) const, F, Derived>
    {
        typedef result_action3<
            Result (Component::*)(T0 , T1 , T2) const, F, Derived
        > type;
    };
    
    
    template <
        typename Component, typename Result,
        typename T0 , typename T1 , typename T2,
        Result (Component::*F)(T0 , T1 , T2) const,
        typename Derived>
    struct direct_result_action3<
            Result (Component::*)(T0 , T1 , T2) const, F, Derived>
      : base_result_action3<
            Result (Component::*)(T0 , T1 , T2) const, F,
            typename detail::action_type<
                direct_result_action3<
                    Result (Component::*)(T0 , T1 , T2) const, F, Derived>,
                    Derived
            >::type>
    {
        typedef typename detail::action_type<
            direct_result_action3, Derived
        >::type derived_type;
        typedef boost::mpl::true_ direct_execution;
        
        
        static base_action::action_type get_action_type()
        {
            return base_action::direct_action;
        }
    };
    
    template <
        typename Component, typename Result, typename T0 , typename T1 , typename T2,
        Result (Component::*F)(T0 , T1 , T2) const, typename Derived>
    struct make_action<Result (Component::*)(T0 , T1 , T2) const,
            F, Derived, boost::mpl::true_>
      : direct_result_action3<
            Result (Component::*)(T0 , T1 , T2) const, F, Derived>
    {
        typedef direct_result_action3<
            Result (Component::*)(T0 , T1 , T2) const, F, Derived
        > type;
    };
    
    
    template <
        typename Component, typename T0 , typename T1 , typename T2,
        void (Component::*F)(T0 , T1 , T2) const, typename Derived>
    class base_action3<
            void (Component::*)(T0 , T1 , T2) const, F, Derived>
      : public action<
            Component const, util::unused_type,
            hpx::util::tuple<typename util::decay<T0>::type , typename util::decay<T1>::type , typename util::decay<T2>::type>,
            Derived>
    {
    public:
        typedef util::unused_type result_type;
        typedef util::unused_type remote_result_type;
        typedef hpx::util::tuple<
            typename util::decay<T0>::type , typename util::decay<T1>::type , typename util::decay<T2>::type> arguments_type;
        typedef action<Component const, remote_result_type, arguments_type, Derived>
            base_type;
    protected:
        
        
        
        struct thread_function
        {
            typedef threads::thread_state_enum result_type;
            template <typename Arg0 , typename Arg1 , typename Arg2>
            BOOST_FORCEINLINE result_type operator()(
                naming::address::address_type lva,
                BOOST_FWD_REF(Arg0) arg0 , BOOST_FWD_REF(Arg1) arg1 , BOOST_FWD_REF(Arg2) arg2) const
            {
                try {
                    LTM_(debug) << "Executing component action("
                                << detail::get_action_name<Derived>()
                                << ") lva(" << reinterpret_cast<void const*>
                                    (get_lva<Component const>::call(lva)) << ")";
                    
                    
                    
                    
                    (get_lva<Component const>::call(lva)->*F)(
                        boost::move(arg0) , boost::move(arg1) , boost::move(arg2));
                }
                catch (hpx::thread_interrupted const&) {
                     
                }
                catch (hpx::exception const& e) {
                    LTM_(error)
                        << "Unhandled exception while executing component action("
                        << detail::get_action_name<Derived>()
                        << ") lva(" << reinterpret_cast<void const*>
                            (get_lva<Component const>::call(lva)) << "): " << e.what();
                    
                    hpx::report_error(boost::current_exception());
                }
                catch (...) {
                    LTM_(error)
                        << "Unhandled exception while executing component action("
                        << detail::get_action_name<Derived>()
                        << ") lva(" << reinterpret_cast<void const*>
                            (get_lva<Component const>::call(lva)) << ")";
                    
                    hpx::report_error(boost::current_exception());
                }
                
                
                
                util::force_error_on_lock();
                return threads::terminated;
            }
        };
    public:
        
        
        
        
        template <typename Arguments>
        static HPX_STD_FUNCTION<threads::thread_function_type>
        construct_thread_function(naming::address::address_type lva,
            BOOST_FWD_REF(Arguments) args)
        {
            
            
            return Derived::decorate_action(
                HPX_STD_BIND(typename Derived::thread_function(), lva,
                    util::get< 0>(boost::forward<Arguments>( args)) , util::get< 1>(boost::forward<Arguments>( args)) , util::get< 2>(boost::forward<Arguments>( args))), lva);
        }
        
        
        
        
        template <typename Arguments>
        static HPX_STD_FUNCTION<threads::thread_function_type>
        construct_thread_function(continuation_type& cont,
            naming::address::address_type lva, BOOST_FWD_REF(Arguments) args)
        {
            return Derived::decorate_action(
                base_type::construct_continuation_thread_object_function_void(
                    cont, F, get_lva<Component const>::call(lva),
                    boost::forward<Arguments>(args)), lva);
        }
        
        template <typename Arguments>
        BOOST_FORCEINLINE static util::unused_type
        execute_function(naming::address::address_type lva,
            BOOST_FWD_REF(Arguments) args)
        {
            LTM_(debug)
                << "base_action" << 3
                << "::execute_function name("
                << detail::get_action_name<Derived>()
                << ") lva(" << reinterpret_cast<void const*>(
                    get_lva<Component const>::call(lva)) << ")";
            (get_lva<Component const>::call(lva)->*F)(
                util::get< 0>(boost::forward<Arguments>( args)) , util::get< 1>(boost::forward<Arguments>( args)) , util::get< 2>(boost::forward<Arguments>( args)));
            return util::unused;
        }
    };
    
    template <
        typename Component, typename T0 , typename T1 , typename T2,
        void (Component::*F)(T0 , T1 , T2) const,
        typename Derived>
    struct action3<
            void (Component::*)(T0 , T1 , T2) const, F, Derived>
      : base_action3<
            void (Component::*)(T0 , T1 , T2) const, F,
            typename detail::action_type<
                action3<
                    void (Component::*)(T0 , T1 , T2) const, F, Derived>,
                Derived
            >::type>
    {
        typedef typename detail::action_type<
            action3, Derived
        >::type derived_type;
        typedef boost::mpl::false_ direct_execution;
    };
    
    template <typename Component, typename T0 , typename T1 , typename T2,
        void (Component::*F)(T0 , T1 , T2) const, typename Derived>
    struct make_action<void (Component::*)(T0 , T1 , T2) const,
            F, Derived, boost::mpl::false_>
      : action3<
            void (Component::*)(T0 , T1 , T2) const, F, Derived>
    {
        typedef action3<
            void (Component::*)(T0 , T1 , T2) const, F, Derived
        > type;
    };
    
    template <
        typename Component, typename T0 , typename T1 , typename T2,
        void (Component::*F)(T0 , T1 , T2) const,
        typename Derived>
    struct direct_action3<
            void (Component::*)(T0 , T1 , T2) const, F, Derived>
      : base_action3<
            void (Component::*)(T0 , T1 , T2) const, F,
            typename detail::action_type<
                direct_action3<
                    void (Component::*)(T0 , T1 , T2) const, F, Derived>,
                    Derived
            >::type>
    {
        typedef typename detail::action_type<
            direct_action3, Derived
        >::type derived_type;
        typedef boost::mpl::true_ direct_execution;
        
        
        static base_action::action_type get_action_type()
        {
            return base_action::direct_action;
        }
    };
    
    template <
        typename Component, typename T0 , typename T1 , typename T2,
        void (Component::*F)(T0 , T1 , T2) const, typename Derived>
    struct make_action<void (Component::*)(T0 , T1 , T2) const,
            F, Derived, boost::mpl::true_>
      : direct_action3<
            void (Component::*)(T0 , T1 , T2) const, F, Derived>
    {
        typedef direct_action3<
            void (Component::*)(T0 , T1 , T2) const, F, Derived
        > type;
    };
    
    
    template <
        typename Component,
        typename T0 , typename T1 , typename T2,
        void (Component::*F)(T0 , T1 , T2) const,
        typename Derived>
    struct result_action3<
            void (Component::*)(T0 , T1 , T2) const, F, Derived>
      : action3<
            void (Component::*)(T0 , T1 , T2) const, F, Derived>
    {};
}}
namespace hpx { namespace actions
{
    
    
    template <
        typename Component, typename Result,
        typename T0 , typename T1 , typename T2 , typename T3,
        Result (Component::*F)(T0 , T1 , T2 , T3) const, typename Derived>
    class base_result_action4<
            Result (Component::*)(T0 , T1 , T2 , T3) const, F, Derived>
      : public action<
            Component const, Result,
            hpx::util::tuple<typename util::decay<T0>::type , typename util::decay<T1>::type , typename util::decay<T2>::type , typename util::decay<T3>::type>,
            Derived>
    {
    public:
        typedef Result result_type;
        typedef typename detail::remote_action_result<Result>::type
            remote_result_type;
        typedef hpx::util::tuple<
            typename util::decay<T0>::type , typename util::decay<T1>::type , typename util::decay<T2>::type , typename util::decay<T3>::type> arguments_type;
        typedef action<Component const, remote_result_type, arguments_type, Derived>
            base_type;
    protected:
        
        
        
        struct thread_function
        {
            typedef threads::thread_state_enum result_type;
            template <typename Arg0 , typename Arg1 , typename Arg2 , typename Arg3>
            BOOST_FORCEINLINE result_type operator()(
                naming::address::address_type lva,
                BOOST_FWD_REF(Arg0) arg0 , BOOST_FWD_REF(Arg1) arg1 , BOOST_FWD_REF(Arg2) arg2 , BOOST_FWD_REF(Arg3) arg3) const
            {
                try {
                    LTM_(debug) << "Executing component action("
                                << detail::get_action_name<Derived>()
                                << ") lva(" << reinterpret_cast<void const*>
                                    (get_lva<Component const>::call(lva)) << ")";
                    
                    
                    
                    
                    (get_lva<Component const>::call(lva)->*F)(
                        boost::move(arg0) , boost::move(arg1) , boost::move(arg2) , boost::move(arg3));
                }
                catch (hpx::thread_interrupted const&) {
                     
                }
                catch (hpx::exception const& e) {
                    LTM_(error)
                        << "Unhandled exception while executing component action("
                        << detail::get_action_name<Derived>()
                        << ") lva(" << reinterpret_cast<void const*>
                            (get_lva<Component const>::call(lva)) << "): " << e.what();
                    
                    hpx::report_error(boost::current_exception());
                }
                catch (...) {
                    LTM_(error)
                        << "Unhandled exception while executing component action("
                        << detail::get_action_name<Derived>()
                        << ") lva(" << reinterpret_cast<void const*>
                            (get_lva<Component const>::call(lva)) << ")";
                    
                    hpx::report_error(boost::current_exception());
                }
                
                
                
                util::force_error_on_lock();
                return threads::terminated;
            }
        };
    public:
        typedef boost::mpl::false_ direct_execution;
        
        
        
        
        template <typename Arguments>
        static HPX_STD_FUNCTION<threads::thread_function_type>
        construct_thread_function(naming::address::address_type lva,
            BOOST_FWD_REF(Arguments) args)
        {
            return Derived::decorate_action(
                HPX_STD_BIND(typename Derived::thread_function(),
                    lva, util::get< 0>(boost::forward<Arguments>( args)) , util::get< 1>(boost::forward<Arguments>( args)) , util::get< 2>(boost::forward<Arguments>( args)) , util::get< 3>(boost::forward<Arguments>( args))), lva);
        }
        
        
        
        
        template <typename Arguments>
        static HPX_STD_FUNCTION<threads::thread_function_type>
        construct_thread_function(continuation_type& cont,
            naming::address::address_type lva, BOOST_FWD_REF(Arguments) args)
        {
            return Derived::decorate_action(
                base_type::construct_continuation_thread_object_function(
                    cont, F, get_lva<Component const>::call(lva),
                    boost::forward<Arguments>(args)), lva);
        }
        
        template <typename Arguments>
        BOOST_FORCEINLINE static Result
        execute_function(naming::address::address_type lva,
            BOOST_FWD_REF(Arguments) args)
        {
            LTM_(debug)
                << "base_result_action" << 4
                << "::execute_function name("
                << detail::get_action_name<Derived>()
                << ") lva(" << reinterpret_cast<void const*>(
                    get_lva<Component const>::call(lva)) << ")";
            return (get_lva<Component const>::call(lva)->*F)(
                util::get< 0>(boost::forward<Arguments>( args)) , util::get< 1>(boost::forward<Arguments>( args)) , util::get< 2>(boost::forward<Arguments>( args)) , util::get< 3>(boost::forward<Arguments>( args)));
        }
    };
    
    
    template <
        typename Component, typename Result,
        typename T0 , typename T1 , typename T2 , typename T3,
        Result (Component::*F)(T0 , T1 , T2 , T3) const,
        typename Derived>
    struct result_action4<
            Result (Component::*)(T0 , T1 , T2 , T3) const, F, Derived>
      : base_result_action4<
            Result (Component::*)(T0 , T1 , T2 , T3) const, F,
            typename detail::action_type<
                result_action4<
                    Result (Component::*)(T0 , T1 , T2 , T3) const, F, Derived>,
                Derived
            >::type>
    {
        typedef typename detail::action_type<
            result_action4, Derived
        >::type derived_type;
        typedef boost::mpl::false_ direct_execution;
    };
    
    template <
        typename Component, typename Result, typename T0 , typename T1 , typename T2 , typename T3,
        Result (Component::*F)(T0 , T1 , T2 , T3) const, typename Derived>
    struct make_action<Result (Component::*)(T0 , T1 , T2 , T3) const,
            F, Derived, boost::mpl::false_>
      : result_action4<
            Result (Component::*)(T0 , T1 , T2 , T3) const, F, Derived>
    {
        typedef result_action4<
            Result (Component::*)(T0 , T1 , T2 , T3) const, F, Derived
        > type;
    };
    
    
    template <
        typename Component, typename Result,
        typename T0 , typename T1 , typename T2 , typename T3,
        Result (Component::*F)(T0 , T1 , T2 , T3) const,
        typename Derived>
    struct direct_result_action4<
            Result (Component::*)(T0 , T1 , T2 , T3) const, F, Derived>
      : base_result_action4<
            Result (Component::*)(T0 , T1 , T2 , T3) const, F,
            typename detail::action_type<
                direct_result_action4<
                    Result (Component::*)(T0 , T1 , T2 , T3) const, F, Derived>,
                    Derived
            >::type>
    {
        typedef typename detail::action_type<
            direct_result_action4, Derived
        >::type derived_type;
        typedef boost::mpl::true_ direct_execution;
        
        
        static base_action::action_type get_action_type()
        {
            return base_action::direct_action;
        }
    };
    
    template <
        typename Component, typename Result, typename T0 , typename T1 , typename T2 , typename T3,
        Result (Component::*F)(T0 , T1 , T2 , T3) const, typename Derived>
    struct make_action<Result (Component::*)(T0 , T1 , T2 , T3) const,
            F, Derived, boost::mpl::true_>
      : direct_result_action4<
            Result (Component::*)(T0 , T1 , T2 , T3) const, F, Derived>
    {
        typedef direct_result_action4<
            Result (Component::*)(T0 , T1 , T2 , T3) const, F, Derived
        > type;
    };
    
    
    template <
        typename Component, typename T0 , typename T1 , typename T2 , typename T3,
        void (Component::*F)(T0 , T1 , T2 , T3) const, typename Derived>
    class base_action4<
            void (Component::*)(T0 , T1 , T2 , T3) const, F, Derived>
      : public action<
            Component const, util::unused_type,
            hpx::util::tuple<typename util::decay<T0>::type , typename util::decay<T1>::type , typename util::decay<T2>::type , typename util::decay<T3>::type>,
            Derived>
    {
    public:
        typedef util::unused_type result_type;
        typedef util::unused_type remote_result_type;
        typedef hpx::util::tuple<
            typename util::decay<T0>::type , typename util::decay<T1>::type , typename util::decay<T2>::type , typename util::decay<T3>::type> arguments_type;
        typedef action<Component const, remote_result_type, arguments_type, Derived>
            base_type;
    protected:
        
        
        
        struct thread_function
        {
            typedef threads::thread_state_enum result_type;
            template <typename Arg0 , typename Arg1 , typename Arg2 , typename Arg3>
            BOOST_FORCEINLINE result_type operator()(
                naming::address::address_type lva,
                BOOST_FWD_REF(Arg0) arg0 , BOOST_FWD_REF(Arg1) arg1 , BOOST_FWD_REF(Arg2) arg2 , BOOST_FWD_REF(Arg3) arg3) const
            {
                try {
                    LTM_(debug) << "Executing component action("
                                << detail::get_action_name<Derived>()
                                << ") lva(" << reinterpret_cast<void const*>
                                    (get_lva<Component const>::call(lva)) << ")";
                    
                    
                    
                    
                    (get_lva<Component const>::call(lva)->*F)(
                        boost::move(arg0) , boost::move(arg1) , boost::move(arg2) , boost::move(arg3));
                }
                catch (hpx::thread_interrupted const&) {
                     
                }
                catch (hpx::exception const& e) {
                    LTM_(error)
                        << "Unhandled exception while executing component action("
                        << detail::get_action_name<Derived>()
                        << ") lva(" << reinterpret_cast<void const*>
                            (get_lva<Component const>::call(lva)) << "): " << e.what();
                    
                    hpx::report_error(boost::current_exception());
                }
                catch (...) {
                    LTM_(error)
                        << "Unhandled exception while executing component action("
                        << detail::get_action_name<Derived>()
                        << ") lva(" << reinterpret_cast<void const*>
                            (get_lva<Component const>::call(lva)) << ")";
                    
                    hpx::report_error(boost::current_exception());
                }
                
                
                
                util::force_error_on_lock();
                return threads::terminated;
            }
        };
    public:
        
        
        
        
        template <typename Arguments>
        static HPX_STD_FUNCTION<threads::thread_function_type>
        construct_thread_function(naming::address::address_type lva,
            BOOST_FWD_REF(Arguments) args)
        {
            
            
            return Derived::decorate_action(
                HPX_STD_BIND(typename Derived::thread_function(), lva,
                    util::get< 0>(boost::forward<Arguments>( args)) , util::get< 1>(boost::forward<Arguments>( args)) , util::get< 2>(boost::forward<Arguments>( args)) , util::get< 3>(boost::forward<Arguments>( args))), lva);
        }
        
        
        
        
        template <typename Arguments>
        static HPX_STD_FUNCTION<threads::thread_function_type>
        construct_thread_function(continuation_type& cont,
            naming::address::address_type lva, BOOST_FWD_REF(Arguments) args)
        {
            return Derived::decorate_action(
                base_type::construct_continuation_thread_object_function_void(
                    cont, F, get_lva<Component const>::call(lva),
                    boost::forward<Arguments>(args)), lva);
        }
        
        template <typename Arguments>
        BOOST_FORCEINLINE static util::unused_type
        execute_function(naming::address::address_type lva,
            BOOST_FWD_REF(Arguments) args)
        {
            LTM_(debug)
                << "base_action" << 4
                << "::execute_function name("
                << detail::get_action_name<Derived>()
                << ") lva(" << reinterpret_cast<void const*>(
                    get_lva<Component const>::call(lva)) << ")";
            (get_lva<Component const>::call(lva)->*F)(
                util::get< 0>(boost::forward<Arguments>( args)) , util::get< 1>(boost::forward<Arguments>( args)) , util::get< 2>(boost::forward<Arguments>( args)) , util::get< 3>(boost::forward<Arguments>( args)));
            return util::unused;
        }
    };
    
    template <
        typename Component, typename T0 , typename T1 , typename T2 , typename T3,
        void (Component::*F)(T0 , T1 , T2 , T3) const,
        typename Derived>
    struct action4<
            void (Component::*)(T0 , T1 , T2 , T3) const, F, Derived>
      : base_action4<
            void (Component::*)(T0 , T1 , T2 , T3) const, F,
            typename detail::action_type<
                action4<
                    void (Component::*)(T0 , T1 , T2 , T3) const, F, Derived>,
                Derived
            >::type>
    {
        typedef typename detail::action_type<
            action4, Derived
        >::type derived_type;
        typedef boost::mpl::false_ direct_execution;
    };
    
    template <typename Component, typename T0 , typename T1 , typename T2 , typename T3,
        void (Component::*F)(T0 , T1 , T2 , T3) const, typename Derived>
    struct make_action<void (Component::*)(T0 , T1 , T2 , T3) const,
            F, Derived, boost::mpl::false_>
      : action4<
            void (Component::*)(T0 , T1 , T2 , T3) const, F, Derived>
    {
        typedef action4<
            void (Component::*)(T0 , T1 , T2 , T3) const, F, Derived
        > type;
    };
    
    template <
        typename Component, typename T0 , typename T1 , typename T2 , typename T3,
        void (Component::*F)(T0 , T1 , T2 , T3) const,
        typename Derived>
    struct direct_action4<
            void (Component::*)(T0 , T1 , T2 , T3) const, F, Derived>
      : base_action4<
            void (Component::*)(T0 , T1 , T2 , T3) const, F,
            typename detail::action_type<
                direct_action4<
                    void (Component::*)(T0 , T1 , T2 , T3) const, F, Derived>,
                    Derived
            >::type>
    {
        typedef typename detail::action_type<
            direct_action4, Derived
        >::type derived_type;
        typedef boost::mpl::true_ direct_execution;
        
        
        static base_action::action_type get_action_type()
        {
            return base_action::direct_action;
        }
    };
    
    template <
        typename Component, typename T0 , typename T1 , typename T2 , typename T3,
        void (Component::*F)(T0 , T1 , T2 , T3) const, typename Derived>
    struct make_action<void (Component::*)(T0 , T1 , T2 , T3) const,
            F, Derived, boost::mpl::true_>
      : direct_action4<
            void (Component::*)(T0 , T1 , T2 , T3) const, F, Derived>
    {
        typedef direct_action4<
            void (Component::*)(T0 , T1 , T2 , T3) const, F, Derived
        > type;
    };
    
    
    template <
        typename Component,
        typename T0 , typename T1 , typename T2 , typename T3,
        void (Component::*F)(T0 , T1 , T2 , T3) const,
        typename Derived>
    struct result_action4<
            void (Component::*)(T0 , T1 , T2 , T3) const, F, Derived>
      : action4<
            void (Component::*)(T0 , T1 , T2 , T3) const, F, Derived>
    {};
}}
namespace hpx { namespace actions
{
    
    
    template <
        typename Component, typename Result,
        typename T0 , typename T1 , typename T2 , typename T3 , typename T4,
        Result (Component::*F)(T0 , T1 , T2 , T3 , T4) const, typename Derived>
    class base_result_action5<
            Result (Component::*)(T0 , T1 , T2 , T3 , T4) const, F, Derived>
      : public action<
            Component const, Result,
            hpx::util::tuple<typename util::decay<T0>::type , typename util::decay<T1>::type , typename util::decay<T2>::type , typename util::decay<T3>::type , typename util::decay<T4>::type>,
            Derived>
    {
    public:
        typedef Result result_type;
        typedef typename detail::remote_action_result<Result>::type
            remote_result_type;
        typedef hpx::util::tuple<
            typename util::decay<T0>::type , typename util::decay<T1>::type , typename util::decay<T2>::type , typename util::decay<T3>::type , typename util::decay<T4>::type> arguments_type;
        typedef action<Component const, remote_result_type, arguments_type, Derived>
            base_type;
    protected:
        
        
        
        struct thread_function
        {
            typedef threads::thread_state_enum result_type;
            template <typename Arg0 , typename Arg1 , typename Arg2 , typename Arg3 , typename Arg4>
            BOOST_FORCEINLINE result_type operator()(
                naming::address::address_type lva,
                BOOST_FWD_REF(Arg0) arg0 , BOOST_FWD_REF(Arg1) arg1 , BOOST_FWD_REF(Arg2) arg2 , BOOST_FWD_REF(Arg3) arg3 , BOOST_FWD_REF(Arg4) arg4) const
            {
                try {
                    LTM_(debug) << "Executing component action("
                                << detail::get_action_name<Derived>()
                                << ") lva(" << reinterpret_cast<void const*>
                                    (get_lva<Component const>::call(lva)) << ")";
                    
                    
                    
                    
                    (get_lva<Component const>::call(lva)->*F)(
                        boost::move(arg0) , boost::move(arg1) , boost::move(arg2) , boost::move(arg3) , boost::move(arg4));
                }
                catch (hpx::thread_interrupted const&) {
                     
                }
                catch (hpx::exception const& e) {
                    LTM_(error)
                        << "Unhandled exception while executing component action("
                        << detail::get_action_name<Derived>()
                        << ") lva(" << reinterpret_cast<void const*>
                            (get_lva<Component const>::call(lva)) << "): " << e.what();
                    
                    hpx::report_error(boost::current_exception());
                }
                catch (...) {
                    LTM_(error)
                        << "Unhandled exception while executing component action("
                        << detail::get_action_name<Derived>()
                        << ") lva(" << reinterpret_cast<void const*>
                            (get_lva<Component const>::call(lva)) << ")";
                    
                    hpx::report_error(boost::current_exception());
                }
                
                
                
                util::force_error_on_lock();
                return threads::terminated;
            }
        };
    public:
        typedef boost::mpl::false_ direct_execution;
        
        
        
        
        template <typename Arguments>
        static HPX_STD_FUNCTION<threads::thread_function_type>
        construct_thread_function(naming::address::address_type lva,
            BOOST_FWD_REF(Arguments) args)
        {
            return Derived::decorate_action(
                HPX_STD_BIND(typename Derived::thread_function(),
                    lva, util::get< 0>(boost::forward<Arguments>( args)) , util::get< 1>(boost::forward<Arguments>( args)) , util::get< 2>(boost::forward<Arguments>( args)) , util::get< 3>(boost::forward<Arguments>( args)) , util::get< 4>(boost::forward<Arguments>( args))), lva);
        }
        
        
        
        
        template <typename Arguments>
        static HPX_STD_FUNCTION<threads::thread_function_type>
        construct_thread_function(continuation_type& cont,
            naming::address::address_type lva, BOOST_FWD_REF(Arguments) args)
        {
            return Derived::decorate_action(
                base_type::construct_continuation_thread_object_function(
                    cont, F, get_lva<Component const>::call(lva),
                    boost::forward<Arguments>(args)), lva);
        }
        
        template <typename Arguments>
        BOOST_FORCEINLINE static Result
        execute_function(naming::address::address_type lva,
            BOOST_FWD_REF(Arguments) args)
        {
            LTM_(debug)
                << "base_result_action" << 5
                << "::execute_function name("
                << detail::get_action_name<Derived>()
                << ") lva(" << reinterpret_cast<void const*>(
                    get_lva<Component const>::call(lva)) << ")";
            return (get_lva<Component const>::call(lva)->*F)(
                util::get< 0>(boost::forward<Arguments>( args)) , util::get< 1>(boost::forward<Arguments>( args)) , util::get< 2>(boost::forward<Arguments>( args)) , util::get< 3>(boost::forward<Arguments>( args)) , util::get< 4>(boost::forward<Arguments>( args)));
        }
    };
    
    
    template <
        typename Component, typename Result,
        typename T0 , typename T1 , typename T2 , typename T3 , typename T4,
        Result (Component::*F)(T0 , T1 , T2 , T3 , T4) const,
        typename Derived>
    struct result_action5<
            Result (Component::*)(T0 , T1 , T2 , T3 , T4) const, F, Derived>
      : base_result_action5<
            Result (Component::*)(T0 , T1 , T2 , T3 , T4) const, F,
            typename detail::action_type<
                result_action5<
                    Result (Component::*)(T0 , T1 , T2 , T3 , T4) const, F, Derived>,
                Derived
            >::type>
    {
        typedef typename detail::action_type<
            result_action5, Derived
        >::type derived_type;
        typedef boost::mpl::false_ direct_execution;
    };
    
    template <
        typename Component, typename Result, typename T0 , typename T1 , typename T2 , typename T3 , typename T4,
        Result (Component::*F)(T0 , T1 , T2 , T3 , T4) const, typename Derived>
    struct make_action<Result (Component::*)(T0 , T1 , T2 , T3 , T4) const,
            F, Derived, boost::mpl::false_>
      : result_action5<
            Result (Component::*)(T0 , T1 , T2 , T3 , T4) const, F, Derived>
    {
        typedef result_action5<
            Result (Component::*)(T0 , T1 , T2 , T3 , T4) const, F, Derived
        > type;
    };
    
    
    template <
        typename Component, typename Result,
        typename T0 , typename T1 , typename T2 , typename T3 , typename T4,
        Result (Component::*F)(T0 , T1 , T2 , T3 , T4) const,
        typename Derived>
    struct direct_result_action5<
            Result (Component::*)(T0 , T1 , T2 , T3 , T4) const, F, Derived>
      : base_result_action5<
            Result (Component::*)(T0 , T1 , T2 , T3 , T4) const, F,
            typename detail::action_type<
                direct_result_action5<
                    Result (Component::*)(T0 , T1 , T2 , T3 , T4) const, F, Derived>,
                    Derived
            >::type>
    {
        typedef typename detail::action_type<
            direct_result_action5, Derived
        >::type derived_type;
        typedef boost::mpl::true_ direct_execution;
        
        
        static base_action::action_type get_action_type()
        {
            return base_action::direct_action;
        }
    };
    
    template <
        typename Component, typename Result, typename T0 , typename T1 , typename T2 , typename T3 , typename T4,
        Result (Component::*F)(T0 , T1 , T2 , T3 , T4) const, typename Derived>
    struct make_action<Result (Component::*)(T0 , T1 , T2 , T3 , T4) const,
            F, Derived, boost::mpl::true_>
      : direct_result_action5<
            Result (Component::*)(T0 , T1 , T2 , T3 , T4) const, F, Derived>
    {
        typedef direct_result_action5<
            Result (Component::*)(T0 , T1 , T2 , T3 , T4) const, F, Derived
        > type;
    };
    
    
    template <
        typename Component, typename T0 , typename T1 , typename T2 , typename T3 , typename T4,
        void (Component::*F)(T0 , T1 , T2 , T3 , T4) const, typename Derived>
    class base_action5<
            void (Component::*)(T0 , T1 , T2 , T3 , T4) const, F, Derived>
      : public action<
            Component const, util::unused_type,
            hpx::util::tuple<typename util::decay<T0>::type , typename util::decay<T1>::type , typename util::decay<T2>::type , typename util::decay<T3>::type , typename util::decay<T4>::type>,
            Derived>
    {
    public:
        typedef util::unused_type result_type;
        typedef util::unused_type remote_result_type;
        typedef hpx::util::tuple<
            typename util::decay<T0>::type , typename util::decay<T1>::type , typename util::decay<T2>::type , typename util::decay<T3>::type , typename util::decay<T4>::type> arguments_type;
        typedef action<Component const, remote_result_type, arguments_type, Derived>
            base_type;
    protected:
        
        
        
        struct thread_function
        {
            typedef threads::thread_state_enum result_type;
            template <typename Arg0 , typename Arg1 , typename Arg2 , typename Arg3 , typename Arg4>
            BOOST_FORCEINLINE result_type operator()(
                naming::address::address_type lva,
                BOOST_FWD_REF(Arg0) arg0 , BOOST_FWD_REF(Arg1) arg1 , BOOST_FWD_REF(Arg2) arg2 , BOOST_FWD_REF(Arg3) arg3 , BOOST_FWD_REF(Arg4) arg4) const
            {
                try {
                    LTM_(debug) << "Executing component action("
                                << detail::get_action_name<Derived>()
                                << ") lva(" << reinterpret_cast<void const*>
                                    (get_lva<Component const>::call(lva)) << ")";
                    
                    
                    
                    
                    (get_lva<Component const>::call(lva)->*F)(
                        boost::move(arg0) , boost::move(arg1) , boost::move(arg2) , boost::move(arg3) , boost::move(arg4));
                }
                catch (hpx::thread_interrupted const&) {
                     
                }
                catch (hpx::exception const& e) {
                    LTM_(error)
                        << "Unhandled exception while executing component action("
                        << detail::get_action_name<Derived>()
                        << ") lva(" << reinterpret_cast<void const*>
                            (get_lva<Component const>::call(lva)) << "): " << e.what();
                    
                    hpx::report_error(boost::current_exception());
                }
                catch (...) {
                    LTM_(error)
                        << "Unhandled exception while executing component action("
                        << detail::get_action_name<Derived>()
                        << ") lva(" << reinterpret_cast<void const*>
                            (get_lva<Component const>::call(lva)) << ")";
                    
                    hpx::report_error(boost::current_exception());
                }
                
                
                
                util::force_error_on_lock();
                return threads::terminated;
            }
        };
    public:
        
        
        
        
        template <typename Arguments>
        static HPX_STD_FUNCTION<threads::thread_function_type>
        construct_thread_function(naming::address::address_type lva,
            BOOST_FWD_REF(Arguments) args)
        {
            
            
            return Derived::decorate_action(
                HPX_STD_BIND(typename Derived::thread_function(), lva,
                    util::get< 0>(boost::forward<Arguments>( args)) , util::get< 1>(boost::forward<Arguments>( args)) , util::get< 2>(boost::forward<Arguments>( args)) , util::get< 3>(boost::forward<Arguments>( args)) , util::get< 4>(boost::forward<Arguments>( args))), lva);
        }
        
        
        
        
        template <typename Arguments>
        static HPX_STD_FUNCTION<threads::thread_function_type>
        construct_thread_function(continuation_type& cont,
            naming::address::address_type lva, BOOST_FWD_REF(Arguments) args)
        {
            return Derived::decorate_action(
                base_type::construct_continuation_thread_object_function_void(
                    cont, F, get_lva<Component const>::call(lva),
                    boost::forward<Arguments>(args)), lva);
        }
        
        template <typename Arguments>
        BOOST_FORCEINLINE static util::unused_type
        execute_function(naming::address::address_type lva,
            BOOST_FWD_REF(Arguments) args)
        {
            LTM_(debug)
                << "base_action" << 5
                << "::execute_function name("
                << detail::get_action_name<Derived>()
                << ") lva(" << reinterpret_cast<void const*>(
                    get_lva<Component const>::call(lva)) << ")";
            (get_lva<Component const>::call(lva)->*F)(
                util::get< 0>(boost::forward<Arguments>( args)) , util::get< 1>(boost::forward<Arguments>( args)) , util::get< 2>(boost::forward<Arguments>( args)) , util::get< 3>(boost::forward<Arguments>( args)) , util::get< 4>(boost::forward<Arguments>( args)));
            return util::unused;
        }
    };
    
    template <
        typename Component, typename T0 , typename T1 , typename T2 , typename T3 , typename T4,
        void (Component::*F)(T0 , T1 , T2 , T3 , T4) const,
        typename Derived>
    struct action5<
            void (Component::*)(T0 , T1 , T2 , T3 , T4) const, F, Derived>
      : base_action5<
            void (Component::*)(T0 , T1 , T2 , T3 , T4) const, F,
            typename detail::action_type<
                action5<
                    void (Component::*)(T0 , T1 , T2 , T3 , T4) const, F, Derived>,
                Derived
            >::type>
    {
        typedef typename detail::action_type<
            action5, Derived
        >::type derived_type;
        typedef boost::mpl::false_ direct_execution;
    };
    
    template <typename Component, typename T0 , typename T1 , typename T2 , typename T3 , typename T4,
        void (Component::*F)(T0 , T1 , T2 , T3 , T4) const, typename Derived>
    struct make_action<void (Component::*)(T0 , T1 , T2 , T3 , T4) const,
            F, Derived, boost::mpl::false_>
      : action5<
            void (Component::*)(T0 , T1 , T2 , T3 , T4) const, F, Derived>
    {
        typedef action5<
            void (Component::*)(T0 , T1 , T2 , T3 , T4) const, F, Derived
        > type;
    };
    
    template <
        typename Component, typename T0 , typename T1 , typename T2 , typename T3 , typename T4,
        void (Component::*F)(T0 , T1 , T2 , T3 , T4) const,
        typename Derived>
    struct direct_action5<
            void (Component::*)(T0 , T1 , T2 , T3 , T4) const, F, Derived>
      : base_action5<
            void (Component::*)(T0 , T1 , T2 , T3 , T4) const, F,
            typename detail::action_type<
                direct_action5<
                    void (Component::*)(T0 , T1 , T2 , T3 , T4) const, F, Derived>,
                    Derived
            >::type>
    {
        typedef typename detail::action_type<
            direct_action5, Derived
        >::type derived_type;
        typedef boost::mpl::true_ direct_execution;
        
        
        static base_action::action_type get_action_type()
        {
            return base_action::direct_action;
        }
    };
    
    template <
        typename Component, typename T0 , typename T1 , typename T2 , typename T3 , typename T4,
        void (Component::*F)(T0 , T1 , T2 , T3 , T4) const, typename Derived>
    struct make_action<void (Component::*)(T0 , T1 , T2 , T3 , T4) const,
            F, Derived, boost::mpl::true_>
      : direct_action5<
            void (Component::*)(T0 , T1 , T2 , T3 , T4) const, F, Derived>
    {
        typedef direct_action5<
            void (Component::*)(T0 , T1 , T2 , T3 , T4) const, F, Derived
        > type;
    };
    
    
    template <
        typename Component,
        typename T0 , typename T1 , typename T2 , typename T3 , typename T4,
        void (Component::*F)(T0 , T1 , T2 , T3 , T4) const,
        typename Derived>
    struct result_action5<
            void (Component::*)(T0 , T1 , T2 , T3 , T4) const, F, Derived>
      : action5<
            void (Component::*)(T0 , T1 , T2 , T3 , T4) const, F, Derived>
    {};
}}
namespace hpx { namespace actions
{
    
    
    template <
        typename Component, typename Result,
        typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5,
        Result (Component::*F)(T0 , T1 , T2 , T3 , T4 , T5) const, typename Derived>
    class base_result_action6<
            Result (Component::*)(T0 , T1 , T2 , T3 , T4 , T5) const, F, Derived>
      : public action<
            Component const, Result,
            hpx::util::tuple<typename util::decay<T0>::type , typename util::decay<T1>::type , typename util::decay<T2>::type , typename util::decay<T3>::type , typename util::decay<T4>::type , typename util::decay<T5>::type>,
            Derived>
    {
    public:
        typedef Result result_type;
        typedef typename detail::remote_action_result<Result>::type
            remote_result_type;
        typedef hpx::util::tuple<
            typename util::decay<T0>::type , typename util::decay<T1>::type , typename util::decay<T2>::type , typename util::decay<T3>::type , typename util::decay<T4>::type , typename util::decay<T5>::type> arguments_type;
        typedef action<Component const, remote_result_type, arguments_type, Derived>
            base_type;
    protected:
        
        
        
        struct thread_function
        {
            typedef threads::thread_state_enum result_type;
            template <typename Arg0 , typename Arg1 , typename Arg2 , typename Arg3 , typename Arg4 , typename Arg5>
            BOOST_FORCEINLINE result_type operator()(
                naming::address::address_type lva,
                BOOST_FWD_REF(Arg0) arg0 , BOOST_FWD_REF(Arg1) arg1 , BOOST_FWD_REF(Arg2) arg2 , BOOST_FWD_REF(Arg3) arg3 , BOOST_FWD_REF(Arg4) arg4 , BOOST_FWD_REF(Arg5) arg5) const
            {
                try {
                    LTM_(debug) << "Executing component action("
                                << detail::get_action_name<Derived>()
                                << ") lva(" << reinterpret_cast<void const*>
                                    (get_lva<Component const>::call(lva)) << ")";
                    
                    
                    
                    
                    (get_lva<Component const>::call(lva)->*F)(
                        boost::move(arg0) , boost::move(arg1) , boost::move(arg2) , boost::move(arg3) , boost::move(arg4) , boost::move(arg5));
                }
                catch (hpx::thread_interrupted const&) {
                     
                }
                catch (hpx::exception const& e) {
                    LTM_(error)
                        << "Unhandled exception while executing component action("
                        << detail::get_action_name<Derived>()
                        << ") lva(" << reinterpret_cast<void const*>
                            (get_lva<Component const>::call(lva)) << "): " << e.what();
                    
                    hpx::report_error(boost::current_exception());
                }
                catch (...) {
                    LTM_(error)
                        << "Unhandled exception while executing component action("
                        << detail::get_action_name<Derived>()
                        << ") lva(" << reinterpret_cast<void const*>
                            (get_lva<Component const>::call(lva)) << ")";
                    
                    hpx::report_error(boost::current_exception());
                }
                
                
                
                util::force_error_on_lock();
                return threads::terminated;
            }
        };
    public:
        typedef boost::mpl::false_ direct_execution;
        
        
        
        
        template <typename Arguments>
        static HPX_STD_FUNCTION<threads::thread_function_type>
        construct_thread_function(naming::address::address_type lva,
            BOOST_FWD_REF(Arguments) args)
        {
            return Derived::decorate_action(
                HPX_STD_BIND(typename Derived::thread_function(),
                    lva, util::get< 0>(boost::forward<Arguments>( args)) , util::get< 1>(boost::forward<Arguments>( args)) , util::get< 2>(boost::forward<Arguments>( args)) , util::get< 3>(boost::forward<Arguments>( args)) , util::get< 4>(boost::forward<Arguments>( args)) , util::get< 5>(boost::forward<Arguments>( args))), lva);
        }
        
        
        
        
        template <typename Arguments>
        static HPX_STD_FUNCTION<threads::thread_function_type>
        construct_thread_function(continuation_type& cont,
            naming::address::address_type lva, BOOST_FWD_REF(Arguments) args)
        {
            return Derived::decorate_action(
                base_type::construct_continuation_thread_object_function(
                    cont, F, get_lva<Component const>::call(lva),
                    boost::forward<Arguments>(args)), lva);
        }
        
        template <typename Arguments>
        BOOST_FORCEINLINE static Result
        execute_function(naming::address::address_type lva,
            BOOST_FWD_REF(Arguments) args)
        {
            LTM_(debug)
                << "base_result_action" << 6
                << "::execute_function name("
                << detail::get_action_name<Derived>()
                << ") lva(" << reinterpret_cast<void const*>(
                    get_lva<Component const>::call(lva)) << ")";
            return (get_lva<Component const>::call(lva)->*F)(
                util::get< 0>(boost::forward<Arguments>( args)) , util::get< 1>(boost::forward<Arguments>( args)) , util::get< 2>(boost::forward<Arguments>( args)) , util::get< 3>(boost::forward<Arguments>( args)) , util::get< 4>(boost::forward<Arguments>( args)) , util::get< 5>(boost::forward<Arguments>( args)));
        }
    };
    
    
    template <
        typename Component, typename Result,
        typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5,
        Result (Component::*F)(T0 , T1 , T2 , T3 , T4 , T5) const,
        typename Derived>
    struct result_action6<
            Result (Component::*)(T0 , T1 , T2 , T3 , T4 , T5) const, F, Derived>
      : base_result_action6<
            Result (Component::*)(T0 , T1 , T2 , T3 , T4 , T5) const, F,
            typename detail::action_type<
                result_action6<
                    Result (Component::*)(T0 , T1 , T2 , T3 , T4 , T5) const, F, Derived>,
                Derived
            >::type>
    {
        typedef typename detail::action_type<
            result_action6, Derived
        >::type derived_type;
        typedef boost::mpl::false_ direct_execution;
    };
    
    template <
        typename Component, typename Result, typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5,
        Result (Component::*F)(T0 , T1 , T2 , T3 , T4 , T5) const, typename Derived>
    struct make_action<Result (Component::*)(T0 , T1 , T2 , T3 , T4 , T5) const,
            F, Derived, boost::mpl::false_>
      : result_action6<
            Result (Component::*)(T0 , T1 , T2 , T3 , T4 , T5) const, F, Derived>
    {
        typedef result_action6<
            Result (Component::*)(T0 , T1 , T2 , T3 , T4 , T5) const, F, Derived
        > type;
    };
    
    
    template <
        typename Component, typename Result,
        typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5,
        Result (Component::*F)(T0 , T1 , T2 , T3 , T4 , T5) const,
        typename Derived>
    struct direct_result_action6<
            Result (Component::*)(T0 , T1 , T2 , T3 , T4 , T5) const, F, Derived>
      : base_result_action6<
            Result (Component::*)(T0 , T1 , T2 , T3 , T4 , T5) const, F,
            typename detail::action_type<
                direct_result_action6<
                    Result (Component::*)(T0 , T1 , T2 , T3 , T4 , T5) const, F, Derived>,
                    Derived
            >::type>
    {
        typedef typename detail::action_type<
            direct_result_action6, Derived
        >::type derived_type;
        typedef boost::mpl::true_ direct_execution;
        
        
        static base_action::action_type get_action_type()
        {
            return base_action::direct_action;
        }
    };
    
    template <
        typename Component, typename Result, typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5,
        Result (Component::*F)(T0 , T1 , T2 , T3 , T4 , T5) const, typename Derived>
    struct make_action<Result (Component::*)(T0 , T1 , T2 , T3 , T4 , T5) const,
            F, Derived, boost::mpl::true_>
      : direct_result_action6<
            Result (Component::*)(T0 , T1 , T2 , T3 , T4 , T5) const, F, Derived>
    {
        typedef direct_result_action6<
            Result (Component::*)(T0 , T1 , T2 , T3 , T4 , T5) const, F, Derived
        > type;
    };
    
    
    template <
        typename Component, typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5,
        void (Component::*F)(T0 , T1 , T2 , T3 , T4 , T5) const, typename Derived>
    class base_action6<
            void (Component::*)(T0 , T1 , T2 , T3 , T4 , T5) const, F, Derived>
      : public action<
            Component const, util::unused_type,
            hpx::util::tuple<typename util::decay<T0>::type , typename util::decay<T1>::type , typename util::decay<T2>::type , typename util::decay<T3>::type , typename util::decay<T4>::type , typename util::decay<T5>::type>,
            Derived>
    {
    public:
        typedef util::unused_type result_type;
        typedef util::unused_type remote_result_type;
        typedef hpx::util::tuple<
            typename util::decay<T0>::type , typename util::decay<T1>::type , typename util::decay<T2>::type , typename util::decay<T3>::type , typename util::decay<T4>::type , typename util::decay<T5>::type> arguments_type;
        typedef action<Component const, remote_result_type, arguments_type, Derived>
            base_type;
    protected:
        
        
        
        struct thread_function
        {
            typedef threads::thread_state_enum result_type;
            template <typename Arg0 , typename Arg1 , typename Arg2 , typename Arg3 , typename Arg4 , typename Arg5>
            BOOST_FORCEINLINE result_type operator()(
                naming::address::address_type lva,
                BOOST_FWD_REF(Arg0) arg0 , BOOST_FWD_REF(Arg1) arg1 , BOOST_FWD_REF(Arg2) arg2 , BOOST_FWD_REF(Arg3) arg3 , BOOST_FWD_REF(Arg4) arg4 , BOOST_FWD_REF(Arg5) arg5) const
            {
                try {
                    LTM_(debug) << "Executing component action("
                                << detail::get_action_name<Derived>()
                                << ") lva(" << reinterpret_cast<void const*>
                                    (get_lva<Component const>::call(lva)) << ")";
                    
                    
                    
                    
                    (get_lva<Component const>::call(lva)->*F)(
                        boost::move(arg0) , boost::move(arg1) , boost::move(arg2) , boost::move(arg3) , boost::move(arg4) , boost::move(arg5));
                }
                catch (hpx::thread_interrupted const&) {
                     
                }
                catch (hpx::exception const& e) {
                    LTM_(error)
                        << "Unhandled exception while executing component action("
                        << detail::get_action_name<Derived>()
                        << ") lva(" << reinterpret_cast<void const*>
                            (get_lva<Component const>::call(lva)) << "): " << e.what();
                    
                    hpx::report_error(boost::current_exception());
                }
                catch (...) {
                    LTM_(error)
                        << "Unhandled exception while executing component action("
                        << detail::get_action_name<Derived>()
                        << ") lva(" << reinterpret_cast<void const*>
                            (get_lva<Component const>::call(lva)) << ")";
                    
                    hpx::report_error(boost::current_exception());
                }
                
                
                
                util::force_error_on_lock();
                return threads::terminated;
            }
        };
    public:
        
        
        
        
        template <typename Arguments>
        static HPX_STD_FUNCTION<threads::thread_function_type>
        construct_thread_function(naming::address::address_type lva,
            BOOST_FWD_REF(Arguments) args)
        {
            
            
            return Derived::decorate_action(
                HPX_STD_BIND(typename Derived::thread_function(), lva,
                    util::get< 0>(boost::forward<Arguments>( args)) , util::get< 1>(boost::forward<Arguments>( args)) , util::get< 2>(boost::forward<Arguments>( args)) , util::get< 3>(boost::forward<Arguments>( args)) , util::get< 4>(boost::forward<Arguments>( args)) , util::get< 5>(boost::forward<Arguments>( args))), lva);
        }
        
        
        
        
        template <typename Arguments>
        static HPX_STD_FUNCTION<threads::thread_function_type>
        construct_thread_function(continuation_type& cont,
            naming::address::address_type lva, BOOST_FWD_REF(Arguments) args)
        {
            return Derived::decorate_action(
                base_type::construct_continuation_thread_object_function_void(
                    cont, F, get_lva<Component const>::call(lva),
                    boost::forward<Arguments>(args)), lva);
        }
        
        template <typename Arguments>
        BOOST_FORCEINLINE static util::unused_type
        execute_function(naming::address::address_type lva,
            BOOST_FWD_REF(Arguments) args)
        {
            LTM_(debug)
                << "base_action" << 6
                << "::execute_function name("
                << detail::get_action_name<Derived>()
                << ") lva(" << reinterpret_cast<void const*>(
                    get_lva<Component const>::call(lva)) << ")";
            (get_lva<Component const>::call(lva)->*F)(
                util::get< 0>(boost::forward<Arguments>( args)) , util::get< 1>(boost::forward<Arguments>( args)) , util::get< 2>(boost::forward<Arguments>( args)) , util::get< 3>(boost::forward<Arguments>( args)) , util::get< 4>(boost::forward<Arguments>( args)) , util::get< 5>(boost::forward<Arguments>( args)));
            return util::unused;
        }
    };
    
    template <
        typename Component, typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5,
        void (Component::*F)(T0 , T1 , T2 , T3 , T4 , T5) const,
        typename Derived>
    struct action6<
            void (Component::*)(T0 , T1 , T2 , T3 , T4 , T5) const, F, Derived>
      : base_action6<
            void (Component::*)(T0 , T1 , T2 , T3 , T4 , T5) const, F,
            typename detail::action_type<
                action6<
                    void (Component::*)(T0 , T1 , T2 , T3 , T4 , T5) const, F, Derived>,
                Derived
            >::type>
    {
        typedef typename detail::action_type<
            action6, Derived
        >::type derived_type;
        typedef boost::mpl::false_ direct_execution;
    };
    
    template <typename Component, typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5,
        void (Component::*F)(T0 , T1 , T2 , T3 , T4 , T5) const, typename Derived>
    struct make_action<void (Component::*)(T0 , T1 , T2 , T3 , T4 , T5) const,
            F, Derived, boost::mpl::false_>
      : action6<
            void (Component::*)(T0 , T1 , T2 , T3 , T4 , T5) const, F, Derived>
    {
        typedef action6<
            void (Component::*)(T0 , T1 , T2 , T3 , T4 , T5) const, F, Derived
        > type;
    };
    
    template <
        typename Component, typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5,
        void (Component::*F)(T0 , T1 , T2 , T3 , T4 , T5) const,
        typename Derived>
    struct direct_action6<
            void (Component::*)(T0 , T1 , T2 , T3 , T4 , T5) const, F, Derived>
      : base_action6<
            void (Component::*)(T0 , T1 , T2 , T3 , T4 , T5) const, F,
            typename detail::action_type<
                direct_action6<
                    void (Component::*)(T0 , T1 , T2 , T3 , T4 , T5) const, F, Derived>,
                    Derived
            >::type>
    {
        typedef typename detail::action_type<
            direct_action6, Derived
        >::type derived_type;
        typedef boost::mpl::true_ direct_execution;
        
        
        static base_action::action_type get_action_type()
        {
            return base_action::direct_action;
        }
    };
    
    template <
        typename Component, typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5,
        void (Component::*F)(T0 , T1 , T2 , T3 , T4 , T5) const, typename Derived>
    struct make_action<void (Component::*)(T0 , T1 , T2 , T3 , T4 , T5) const,
            F, Derived, boost::mpl::true_>
      : direct_action6<
            void (Component::*)(T0 , T1 , T2 , T3 , T4 , T5) const, F, Derived>
    {
        typedef direct_action6<
            void (Component::*)(T0 , T1 , T2 , T3 , T4 , T5) const, F, Derived
        > type;
    };
    
    
    template <
        typename Component,
        typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5,
        void (Component::*F)(T0 , T1 , T2 , T3 , T4 , T5) const,
        typename Derived>
    struct result_action6<
            void (Component::*)(T0 , T1 , T2 , T3 , T4 , T5) const, F, Derived>
      : action6<
            void (Component::*)(T0 , T1 , T2 , T3 , T4 , T5) const, F, Derived>
    {};
}}
namespace hpx { namespace actions
{
    
    
    template <
        typename Component, typename Result,
        typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6,
        Result (Component::*F)(T0 , T1 , T2 , T3 , T4 , T5 , T6) const, typename Derived>
    class base_result_action7<
            Result (Component::*)(T0 , T1 , T2 , T3 , T4 , T5 , T6) const, F, Derived>
      : public action<
            Component const, Result,
            hpx::util::tuple<typename util::decay<T0>::type , typename util::decay<T1>::type , typename util::decay<T2>::type , typename util::decay<T3>::type , typename util::decay<T4>::type , typename util::decay<T5>::type , typename util::decay<T6>::type>,
            Derived>
    {
    public:
        typedef Result result_type;
        typedef typename detail::remote_action_result<Result>::type
            remote_result_type;
        typedef hpx::util::tuple<
            typename util::decay<T0>::type , typename util::decay<T1>::type , typename util::decay<T2>::type , typename util::decay<T3>::type , typename util::decay<T4>::type , typename util::decay<T5>::type , typename util::decay<T6>::type> arguments_type;
        typedef action<Component const, remote_result_type, arguments_type, Derived>
            base_type;
    protected:
        
        
        
        struct thread_function
        {
            typedef threads::thread_state_enum result_type;
            template <typename Arg0 , typename Arg1 , typename Arg2 , typename Arg3 , typename Arg4 , typename Arg5 , typename Arg6>
            BOOST_FORCEINLINE result_type operator()(
                naming::address::address_type lva,
                BOOST_FWD_REF(Arg0) arg0 , BOOST_FWD_REF(Arg1) arg1 , BOOST_FWD_REF(Arg2) arg2 , BOOST_FWD_REF(Arg3) arg3 , BOOST_FWD_REF(Arg4) arg4 , BOOST_FWD_REF(Arg5) arg5 , BOOST_FWD_REF(Arg6) arg6) const
            {
                try {
                    LTM_(debug) << "Executing component action("
                                << detail::get_action_name<Derived>()
                                << ") lva(" << reinterpret_cast<void const*>
                                    (get_lva<Component const>::call(lva)) << ")";
                    
                    
                    
                    
                    (get_lva<Component const>::call(lva)->*F)(
                        boost::move(arg0) , boost::move(arg1) , boost::move(arg2) , boost::move(arg3) , boost::move(arg4) , boost::move(arg5) , boost::move(arg6));
                }
                catch (hpx::thread_interrupted const&) {
                     
                }
                catch (hpx::exception const& e) {
                    LTM_(error)
                        << "Unhandled exception while executing component action("
                        << detail::get_action_name<Derived>()
                        << ") lva(" << reinterpret_cast<void const*>
                            (get_lva<Component const>::call(lva)) << "): " << e.what();
                    
                    hpx::report_error(boost::current_exception());
                }
                catch (...) {
                    LTM_(error)
                        << "Unhandled exception while executing component action("
                        << detail::get_action_name<Derived>()
                        << ") lva(" << reinterpret_cast<void const*>
                            (get_lva<Component const>::call(lva)) << ")";
                    
                    hpx::report_error(boost::current_exception());
                }
                
                
                
                util::force_error_on_lock();
                return threads::terminated;
            }
        };
    public:
        typedef boost::mpl::false_ direct_execution;
        
        
        
        
        template <typename Arguments>
        static HPX_STD_FUNCTION<threads::thread_function_type>
        construct_thread_function(naming::address::address_type lva,
            BOOST_FWD_REF(Arguments) args)
        {
            return Derived::decorate_action(
                HPX_STD_BIND(typename Derived::thread_function(),
                    lva, util::get< 0>(boost::forward<Arguments>( args)) , util::get< 1>(boost::forward<Arguments>( args)) , util::get< 2>(boost::forward<Arguments>( args)) , util::get< 3>(boost::forward<Arguments>( args)) , util::get< 4>(boost::forward<Arguments>( args)) , util::get< 5>(boost::forward<Arguments>( args)) , util::get< 6>(boost::forward<Arguments>( args))), lva);
        }
        
        
        
        
        template <typename Arguments>
        static HPX_STD_FUNCTION<threads::thread_function_type>
        construct_thread_function(continuation_type& cont,
            naming::address::address_type lva, BOOST_FWD_REF(Arguments) args)
        {
            return Derived::decorate_action(
                base_type::construct_continuation_thread_object_function(
                    cont, F, get_lva<Component const>::call(lva),
                    boost::forward<Arguments>(args)), lva);
        }
        
        template <typename Arguments>
        BOOST_FORCEINLINE static Result
        execute_function(naming::address::address_type lva,
            BOOST_FWD_REF(Arguments) args)
        {
            LTM_(debug)
                << "base_result_action" << 7
                << "::execute_function name("
                << detail::get_action_name<Derived>()
                << ") lva(" << reinterpret_cast<void const*>(
                    get_lva<Component const>::call(lva)) << ")";
            return (get_lva<Component const>::call(lva)->*F)(
                util::get< 0>(boost::forward<Arguments>( args)) , util::get< 1>(boost::forward<Arguments>( args)) , util::get< 2>(boost::forward<Arguments>( args)) , util::get< 3>(boost::forward<Arguments>( args)) , util::get< 4>(boost::forward<Arguments>( args)) , util::get< 5>(boost::forward<Arguments>( args)) , util::get< 6>(boost::forward<Arguments>( args)));
        }
    };
    
    
    template <
        typename Component, typename Result,
        typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6,
        Result (Component::*F)(T0 , T1 , T2 , T3 , T4 , T5 , T6) const,
        typename Derived>
    struct result_action7<
            Result (Component::*)(T0 , T1 , T2 , T3 , T4 , T5 , T6) const, F, Derived>
      : base_result_action7<
            Result (Component::*)(T0 , T1 , T2 , T3 , T4 , T5 , T6) const, F,
            typename detail::action_type<
                result_action7<
                    Result (Component::*)(T0 , T1 , T2 , T3 , T4 , T5 , T6) const, F, Derived>,
                Derived
            >::type>
    {
        typedef typename detail::action_type<
            result_action7, Derived
        >::type derived_type;
        typedef boost::mpl::false_ direct_execution;
    };
    
    template <
        typename Component, typename Result, typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6,
        Result (Component::*F)(T0 , T1 , T2 , T3 , T4 , T5 , T6) const, typename Derived>
    struct make_action<Result (Component::*)(T0 , T1 , T2 , T3 , T4 , T5 , T6) const,
            F, Derived, boost::mpl::false_>
      : result_action7<
            Result (Component::*)(T0 , T1 , T2 , T3 , T4 , T5 , T6) const, F, Derived>
    {
        typedef result_action7<
            Result (Component::*)(T0 , T1 , T2 , T3 , T4 , T5 , T6) const, F, Derived
        > type;
    };
    
    
    template <
        typename Component, typename Result,
        typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6,
        Result (Component::*F)(T0 , T1 , T2 , T3 , T4 , T5 , T6) const,
        typename Derived>
    struct direct_result_action7<
            Result (Component::*)(T0 , T1 , T2 , T3 , T4 , T5 , T6) const, F, Derived>
      : base_result_action7<
            Result (Component::*)(T0 , T1 , T2 , T3 , T4 , T5 , T6) const, F,
            typename detail::action_type<
                direct_result_action7<
                    Result (Component::*)(T0 , T1 , T2 , T3 , T4 , T5 , T6) const, F, Derived>,
                    Derived
            >::type>
    {
        typedef typename detail::action_type<
            direct_result_action7, Derived
        >::type derived_type;
        typedef boost::mpl::true_ direct_execution;
        
        
        static base_action::action_type get_action_type()
        {
            return base_action::direct_action;
        }
    };
    
    template <
        typename Component, typename Result, typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6,
        Result (Component::*F)(T0 , T1 , T2 , T3 , T4 , T5 , T6) const, typename Derived>
    struct make_action<Result (Component::*)(T0 , T1 , T2 , T3 , T4 , T5 , T6) const,
            F, Derived, boost::mpl::true_>
      : direct_result_action7<
            Result (Component::*)(T0 , T1 , T2 , T3 , T4 , T5 , T6) const, F, Derived>
    {
        typedef direct_result_action7<
            Result (Component::*)(T0 , T1 , T2 , T3 , T4 , T5 , T6) const, F, Derived
        > type;
    };
    
    
    template <
        typename Component, typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6,
        void (Component::*F)(T0 , T1 , T2 , T3 , T4 , T5 , T6) const, typename Derived>
    class base_action7<
            void (Component::*)(T0 , T1 , T2 , T3 , T4 , T5 , T6) const, F, Derived>
      : public action<
            Component const, util::unused_type,
            hpx::util::tuple<typename util::decay<T0>::type , typename util::decay<T1>::type , typename util::decay<T2>::type , typename util::decay<T3>::type , typename util::decay<T4>::type , typename util::decay<T5>::type , typename util::decay<T6>::type>,
            Derived>
    {
    public:
        typedef util::unused_type result_type;
        typedef util::unused_type remote_result_type;
        typedef hpx::util::tuple<
            typename util::decay<T0>::type , typename util::decay<T1>::type , typename util::decay<T2>::type , typename util::decay<T3>::type , typename util::decay<T4>::type , typename util::decay<T5>::type , typename util::decay<T6>::type> arguments_type;
        typedef action<Component const, remote_result_type, arguments_type, Derived>
            base_type;
    protected:
        
        
        
        struct thread_function
        {
            typedef threads::thread_state_enum result_type;
            template <typename Arg0 , typename Arg1 , typename Arg2 , typename Arg3 , typename Arg4 , typename Arg5 , typename Arg6>
            BOOST_FORCEINLINE result_type operator()(
                naming::address::address_type lva,
                BOOST_FWD_REF(Arg0) arg0 , BOOST_FWD_REF(Arg1) arg1 , BOOST_FWD_REF(Arg2) arg2 , BOOST_FWD_REF(Arg3) arg3 , BOOST_FWD_REF(Arg4) arg4 , BOOST_FWD_REF(Arg5) arg5 , BOOST_FWD_REF(Arg6) arg6) const
            {
                try {
                    LTM_(debug) << "Executing component action("
                                << detail::get_action_name<Derived>()
                                << ") lva(" << reinterpret_cast<void const*>
                                    (get_lva<Component const>::call(lva)) << ")";
                    
                    
                    
                    
                    (get_lva<Component const>::call(lva)->*F)(
                        boost::move(arg0) , boost::move(arg1) , boost::move(arg2) , boost::move(arg3) , boost::move(arg4) , boost::move(arg5) , boost::move(arg6));
                }
                catch (hpx::thread_interrupted const&) {
                     
                }
                catch (hpx::exception const& e) {
                    LTM_(error)
                        << "Unhandled exception while executing component action("
                        << detail::get_action_name<Derived>()
                        << ") lva(" << reinterpret_cast<void const*>
                            (get_lva<Component const>::call(lva)) << "): " << e.what();
                    
                    hpx::report_error(boost::current_exception());
                }
                catch (...) {
                    LTM_(error)
                        << "Unhandled exception while executing component action("
                        << detail::get_action_name<Derived>()
                        << ") lva(" << reinterpret_cast<void const*>
                            (get_lva<Component const>::call(lva)) << ")";
                    
                    hpx::report_error(boost::current_exception());
                }
                
                
                
                util::force_error_on_lock();
                return threads::terminated;
            }
        };
    public:
        
        
        
        
        template <typename Arguments>
        static HPX_STD_FUNCTION<threads::thread_function_type>
        construct_thread_function(naming::address::address_type lva,
            BOOST_FWD_REF(Arguments) args)
        {
            
            
            return Derived::decorate_action(
                HPX_STD_BIND(typename Derived::thread_function(), lva,
                    util::get< 0>(boost::forward<Arguments>( args)) , util::get< 1>(boost::forward<Arguments>( args)) , util::get< 2>(boost::forward<Arguments>( args)) , util::get< 3>(boost::forward<Arguments>( args)) , util::get< 4>(boost::forward<Arguments>( args)) , util::get< 5>(boost::forward<Arguments>( args)) , util::get< 6>(boost::forward<Arguments>( args))), lva);
        }
        
        
        
        
        template <typename Arguments>
        static HPX_STD_FUNCTION<threads::thread_function_type>
        construct_thread_function(continuation_type& cont,
            naming::address::address_type lva, BOOST_FWD_REF(Arguments) args)
        {
            return Derived::decorate_action(
                base_type::construct_continuation_thread_object_function_void(
                    cont, F, get_lva<Component const>::call(lva),
                    boost::forward<Arguments>(args)), lva);
        }
        
        template <typename Arguments>
        BOOST_FORCEINLINE static util::unused_type
        execute_function(naming::address::address_type lva,
            BOOST_FWD_REF(Arguments) args)
        {
            LTM_(debug)
                << "base_action" << 7
                << "::execute_function name("
                << detail::get_action_name<Derived>()
                << ") lva(" << reinterpret_cast<void const*>(
                    get_lva<Component const>::call(lva)) << ")";
            (get_lva<Component const>::call(lva)->*F)(
                util::get< 0>(boost::forward<Arguments>( args)) , util::get< 1>(boost::forward<Arguments>( args)) , util::get< 2>(boost::forward<Arguments>( args)) , util::get< 3>(boost::forward<Arguments>( args)) , util::get< 4>(boost::forward<Arguments>( args)) , util::get< 5>(boost::forward<Arguments>( args)) , util::get< 6>(boost::forward<Arguments>( args)));
            return util::unused;
        }
    };
    
    template <
        typename Component, typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6,
        void (Component::*F)(T0 , T1 , T2 , T3 , T4 , T5 , T6) const,
        typename Derived>
    struct action7<
            void (Component::*)(T0 , T1 , T2 , T3 , T4 , T5 , T6) const, F, Derived>
      : base_action7<
            void (Component::*)(T0 , T1 , T2 , T3 , T4 , T5 , T6) const, F,
            typename detail::action_type<
                action7<
                    void (Component::*)(T0 , T1 , T2 , T3 , T4 , T5 , T6) const, F, Derived>,
                Derived
            >::type>
    {
        typedef typename detail::action_type<
            action7, Derived
        >::type derived_type;
        typedef boost::mpl::false_ direct_execution;
    };
    
    template <typename Component, typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6,
        void (Component::*F)(T0 , T1 , T2 , T3 , T4 , T5 , T6) const, typename Derived>
    struct make_action<void (Component::*)(T0 , T1 , T2 , T3 , T4 , T5 , T6) const,
            F, Derived, boost::mpl::false_>
      : action7<
            void (Component::*)(T0 , T1 , T2 , T3 , T4 , T5 , T6) const, F, Derived>
    {
        typedef action7<
            void (Component::*)(T0 , T1 , T2 , T3 , T4 , T5 , T6) const, F, Derived
        > type;
    };
    
    template <
        typename Component, typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6,
        void (Component::*F)(T0 , T1 , T2 , T3 , T4 , T5 , T6) const,
        typename Derived>
    struct direct_action7<
            void (Component::*)(T0 , T1 , T2 , T3 , T4 , T5 , T6) const, F, Derived>
      : base_action7<
            void (Component::*)(T0 , T1 , T2 , T3 , T4 , T5 , T6) const, F,
            typename detail::action_type<
                direct_action7<
                    void (Component::*)(T0 , T1 , T2 , T3 , T4 , T5 , T6) const, F, Derived>,
                    Derived
            >::type>
    {
        typedef typename detail::action_type<
            direct_action7, Derived
        >::type derived_type;
        typedef boost::mpl::true_ direct_execution;
        
        
        static base_action::action_type get_action_type()
        {
            return base_action::direct_action;
        }
    };
    
    template <
        typename Component, typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6,
        void (Component::*F)(T0 , T1 , T2 , T3 , T4 , T5 , T6) const, typename Derived>
    struct make_action<void (Component::*)(T0 , T1 , T2 , T3 , T4 , T5 , T6) const,
            F, Derived, boost::mpl::true_>
      : direct_action7<
            void (Component::*)(T0 , T1 , T2 , T3 , T4 , T5 , T6) const, F, Derived>
    {
        typedef direct_action7<
            void (Component::*)(T0 , T1 , T2 , T3 , T4 , T5 , T6) const, F, Derived
        > type;
    };
    
    
    template <
        typename Component,
        typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6,
        void (Component::*F)(T0 , T1 , T2 , T3 , T4 , T5 , T6) const,
        typename Derived>
    struct result_action7<
            void (Component::*)(T0 , T1 , T2 , T3 , T4 , T5 , T6) const, F, Derived>
      : action7<
            void (Component::*)(T0 , T1 , T2 , T3 , T4 , T5 , T6) const, F, Derived>
    {};
}}
namespace hpx { namespace actions
{
    
    
    template <
        typename Component, typename Result,
        typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7,
        Result (Component::*F)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7) const, typename Derived>
    class base_result_action8<
            Result (Component::*)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7) const, F, Derived>
      : public action<
            Component const, Result,
            hpx::util::tuple<typename util::decay<T0>::type , typename util::decay<T1>::type , typename util::decay<T2>::type , typename util::decay<T3>::type , typename util::decay<T4>::type , typename util::decay<T5>::type , typename util::decay<T6>::type , typename util::decay<T7>::type>,
            Derived>
    {
    public:
        typedef Result result_type;
        typedef typename detail::remote_action_result<Result>::type
            remote_result_type;
        typedef hpx::util::tuple<
            typename util::decay<T0>::type , typename util::decay<T1>::type , typename util::decay<T2>::type , typename util::decay<T3>::type , typename util::decay<T4>::type , typename util::decay<T5>::type , typename util::decay<T6>::type , typename util::decay<T7>::type> arguments_type;
        typedef action<Component const, remote_result_type, arguments_type, Derived>
            base_type;
    protected:
        
        
        
        struct thread_function
        {
            typedef threads::thread_state_enum result_type;
            template <typename Arg0 , typename Arg1 , typename Arg2 , typename Arg3 , typename Arg4 , typename Arg5 , typename Arg6 , typename Arg7>
            BOOST_FORCEINLINE result_type operator()(
                naming::address::address_type lva,
                BOOST_FWD_REF(Arg0) arg0 , BOOST_FWD_REF(Arg1) arg1 , BOOST_FWD_REF(Arg2) arg2 , BOOST_FWD_REF(Arg3) arg3 , BOOST_FWD_REF(Arg4) arg4 , BOOST_FWD_REF(Arg5) arg5 , BOOST_FWD_REF(Arg6) arg6 , BOOST_FWD_REF(Arg7) arg7) const
            {
                try {
                    LTM_(debug) << "Executing component action("
                                << detail::get_action_name<Derived>()
                                << ") lva(" << reinterpret_cast<void const*>
                                    (get_lva<Component const>::call(lva)) << ")";
                    
                    
                    
                    
                    (get_lva<Component const>::call(lva)->*F)(
                        boost::move(arg0) , boost::move(arg1) , boost::move(arg2) , boost::move(arg3) , boost::move(arg4) , boost::move(arg5) , boost::move(arg6) , boost::move(arg7));
                }
                catch (hpx::thread_interrupted const&) {
                     
                }
                catch (hpx::exception const& e) {
                    LTM_(error)
                        << "Unhandled exception while executing component action("
                        << detail::get_action_name<Derived>()
                        << ") lva(" << reinterpret_cast<void const*>
                            (get_lva<Component const>::call(lva)) << "): " << e.what();
                    
                    hpx::report_error(boost::current_exception());
                }
                catch (...) {
                    LTM_(error)
                        << "Unhandled exception while executing component action("
                        << detail::get_action_name<Derived>()
                        << ") lva(" << reinterpret_cast<void const*>
                            (get_lva<Component const>::call(lva)) << ")";
                    
                    hpx::report_error(boost::current_exception());
                }
                
                
                
                util::force_error_on_lock();
                return threads::terminated;
            }
        };
    public:
        typedef boost::mpl::false_ direct_execution;
        
        
        
        
        template <typename Arguments>
        static HPX_STD_FUNCTION<threads::thread_function_type>
        construct_thread_function(naming::address::address_type lva,
            BOOST_FWD_REF(Arguments) args)
        {
            return Derived::decorate_action(
                HPX_STD_BIND(typename Derived::thread_function(),
                    lva, util::get< 0>(boost::forward<Arguments>( args)) , util::get< 1>(boost::forward<Arguments>( args)) , util::get< 2>(boost::forward<Arguments>( args)) , util::get< 3>(boost::forward<Arguments>( args)) , util::get< 4>(boost::forward<Arguments>( args)) , util::get< 5>(boost::forward<Arguments>( args)) , util::get< 6>(boost::forward<Arguments>( args)) , util::get< 7>(boost::forward<Arguments>( args))), lva);
        }
        
        
        
        
        template <typename Arguments>
        static HPX_STD_FUNCTION<threads::thread_function_type>
        construct_thread_function(continuation_type& cont,
            naming::address::address_type lva, BOOST_FWD_REF(Arguments) args)
        {
            return Derived::decorate_action(
                base_type::construct_continuation_thread_object_function(
                    cont, F, get_lva<Component const>::call(lva),
                    boost::forward<Arguments>(args)), lva);
        }
        
        template <typename Arguments>
        BOOST_FORCEINLINE static Result
        execute_function(naming::address::address_type lva,
            BOOST_FWD_REF(Arguments) args)
        {
            LTM_(debug)
                << "base_result_action" << 8
                << "::execute_function name("
                << detail::get_action_name<Derived>()
                << ") lva(" << reinterpret_cast<void const*>(
                    get_lva<Component const>::call(lva)) << ")";
            return (get_lva<Component const>::call(lva)->*F)(
                util::get< 0>(boost::forward<Arguments>( args)) , util::get< 1>(boost::forward<Arguments>( args)) , util::get< 2>(boost::forward<Arguments>( args)) , util::get< 3>(boost::forward<Arguments>( args)) , util::get< 4>(boost::forward<Arguments>( args)) , util::get< 5>(boost::forward<Arguments>( args)) , util::get< 6>(boost::forward<Arguments>( args)) , util::get< 7>(boost::forward<Arguments>( args)));
        }
    };
    
    
    template <
        typename Component, typename Result,
        typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7,
        Result (Component::*F)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7) const,
        typename Derived>
    struct result_action8<
            Result (Component::*)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7) const, F, Derived>
      : base_result_action8<
            Result (Component::*)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7) const, F,
            typename detail::action_type<
                result_action8<
                    Result (Component::*)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7) const, F, Derived>,
                Derived
            >::type>
    {
        typedef typename detail::action_type<
            result_action8, Derived
        >::type derived_type;
        typedef boost::mpl::false_ direct_execution;
    };
    
    template <
        typename Component, typename Result, typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7,
        Result (Component::*F)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7) const, typename Derived>
    struct make_action<Result (Component::*)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7) const,
            F, Derived, boost::mpl::false_>
      : result_action8<
            Result (Component::*)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7) const, F, Derived>
    {
        typedef result_action8<
            Result (Component::*)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7) const, F, Derived
        > type;
    };
    
    
    template <
        typename Component, typename Result,
        typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7,
        Result (Component::*F)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7) const,
        typename Derived>
    struct direct_result_action8<
            Result (Component::*)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7) const, F, Derived>
      : base_result_action8<
            Result (Component::*)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7) const, F,
            typename detail::action_type<
                direct_result_action8<
                    Result (Component::*)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7) const, F, Derived>,
                    Derived
            >::type>
    {
        typedef typename detail::action_type<
            direct_result_action8, Derived
        >::type derived_type;
        typedef boost::mpl::true_ direct_execution;
        
        
        static base_action::action_type get_action_type()
        {
            return base_action::direct_action;
        }
    };
    
    template <
        typename Component, typename Result, typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7,
        Result (Component::*F)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7) const, typename Derived>
    struct make_action<Result (Component::*)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7) const,
            F, Derived, boost::mpl::true_>
      : direct_result_action8<
            Result (Component::*)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7) const, F, Derived>
    {
        typedef direct_result_action8<
            Result (Component::*)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7) const, F, Derived
        > type;
    };
    
    
    template <
        typename Component, typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7,
        void (Component::*F)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7) const, typename Derived>
    class base_action8<
            void (Component::*)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7) const, F, Derived>
      : public action<
            Component const, util::unused_type,
            hpx::util::tuple<typename util::decay<T0>::type , typename util::decay<T1>::type , typename util::decay<T2>::type , typename util::decay<T3>::type , typename util::decay<T4>::type , typename util::decay<T5>::type , typename util::decay<T6>::type , typename util::decay<T7>::type>,
            Derived>
    {
    public:
        typedef util::unused_type result_type;
        typedef util::unused_type remote_result_type;
        typedef hpx::util::tuple<
            typename util::decay<T0>::type , typename util::decay<T1>::type , typename util::decay<T2>::type , typename util::decay<T3>::type , typename util::decay<T4>::type , typename util::decay<T5>::type , typename util::decay<T6>::type , typename util::decay<T7>::type> arguments_type;
        typedef action<Component const, remote_result_type, arguments_type, Derived>
            base_type;
    protected:
        
        
        
        struct thread_function
        {
            typedef threads::thread_state_enum result_type;
            template <typename Arg0 , typename Arg1 , typename Arg2 , typename Arg3 , typename Arg4 , typename Arg5 , typename Arg6 , typename Arg7>
            BOOST_FORCEINLINE result_type operator()(
                naming::address::address_type lva,
                BOOST_FWD_REF(Arg0) arg0 , BOOST_FWD_REF(Arg1) arg1 , BOOST_FWD_REF(Arg2) arg2 , BOOST_FWD_REF(Arg3) arg3 , BOOST_FWD_REF(Arg4) arg4 , BOOST_FWD_REF(Arg5) arg5 , BOOST_FWD_REF(Arg6) arg6 , BOOST_FWD_REF(Arg7) arg7) const
            {
                try {
                    LTM_(debug) << "Executing component action("
                                << detail::get_action_name<Derived>()
                                << ") lva(" << reinterpret_cast<void const*>
                                    (get_lva<Component const>::call(lva)) << ")";
                    
                    
                    
                    
                    (get_lva<Component const>::call(lva)->*F)(
                        boost::move(arg0) , boost::move(arg1) , boost::move(arg2) , boost::move(arg3) , boost::move(arg4) , boost::move(arg5) , boost::move(arg6) , boost::move(arg7));
                }
                catch (hpx::thread_interrupted const&) {
                     
                }
                catch (hpx::exception const& e) {
                    LTM_(error)
                        << "Unhandled exception while executing component action("
                        << detail::get_action_name<Derived>()
                        << ") lva(" << reinterpret_cast<void const*>
                            (get_lva<Component const>::call(lva)) << "): " << e.what();
                    
                    hpx::report_error(boost::current_exception());
                }
                catch (...) {
                    LTM_(error)
                        << "Unhandled exception while executing component action("
                        << detail::get_action_name<Derived>()
                        << ") lva(" << reinterpret_cast<void const*>
                            (get_lva<Component const>::call(lva)) << ")";
                    
                    hpx::report_error(boost::current_exception());
                }
                
                
                
                util::force_error_on_lock();
                return threads::terminated;
            }
        };
    public:
        
        
        
        
        template <typename Arguments>
        static HPX_STD_FUNCTION<threads::thread_function_type>
        construct_thread_function(naming::address::address_type lva,
            BOOST_FWD_REF(Arguments) args)
        {
            
            
            return Derived::decorate_action(
                HPX_STD_BIND(typename Derived::thread_function(), lva,
                    util::get< 0>(boost::forward<Arguments>( args)) , util::get< 1>(boost::forward<Arguments>( args)) , util::get< 2>(boost::forward<Arguments>( args)) , util::get< 3>(boost::forward<Arguments>( args)) , util::get< 4>(boost::forward<Arguments>( args)) , util::get< 5>(boost::forward<Arguments>( args)) , util::get< 6>(boost::forward<Arguments>( args)) , util::get< 7>(boost::forward<Arguments>( args))), lva);
        }
        
        
        
        
        template <typename Arguments>
        static HPX_STD_FUNCTION<threads::thread_function_type>
        construct_thread_function(continuation_type& cont,
            naming::address::address_type lva, BOOST_FWD_REF(Arguments) args)
        {
            return Derived::decorate_action(
                base_type::construct_continuation_thread_object_function_void(
                    cont, F, get_lva<Component const>::call(lva),
                    boost::forward<Arguments>(args)), lva);
        }
        
        template <typename Arguments>
        BOOST_FORCEINLINE static util::unused_type
        execute_function(naming::address::address_type lva,
            BOOST_FWD_REF(Arguments) args)
        {
            LTM_(debug)
                << "base_action" << 8
                << "::execute_function name("
                << detail::get_action_name<Derived>()
                << ") lva(" << reinterpret_cast<void const*>(
                    get_lva<Component const>::call(lva)) << ")";
            (get_lva<Component const>::call(lva)->*F)(
                util::get< 0>(boost::forward<Arguments>( args)) , util::get< 1>(boost::forward<Arguments>( args)) , util::get< 2>(boost::forward<Arguments>( args)) , util::get< 3>(boost::forward<Arguments>( args)) , util::get< 4>(boost::forward<Arguments>( args)) , util::get< 5>(boost::forward<Arguments>( args)) , util::get< 6>(boost::forward<Arguments>( args)) , util::get< 7>(boost::forward<Arguments>( args)));
            return util::unused;
        }
    };
    
    template <
        typename Component, typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7,
        void (Component::*F)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7) const,
        typename Derived>
    struct action8<
            void (Component::*)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7) const, F, Derived>
      : base_action8<
            void (Component::*)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7) const, F,
            typename detail::action_type<
                action8<
                    void (Component::*)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7) const, F, Derived>,
                Derived
            >::type>
    {
        typedef typename detail::action_type<
            action8, Derived
        >::type derived_type;
        typedef boost::mpl::false_ direct_execution;
    };
    
    template <typename Component, typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7,
        void (Component::*F)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7) const, typename Derived>
    struct make_action<void (Component::*)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7) const,
            F, Derived, boost::mpl::false_>
      : action8<
            void (Component::*)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7) const, F, Derived>
    {
        typedef action8<
            void (Component::*)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7) const, F, Derived
        > type;
    };
    
    template <
        typename Component, typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7,
        void (Component::*F)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7) const,
        typename Derived>
    struct direct_action8<
            void (Component::*)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7) const, F, Derived>
      : base_action8<
            void (Component::*)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7) const, F,
            typename detail::action_type<
                direct_action8<
                    void (Component::*)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7) const, F, Derived>,
                    Derived
            >::type>
    {
        typedef typename detail::action_type<
            direct_action8, Derived
        >::type derived_type;
        typedef boost::mpl::true_ direct_execution;
        
        
        static base_action::action_type get_action_type()
        {
            return base_action::direct_action;
        }
    };
    
    template <
        typename Component, typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7,
        void (Component::*F)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7) const, typename Derived>
    struct make_action<void (Component::*)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7) const,
            F, Derived, boost::mpl::true_>
      : direct_action8<
            void (Component::*)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7) const, F, Derived>
    {
        typedef direct_action8<
            void (Component::*)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7) const, F, Derived
        > type;
    };
    
    
    template <
        typename Component,
        typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7,
        void (Component::*F)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7) const,
        typename Derived>
    struct result_action8<
            void (Component::*)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7) const, F, Derived>
      : action8<
            void (Component::*)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7) const, F, Derived>
    {};
}}
namespace hpx { namespace actions
{
    
    
    template <
        typename Component, typename Result,
        typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8,
        Result (Component::*F)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8) const, typename Derived>
    class base_result_action9<
            Result (Component::*)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8) const, F, Derived>
      : public action<
            Component const, Result,
            hpx::util::tuple<typename util::decay<T0>::type , typename util::decay<T1>::type , typename util::decay<T2>::type , typename util::decay<T3>::type , typename util::decay<T4>::type , typename util::decay<T5>::type , typename util::decay<T6>::type , typename util::decay<T7>::type , typename util::decay<T8>::type>,
            Derived>
    {
    public:
        typedef Result result_type;
        typedef typename detail::remote_action_result<Result>::type
            remote_result_type;
        typedef hpx::util::tuple<
            typename util::decay<T0>::type , typename util::decay<T1>::type , typename util::decay<T2>::type , typename util::decay<T3>::type , typename util::decay<T4>::type , typename util::decay<T5>::type , typename util::decay<T6>::type , typename util::decay<T7>::type , typename util::decay<T8>::type> arguments_type;
        typedef action<Component const, remote_result_type, arguments_type, Derived>
            base_type;
    protected:
        
        
        
        struct thread_function
        {
            typedef threads::thread_state_enum result_type;
            template <typename Arg0 , typename Arg1 , typename Arg2 , typename Arg3 , typename Arg4 , typename Arg5 , typename Arg6 , typename Arg7 , typename Arg8>
            BOOST_FORCEINLINE result_type operator()(
                naming::address::address_type lva,
                BOOST_FWD_REF(Arg0) arg0 , BOOST_FWD_REF(Arg1) arg1 , BOOST_FWD_REF(Arg2) arg2 , BOOST_FWD_REF(Arg3) arg3 , BOOST_FWD_REF(Arg4) arg4 , BOOST_FWD_REF(Arg5) arg5 , BOOST_FWD_REF(Arg6) arg6 , BOOST_FWD_REF(Arg7) arg7 , BOOST_FWD_REF(Arg8) arg8) const
            {
                try {
                    LTM_(debug) << "Executing component action("
                                << detail::get_action_name<Derived>()
                                << ") lva(" << reinterpret_cast<void const*>
                                    (get_lva<Component const>::call(lva)) << ")";
                    
                    
                    
                    
                    (get_lva<Component const>::call(lva)->*F)(
                        boost::move(arg0) , boost::move(arg1) , boost::move(arg2) , boost::move(arg3) , boost::move(arg4) , boost::move(arg5) , boost::move(arg6) , boost::move(arg7) , boost::move(arg8));
                }
                catch (hpx::thread_interrupted const&) {
                     
                }
                catch (hpx::exception const& e) {
                    LTM_(error)
                        << "Unhandled exception while executing component action("
                        << detail::get_action_name<Derived>()
                        << ") lva(" << reinterpret_cast<void const*>
                            (get_lva<Component const>::call(lva)) << "): " << e.what();
                    
                    hpx::report_error(boost::current_exception());
                }
                catch (...) {
                    LTM_(error)
                        << "Unhandled exception while executing component action("
                        << detail::get_action_name<Derived>()
                        << ") lva(" << reinterpret_cast<void const*>
                            (get_lva<Component const>::call(lva)) << ")";
                    
                    hpx::report_error(boost::current_exception());
                }
                
                
                
                util::force_error_on_lock();
                return threads::terminated;
            }
        };
    public:
        typedef boost::mpl::false_ direct_execution;
        
        
        
        
        template <typename Arguments>
        static HPX_STD_FUNCTION<threads::thread_function_type>
        construct_thread_function(naming::address::address_type lva,
            BOOST_FWD_REF(Arguments) args)
        {
            return Derived::decorate_action(
                HPX_STD_BIND(typename Derived::thread_function(),
                    lva, util::get< 0>(boost::forward<Arguments>( args)) , util::get< 1>(boost::forward<Arguments>( args)) , util::get< 2>(boost::forward<Arguments>( args)) , util::get< 3>(boost::forward<Arguments>( args)) , util::get< 4>(boost::forward<Arguments>( args)) , util::get< 5>(boost::forward<Arguments>( args)) , util::get< 6>(boost::forward<Arguments>( args)) , util::get< 7>(boost::forward<Arguments>( args)) , util::get< 8>(boost::forward<Arguments>( args))), lva);
        }
        
        
        
        
        template <typename Arguments>
        static HPX_STD_FUNCTION<threads::thread_function_type>
        construct_thread_function(continuation_type& cont,
            naming::address::address_type lva, BOOST_FWD_REF(Arguments) args)
        {
            return Derived::decorate_action(
                base_type::construct_continuation_thread_object_function(
                    cont, F, get_lva<Component const>::call(lva),
                    boost::forward<Arguments>(args)), lva);
        }
        
        template <typename Arguments>
        BOOST_FORCEINLINE static Result
        execute_function(naming::address::address_type lva,
            BOOST_FWD_REF(Arguments) args)
        {
            LTM_(debug)
                << "base_result_action" << 9
                << "::execute_function name("
                << detail::get_action_name<Derived>()
                << ") lva(" << reinterpret_cast<void const*>(
                    get_lva<Component const>::call(lva)) << ")";
            return (get_lva<Component const>::call(lva)->*F)(
                util::get< 0>(boost::forward<Arguments>( args)) , util::get< 1>(boost::forward<Arguments>( args)) , util::get< 2>(boost::forward<Arguments>( args)) , util::get< 3>(boost::forward<Arguments>( args)) , util::get< 4>(boost::forward<Arguments>( args)) , util::get< 5>(boost::forward<Arguments>( args)) , util::get< 6>(boost::forward<Arguments>( args)) , util::get< 7>(boost::forward<Arguments>( args)) , util::get< 8>(boost::forward<Arguments>( args)));
        }
    };
    
    
    template <
        typename Component, typename Result,
        typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8,
        Result (Component::*F)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8) const,
        typename Derived>
    struct result_action9<
            Result (Component::*)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8) const, F, Derived>
      : base_result_action9<
            Result (Component::*)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8) const, F,
            typename detail::action_type<
                result_action9<
                    Result (Component::*)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8) const, F, Derived>,
                Derived
            >::type>
    {
        typedef typename detail::action_type<
            result_action9, Derived
        >::type derived_type;
        typedef boost::mpl::false_ direct_execution;
    };
    
    template <
        typename Component, typename Result, typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8,
        Result (Component::*F)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8) const, typename Derived>
    struct make_action<Result (Component::*)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8) const,
            F, Derived, boost::mpl::false_>
      : result_action9<
            Result (Component::*)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8) const, F, Derived>
    {
        typedef result_action9<
            Result (Component::*)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8) const, F, Derived
        > type;
    };
    
    
    template <
        typename Component, typename Result,
        typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8,
        Result (Component::*F)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8) const,
        typename Derived>
    struct direct_result_action9<
            Result (Component::*)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8) const, F, Derived>
      : base_result_action9<
            Result (Component::*)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8) const, F,
            typename detail::action_type<
                direct_result_action9<
                    Result (Component::*)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8) const, F, Derived>,
                    Derived
            >::type>
    {
        typedef typename detail::action_type<
            direct_result_action9, Derived
        >::type derived_type;
        typedef boost::mpl::true_ direct_execution;
        
        
        static base_action::action_type get_action_type()
        {
            return base_action::direct_action;
        }
    };
    
    template <
        typename Component, typename Result, typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8,
        Result (Component::*F)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8) const, typename Derived>
    struct make_action<Result (Component::*)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8) const,
            F, Derived, boost::mpl::true_>
      : direct_result_action9<
            Result (Component::*)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8) const, F, Derived>
    {
        typedef direct_result_action9<
            Result (Component::*)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8) const, F, Derived
        > type;
    };
    
    
    template <
        typename Component, typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8,
        void (Component::*F)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8) const, typename Derived>
    class base_action9<
            void (Component::*)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8) const, F, Derived>
      : public action<
            Component const, util::unused_type,
            hpx::util::tuple<typename util::decay<T0>::type , typename util::decay<T1>::type , typename util::decay<T2>::type , typename util::decay<T3>::type , typename util::decay<T4>::type , typename util::decay<T5>::type , typename util::decay<T6>::type , typename util::decay<T7>::type , typename util::decay<T8>::type>,
            Derived>
    {
    public:
        typedef util::unused_type result_type;
        typedef util::unused_type remote_result_type;
        typedef hpx::util::tuple<
            typename util::decay<T0>::type , typename util::decay<T1>::type , typename util::decay<T2>::type , typename util::decay<T3>::type , typename util::decay<T4>::type , typename util::decay<T5>::type , typename util::decay<T6>::type , typename util::decay<T7>::type , typename util::decay<T8>::type> arguments_type;
        typedef action<Component const, remote_result_type, arguments_type, Derived>
            base_type;
    protected:
        
        
        
        struct thread_function
        {
            typedef threads::thread_state_enum result_type;
            template <typename Arg0 , typename Arg1 , typename Arg2 , typename Arg3 , typename Arg4 , typename Arg5 , typename Arg6 , typename Arg7 , typename Arg8>
            BOOST_FORCEINLINE result_type operator()(
                naming::address::address_type lva,
                BOOST_FWD_REF(Arg0) arg0 , BOOST_FWD_REF(Arg1) arg1 , BOOST_FWD_REF(Arg2) arg2 , BOOST_FWD_REF(Arg3) arg3 , BOOST_FWD_REF(Arg4) arg4 , BOOST_FWD_REF(Arg5) arg5 , BOOST_FWD_REF(Arg6) arg6 , BOOST_FWD_REF(Arg7) arg7 , BOOST_FWD_REF(Arg8) arg8) const
            {
                try {
                    LTM_(debug) << "Executing component action("
                                << detail::get_action_name<Derived>()
                                << ") lva(" << reinterpret_cast<void const*>
                                    (get_lva<Component const>::call(lva)) << ")";
                    
                    
                    
                    
                    (get_lva<Component const>::call(lva)->*F)(
                        boost::move(arg0) , boost::move(arg1) , boost::move(arg2) , boost::move(arg3) , boost::move(arg4) , boost::move(arg5) , boost::move(arg6) , boost::move(arg7) , boost::move(arg8));
                }
                catch (hpx::thread_interrupted const&) {
                     
                }
                catch (hpx::exception const& e) {
                    LTM_(error)
                        << "Unhandled exception while executing component action("
                        << detail::get_action_name<Derived>()
                        << ") lva(" << reinterpret_cast<void const*>
                            (get_lva<Component const>::call(lva)) << "): " << e.what();
                    
                    hpx::report_error(boost::current_exception());
                }
                catch (...) {
                    LTM_(error)
                        << "Unhandled exception while executing component action("
                        << detail::get_action_name<Derived>()
                        << ") lva(" << reinterpret_cast<void const*>
                            (get_lva<Component const>::call(lva)) << ")";
                    
                    hpx::report_error(boost::current_exception());
                }
                
                
                
                util::force_error_on_lock();
                return threads::terminated;
            }
        };
    public:
        
        
        
        
        template <typename Arguments>
        static HPX_STD_FUNCTION<threads::thread_function_type>
        construct_thread_function(naming::address::address_type lva,
            BOOST_FWD_REF(Arguments) args)
        {
            
            
            return Derived::decorate_action(
                HPX_STD_BIND(typename Derived::thread_function(), lva,
                    util::get< 0>(boost::forward<Arguments>( args)) , util::get< 1>(boost::forward<Arguments>( args)) , util::get< 2>(boost::forward<Arguments>( args)) , util::get< 3>(boost::forward<Arguments>( args)) , util::get< 4>(boost::forward<Arguments>( args)) , util::get< 5>(boost::forward<Arguments>( args)) , util::get< 6>(boost::forward<Arguments>( args)) , util::get< 7>(boost::forward<Arguments>( args)) , util::get< 8>(boost::forward<Arguments>( args))), lva);
        }
        
        
        
        
        template <typename Arguments>
        static HPX_STD_FUNCTION<threads::thread_function_type>
        construct_thread_function(continuation_type& cont,
            naming::address::address_type lva, BOOST_FWD_REF(Arguments) args)
        {
            return Derived::decorate_action(
                base_type::construct_continuation_thread_object_function_void(
                    cont, F, get_lva<Component const>::call(lva),
                    boost::forward<Arguments>(args)), lva);
        }
        
        template <typename Arguments>
        BOOST_FORCEINLINE static util::unused_type
        execute_function(naming::address::address_type lva,
            BOOST_FWD_REF(Arguments) args)
        {
            LTM_(debug)
                << "base_action" << 9
                << "::execute_function name("
                << detail::get_action_name<Derived>()
                << ") lva(" << reinterpret_cast<void const*>(
                    get_lva<Component const>::call(lva)) << ")";
            (get_lva<Component const>::call(lva)->*F)(
                util::get< 0>(boost::forward<Arguments>( args)) , util::get< 1>(boost::forward<Arguments>( args)) , util::get< 2>(boost::forward<Arguments>( args)) , util::get< 3>(boost::forward<Arguments>( args)) , util::get< 4>(boost::forward<Arguments>( args)) , util::get< 5>(boost::forward<Arguments>( args)) , util::get< 6>(boost::forward<Arguments>( args)) , util::get< 7>(boost::forward<Arguments>( args)) , util::get< 8>(boost::forward<Arguments>( args)));
            return util::unused;
        }
    };
    
    template <
        typename Component, typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8,
        void (Component::*F)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8) const,
        typename Derived>
    struct action9<
            void (Component::*)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8) const, F, Derived>
      : base_action9<
            void (Component::*)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8) const, F,
            typename detail::action_type<
                action9<
                    void (Component::*)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8) const, F, Derived>,
                Derived
            >::type>
    {
        typedef typename detail::action_type<
            action9, Derived
        >::type derived_type;
        typedef boost::mpl::false_ direct_execution;
    };
    
    template <typename Component, typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8,
        void (Component::*F)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8) const, typename Derived>
    struct make_action<void (Component::*)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8) const,
            F, Derived, boost::mpl::false_>
      : action9<
            void (Component::*)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8) const, F, Derived>
    {
        typedef action9<
            void (Component::*)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8) const, F, Derived
        > type;
    };
    
    template <
        typename Component, typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8,
        void (Component::*F)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8) const,
        typename Derived>
    struct direct_action9<
            void (Component::*)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8) const, F, Derived>
      : base_action9<
            void (Component::*)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8) const, F,
            typename detail::action_type<
                direct_action9<
                    void (Component::*)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8) const, F, Derived>,
                    Derived
            >::type>
    {
        typedef typename detail::action_type<
            direct_action9, Derived
        >::type derived_type;
        typedef boost::mpl::true_ direct_execution;
        
        
        static base_action::action_type get_action_type()
        {
            return base_action::direct_action;
        }
    };
    
    template <
        typename Component, typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8,
        void (Component::*F)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8) const, typename Derived>
    struct make_action<void (Component::*)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8) const,
            F, Derived, boost::mpl::true_>
      : direct_action9<
            void (Component::*)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8) const, F, Derived>
    {
        typedef direct_action9<
            void (Component::*)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8) const, F, Derived
        > type;
    };
    
    
    template <
        typename Component,
        typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8,
        void (Component::*F)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8) const,
        typename Derived>
    struct result_action9<
            void (Component::*)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8) const, F, Derived>
      : action9<
            void (Component::*)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8) const, F, Derived>
    {};
}}
namespace hpx { namespace actions
{
    
    
    template <
        typename Component, typename Result,
        typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9,
        Result (Component::*F)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9) const, typename Derived>
    class base_result_action10<
            Result (Component::*)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9) const, F, Derived>
      : public action<
            Component const, Result,
            hpx::util::tuple<typename util::decay<T0>::type , typename util::decay<T1>::type , typename util::decay<T2>::type , typename util::decay<T3>::type , typename util::decay<T4>::type , typename util::decay<T5>::type , typename util::decay<T6>::type , typename util::decay<T7>::type , typename util::decay<T8>::type , typename util::decay<T9>::type>,
            Derived>
    {
    public:
        typedef Result result_type;
        typedef typename detail::remote_action_result<Result>::type
            remote_result_type;
        typedef hpx::util::tuple<
            typename util::decay<T0>::type , typename util::decay<T1>::type , typename util::decay<T2>::type , typename util::decay<T3>::type , typename util::decay<T4>::type , typename util::decay<T5>::type , typename util::decay<T6>::type , typename util::decay<T7>::type , typename util::decay<T8>::type , typename util::decay<T9>::type> arguments_type;
        typedef action<Component const, remote_result_type, arguments_type, Derived>
            base_type;
    protected:
        
        
        
        struct thread_function
        {
            typedef threads::thread_state_enum result_type;
            template <typename Arg0 , typename Arg1 , typename Arg2 , typename Arg3 , typename Arg4 , typename Arg5 , typename Arg6 , typename Arg7 , typename Arg8 , typename Arg9>
            BOOST_FORCEINLINE result_type operator()(
                naming::address::address_type lva,
                BOOST_FWD_REF(Arg0) arg0 , BOOST_FWD_REF(Arg1) arg1 , BOOST_FWD_REF(Arg2) arg2 , BOOST_FWD_REF(Arg3) arg3 , BOOST_FWD_REF(Arg4) arg4 , BOOST_FWD_REF(Arg5) arg5 , BOOST_FWD_REF(Arg6) arg6 , BOOST_FWD_REF(Arg7) arg7 , BOOST_FWD_REF(Arg8) arg8 , BOOST_FWD_REF(Arg9) arg9) const
            {
                try {
                    LTM_(debug) << "Executing component action("
                                << detail::get_action_name<Derived>()
                                << ") lva(" << reinterpret_cast<void const*>
                                    (get_lva<Component const>::call(lva)) << ")";
                    
                    
                    
                    
                    (get_lva<Component const>::call(lva)->*F)(
                        boost::move(arg0) , boost::move(arg1) , boost::move(arg2) , boost::move(arg3) , boost::move(arg4) , boost::move(arg5) , boost::move(arg6) , boost::move(arg7) , boost::move(arg8) , boost::move(arg9));
                }
                catch (hpx::thread_interrupted const&) {
                     
                }
                catch (hpx::exception const& e) {
                    LTM_(error)
                        << "Unhandled exception while executing component action("
                        << detail::get_action_name<Derived>()
                        << ") lva(" << reinterpret_cast<void const*>
                            (get_lva<Component const>::call(lva)) << "): " << e.what();
                    
                    hpx::report_error(boost::current_exception());
                }
                catch (...) {
                    LTM_(error)
                        << "Unhandled exception while executing component action("
                        << detail::get_action_name<Derived>()
                        << ") lva(" << reinterpret_cast<void const*>
                            (get_lva<Component const>::call(lva)) << ")";
                    
                    hpx::report_error(boost::current_exception());
                }
                
                
                
                util::force_error_on_lock();
                return threads::terminated;
            }
        };
    public:
        typedef boost::mpl::false_ direct_execution;
        
        
        
        
        template <typename Arguments>
        static HPX_STD_FUNCTION<threads::thread_function_type>
        construct_thread_function(naming::address::address_type lva,
            BOOST_FWD_REF(Arguments) args)
        {
            return Derived::decorate_action(
                HPX_STD_BIND(typename Derived::thread_function(),
                    lva, util::get< 0>(boost::forward<Arguments>( args)) , util::get< 1>(boost::forward<Arguments>( args)) , util::get< 2>(boost::forward<Arguments>( args)) , util::get< 3>(boost::forward<Arguments>( args)) , util::get< 4>(boost::forward<Arguments>( args)) , util::get< 5>(boost::forward<Arguments>( args)) , util::get< 6>(boost::forward<Arguments>( args)) , util::get< 7>(boost::forward<Arguments>( args)) , util::get< 8>(boost::forward<Arguments>( args)) , util::get< 9>(boost::forward<Arguments>( args))), lva);
        }
        
        
        
        
        template <typename Arguments>
        static HPX_STD_FUNCTION<threads::thread_function_type>
        construct_thread_function(continuation_type& cont,
            naming::address::address_type lva, BOOST_FWD_REF(Arguments) args)
        {
            return Derived::decorate_action(
                base_type::construct_continuation_thread_object_function(
                    cont, F, get_lva<Component const>::call(lva),
                    boost::forward<Arguments>(args)), lva);
        }
        
        template <typename Arguments>
        BOOST_FORCEINLINE static Result
        execute_function(naming::address::address_type lva,
            BOOST_FWD_REF(Arguments) args)
        {
            LTM_(debug)
                << "base_result_action" << 10
                << "::execute_function name("
                << detail::get_action_name<Derived>()
                << ") lva(" << reinterpret_cast<void const*>(
                    get_lva<Component const>::call(lva)) << ")";
            return (get_lva<Component const>::call(lva)->*F)(
                util::get< 0>(boost::forward<Arguments>( args)) , util::get< 1>(boost::forward<Arguments>( args)) , util::get< 2>(boost::forward<Arguments>( args)) , util::get< 3>(boost::forward<Arguments>( args)) , util::get< 4>(boost::forward<Arguments>( args)) , util::get< 5>(boost::forward<Arguments>( args)) , util::get< 6>(boost::forward<Arguments>( args)) , util::get< 7>(boost::forward<Arguments>( args)) , util::get< 8>(boost::forward<Arguments>( args)) , util::get< 9>(boost::forward<Arguments>( args)));
        }
    };
    
    
    template <
        typename Component, typename Result,
        typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9,
        Result (Component::*F)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9) const,
        typename Derived>
    struct result_action10<
            Result (Component::*)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9) const, F, Derived>
      : base_result_action10<
            Result (Component::*)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9) const, F,
            typename detail::action_type<
                result_action10<
                    Result (Component::*)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9) const, F, Derived>,
                Derived
            >::type>
    {
        typedef typename detail::action_type<
            result_action10, Derived
        >::type derived_type;
        typedef boost::mpl::false_ direct_execution;
    };
    
    template <
        typename Component, typename Result, typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9,
        Result (Component::*F)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9) const, typename Derived>
    struct make_action<Result (Component::*)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9) const,
            F, Derived, boost::mpl::false_>
      : result_action10<
            Result (Component::*)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9) const, F, Derived>
    {
        typedef result_action10<
            Result (Component::*)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9) const, F, Derived
        > type;
    };
    
    
    template <
        typename Component, typename Result,
        typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9,
        Result (Component::*F)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9) const,
        typename Derived>
    struct direct_result_action10<
            Result (Component::*)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9) const, F, Derived>
      : base_result_action10<
            Result (Component::*)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9) const, F,
            typename detail::action_type<
                direct_result_action10<
                    Result (Component::*)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9) const, F, Derived>,
                    Derived
            >::type>
    {
        typedef typename detail::action_type<
            direct_result_action10, Derived
        >::type derived_type;
        typedef boost::mpl::true_ direct_execution;
        
        
        static base_action::action_type get_action_type()
        {
            return base_action::direct_action;
        }
    };
    
    template <
        typename Component, typename Result, typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9,
        Result (Component::*F)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9) const, typename Derived>
    struct make_action<Result (Component::*)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9) const,
            F, Derived, boost::mpl::true_>
      : direct_result_action10<
            Result (Component::*)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9) const, F, Derived>
    {
        typedef direct_result_action10<
            Result (Component::*)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9) const, F, Derived
        > type;
    };
    
    
    template <
        typename Component, typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9,
        void (Component::*F)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9) const, typename Derived>
    class base_action10<
            void (Component::*)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9) const, F, Derived>
      : public action<
            Component const, util::unused_type,
            hpx::util::tuple<typename util::decay<T0>::type , typename util::decay<T1>::type , typename util::decay<T2>::type , typename util::decay<T3>::type , typename util::decay<T4>::type , typename util::decay<T5>::type , typename util::decay<T6>::type , typename util::decay<T7>::type , typename util::decay<T8>::type , typename util::decay<T9>::type>,
            Derived>
    {
    public:
        typedef util::unused_type result_type;
        typedef util::unused_type remote_result_type;
        typedef hpx::util::tuple<
            typename util::decay<T0>::type , typename util::decay<T1>::type , typename util::decay<T2>::type , typename util::decay<T3>::type , typename util::decay<T4>::type , typename util::decay<T5>::type , typename util::decay<T6>::type , typename util::decay<T7>::type , typename util::decay<T8>::type , typename util::decay<T9>::type> arguments_type;
        typedef action<Component const, remote_result_type, arguments_type, Derived>
            base_type;
    protected:
        
        
        
        struct thread_function
        {
            typedef threads::thread_state_enum result_type;
            template <typename Arg0 , typename Arg1 , typename Arg2 , typename Arg3 , typename Arg4 , typename Arg5 , typename Arg6 , typename Arg7 , typename Arg8 , typename Arg9>
            BOOST_FORCEINLINE result_type operator()(
                naming::address::address_type lva,
                BOOST_FWD_REF(Arg0) arg0 , BOOST_FWD_REF(Arg1) arg1 , BOOST_FWD_REF(Arg2) arg2 , BOOST_FWD_REF(Arg3) arg3 , BOOST_FWD_REF(Arg4) arg4 , BOOST_FWD_REF(Arg5) arg5 , BOOST_FWD_REF(Arg6) arg6 , BOOST_FWD_REF(Arg7) arg7 , BOOST_FWD_REF(Arg8) arg8 , BOOST_FWD_REF(Arg9) arg9) const
            {
                try {
                    LTM_(debug) << "Executing component action("
                                << detail::get_action_name<Derived>()
                                << ") lva(" << reinterpret_cast<void const*>
                                    (get_lva<Component const>::call(lva)) << ")";
                    
                    
                    
                    
                    (get_lva<Component const>::call(lva)->*F)(
                        boost::move(arg0) , boost::move(arg1) , boost::move(arg2) , boost::move(arg3) , boost::move(arg4) , boost::move(arg5) , boost::move(arg6) , boost::move(arg7) , boost::move(arg8) , boost::move(arg9));
                }
                catch (hpx::thread_interrupted const&) {
                     
                }
                catch (hpx::exception const& e) {
                    LTM_(error)
                        << "Unhandled exception while executing component action("
                        << detail::get_action_name<Derived>()
                        << ") lva(" << reinterpret_cast<void const*>
                            (get_lva<Component const>::call(lva)) << "): " << e.what();
                    
                    hpx::report_error(boost::current_exception());
                }
                catch (...) {
                    LTM_(error)
                        << "Unhandled exception while executing component action("
                        << detail::get_action_name<Derived>()
                        << ") lva(" << reinterpret_cast<void const*>
                            (get_lva<Component const>::call(lva)) << ")";
                    
                    hpx::report_error(boost::current_exception());
                }
                
                
                
                util::force_error_on_lock();
                return threads::terminated;
            }
        };
    public:
        
        
        
        
        template <typename Arguments>
        static HPX_STD_FUNCTION<threads::thread_function_type>
        construct_thread_function(naming::address::address_type lva,
            BOOST_FWD_REF(Arguments) args)
        {
            
            
            return Derived::decorate_action(
                HPX_STD_BIND(typename Derived::thread_function(), lva,
                    util::get< 0>(boost::forward<Arguments>( args)) , util::get< 1>(boost::forward<Arguments>( args)) , util::get< 2>(boost::forward<Arguments>( args)) , util::get< 3>(boost::forward<Arguments>( args)) , util::get< 4>(boost::forward<Arguments>( args)) , util::get< 5>(boost::forward<Arguments>( args)) , util::get< 6>(boost::forward<Arguments>( args)) , util::get< 7>(boost::forward<Arguments>( args)) , util::get< 8>(boost::forward<Arguments>( args)) , util::get< 9>(boost::forward<Arguments>( args))), lva);
        }
        
        
        
        
        template <typename Arguments>
        static HPX_STD_FUNCTION<threads::thread_function_type>
        construct_thread_function(continuation_type& cont,
            naming::address::address_type lva, BOOST_FWD_REF(Arguments) args)
        {
            return Derived::decorate_action(
                base_type::construct_continuation_thread_object_function_void(
                    cont, F, get_lva<Component const>::call(lva),
                    boost::forward<Arguments>(args)), lva);
        }
        
        template <typename Arguments>
        BOOST_FORCEINLINE static util::unused_type
        execute_function(naming::address::address_type lva,
            BOOST_FWD_REF(Arguments) args)
        {
            LTM_(debug)
                << "base_action" << 10
                << "::execute_function name("
                << detail::get_action_name<Derived>()
                << ") lva(" << reinterpret_cast<void const*>(
                    get_lva<Component const>::call(lva)) << ")";
            (get_lva<Component const>::call(lva)->*F)(
                util::get< 0>(boost::forward<Arguments>( args)) , util::get< 1>(boost::forward<Arguments>( args)) , util::get< 2>(boost::forward<Arguments>( args)) , util::get< 3>(boost::forward<Arguments>( args)) , util::get< 4>(boost::forward<Arguments>( args)) , util::get< 5>(boost::forward<Arguments>( args)) , util::get< 6>(boost::forward<Arguments>( args)) , util::get< 7>(boost::forward<Arguments>( args)) , util::get< 8>(boost::forward<Arguments>( args)) , util::get< 9>(boost::forward<Arguments>( args)));
            return util::unused;
        }
    };
    
    template <
        typename Component, typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9,
        void (Component::*F)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9) const,
        typename Derived>
    struct action10<
            void (Component::*)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9) const, F, Derived>
      : base_action10<
            void (Component::*)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9) const, F,
            typename detail::action_type<
                action10<
                    void (Component::*)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9) const, F, Derived>,
                Derived
            >::type>
    {
        typedef typename detail::action_type<
            action10, Derived
        >::type derived_type;
        typedef boost::mpl::false_ direct_execution;
    };
    
    template <typename Component, typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9,
        void (Component::*F)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9) const, typename Derived>
    struct make_action<void (Component::*)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9) const,
            F, Derived, boost::mpl::false_>
      : action10<
            void (Component::*)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9) const, F, Derived>
    {
        typedef action10<
            void (Component::*)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9) const, F, Derived
        > type;
    };
    
    template <
        typename Component, typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9,
        void (Component::*F)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9) const,
        typename Derived>
    struct direct_action10<
            void (Component::*)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9) const, F, Derived>
      : base_action10<
            void (Component::*)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9) const, F,
            typename detail::action_type<
                direct_action10<
                    void (Component::*)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9) const, F, Derived>,
                    Derived
            >::type>
    {
        typedef typename detail::action_type<
            direct_action10, Derived
        >::type derived_type;
        typedef boost::mpl::true_ direct_execution;
        
        
        static base_action::action_type get_action_type()
        {
            return base_action::direct_action;
        }
    };
    
    template <
        typename Component, typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9,
        void (Component::*F)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9) const, typename Derived>
    struct make_action<void (Component::*)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9) const,
            F, Derived, boost::mpl::true_>
      : direct_action10<
            void (Component::*)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9) const, F, Derived>
    {
        typedef direct_action10<
            void (Component::*)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9) const, F, Derived
        > type;
    };
    
    
    template <
        typename Component,
        typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9,
        void (Component::*F)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9) const,
        typename Derived>
    struct result_action10<
            void (Component::*)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9) const, F, Derived>
      : action10<
            void (Component::*)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9) const, F, Derived>
    {};
}}
