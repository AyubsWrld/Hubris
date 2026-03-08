set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED On)
set(CMAKE_CXX_EXTENSIONS Off)

add_library(hubrisparser Private/Parser.cpp)

target_sources(hubrisparser 
    PUBLIC 
    Private/ParseError.cpp
)
target_include_directories(
    hubrisparser
    PUBLIC
    Public/
    ${CMAKE_SOURCE_DIR}/Utils
)
