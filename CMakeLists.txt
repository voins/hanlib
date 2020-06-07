cmake_minimum_required(VERSION 3.15)
project(hanlib CXX)

enable_testing()

add_executable(test-maybe test.cc)
target_compile_features(test-maybe PRIVATE cxx_std_17)
target_include_directories(test-maybe PRIVATE include)
target_compile_options(test-maybe PRIVATE
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

add_test(test-maybe test-maybe)


add_executable(test-maybe-copies test-copies.cc)
target_compile_features(test-maybe-copies PRIVATE cxx_std_17)
target_include_directories(test-maybe-copies PRIVATE include)
target_compile_options(test-maybe-copies PRIVATE
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

add_test(test-maybe-copies test-maybe-copies)
