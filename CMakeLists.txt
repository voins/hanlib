cmake_minimum_required(VERSION 3.15)
project(hanlib CXX)

add_executable(test test.cc)
target_compile_features(test PRIVATE cxx_std_17)
target_include_directories(test PRIVATE include)
target_compile_options(test PRIVATE
    -Weverything
    -Werror
    -pedantic
    -pedantic-errors
    -Wno-c++98-compat
    -Wno-c++98-compat-pedantic
    -Wno-c99-extensions
    -Wno-global-constructors
    -Wno-exit-time-destructors
    -Wno-missing-variable-declarations
    -Wno-padded
    -Wno-ctad-maybe-unsupported
    -Wno-c++2a-extensions)
