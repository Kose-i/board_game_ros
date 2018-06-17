#include <opencv/opencv.hpp>

struct Plot_data{
  char output_c;
  cv::Point left_up;
  cv::Point right_down;
  cv::Scalar color;
};
int main(){
  cv::Mat target_img = Mat::zeros(480, 640, CV_8UC1);

  std::vector<Plot_data> pack_data(9);
  for (int i {};i < 7;++i) {
    pack_data[i].output_c = '1' + i;
    pack_data[i].left_up = cv::Point();
    pack_data[i].right_down = cv::Point();
    pack_data[i].color = cv::Scalar(255, 255, 255);//white color
  }

  for (auto& e : pack_data) {
    cv::putText(target_img, e.output_c, e.left_up, e.)
  }
  cv::putText(target_img, )
}
