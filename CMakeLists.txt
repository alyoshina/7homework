cmake_minimum_required(VERSION 3.16.3)

project(07.homework)

# build googletest
add_subdirectory(
    "${CMAKE_CURRENT_SOURCE_DIR}/googletest"
    "googletest"
)

# main target
add_executable(
    demo 
    6homework/main.cpp
    6homework/include/serial_container.h
    6homework/include/ilist.h
    6homework/include/list.h
    6homework/include/forward_list.h
)

target_include_directories(
    demo PRIVATE
    6homework/include
    6homework/src
)

# test target
add_executable(
    containers_tests
    test/main.cpp
    test/container_tests.cpp
    test/list_tests_with_param.cpp
    test/serial_tests_with_param.cpp
    test/container_operator_tests.cpp
    test/container_delete_el_tests.cpp
)

target_include_directories(
    containers_tests PRIVATE
    "${CMAKE_CURRENT_SOURCE_DIR}/6homework"
    "${CMAKE_CURRENT_SOURCE_DIR}/6homework/include"
    "${CMAKE_CURRENT_SOURCE_DIR}/6homework/src"
)

target_link_libraries(
    containers_tests PRIVATE
    gtest gtest_main gmock
)

set_target_properties(demo PROPERTIES CXX_STANDARD 17 CXX_STANDARD_REQUIRED ON)
set_target_properties(containers_tests PROPERTIES CXX_STANDARD 17 CXX_STANDARD_REQUIRED ON)
