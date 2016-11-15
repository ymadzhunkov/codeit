
set(UNIT_SOURCES 
   "main.cpp"
   "test_keyboard.cpp"
   "test_problem.cpp"
   "test_solution.cpp"
)

add_coverage_target(
   PROJECT_NAME ${PROJECT_NAME} 
   SOURCES      ${SOURCES}
   UNIT_SOURCES ${UNIT_SOURCES})
