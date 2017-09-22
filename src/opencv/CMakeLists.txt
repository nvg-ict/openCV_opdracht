cmake_minimum_required(VERSION 2.8.3)
project(opencv)

add_definitions(-std=c++11)

## Find catkin macros and libraries
## if COMPONENTS list like find_package(catkin REQUIRED COMPONENTS xyz)
## is used, also find other catkin packages
find_package(catkin REQUIRED
	roscpp
)

find_package( OpenCV 3 REQUIRED)

## System dependencies are found with CMake's conventions
# find_package(Boost REQUIRED COMPONENTS system)


catkin_package(
  CATKIN_DEPENDS
)

include_directories(
  ${catkin_INCLUDE_DIRS}
  ${OpenCV_INCLUDE_DIRS} 
)

add_executable(opencv_opdracht
main.cpp
BestandInlezen.cpp
Calibration.cpp
ColorDetection.cpp
CommandLineParser.cpp
DetectShape.cpp
MainApplication.cpp
VideoCapture.cpp
)

add_dependencies(opencv_opdracht opencv_gencpp)

target_link_libraries(opencv_opdracht 
${catkin_LIBRARIES}
${OpenCV_LIBS}
)
