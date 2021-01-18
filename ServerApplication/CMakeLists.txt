cmake_minimum_required(VERSION 3.5)
project(ServerApplication)

include_directories("${PROJECT_SOURCE_DIR}/include")

file(GLOB sources
        "${PROJECT_SOURCE_DIR}/include/*.h"
        "${PROJECT_SOURCE_DIR}/src/*.cpp"
        )

file(GLOB test_source
        "${PROJECT_SOURCE_DIR}/test/*.cpp"
        )

set(PQXX_AND_PQ_FLAGS "-I/usr/local/include -L/usr/local/lib")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${PQXX_AND_PQ_FLAGS}")

add_library(ServerApplication STATIC ${sources} src/Editor.cpp include/EditorManagerDelegate.h include/EditorListener.h)
target_include_directories(ServerApplication PUBLIC ${PROJECT_SOURCE_DIR}/src)
target_link_libraries(ServerApplication PUBLIC Utils DB)

add_executable(main.out main.cpp)
target_link_libraries(main.out ServerApplication Utils DB)

add_executable(test_server ${test_source})
#target_link_libraries(test_server  ServerApplication ${GTEST_LIBRARIES})
#target_link_libraries(test_server -lgmock pthread)
