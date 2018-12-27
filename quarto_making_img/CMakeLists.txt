cmake_minimum_required(VERSION 2.8.3)
project(quarto_making_img)

find_package(catkin REQUIRED COMPONENTS
  roscpp
  OpenCV
)

catkin_package(
  CATKIN_DEPENDS
)

include_directories(
  ${catkin_INCLUDE_DIRS}
  ${OpenCV_INCLUDE_DIRS}
)

add_executable(${PROJECT_NAME}_node src/quarto_making_img.cpp)
target_link_libraries(${PROJECT_NAME}_node
  ${OpenCV_LIBRARIES}
  ${catkin_LIBRARIES}
)
