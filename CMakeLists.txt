cmake_minimum_required(VERSION 3.17)
project(OpenPresentation2)

set(CMAKE_CXX_STANDARD 17)

add_executable(static static.cpp)
add_executable(volatile volatile.cpp)

add_executable(this_call this_call.cpp)
target_link_libraries(this_call pthread)

add_executable(basic basic.cpp)
target_link_libraries(basic pthread)
set_target_properties(basic PROPERTIES
        CXX_STANDART 17
        COMPILE_OPTIONS "-fsanitize=thread"
        LINK_OPTIONS "-fsanitize=thread"
)

add_executable(example example.cpp)