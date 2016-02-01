CMAKE_MINIMUM_REQUIRED( VERSION 2.8 )

project(ball_detector)

add_definitions(-std=c++11)
set(CMAKE_EXPORT_COMPILE_COMMANDS 1)

include(FindPkgConfig)
find_package(OpenCV REQUIRED core highgui)

include_directories(include)

add_library(ball_detector_lib SHARED
  src/ball_detector.cpp
)

add_executable(ball_detector
  src/main.cpp
)

target_link_libraries(ball_detector
  ball_detector_lib
  ${OpenCV_LIBS}
)
