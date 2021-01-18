cmake_minimum_required(VERSION 3.5)
project(Utils)

include_directories("${PROJECT_SOURCE_DIR}/include")

file(GLOB sources
        "${PROJECT_SOURCE_DIR}/include/*.h"
        "${PROJECT_SOURCE_DIR}/src/*.cpp"
)

file(GLOB test_source
        "${PROJECT_SOURCE_DIR}/test/*.cpp"
        )

FIND_PACKAGE( Boost COMPONENTS program_options REQUIRED )
INCLUDE_DIRECTORIES( ${Boost_INCLUDE_DIR} )


add_library(Utils STATIC ${sources})
target_include_directories(Utils PUBLIC ${PROJECT_SOURCE_DIR}/src)
target_include_directories(Utils PUBLIC ${Boost_INCLUDE_DIR})

add_executable(gtest ${test_source})
#target_link_libraries(gtest  Utils ServerApplication ${GTEST_LIBRARIES} pthread)
#target_link_libraries(gtest -lgmock)
