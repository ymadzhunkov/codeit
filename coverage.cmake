if(coverage_included)
    return()
endif()
set(coverage_included true)

if(CMAKE_CXX_COMPILER_ID MATCHES "GNU")

   add_custom_target(all_tests_coverage)

   include(CMakeParseArguments)
   function(add_coverage_target)
      cmake_parse_arguments(ARG "" "PROJECT_NAME" "SOURCES;UNIT_SOURCES;LINK_LIBS" ${ARGN})

      set(GCC_COV_FLAGS "-fprofile-arcs -ftest-coverage -fPIC -O0 -g -fno-inline -fno-inline-small-functions -fno-default-inline")
 
      include_directories(${DOCTEST_INCLUDE})
 
      set                  (UNIT_TESTS ${ARG_PROJECT_NAME}_tests)
      add_executable       (${UNIT_TESTS} ${ARG_UNIT_SOURCES} ${ARG_SOURCES})
      target_link_libraries(${UNIT_TESTS} gcov ${ARG_LINK_LIBS})
 
      get_target_property  (EXISTING_LINK_FLAGS ${UNIT_TESTS} LINK_FLAGS)
      set_target_properties(${UNIT_TESTS} PROPERTIES LINK_FLAGS "${LINK_FLAGS} ${GCC_COV_FLAGS}")
      set_target_properties(${UNIT_TESTS} PROPERTIES COMPILE_FLAGS "${GCC_COV_FLAGS}" ) 
 
      set(COV_BASE  ${PROJECT_NAME}_base)
      set(COV_TEST  ${PROJECT_NAME}_test)
      set(COV_TOTAL ${PROJECT_NAME}_total)
 
#      set(LCOV_BRANCH_FLAG    "--rc lcov_branch_coverage=1")
#      set(GENHTML_BRANCH_FLAG "--branch-coverage")
      
      set(lcov_dir "--external"  "--directory" "${CMAKE_CURRENT_BINARY_DIR}/CMakeFiles/${PROJECT_NAME}_tests.dir/__/src/")
 
      set(GCNO_FILES "")
      foreach(s ${ARG_SOURCES})
         string(REGEX REPLACE "[.][.]" "__"  s2  ${s})
         list(APPEND GCNO_FILES "${CMAKE_CURRENT_BINARY_DIR}/CMakeFiles/${PROJECT_NAME}_tests.dir/${s2}.gcno")
      endforeach()
      
      add_custom_command(
         OUTPUT ${COV_BASE} ${COV_BASE}.log
         DEPENDS ${GCNO_FILES}
         COMMAND lcov ${lcov_dir} --capture --initial -o ${COV_BASE} > ${COV_BASE}.log 
         COMMENT "Creating code base in ${CMAKE_CURRENT_BINARY_DIR}"
      )

      add_custom_command(
         OUTPUT ${COV_TEST} ${COV_TEST}.log
         DEPENDS ${UNIT_TESTS} ${COV_BASE}
         COMMAND lcov ${lcov_dir} --zerocounters > ${COV_TEST}.log
         COMMAND $<TARGET_FILE:${UNIT_TESTS}> 
         COMMAND lcov ${lcov_dir} --capture --output-file ${COV_TEST} ${LCOV_BRANCH_FLAG} >> ${COV_TEST}.log 
         COMMENT "Measuring coverage in ${CMAKE_CURRENT_BINARY_DIR}"
      )
      
      add_custom_command(
         OUTPUT ${COV_TOTAL} ${COV_TOTAL}.log
         DEPENDS ${COV_BASE} ${COV_TEST}
         COMMAND lcov -a ${COV_BASE} -a ${COV_TEST} -o ${COV_TOTAL} ${LCOV_BRANCH_FLAG} > ${COV_TOTAL}.log
         COMMENT "Accumulation covarege runs in ${CMAKE_CURRENT_BINARY_DIR}"
      )

      add_custom_target(${PROJECT_NAME}_coverage DEPENDS ${COV_TOTAL})
      add_dependencies(all_tests_coverage ${PROJECT_NAME}_coverage)
      
      set(tmp ${COVERAGE_TOTAL_FILES})
      list(APPEND tmp "-a;${CMAKE_CURRENT_BINARY_DIR}/${COV_TOTAL}")
      set(COVERAGE_TOTAL_FILES ${tmp} CACHE INTERNAL "All coverage files to be aggregated by the final coverage report")


   endfunction()

else()
   function(add_coverage_target)
   endfunction()
endif()


function(add_integration_test)
   cmake_parse_arguments(ARG "" "TEST_NAME" "TEST_SOURCES;LINK_LIBS" ${ARGN})

   add_executable       (${ARG_TEST_NAME} ${ARG_TEST_SOURCES})
   target_link_libraries(${ARG_TEST_NAME} ${ARG_LINK_LIBS})
   add_test(NAME ${ARG_TEST_NAME} COMMAND $<TARGET_FILE:${ARG_TEST_NAME}>)
endfunction()
