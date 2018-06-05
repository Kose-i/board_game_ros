#include <iostream>
#include <ros/ros.h>

#include <thread>
#include <chrono>

#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/imgcodecs.hpp>

#include "quarto/bridge.h"

int global_pin = 0;
int before_pin = global_pin;
int width = 0;
int height = 0;

void callback_mouse(int event, int x, int y, int flags, void*)
{
  before_pin = global_pin;
  switch(event){
    case CV_EVENT_LBUTTONDOWN:
    case CV_EVENT_RBUTTONDOWN:
      global_pin = (y / ((height + 3)/3))*3 + x / (width/ 3);
      break;
  }
}

const std::string pin_box[] = {"0", "1", "2", "3","4","5","6","7","8","9"};

int main(int argc, char** argv){

  ros::init(argc, argv, "quarto_select_pin_client");

  ros::NodeHandle nh;

  cv::VideoCapture cap(0);
  if(!cap.isOpened()) {
    std::cout << "error\n";
  }

  cv::Mat img_src = cv::imread("/home/tamura-kosei/works/board_game_ros/src/quarto/img/test.jpg", cv::IMREAD_COLOR);

  width = img_src.size().width;
  height = img_src.size().height;
  ROS_INFO("START %s","select_pin" );
  ROS_INFO("%d %d", width, height);

  if(img_src.empty()){
    ROS_INFO("can't open picture");
    return -1;
  }

  cv::namedWindow("img_src");
  cv::setMouseCallback("img_src", &callback_mouse);
  cv::imshow("img_src", img_src);

  quarto::bridge srv;
  srv.request.str_pin = pin_box[global_pin];
  ros::ServiceClient client = nh.serviceClient<quarto::bridge>("select_pin");
  /*
  while(cv::waitKey(1) != 'q') {
    if(global_pin != before_pin && 0 <= global_pin && global_pin <= 9) {
      ROS_INFO("%d" , global_pin);
    }
  }
  */

  ros::Rate r(1);

  //ros::ServiceClient client = nh.serviceClient<quarto::bridge>("select_pin");

  while(cv::waitKey(1) != 'q'){

    if(global_pin != before_pin){
      if(0 <= global_pin && global_pin <= 9){
        srv.request.str_pin = pin_box[global_pin];
        ROS_INFO("Push to server from selectPin client");
        client.call(srv);
      }
      /*

      if(client.call(srv)) {
        ROS_INFO("s");
        ROS_INFO("%s", srv.request.str_pin.c_str());
      }else {
        ROS_INFO("ERROR\n");
        return -1;
      }
      */
    }


    //ros::spin();
    std::this_thread::sleep_for(std::chrono::seconds(5));
    r.sleep();
  }

  ros::spin();
  return 0;
}
