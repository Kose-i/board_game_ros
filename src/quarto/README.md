#This is quarto prac game

img_interface_select_pin によって srvice 経由で pin の番号を select_pin_server に渡す.
select_pin_server は topic_select_spot に topic で 置かれたかを調べる.

SRC-FILE
img_interface_select_pin.cpp
  [target]img for touching 
select_pin_server
  [target]img for touching and draw picture from picture

test_making_img.cpp
  making image needed
test_img_draw.cpp
  testing image backside image


setup
  roslaunch quarto making_img.launch
test
  roslaunch quarto quarto.launch
