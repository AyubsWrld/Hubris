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
