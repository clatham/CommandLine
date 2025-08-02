cmake_minimum_required(VERSION 3.10)


project(CommandLine)


if("${CMAKE_SOURCE_DIR}" STREQUAL "${CMAKE_BINARY_DIR}")
    message(FATAL_ERROR "In-source builds are not allowed.  Change directory to a different location and build again.")
endif()


add_compile_options($<$<CXX_COMPILER_ID:MSVC>:/MP>)


set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(NOT MSVC)
    set(CMAKE_CXX_EXTENSIONS OFF)
endif()


add_executable(CommandLine
    src/CommandLine.cpp
    src/main.cpp
)
