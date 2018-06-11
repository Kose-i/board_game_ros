#include <ros/ros.h>
#include "quarto/bridge.h"

#include <chrono>
#include <thread>

#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/imgcodecs.hpp>

bool ans = false;
bool is_check(){
  return ans;
}
bool set_pin(quarto::bridge::Request &req,
         quarto::bridge::Response &res)
{
  if(is_check())res.str_answer = "ok";
  else res.str_answer = "ng";
  ans = false;
  return true;
}

void callback_mouse(int event, int x, int y, int flags, void*)
{
  switch(event){
    case CV_EVENT_LBUTTONDOWN:
    case CV_EVENT_RBUTTONDOWN:
      ans = true;
    break;
  }
}
int main(int argc, char **argv)
{
  //test
  ans = true;
  ros::init(argc, argv, "quarto_select_pin_server");
  ros::NodeHandle n;

  cv::Mat zero_img = cv::imread("/home/tamura-kosei/works/board_game_ros/src/quarto/img/five.jpg", cv::IMREAD_COLOR);
  if (zero_img.empty()){
    ROS_INFO("SELECT SERVER ERROR");
    return -1;
  }

  cv::namedWindow("quarto_selectPIN_img_window");
  cv::setMouseCallback("quarto_selectPIN_img_window", &callback_mouse);
  ROS_INFO("Ready to select pin.");

  ros::ServiceServer service = n.advertiseService("select_pin", set_pin);
  /*while(ans == false) {
    cv::imshow("quarto_selectPIN_img_window", zero_img);
  }*/
  
  cv::imshow("quarto_selectPIN_img_window", zero_img);

  //ros::ServiceServer service = n.advertiseService("select_pin", set_pin);
  /*while(cv::waitKey(1) != 'q') {
    cv::imshow("quarto_selectPIN_img_window", zero_img);
    std::this_thread::sleep_for(std::chrono::seconds(3));
  }*/
  


  //ROS_INFO("%s", "select_pin");

  ros::spin();

  return 0;
}
