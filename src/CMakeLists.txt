include_directories(${CMAKE_SOURCE_DIR}/include)
add_library(pp_thread SHARED Thread.cpp Eventloop.cpp Channel.cpp)
