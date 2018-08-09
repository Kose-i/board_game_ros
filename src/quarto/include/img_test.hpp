#ifndef Img_HPP
#define Img_HPP

#include <opencv2/opencv.hpp>

class Img_put{
  public:
    Img_put();
    virtual ~Img_put();
    Img_put(class Img_put&)=delete;
    Img_put(class Img_put&&)=delete;
    //bool operator=()=default;
    void draw_img_on_img();
    const cv::Mat show_img_src()const;
  private:
    cv::Mat img_src;
    void draw_img();
};
#endif
