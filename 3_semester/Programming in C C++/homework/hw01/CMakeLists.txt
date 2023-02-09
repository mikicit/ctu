cmake_minimum_required(VERSION 3.5)
project(ArrPicture LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(core-files
        telescope.cpp
        telescope.hpp
        tests-main.cpp
        test-helpers.cpp
        test-helpers.hpp
        catch.hpp
)

#add_executable(ArrPicture main.cpp telescope.cpp telescope.hpp)

add_executable(tests-stage-1
        tests-arr-01.cpp
        ${core-files}
)

add_executable(tests-stage-2
        tests-arr-02.cpp
        ${core-files}
)

add_executable(tests-stage-3
        tests-arr-03.cpp
        ${core-files}
)

add_executable(tests-stage-4
        tests-arr-04.cpp
        ${core-files}
)

set(binaries
        tests-stage-1
        tests-stage-2
        tests-stage-3
        tests-stage-4
)

foreach(target ${binaries})
    if ( CMAKE_CXX_COMPILER_ID MATCHES "Clang|AppleClang|GNU" )
        target_compile_options( ${target} PRIVATE -Wall -Wextra -Wunreachable-code -Wpedantic)
    endif()
    if ( CMAKE_CXX_COMPILER_ID MATCHES "MSVC" )
        target_compile_options( ${target} PRIVATE /W4 )
        target_compile_options( ${target} PRIVATE /utf-8 )
    endif()
endforeach()

enable_testing()
add_test(NAME stage-1 COMMAND tests-stage-1)
add_test(NAME stage-2 COMMAND tests-stage-2)
add_test(NAME stage-3 COMMAND tests-stage-3)
add_test(NAME stage-4 COMMAND tests-stage-4)
