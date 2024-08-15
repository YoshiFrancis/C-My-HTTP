add_library(http STATIC server.cpp)
target_include_directories(http PUBLIC ${PROJECT_SOURCE_DIR}/include)