cmake_minimum_required(VERSION 3.0.2)
project(quarto_description)

set(CMAKE_CXX_STANDARD 11)

find_package(catkin REQUIRED COMPONENTS
  OpenCV
  roscpp
  quarto_msg_generator
)

include_directories(include 
    ${catkin_INCLUDE_DIRS}
    ${OpenCV_INCLUDE_DIRS}
)

catkin_package(
  CATKIN_DEPENDS
  quarto_msg_generator
)

add_executable(${PROJECT_NAME}_lib src/img_test.cpp src/test.cpp)
add_dependencies(${PROJECT_NAME}_lib ${catkin_EXPORTED_TARGETS})
target_link_libraries(${PROJECT_NAME}_lib
  ${catkin_LIBRARIES}
  ${OpenCV_LIBRARIES}
)

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
