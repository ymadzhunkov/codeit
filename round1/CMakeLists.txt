cmake_minimum_required(VERSION 2.8.12)

get_filename_component(PROJECT_NAME ${CMAKE_CURRENT_SOURCE_DIR} NAME)
project(${PROJECT_NAME})


include_directories("include")

add_definitions(-std=c++11)
set(SOURCES 
    "../src/keyboard.cpp"
    "../src/answer.cpp"
    "../src/problem.cpp"
    "../src/progress.cpp"
    "../src/simulated_annealing.cpp"
    "../src/differential_evolution.cpp"
)

add_subdirectory(test)
add_subdirectory(integration)



