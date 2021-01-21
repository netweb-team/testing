cmake_minimum_required(VERSION 3.5)
project(ComRed)

#include(configure_gtest.cmake)

include_directories("${PROJECT_SOURCE_DIR}/include")

file(GLOB sources
        "${PROJECT_SOURCE_DIR}/include/*.h"
        "${PROJECT_SOURCE_DIR}/include/server/*.h"
        "include/server/requests/controller/*.h"
        "include/server/requests/*.h"
        "${PROJECT_SOURCE_DIR}/src/*.cpp")

find_package(Boost 1.71 REQUIRED)
find_package(Threads)

#set(GCC_COVERAGE_COMPILE_FLAGS "-std=gnu++11")
#set(PQXX_AND_PQ_FLAGS "-lpqxx -lpq -I/usr/local/include -L/usr/local/lib")
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${PQXX_AND_PQ_FLAGS} #${GCC_COVERAGE_COMPILE_FLAGS}")

#set(GCC_COVERAGE_COMPILE_FLAGS "-std=gnu++11")
set(PQXX_AND_PQ_FLAGS "-I/usr/local/include -L/usr/local/lib")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${PQXX_AND_PQ_FLAGS}")


include_directories(${Boost_INCLUDE_DIRS})
file(GLOB ServerApplication_DIRS
        "../ServerApplication/include*")
include_directories(${ServerApplication_DIRS})

add_executable(server ${sources})

target_link_libraries(server
            ${CMAKE_THREAD_LIBS_INIT}
            ServerApplication Utils
        )

add_library(Client STATIC ${PROJECT_SOURCE_DIR}/src/client/httpClient.cpp)
target_include_directories(Client PUBLIC ${PROJECT_SOURCE_DIR}/src/client)

add_executable(test_e2e ${PROJECT_SOURCE_DIR}/test/test_e2e.cpp)
target_link_libraries(test_e2e ${CMAKE_THREAD_LIBS_INIT} Client)