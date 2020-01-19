#include "zmq.hpp"
#include "img.pb.h"
#include <string>
#include "CImg.h"
using namespace cimg_library;

int main(){

  CImg<unsigned char> image("example.jpg");
  // CImgDisplay main_disp(image);
  // while (!main_disp.is_closed()){
  //   main_disp.wait();
  // }
  
  zmq::context_t context(1);
  zmq::socket_t publisher(context, ZMQ_PUB);

  publisher.bind("tcp://*:5555");

  img::gray_img gray_img;
  gray_img.set_width(image.width());
  gray_img.set_height(image.height());

  
  gray_img.set_img_data(reinterpret_cast<char*>(image.data()));
  std::cout << image.data() << std::endl;
  std::string msg_str;
  gray_img.SerializeToString(&msg_str);
  while (true){
    // !!! Message must be built every time before you send them
    zmq::message_t message(msg_str.size());
    std::cout << msg_str.size() << std::endl;
    memcpy(message.data(), msg_str.c_str(), msg_str.size());    
    publisher.send(message);
  }
  return 0;
}
