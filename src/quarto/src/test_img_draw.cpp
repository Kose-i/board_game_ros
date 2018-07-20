#include <ros/ros.h>

#include <thread>
#include <chrono>
#include <bitset>
#include <vector>

#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/imgcodecs.hpp>

#include "quarto/string_msgs.h"

int width = 0;
int heigh = 0;
std::bitset<9> is_not_blank("111111111");

struct pos{
  int x;
  int y;
  int width;
  int heigh;
};

std::vector<struct pos> vec(9);

int global_pin{};
int before_pin{};

void callback_mouse(int event, int x, int y, int flags, void*)
{
  switch(event){
    case CV_EVENT_LBUTTONDOWN:
    case CV_EVENT_RBUTTONDOWN:
      ROS_INFO("x:%d y:%d",x, y);
      global_pin = 0*x/ (width/3) + 3*y/ (heigh/3);
      ROS_INFO("global_pin:%d before_pin:%d",global_pin, before_pin);
      break;
  }
}
/*
void paste_mat_img(cv::Mat src, cv::Mat dst, int x, int y, int copy_width, int copy_heigh) {
  std::cout << "check\n";
  cv::Mat resized_img;
  cv::resize(src, resized_img, cv::Size(copy_width, copy_heigh));
  //cv::Mat roi(dst, cv::Rect(y, x, copy_heigh, copy_width));
  cv::Mat roi= dst(cv::Rect(y, x, copy_heigh, copy_width));
  resized_img.copyTo(roi);
}
*/
// 画像を画像に貼り付ける関数
void paste_mat_img(cv::Mat src, cv::Mat dst, const int& x, const int& y, const int& resize_width, const int& resize_heigh) {

	cv::Mat resized_img;
	cv::resize(src, resized_img, cv::Size(resize_width, resize_heigh));

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
/*
struct pos{
  int x;
  int y;
  int width;
  int heigh;
};
*/
void paste_mat_img(cv::Mat src, cv::Mat dst, const struct pos& select) {
  paste_mat_img(src, dst, select.x, select.y, select.width ,select.heigh);
}

const std::string pin_box[] = {"first_pos", "second_pos", "third_pos", "fourth_pos","fifth_pos","sixth_pos","seventh_pos","eighth_pos","ninth_pos"};

int main(int argc, char** argv){

  ros::init(argc, argv, "quarto_select_pin_client");
  ros::NodeHandle nh;

  cv::Mat img_src = cv::imread("/home/tamura-kosei/works/board_game_ros/src/quarto/img/temp.png", cv::IMREAD_COLOR);
  if (img_src.empty()) {
    ROS_INFO("cant open img_src");
  }

  width = img_src.size().width;
  heigh = img_src.size().height;
  for (int i {};i < 3;++i) {
    for (int j {}; j < 3;++j) {
      vec[i*3 + j].x = (width* j) / 3;
      vec[i*3 + j].y = (heigh*i) / 3;
      vec[i*3 + j].width =  width/3;
      vec[i*3 + j].heigh = heigh / 3;
    }
  }

  const cv::Mat image_blank = cv::imread("/home/tamura-kosei/works/board_game_ros/src/quarto/img/blank_img.png");
  if (image_blank.empty()) {
    ROS_INFO("cant open image_blank");
    return -1;
  }

  paste_mat_img(image_blank, img_src, 0, 0, width/3, heigh/ 3);

  ROS_INFO("START %s","select_pin" );
  ROS_INFO("%d %d", width, heigh);

  cv::namedWindow("img_src");
  cv::setMouseCallback("img_src", &callback_mouse);

  while(cv::waitKey(1) != 'q'){
    cv::imshow("img_src", img_src);
    std::this_thread::sleep_for(std::chrono::milliseconds(1));
    if (before_pin != global_pin && is_not_blank[global_pin]) {
      ROS_INFO("capture blank img");
      paste_mat_img(image_blank, img_src, vec[global_pin]);
      before_pin = global_pin;
    }
  }

  ros::spinOnce();
  return 0;
}
