#include "zmq.hpp"
#include "img.pb.h"
#include <string>
#include <vector>
#include <google/protobuf/text_format.h>

#include "CImg.h"
using namespace cimg_library;

// see the example here: https://ogbe.net/blog/zmq_helloworld.html
int main(){
  zmq::context_t context(1);
  zmq::socket_t subscriber(context, ZMQ_SUB);
  std::string transport("tcp://localhost:5555");
  subscriber.connect(transport);
  subscriber.setsockopt(ZMQ_SUBSCRIBE, "", 0);
  subscriber.setsockopt(ZMQ_CONFLATE, 1);

  size_t nmsg = 10;
  size_t nrx = 0;

  // std::vector<zmq::pollitem_t> p = {{subscriber, 0, ZMQ_POLLIN, 0}};

  img::gray_img gray_img;
  while (true){
    zmq::message_t recv_msg;

    // zmq::poll(p.data(), 1, -1);
    // if (p[0].revents & ZMQ_POLLIN){
    subscriber.recv(&recv_msg);
    std::string recv_str;
    recv_str.assign(static_cast<char *>(recv_msg.data()), recv_msg.size());
    gray_img.ParseFromString(recv_str);

    std::cout << recv_str.size() << std::endl;
    // print out the text string
    // std::string text_str;
    // google::protobuf::TextFormat::PrintToString(gray_img, &text_str);
    // std::cout << text_str << std::endl;

    auto img_data = reinterpret_cast<const uint8_t*>(gray_img.img_data().c_str());    
    CImg<uint8_t> image(img_data, gray_img.width(), gray_img.height(), 1, 1);
    CImgDisplay main_disp(image);
    while (!main_disp.is_closed()){
      main_disp.wait();
    }
    std::cout << "Width: " << gray_img.width() << " , " << "Height: " << gray_img.height() << std::endl;
    std::cout << static_cast<int>(image(0, 0)) << std::endl;
    std::cout << static_cast<int>(image(1, 1)) << std::endl;
    std::cout << static_cast<int>(image(2, 3)) << std::endl;
    std::cout << static_cast<int>(image(gray_img.width()-1, gray_img.height()-1)) << std::endl;
    
    if (++nrx == nmsg){
      break;
      // }      
    }

  }
  return 0;
}
