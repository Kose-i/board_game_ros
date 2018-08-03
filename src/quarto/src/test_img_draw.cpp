#include <thread>
#include <chrono>
#include <bitset>
#include <vector>
#include <string>

#include <ros/ros.h>
#include <opencv2/opencv.hpp>

#include "quarto/string_msgs.h"

const std::string path_str{"/home/tamura-kosei/works/board_game_ros/src/quarto/img/"};

struct pos{
  int x, y;
  int width;
  int height;
};

namespace quarto_img_data{
  int width {};
  int height {};
  std::bitset<9> is_not_blank("111111111");

  std::vector<struct pos> vec(9);

  int global_pin{9};
  int before_pin{9};
}

void callback_mouse(int event, int x, int y, int flags, void*)
{
  switch (event) {
    case CV_EVENT_LBUTTONDOWN:
    case CV_EVENT_RBUTTONDOWN:
      quarto_img_data::global_pin = x/ (quarto_img_data::width/3) + 3*(y/ (quarto_img_data::height/3));
      ROS_INFO("global_pin:%d before_pin:%d",quarto_img_data::global_pin, quarto_img_data::before_pin);
      break;
  }
}



// 画像を画像に貼り付ける関数
void paste_mat_img(cv::Mat src, cv::Mat dst, const int& x, const int& y, const int& resize_width, const int& resize_height) {
  ROS_INFO("%d %d %d %d", x,y,resize_width, resize_height);

	cv::Mat resized_img;
	cv::resize(src, resized_img, cv::Size(resize_width, resize_height));

	if (x >= dst.cols || y >= dst.rows) return;
	int w = (x >= 0) ? std::min(dst.cols - x, resized_img.cols) : std::min(std::max(resized_img.cols + x, 0), dst.cols);
	int h = (y >= 0) ? std::min(dst.rows - y, resized_img.rows) : std::min(std::max(resized_img.rows + y, 0), dst.rows);
	int u = (x >= 0) ? 0 : std::min(-x, resized_img.cols - 1);
	int v = (y >= 0) ? 0 : std::min(-y, resized_img.rows - 1);
	int px = std::max(x, 0);
	int py = std::max(y, 0);
  ROS_INFO("%d %d %d %d px:%d py:%d", w, h, u, v, px, py);

	cv::Mat roi_dst = dst(cv::Rect(px, py, w, h));
	cv::Mat roi_resized = resized_img(cv::Rect(u, v, w, h));
	roi_resized.copyTo(roi_dst);
}

void paste_mat_img(cv::Mat src, cv::Mat dst, const struct pos& select) {
  paste_mat_img(src, dst, select.x, select.y, select.width ,select.height);
}

int main(int argc, char** argv){

  ros::init(argc, argv, "quarto_select_pin_client");
  ros::NodeHandle nh;

  cv::Mat img_src = cv::imread(path_str+"pin_img.png", cv::IMREAD_COLOR);
  if (img_src.empty()) {
    ROS_INFO("cant open img_src");
  }

  quarto_img_data::width = img_src.size().width;
  quarto_img_data::height = img_src.size().height;
  for (int i {};i < 3;++i) {
    for (int j {}; j < 3;++j) {
      quarto_img_data::vec[i*3 + j].x = (quarto_img_data::width* j) / 3;
      quarto_img_data::vec[i*3 + j].y = (quarto_img_data::height*i) / 3;
      quarto_img_data::vec[i*3 + j].width =  quarto_img_data::width/3;
      quarto_img_data::vec[i*3 + j].height = quarto_img_data::height / 3;
    }
  }

  const cv::Mat image_blank = cv::imread(path_str+"blank_img.png");
  if (image_blank.empty()) {
    ROS_INFO("cant open image_blank");
    return -1;
  }

  ROS_INFO("START Test for img paste");
  ROS_INFO("width:%d height:%d", quarto_img_data::width, quarto_img_data::height);

  cv::namedWindow("img_src");
  cv::setMouseCallback("img_src", &callback_mouse);

  while(cv::waitKey(1) != 'q'){
    cv::imshow("img_src", img_src);
    std::this_thread::sleep_for(std::chrono::milliseconds(1));
    if (quarto_img_data::before_pin != quarto_img_data::global_pin && quarto_img_data::is_not_blank[quarto_img_data::global_pin]) {
      ROS_INFO("capture blank img");
      paste_mat_img(image_blank, img_src, quarto_img_data::vec[quarto_img_data::global_pin]);
      quarto_img_data::is_not_blank[quarto_img_data::global_pin] = false;
      quarto_img_data::before_pin = quarto_img_data::global_pin;
      ROS_INFO("delete: %d", quarto_img_data::global_pin + 1);
    }
  }

  ros::spinOnce();
  return 0;
}
