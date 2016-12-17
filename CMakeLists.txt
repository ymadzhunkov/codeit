cmake_minimum_required(VERSION 2.8.12)

project(codeit)

enable_testing()
set(DOCTEST_INCLUDE "${PROJECT_SOURCE_DIR}/doctest/doctest")
include(coverage.cmake)
set(COVERAGE_PROJECTS "" CACHE INTERNAL "List of all coverage targets")

#add_subdirectory(round1)
#add_subdirectory(round2)
add_subdirectory(round3)

add_subdirectory(coverage)


