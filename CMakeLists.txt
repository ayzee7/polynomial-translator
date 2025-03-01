cmake_minimum_required(VERSION 3.10)


set(PROJECT_NAME polynom_translator)
project(${PROJECT_NAME})

file(GLOB includes_files "include/*/*.h" "include/*/*.cpp")
file(GLOB tests_files "test/*.cpp")

add_library(gtest STATIC gtest/gtest-all.cc)
add_library(includes ${includes_files})
if((${CMAKE_CXX_COMPILER_ID} MATCHES "GNU" OR
    ${CMAKE_CXX_COMPILER_ID} MATCHES "Clang") AND
    (${CMAKE_SYSTEM_NAME} MATCHES "Linux"))
    set(pthread "-pthread")
endif()
target_link_libraries(gtest ${pthread})

include_directories(include/arithm_translator include/array include/hash_table include/polinom include/search_tree gtest)

add_executable(main src/main.cpp)
target_link_libraries(main includes)
add_executable(tests ${tests_files} gtest/gtest.h)
target_link_libraries(tests gtest includes)
