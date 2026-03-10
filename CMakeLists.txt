cmake_minimum_required(VERSION 3.20)
project(
    Hubris
    VERSION 1.0
    LANGUAGES C CXX
)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED On)
set(CMAKE_CXX_EXTENSIONS Off)
set(CMAKE_EXPORT_COMPILE_COMMANDS on)

include(FetchContent)
FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/refs/heads/main.zip
)

FetchContent_MakeAvailable(googletest)

add_subdirectory(Source/AST)
add_subdirectory(Source/Parser)
add_subdirectory(Source/Tokenizer)

add_executable(Hubris Source/main.cpp)
target_include_directories(Hubris PUBLIC Utils/)
target_link_libraries(Hubris PRIVATE hubrisast hubrisparser hubristokenizer)


# test configs. 

enable_testing()
add_executable(HubrisTests Tests/main.cpp)
target_include_directories(HubrisTests PUBLIC Utils/)
target_link_libraries(HubrisTests PRIVATE gtest_main hubrisast hubrisparser hubristokenizer)
include(GoogleTest)
gtest_discover_tests(HubrisTests)
