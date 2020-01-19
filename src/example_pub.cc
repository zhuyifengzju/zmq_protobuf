#include "zmq.hpp"
#include "img.pb.h"
#include <string>
int main(){
  zmq::context_t context(1);
  zmq::socket_t publisher(context, ZMQ_PUB);

  publisher.bind("tcp://*:5555");

  img::gray_img gray_img;
  gray_img.set_width(128);
  gray_img.set_height(128);
  gray_img.set_img_data(std::string("this is a test string"));
  std::string msg_str;
  gray_img.SerializeToString(&msg_str);

  while (true){
    // !!! Message must be built every time before you send them
    zmq::message_t message(msg_str.size());
    memcpy(message.data(), msg_str.c_str(), msg_str.size());    
    publisher.send(message);
  }
  return 0;
}
