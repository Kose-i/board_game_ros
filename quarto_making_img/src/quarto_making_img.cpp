#include <vector>
#include <string>

#include <ros/ros.h>

#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/imgcodecs.hpp>

namespace data{
  std::string path_str{"/home/tamura-kosei/"};
  constexpr int target_size{9};
}

struct Plot_data{
  std::string output_c;
  cv::Point left_up;//start position
};

namespace making_img{
  void draw_blank_img();
  void draw_board_img();
  void draw_number(cv::Mat, cv::Scalar);
  void draw_pin_img();
  void draw_coloring_pin_img();
}

int main(int argc, char** argv){

  std::string pt_str;
  ros::init(argc, argv, "param file-path");
  ros::NodeHandle nh_;
  nh_.getParam("/img_file_path", data::path_str);
  nh_.getParam("/img_file_path", pt_str);

std::cout << "pt_str : " << pt_str << '\n';
  std::cout << data::path_str << '\n';
  making_img::draw_blank_img();
  making_img::draw_board_img();
  making_img::draw_pin_img();
  making_img::draw_coloring_pin_img();

  ROS_INFO("Finish make img");
  ros::spin();
}

void making_img::draw_blank_img(){
  cv::Mat blank_img = cv::Mat::zeros(640, 480, CV_8UC3);
  cv::imwrite(data::path_str+"blank_img.png", blank_img);
}
void making_img::draw_board_img(){
  cv::Mat board_img = cv::Mat::zeros(640, 480, CV_8UC3);
  cv::imwrite(data::path_str+"board_img.png",board_img);
}
void making_img::draw_number(cv::Mat target_img, cv::Scalar color) {
  std::vector<struct Plot_data> pack_data(data::target_size);
  for (int i {};i < data::target_size;++i) {
    pack_data[i].output_c = '1' + i;
    pack_data[i].left_up = cv::Point((480/4)*(i%3 + 1), (640/4)*(i/3 + 1));
  }

  for (auto& e : pack_data) {
    cv::putText(target_img, e.output_c, e.left_up, cv::FONT_HERSHEY_SIMPLEX, 1.2, color, 2, CV_AA);
  }
}
void making_img::draw_pin_img(){
  cv::Mat pin_img = cv::Mat::zeros(640, 480, CV_8UC3);
  cv::Scalar white_color(255,255,255);//white
  making_img::draw_number(pin_img,white_color);
  cv::imwrite(data::path_str+"pin_img.png", pin_img);
}
void making_img::draw_coloring_pin_img(){
  cv::Mat coloring_pin_img = cv::Mat::zeros(640, 480, CV_8UC3);
  cv::Scalar yellow_color(0, 255,255);//yellow
  making_img::draw_number(coloring_pin_img, yellow_color);
  cv::imwrite(data::path_str+"coloring_pin_img.png", coloring_pin_img);
}

