cmake_minimum_required(VERSION 3.5)
project(Crusoe LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(core-files
        crusoe.cpp
        crusoe.hpp
        tests-main.cpp
        tests-helper.hpp
        tests-helper.cpp
        catch.hpp
)

add_executable(tests-stage-1
    tests-crusoe-01.cpp
    ${core-files}
)

add_executable(tests-stage-2
    tests-crusoe-02.cpp
    ${core-files}
)

add_executable(tests-stage-3
    tests-crusoe-03.cpp
    ${core-files}
)

set(binaries
    tests-stage-1
    tests-stage-2
    tests-stage-3
)

foreach(target ${BINARIES})
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

