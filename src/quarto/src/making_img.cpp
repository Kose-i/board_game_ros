#include <vector>
#include <string>

#include <ros/ros.h>

#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/imgcodecs.hpp>

#define SIZE 9

struct Plot_data{
  std::string output_c;
  cv::Point left_up;//start position
  cv::Scalar color;
};

int main(int argc, char** argv){
  cv::Mat target_img = cv::Mat::zeros(640, 480, CV_8UC3);
  cv::imwrite("/home/tamura-kosei/works/board_game_ros/src/quarto/img/blank_img.png", target_img);

  std::vector<struct Plot_data> pack_data(9);
  for (int i {};i < SIZE;++i) {
    pack_data[i].output_c = '1' + i;
    pack_data[i].left_up = cv::Point((480/4)*(i%3 + 1), (640/4)*(i/3 + 1));
    pack_data[i].color = cv::Scalar(255, 255, 255);//white color
  }

  for (auto& e : pack_data) {
    cv::putText(target_img, e.output_c, e.left_up, cv::FONT_HERSHEY_SIMPLEX, 1.2, e.color, 2, CV_AA);
    //cv::putText(target_img, e.output_c,cv::Point(50,50) , cv::FONT_HERSHEY_SIMPLEX, 1.2, cv::Scalar(0, 0, 200), 2, CV_AA);
    //cv::putText(img, "OpenCV", cv::Point(50,50), face[0], 1.2, cv::Scalar(0,0,200), 2, CV_AA);
  }

  cv::imwrite("/home/tamura-kosei/works/board_game_ros/src/quarto/img/temp.png", target_img);

  cv::namedWindow("target");
  ROS_INFO("Push keyboard 'q'");
  while(cv::waitKey(1) != 'q') {
    cv::imshow("target", target_img);
  }
}
