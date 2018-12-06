cmake_minimum_required(VERSION 3.0.2)
project(quarto)

set(CMAKE_CXX_STANDARD 11)

find_package(catkin REQUIRED COMPONENTS
  roscpp
  std_msgs
  message_generation
)

find_package(OpenCV REQUIRED)
include_directories(include ${catkin_INCLUDE_DIRS} ${OpenCV_INCLUDE_DIRS})

include_directories(
  ${catkin_INCLUDE_DIRS}
  include
)


catkin_package()

#add_executable(${PROJECT_NAME}_lib src/img_test.cpp src/test.cpp)
#
#target_link_libraries(${PROJECT_NAME}_lib
#  ${catkin_LIBRARIES}
#  ${OpenCV_LIBRARIES}
#  include
#)
#
#add_executable(${PROJECT_NAME}_select_pin_client src/img_interface_select_pin.cpp)
#add_executable(${PROJECT_NAME}_select_pin_server src/select_pin_server.cpp)
#
#add_executable(${PROJECT_NAME}_making_img src/test_making_img.cpp)
#
#add_executable(${PROJECT_NAME}_test_image src/test_img_draw.cpp)
#add_executable(${PROJECT_NAME}_test_interface src/test_img_interface_select_pin.cpp)
#
#
#target_link_libraries(${PROJECT_NAME}_select_pin_client
#  ${catkin_LIBRARIES}
#  ${OpenCV_LIBRARIES}
#)
#target_link_libraries(${PROJECT_NAME}_select_pin_server
#  ${catkin_LIBRARIES}
#  ${OpenCV_LIBRARIES}
#)
#
#target_link_libraries(${PROJECT_NAME}_making_img
#  ${catkin_LIBRARIES}
#  ${OpenCV_LIBRARIES}
#)
#
#target_link_libraries(${PROJECT_NAME}_test_image
#  ${catkin_LIBRARIES}
#  ${OpenCV_LIBRARIES}
#)
#target_link_libraries(${PROJECT_NAME}_test_interface
#  ${catkin_LIBRARIES}
#  ${OpenCV_LIBRARIES}
#)
