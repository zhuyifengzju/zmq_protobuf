#include "formation.pb.h"
#include <vector>
#include <string>

int main(){

  GOOGLE_PROTOBUF_VERIFY_VERSION;
  std::cout << "Hello World" << std::endl;

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

  std::cout << msg_str << std::endl;
  
}
