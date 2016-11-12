
set (AGGREGATED_TESTS_COVERAGE "aggregated_tests_coverage")
add_custom_command(
   OUTPUT index.html genhtml.log amber.png  emerald.png  glass.png  ruby.png  snow.png  updown.png gcov.css index-sort-f.html index-sort-l.html index-sort-b.html ${AGGREGATED_TESTS_COVERAGE} ${AGGREGATED_TESTS_COVERAGE}.log

   DEPENDS all_tests_coverage
   COMMAND lcov ${COVERAGE_TOTAL_FILES} -o ${AGGREGATED_TESTS_COVERAGE} > ${AGGREGATED_TESTS_COVERAGE}.log
   COMMAND lcov -l ${AGGREGATED_TESTS_COVERAGE} >> ${AGGREGATED_TESTS_COVERAGE}.log
   COMMAND genhtml ${AGGREGATED_TESTS_COVERAGE} --highlight --legend --demangle-cpp > genhtml.log
   COMMENT "Generating coverage report in ${CMAKE_CURRENT_BINARY_DIR}"
#   VERBATIM
)

add_custom_target(report_coverage DEPENDS index.html)
