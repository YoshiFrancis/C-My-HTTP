cmake_minimum_required(VERSION 3.29) 
set(CMAKE_CXX_STANDARD_REQUIRED 20)
set(CMAKE_CXX_STANDARD 20)

project(c_my_http 
				VERSION 3.29
				LANGUAGES CXX
)

add_subdirectory(src)
add_subdirectory(tests)

add_executable(main main.cpp)

# Fetching Catch2 for unit testing
include(FetchContent)
FetchContent_Declare(Catch2
    GIT_REPOSITORY https://github.com/catchorg/Catch2.git
    GIT_TAG        v3.4.0
)
FetchContent_MakeAvailable(Catch2)

target_link_libraries(tests PUBLIC http)


enable_testing()

add_test(NAME test COMMAND tests)