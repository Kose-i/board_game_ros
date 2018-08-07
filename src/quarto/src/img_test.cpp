#include "img_test.hpp"

/*
class Img_put{
  public:
    Img_put();
    virtual ~Img_put();
    void Img_put(class Img_put)=delete;
    void Img_put(class Img_put)&&=delete;
    void operator=()=default;
    void draw_img_on_img();
    cv::Mat show_img_src()const;
  private:
    cv::Mat img_src;
    void draw_img();
}*/

Img_put::img_put(){}
virtual Img_put::~Img_put(){}
void draw_img_on_img(){}
cv::Mat show_img_src()const{}
