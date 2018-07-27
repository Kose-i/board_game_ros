#include <ros/ros.h>

#include "quarto/bridge.h"

#include <opencv2/opencv.hpp>

#include <vector>
#include <string>
#include <thread>
#include <chrono>
const std::string path_str{"/home/tamura-kosei/works/board_game_ros/src/quarto/img/"};

int width{};
int height{};

struct pos{
  int x;
  int y;
  int width;
  int height;
};

int main(int argc, char **argv) {

  ros::init(argc, argv, "quarto_select_pin_server");
  ros::NodeHandle nh;

  ROS_INFO("Ready to select pin.");

  std::this_thread::sleep_for(std::chrono::seconds(1));

  cv::Mat img = cv::imread(path_str+"blank_img.png");
  cv::namedWindow("test");
  while (true) {
    cv::imshow("test",img);
    std::this_thread::sleep_for(std::chrono::milliseconds(1));
  }
  ros::spin();

  return 0;
}
