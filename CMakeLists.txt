cmake_minimum_required(VERSION 3.10)


set(PROJECT_NAME polynom_translator)
project(${PROJECT_NAME})

file(GLOB arithm_translator_files "include/arithm_translator/*.h" "include/arithm_translator/*.cpp")
file(GLOB array_files "include/array/*.h" "include/array/*.cpp")
file(GLOB hash_table_files "include/hash_table/*.h" "include/hash_table/*.cpp")
file(GLOB polinom_files "include/polinom/*.h" "include/polinom/*.cpp")
file(GLOB search_tree_files "include/search_tree/*.h" "include/search_tree/*.cpp")
file(GLOB tests_files "test/*.cpp")

add_library(gtest STATIC gtest/gtest-all.cc)
add_library(arithm_translator ${arithm_translator_files})
add_library(array ${array_files})
add_library(hash_table ${hash_table_files})
add_library(polinom ${polinom_files})
add_library(search_tree ${search_tree_files})

if((${CMAKE_CXX_COMPILER_ID} MATCHES "GNU" OR
    ${CMAKE_CXX_COMPILER_ID} MATCHES "Clang") AND
    (${CMAKE_SYSTEM_NAME} MATCHES "Linux"))
    set(pthread "-pthread")
endif()
target_link_libraries(gtest ${pthread})

include_directories(include/arithm_translator include/array include/hash_table include/polinom include/search_tree gtest)

add_executable(main src/main.cpp)
target_link_libraries(main arithm_translator array hash_table polinom search_tree)
add_executable(tests ${tests_files} gtest/gtest.h)
target_link_libraries(tests gtest arithm_translator array hash_table polinom search_tree)
