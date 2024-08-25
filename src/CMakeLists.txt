add_library(http STATIC http.cpp reqReader.cpp request.cpp response.cpp)
target_include_directories(http PUBLIC ${PROJECT_SOURCE_DIR}/include)