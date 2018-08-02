#include <vector>
#include <string>

const std::string path_str{"/home/tamura-kosei/works/board_game_ros/src/quarto/img/"};

#include <ros/ros.h>

#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/imgcodecs.hpp>

constexpr int target_size{9};

struct Plot_data{
  std::string output_c;
  cv::Point left_up;//start position
};

int main(int argc, char** argv){
  cv::Mat target_img = cv::Mat::zeros(640, 480, CV_8UC3);
  cv::Mat target_highlight_img = cv::Mat::zeros(640, 480, CV_8UC3);

  cv::imwrite(path_str+"blank_img.png", target_img);

  std::vector<struct Plot_data> pack_data(target_size);
  for (int i {};i < target_size;++i) {
    pack_data[i].output_c = '1' + i;
    pack_data[i].left_up = cv::Point((480/4)*(i%3 + 1), (640/4)*(i/3 + 1));
  }

  cv::Scalar white_color(255,255,255);//white
  cv::Scalar highlight_color(0, 255,255);//yellow
  for (auto& e : pack_data) {
    cv::putText(target_img, e.output_c, e.left_up, cv::FONT_HERSHEY_SIMPLEX, 1.2, white_color, 2, CV_AA);
    cv::putText(target_highlight_img, e.output_c, e.left_up, cv::FONT_HERSHEY_SIMPLEX, 1.2, highlight_color, 2, CV_AA);
  }

  cv::imwrite(path_str+"temp.png", target_img);
  cv::imwrite(path_str+"highlight_temp.png", target_highlight_img);

  cv::namedWindow("target");
  cv::namedWindow("highlight_target");

  ROS_INFO("Push keyboard 'q'");
  while(cv::waitKey(1) != 'q') {
    cv::imshow("highlight_target", target_highlight_img);
    cv::imshow("target", target_img);
  }
}
