cmake_minimum_required(VERSION 3.5)
project(DB)

find_package(Boost REQUIRED)

include_directories("${PROJECT_SOURCE_DIR}/include")

file(GLOB SRC
        "${PROJECT_SOURCE_DIR}/include/*.h"
        "${PROJECT_SOURCE_DIR}/src/*.cpp"
        )

#file(GLOB TEST_SRC
#        ${PROJECT_SOURCE_DIR}/test/testDB.cpp
#)

add_library(DB STATIC ${SRC})
target_include_directories(DB PUBLIC ${PROJECT_SOURCE_DIR}/src)

set(PostgreSQL_TYPE_INCLUDE_DIR "/usr/include/postgresql")
find_package(PostgreSQL REQUIRED)
target_include_directories(DB PRIVATE ${PostgreSQL_INCLUDE_DIRS})
target_link_libraries(DB PRIVATE ${PostgreSQL_LIBRARIES} -lpqxx -lpq)
target_link_libraries(DB PRIVATE Utils)

add_executable(test_repo ${PROJECT_SOURCE_DIR}/test/test_repo.cpp)
target_link_libraries(test_repo DB)
target_link_libraries(test_repo ${GTEST_LIBRARIES} pthread -lgmock)

#add_executable(test_db ${TEST_SRC})
#target_link_libraries(test_db
#                        DB
#                        Utils
#                        ServerApplication
#)
#target_link_libraries(test_db ${GTEST_LIBRARIES} pthread)
#target_link_libraries(test_db -lgmock)
