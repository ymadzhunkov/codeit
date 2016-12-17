
set(TEST_SOURCES 
   "main.cpp"
)
add_definitions("-O2")
add_definitions("-g ")
SET(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-std=c++11 -pthread")
SET(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -flto")
add_executable(equations ${TEST_SOURCES} ${SOURCES})

