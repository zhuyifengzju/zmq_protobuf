#include "zmq.hpp"
#include "img.pb.h"
#include <string>
#include <vector>
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
    // std::string recv_str;
    // recv_str.assign(static_cast<char *>(recv_msg.data()), recv_msg.size());
    // gray_img.ParseFromString(recv_str);
    std::cout << recv_msg.size() << std::endl;
    if (++nrx == nmsg){
      break;
      // }      
    }

  }
  return 0;
}
