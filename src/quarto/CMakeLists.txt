cmake_minimum_required(VERSION 2.8.3)
project(quarto)
set(CMAKE_CXX_STANDARD 11)

find_package(catkin REQUIRED COMPONENTS
  roscpp
  std_msgs
  message_generation
)

find_package(OpenCV REQUIRED)
include_directories( ${catkin_INCLUDE_DIRS} ${OpenCV_INCLUDE_DIRS})



## Generate services in the 'srv' folder
add_service_files(
  FILES
  bridge.srv
)

add_message_files(
  FILES
  string_msgs.msg
)

## Generate added messages and services with any dependencies listed here
generate_messages(
  DEPENDENCIES
  std_msgs  # Or other packages containing msgs
)

catkin_package(
)

include_directories(
  ${catkin_INCLUDE_DIRS}
)

add_executable(${PROJECT_NAME}_select_pin_client src/img_interface_select_pin.cpp)
add_executable(${PROJECT_NAME}_select_pin_server src/select_pin_server.cpp)

add_executable(${PROJECT_NAME}_making_img src/making_img.cpp)

add_executable(${PROJECT_NAME}_test_image src/test_img_draw.cpp)

target_link_libraries(${PROJECT_NAME}_select_pin_client
  ${catkin_LIBRARIES}
  ${OpenCV_LIBRARIES}
)
target_link_libraries(${PROJECT_NAME}_select_pin_server
  ${catkin_LIBRARIES}
  ${OpenCV_LIBRARIES}
)

target_link_libraries(${PROJECT_NAME}_making_img
  ${catkin_LIBRARIES}
  ${OpenCV_LIBRARIES}
)

target_link_libraries(${PROJECT_NAME}_test_image
  ${catkin_LIBRARIES}
  ${OpenCV_LIBRARIES}
)
