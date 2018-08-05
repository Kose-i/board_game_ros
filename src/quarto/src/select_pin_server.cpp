#include <ros/ros.h>
#include "quarto/bridge.h"

#include <chrono>
#include <thread>
#include <bitset>
#include <vector>
#include <string>

#include <opencv2/opencv.hpp>

const std::string path_str{"/home/tamura-kosei/works/board_game_ros/src/quarto/img/"};

int width{};
int height{};

struct pos{
  int x;
  int y;
  int width;
  int height;
};


#include <iostream>

namespace is_check_touch_img{
  bool ans = false;
}
namespace window_name{
  const std::string board_name{"board"};
}

const std::vector<std::string> pin_box = {"first", "second", "third", "fourth","fifth","sixth","seventh","eighth","ninth"};

bool set_pin(quarto::bridge::Request &req,
         quarto::bridge::Response &res)
{
  if(is_check_touch_img::ans)res.str_answer = "ok";
  else res.str_answer = "ng";
  //res.str_answer = "ng";
  ROS_INFO("throw from server");
  is_check_touch_img::ans = false;
  return true;
}

void callback_mouse_select(int event, int x, int y, int flags, void*)
{
  switch(event){
    case CV_EVENT_LBUTTONDOWN:
    case CV_EVENT_RBUTTONDOWN:
      ROS_INFO("touch");
      is_check_touch_img::ans = true;
    break;
  }
}
int main(int argc, char **argv)
{
  //test
  is_check_touch_img::ans = true;
  ros::init(argc, argv, "quarto_select_pin_server");
  ros::NodeHandle nh;
  std::this_thread::sleep_for(std::chrono::seconds(2));
  const cv::Mat board_img = cv::imread(path_str+"board_img.png");
  if (board_img.empty()){
    ROS_INFO("SELECT SERVER ERROR");
    return -1;
  }
  cv::namedWindow(window_name::board_name);
  cv::setMouseCallback(window_name::board_name, &callback_mouse_select);

  ROS_INFO("Ready to select pin.");

  ros::ServiceServer service = nh.advertiseService("select_pin", set_pin);
  while (cv::waitKey(1) !=  'q') {
    cv::imshow(window_name::board_name, board_img);
    ros::spinOnce();
  }

  ros::spin();

  return 0;
}
