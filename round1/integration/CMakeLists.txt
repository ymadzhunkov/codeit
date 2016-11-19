
set(TEST_SOURCES 
   "main.cpp"
)
add_definitions("-O2")
#add_definitions("-pthread")
SET(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-std=c++11 -pthread")
SET(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -flto")
add_executable(keyboard ${TEST_SOURCES} ${SOURCES})

file(WRITE ${CMAKE_CURRENT_BINARY_DIR}/example.001.in 
    "20\nwlcvovowllowwvwllvco")

file(WRITE ${CMAKE_CURRENT_BINARY_DIR}/example.002.in 
    "30\nmvpmnqgqiuufouoemorbqqhokvfhoe")

file(WRITE ${CMAKE_CURRENT_BINARY_DIR}/example.003.in 
    "50\nqnuyipirixpledphezbjfencbykwgoloytztwhafdesxfaakts")

file(WRITE ${CMAKE_CURRENT_BINARY_DIR}/example.004.in 
    "100\nqnuyipirixpledphezbjfencbykwgoloytztwhafdesxfaaktsqnuyipirixpledphezbjfencbykwgoloytztwhafdesxfaakts")

file(WRITE ${CMAKE_CURRENT_BINARY_DIR}/example.005.in 
    "200\nqnuyipirixpledphezbjfencbykwgoloytztwhafdesxfaaktsqnuyipirixpledphezbjfencbykwgoloytztwhafdesxfaaktsqnuyipirixpledphezbjfencbykwgoloytztwhafdesxfaaktsqnuyipirixpledphezbjfencbykwgoloytztwhafdesxfaakts")

