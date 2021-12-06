cmake_minimum_required(VERSION 3.16.3)
project(threadtest)

include_directories(./include)
set(EXECUTABLE_OUTPUT_PATH "${CMAKE_SOURCE_DIR}/bin")
set(LIBRARY_OUTPUT_PATH "${CMAKE_SOURCE_DIR}/lib")
add_subdirectory(src)
add_executable(test "${CMAKE_SOURCE_DIR}/text/t_thread.cpp")
target_link_libraries(test pp_thread pthread)