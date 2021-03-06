# Copyright (c) 2013 Agustin Berge
#
# Distributed under the Boost Software License, Version 1.0. (See accompanying
# file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

set(tests
#    bind_and_or_test
#    bind_cdecl_mf_test
    bind_const_test
    bind_cv_test
    bind_dm2_test
    bind_dm3_test
    bind_dm_test
#    bind_eq2_test
#    bind_eq3_test
#    bind_eq_test
#    bind_fastcall_mf_test
#    bind_fastcall_test
#    bind_not_test
    bind_placeholder_test
    bind_ref_test
#    bind_rel_test
    bind_rv_sp_test
    bind_rvalue_test
    bind_stateful_test
#    bind_stdcall_mf_test
#    bind_stdcall_test
    bind_test__avoid_collision_with_function_bind_test
    protect_test
   )

foreach(test ${tests})
  set(sources
      ${test}.cpp)

  source_group("Source Files" FILES ${sources})

  # add example executable
  add_hpx_executable(${test}_test
                     SOURCES ${sources}
                     ${${test}_FLAGS}
                     FOLDER "Tests/Unit/Util/Bind")

  add_hpx_unit_test("util.bind" ${test} ${${test}_PARAMETERS})

  set_property(TARGET ${test}_test_exe APPEND
               PROPERTY COMPILE_DEFINITIONS
               "HPX_LIMIT=9")

  # add a custom target for this example
  add_hpx_pseudo_target(tests.unit.util.binddir.${test})

  # make pseudo-targets depend on master pseudo-target
  add_hpx_pseudo_dependencies(tests.unit.util.binddir
                              tests.unit.util.binddir.${test})

  # add dependencies to pseudo-target
  add_hpx_pseudo_dependencies(tests.unit.util.binddir.${test}
                              ${test}_test_exe)
endforeach()


