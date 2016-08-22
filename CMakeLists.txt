cmake_minimum_required(VERSION 3.5)
project(AgeTest)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp)
add_executable(AgeTest ${SOURCE_FILES})

find_package(OpenCV COMPONENTS core highgui imgproc video objdetect REQUIRED)

target_link_libraries(AgeTest ${OpenCV_LIBS}  crowdsight)