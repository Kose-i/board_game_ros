#include <ros/ros.h>
#include "quarto/bridge.h"

#include <chrono>
#include <thread>
#include <bitset>
#include <vector>
#include <string>

#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/imgcodecs.hpp>

int width{};
int height{};

struct pos{
  int x;
  int y;
  int width;
  int height;
};


#include <iostream>

void paste_mat_img(cv::Mat src, cv::Mat dst, const int& x, const int& y, const int& resize_width, const int& resize_height) {

	cv::Mat resized_img;
	cv::resize(src, resized_img, cv::Size(resize_width, resize_height));

	if (x >= dst.cols || y >= dst.rows) return;
	int w = (x >= 0) ? std::min(dst.cols - x, resized_img.cols) : std::min(std::max(resized_img.cols + x, 0), dst.cols);
	int h = (y >= 0) ? std::min(dst.rows - y, resized_img.rows) : std::min(std::max(resized_img.rows + y, 0), dst.rows);
	int u = (x >= 0) ? 0 : std::min(-x, resized_img.cols - 1);
	int v = (y >= 0) ? 0 : std::min(-y, resized_img.rows - 1);
	int px = std::max(x, 0);
	int py = std::max(y, 0);
    //std::cout << x << ' ' << y << '\n';
    //std::cout << w << ' ' << h << ' ' << u << ' ' << v << ' ' << px << ' ' << py << '\n';

	cv::Mat roi_dst = dst(cv::Rect(px, py, w, h));
	cv::Mat roi_resized = resized_img(cv::Rect(u, v, w, h));
	roi_resized.copyTo(roi_dst);
}
std::vector<struct pos> vec(9);

bool ans = false;
bool is_check(){
  return ans;
}
void paste_mat_img(cv::Mat src, cv::Mat dst, const struct pos* select) {
  paste_mat_img(src, dst, select->x, select->y, select->width ,select->height);
}

const std::vector<std::string> pin_box = {"first", "second", "third", "fourth","fifth","sixth","seventh","eighth","ninth"};

bool set_pin(quarto::bridge::Request &req,
         quarto::bridge::Response &res)
{
  //if(ans)res.str_answer = "ok";
  //else res.str_answer = "ng";
  res.str_answer = "ng";
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
  const cv::Mat zero_img = cv::imread("/home/tamura-kosei/works/board_game_ros/src/quarto/img/blank_img.png");
  if (zero_img.empty()){
    ROS_INFO("SELECT SERVER ERROR");
    return -1;
  }
  cv::namedWindow("quarto_selectPIN_img_window");
  cv::setMouseCallback("quarto_selectPIN_img_window", &callback_mouse_select);

  ROS_INFO("Ready to select pin.");

  ros::ServiceServer service = nh.advertiseService("select_pin", set_pin);
  while (cv::waitKey(1) !=  'q') {
    //ros::ServiceServer service = nh.advertiseService("select_pin", set_pin);
    cv::imshow("quarto_selectPIN_img_window", zero_img);
    //ros::spinOnce();
  }

  ros::spin();

  return 0;
}
