cmake_minimum_required(VERSION 3.20)

project(
    Hubris
    VERSION 1.0
    LANGUAGES C CXX
)

add_subdirectory(Source/AST)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED On)
set(CMAKE_CXX_EXTENSIONS Off)
set(CMAKE_EXPORT_COMPILE_COMMANDS on)

add_executable(Hubris Source/main.cpp)
target_link_libraries(Hubris PRIVATE libast)

