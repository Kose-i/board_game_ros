#include <vector>
#include <string>

#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/imgcodecs.hpp>

struct Plot_data{
  std::string output_c;
  cv::Point left_up;
  cv::Point right_down;
  cv::Scalar color;
};

int main(int argc, char** argv){
  cv::Mat target_img = cv::Mat::zeros(480, 640, CV_8UC1);

  std::vector<Plot_data> pack_data(9);
  for (int i {};i < 7;++i) {
    pack_data[i].output_c = '1' + i;
    pack_data[i].left_up = cv::Point();
    pack_data[i].right_down = cv::Point();
    pack_data[i].color = cv::Scalar(255, 255, 255);//white color
  }

  for (auto& e : pack_data) {
    cv::putText(target_img, e.output_c, e.left_up, cv::FONT_HERSHEY_SIMPLEX, 1.2, cv::Scalar(0, 200, 0), 2, CV_AA);
    //cv::putText(img, "OpenCV", cv::Point(50,50), face[0], 1.2, cv::Scalar(0,0,200), 2, CV_AA);
  }

  cv::namedWindow("target");
  while(cv::waitKey(1) != 'q') {
    cv::imshow("target", target_img);
  }
  //cv::putText(target_img, )
}
