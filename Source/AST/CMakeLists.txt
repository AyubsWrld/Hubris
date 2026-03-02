add_library(libast Private/Empty.cpp)
target_include_directories(libast PUBLIC Public/ {CMAKE_SOURCE_DIR}/Utils)
