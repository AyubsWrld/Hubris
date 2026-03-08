add_library(
    hubristokenizer 
    Private/Context.cpp
    Private/State.cpp
    Private/Tokenizer.cpp
)

target_include_directories(
    hubristokenizer 
    PUBLIC 
    ${CMAKE_CURRENT_SOURCE_DIR}/Public/
)
