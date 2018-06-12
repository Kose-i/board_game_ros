#include <iostream>
#include <bitset>
#include <thread>
#include <chrono>

#include <ros/ros.h>

#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/imgcodecs.hpp>

#include "quarto/bridge.h"

int global_pin = 10;//parfect not exist
int before_pin = global_pin;

int width = 0;
int height = 0;
std::bitset<9> isexist("111111111");
struct pos{
  int x;
  int y;
  int width;
  int height;
};

std::vector<struct pos> vec(9);

/*void check_isexist()
{
  for (int i {};i < 8;++i) {
    std::cout << ((isexist[i] == true)?1:0);
  }
  std::cout << ' ';
}*/

void callback_mouse(int event, int x, int y, int flags, void*)
{
  //before_pin = global_pin;
  switch(event){
    case CV_EVENT_LBUTTONDOWN:
    case CV_EVENT_RBUTTONDOWN:
      global_pin = (y / ((height + 3)/3))*3 + x / (width/ 3);
      break;
  }
}
/*
void paste_mat_img(cv::Mat src, cv::Mat dst, int x, int y, int copy_width, int copy_height) {
  std::cout << "check\n";
  cv::Mat resized_img;
  cv::resize(src, resized_img, cv::Size(copy_width, copy_height));
  //cv::Mat roi(dst, cv::Rect(y, x, copy_height, copy_width));
  cv::Mat roi= dst(cv::Rect(y, x, copy_height, copy_width));
  resized_img.copyTo(roi);
}
*/
// 画像を画像に貼り付ける関数
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
/*
struct pos{
  int x;
  int y;
  int width;
  int height;
};
*/
void paste_mat_img(cv::Mat src, cv::Mat dst, const struct pos* select) {
  paste_mat_img(src, dst, select->x, select->y, select->width ,select->height);
}

const std::string pin_box[] = {"first", "second", "third", "fourth","fifth","sixth","seventh","eighth","ninth"};

int main(int argc, char** argv){
  ros::init(argc, argv, "quarto_select_pin_client");

  ros::NodeHandle nh;

  cv::VideoCapture cap(0);
  if(!cap.isOpened()) {
    ROS_INFO("Camera can't open");
    return -1;
  }

  cv::Mat img_src = cv::imread("/home/tamura-kosei/works/board_game_ros/src/quarto/img/temp.png", cv::IMREAD_COLOR);
  width = img_src.size().width;
  height = img_src.size().height;
  for (int i {};i < 3;++i) {
    for (int j {}; j < 3;++j) {
      vec[i*3 + j].x = (width* j) / 3;
      vec[i*3 + j].y = (height*i) / 3;
      vec[i*3 + j].width =  width/3;
      vec[i*3 + j].height = height / 3;
    }
  }
  std::this_thread::sleep_for(std::chrono::seconds(5));//Wait client
  //const cv::Mat one_img_src = cv::imread("/home/tamura-kosei/works/board_game_ros/src/quarto/img/one.png");
  //paste_mat_img(one_img_src, img_src, 0, 0, width/3, height/ 3);
  //const cv::Mat two_img_src = cv::imread("/home/tamura-kosei/works/board_game_ros/src/quarto/img/two.png");
  //paste_mat_img(two_img_src, img_src, width/3 , 0, width/3 , height/ 3);
  //const cv::Mat three_img_src = cv::imread("/home/tamura-kosei/works/board_game_ros/src/quarto/img/three.png");
  //paste_mat_img(three_img_src, img_src, 2*width/3, 0, width/3, height/3);

  //const cv::Mat four_img_src = cv::imread("/home/tamura-kosei/works/board_game_ros/src/quarto/img/four.png");
  //paste_mat_img(four_img_src, img_src, 0, height/3, width/3, height/3);
  //const cv::Mat five_img_src = cv::imread("/home/tamura-kosei/works/board_game_ros/src/quarto/img/five.jpg");
  //paste_mat_img(five_img_src, img_src, width/3,height/3,width/3, height/ 3);
  //const cv::Mat six_img_src = cv::imread("/home/tamura-kosei/works/board_game_ros/src/quarto/img/six.jpg");
  //paste_mat_img(six_img_src, img_src, 2*width/3, height/3, width/3, height/ 3);
  //
  //const cv::Mat seven_img_src = cv::imread("/home/tamura-kosei/works/board_game_ros/src/quarto/img/seven.png");
  //paste_mat_img(seven_img_src, img_src, 0, 2*height/3, width/3, height/3);
  //const cv::Mat eight_img_src = cv::imread("/home/tamura-kosei/works/board_game_ros/src/quarto/img/eight.png");
  //paste_mat_img(eight_img_src, img_src, width/3, 2*height/3, width/3, height/ 3);
  //const cv::Mat nine_img_src = cv::imread("/home/tamura-kosei/works/board_game_ros/src/quarto/img/nine.png");
  //paste_mat_img(nine_img_src, img_src, 2*width/3,2*height/3,  width/3, height/3);

  const cv::Mat image_blank = cv::imread("/home/tamura-kosei/works/board_game_ros/src/quarto/img/blank_img.png");

  //cv::Mat image_blank = cv::Mat::zeros(640, 480, CV_16U);
  //paste_mat_img(image_blank, img_src, 0, 0, width/3, height/ 3);
  //cv::imwrite("/home/tamura-kosei/works/board_game_ros/src/quarto/img/blank_img.png", image_blank);

  ROS_INFO("START %s","select_pin" );
  ROS_INFO("%d %d", width, height);

  if(img_src.empty()){
    ROS_INFO("can't open picture");
    return -1;
  }

  cv::namedWindow("img_src");
  cv::setMouseCallback("img_src", &callback_mouse);

  quarto::bridge srv;
  srv.request.str_pin = '0';// = pin_box[global_pin];
  ros::ServiceClient client = nh.serviceClient<quarto::bridge>("select_pin");

  int check{};
  while(cv::waitKey(1) != 'q'){

    cv::imshow("img_src", img_src);
    if(global_pin != before_pin || check > 30){
      check = 0;
      if(0 <= global_pin && global_pin < 9 && isexist[global_pin] == true){
        srv.request.str_pin = pin_box[global_pin];

        client.call(srv);
        if(srv.response.str_answer == "ng") {
          ROS_INFO("CHECK NG WORD");
          continue;
        } else if (srv.response.str_answer == "ok") {
          ROS_INFO("CHECK OK WORD");
          before_pin = global_pin;
          paste_mat_img(image_blank, img_src, &vec[global_pin]);
          isexist.reset(global_pin);
        }
      }
    }

    std::this_thread::sleep_for(std::chrono::seconds(1));
    ++check;
  }
  ros::spin();
  return 0;
}
