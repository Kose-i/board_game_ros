#include <ros/ros.h>

#include "quarto/bridge.h"

#include <vector>
#include <string>

int width{};
int height{};

struct pos{
  int x;
  int y;
  int width;
  int height;
};


bool set_pin(quarto::bridge::Request &req,
         quarto::bridge::Response &res)
{
  //if(ans)res.str_answer = "ok";
  //else res.str_answer = "ng";
  res.str_answer = "ng";
  ROS_INFO("throw from server");
  return true;
}

int main(int argc, char **argv) {

  ros::init(argc, argv, "quarto_select_pin_server");
  ros::NodeHandle nh;

  ROS_INFO("Ready to select pin.");

  ros::ServiceServer service = nh.advertiseService("select_pin", set_pin);
  while (true) {
    ros::spinOnce();
  }
  ros::spin();

  return 0;
}
