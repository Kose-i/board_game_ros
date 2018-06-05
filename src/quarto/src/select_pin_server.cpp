#include <ros/ros.h>
#include "quarto/bridge.h"

bool add(quarto::bridge::Request &req,
         quarto::bridge::Response &res)
{
  ROS_INFO("%s", req.str_pin.c_str());
  res.str_answer = "ok";
  return true;
}

int main(int argc, char **argv)
{
  ros::init(argc, argv, "quarto_select_pin_server");
  ros::NodeHandle n;

  ros::ServiceServer service = n.advertiseService("select_pin", add);
  ROS_INFO("Ready to select pin.");
  ros::spin();

  return 0;
}
