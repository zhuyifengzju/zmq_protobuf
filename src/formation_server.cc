#include "zmq.h"
#include "zmq.hpp"
#include "formation.pb.h"
#include <vector>
#include <string>

int main(){

  GOOGLE_PROTOBUF_VERIFY_VERSION;
  std::cout << "Hello World" << std::endl;

  // Prepare the context and socket
  zmq::context_t context(1);
  zmq::socket_t socket(context, ZMQ_PAIR);

  
  
  int num = 5;
  std::vector<double> pos_x, pos_y;
  for (int i=0; i< 5; i++){
    pos_x.push_back(1.);
    pos_y.push_back(-1.);
  }
  Formation::Formation formation;
  formation.set_num(num);
  *formation.mutable_pos_x() = {pos_x.begin(), pos_x.end()};
  *formation.mutable_pos_y() = {pos_y.begin(), pos_y.end()};

  std::string msg_str;
  formation.SerializeToString(&msg_str);

  zmq::message_t request(msg_str.size());
  memcpy((void*)request.data(), msg_str.c_str(), msg_str.size());

  socket.send(request);
  google::protobuf::ShutdownProtobufLibrary();
  return 0;
}
