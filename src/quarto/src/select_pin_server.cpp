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

bool ans = false;
bool is_check(){
  return ans;
}

const std::vector<std::string> pin_box = {"first", "second", "third", "fourth","fifth","sixth","seventh","eighth","ninth"};

bool set_pin(quarto::bridge::Request &req,
         quarto::bridge::Response &res)
{
  if(ans)res.str_answer = "ok";
  else res.str_answer = "ng";
  //res.str_answer = "ng";
  ROS_INFO("throw from server");
  ans = false;
  return true;
}

void callback_mouse_select(int event, int x, int y, int flags, void*)
{
  switch(event){
    case CV_EVENT_LBUTTONDOWN:
    case CV_EVENT_RBUTTONDOWN:
      ROS_INFO("touch");
      ans = true;
    break;
  }
}
int main(int argc, char **argv)
{
  //test
  ans = true;
  ros::init(argc, argv, "quarto_select_pin_server");
  ros::NodeHandle nh;
  std::this_thread::sleep_for(std::chrono::seconds(2));
  const cv::Mat zero_img = cv::imread("blank_img.png");
  if (zero_img.empty()){
    ROS_INFO("SELECT SERVER ERROR");
    return -1;
  }
  cv::namedWindow("quarto_selectPIN_img_window");
  cv::setMouseCallback("quarto_selectPIN_img_window", &callback_mouse_select);

  ROS_INFO("Ready to select pin.");

  ros::ServiceServer service = nh.advertiseService("select_pin", set_pin);
  while (cv::waitKey(1) !=  'q') {
    cv::imshow("quarto_selectPIN_img_window", zero_img);
    ros::spinOnce();
  }

  ros::spin();

  return 0;
}
