cmake_minimum_required(VERSION 2.8)

project(BinaryDescriptors)

find_package (OpenCV REQUIRED)

add_executable(BinaryDescriptors main.cpp)

target_link_libraries(BinaryDescriptors ${OpenCV_LIBS})
