cmake_minimum_required(VERSION 3.16.3)
project(threadtest)

include_directories(${CMAKE_SOURCE_DIR}/include)
set(EXECUTABLE_OUTPUT_PATH "${CMAKE_SOURCE_DIR}/bin")
set(LIBRARY_OUTPUT_PATH "${CMAKE_SOURCE_DIR}/lib")
add_subdirectory(src)
add_executable(test "${CMAKE_SOURCE_DIR}/test/Eventloop_text.cpp")
target_link_libraries(test pp_thread pthread)