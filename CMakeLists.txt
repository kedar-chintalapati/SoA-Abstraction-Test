cmake_minimum_required(VERSION 3.25)

project(soa_abstraction_test LANGUAGES CXX)

add_executable(soa_test tests/main.cpp)

target_include_directories(soa_test PRIVATE include)
target_compile_features(soa_test PRIVATE cxx_std_26)
target_compile_options(soa_test PRIVATE -freflection -Wall -Wextra -Wpedantic)