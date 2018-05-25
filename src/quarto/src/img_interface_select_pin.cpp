#include <iostream>
#include <ros/ros.h>
//#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/core.hpp>

#include "quarto/bridge.h"

int global_pin = 0;
int before_pin = global_pin;
void callback_mouse(int event, int x, int y, int flags, void*)
{
  before_pin = global_pin;
  switch(event){
    case CV_EVENT_LBUTTONDOWN:
    case CV_EVENT_RBUTTONDOWN:
      global_pin = y / 3 + x % 3;
      break;
  }
}

const std::string pin_box[] = {"first", "second", "3", "4","5","6","7","8","9","0"};

int main(int argc, char** argv){

  ros::init(argc, argv, "check_your_select");

  ros::NodeHandle nh;

  cv::VideoCapture cap(0);
  if(!cap.isOpened()) {
    std::cout << "error\n";
  }
  cv::Mat img_src;
  cap >> img_src;
  std::cout << "START\n";

  cv::namedWindow("img_src");
  cv::setMouseCallback("img_src", &callback_mouse);
  cv::imshow("img_src", img_src);

  quarto::bridge srv;
  srv.request.str_pin = pin_box[global_pin];
  ros::ServiceClient client = nh.serviceClient<quarto::bridge>("select_pin");

  while(cv::waitKey(1) != 'q'){

    if(global_pin != before_pin){
      ros::ServiceClient client = nh.serviceClient<quarto::bridge>("select_pin");
      srv.request.str_pin = pin_box[global_pin];
    }

    if(client.call(srv)) {
      ROS_INFO("%s", srv.request.str_pin.c_str());
    }/*else {
      ROS_INFO("ERROR\n");
      return -1;
    }*/

    ros::spin();
  }
  return 0;
}
