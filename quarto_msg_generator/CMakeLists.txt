cmake_minimum_required(VERSION 3.0.2)
project(quarto_msg_generator)

set(CMAKE_CXX_STANDARD 11)

find_package(catkin REQUIRED COMPONENTS
  roscpp
  std_msgs
  message_generation
)

#include_directories(${catkin_INCLUDE_DIRS})

add_service_files(
  FILES
  bridge.srv
)

add_message_files(
  FILES
  string_msgs.msg
)

generate_messages(
  DEPENDENCIES
  std_msgs
)

catkin_package()
