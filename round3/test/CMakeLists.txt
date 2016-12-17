
set(UNIT_SOURCES 
   "main.cpp"
   "test_problem.cpp"
   "test_answer.cpp"
)

add_coverage_target(
   PROJECT_NAME ${PROJECT_NAME} 
   SOURCES      ${SOURCES}
   UNIT_SOURCES ${UNIT_SOURCES})
