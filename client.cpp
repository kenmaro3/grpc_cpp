#include "controller/common.h"

using namespace std;
using namespace grpc;

int main(){
  printf("hello, world!\n");
  //auto channel = CreateChannel("localhost:5001", InsecureChannelCredentials());
  //auto stub = MyServer::NewStub(channel);
  std::shared_ptr<grpc::Channel> channel = CreateChannel("localhost:5001", InsecureChannelCredentials());
  std::unique_ptr< MyServer::Stub> stub = MyServer::NewStub(channel);

  //================================================
  printf("[Client] test1 called.\n");
  ClientContext context_for_test1;
  PB_Message pb_send_for_test1;
  PB_Message reply_for_test1;

  string message_string = "this is message";
  pb_send_for_test1.set_message(message_string);
  stub->test1(&context_for_test1, pb_send_for_test1, &reply_for_test1);
  printf("[Client] test1 done.\n");
  
  //================================================
  printf("[Client] test2 called.\n");
  ClientContext context_for_test2;
  PB_DoubleList pb_send_for_test2;
  PB_DoubleList reply_for_test2;

  vector<double> tmp1 = {1,2,3};
  google::protobuf::RepeatedField<double> tmp2{tmp1.begin(), tmp1.end()};
  pb_send_for_test2.data() = tmp2;
  stub->test2(&context_for_test2, pb_send_for_test2, &reply_for_test2);

  vector<double> tmp2_2(reply_for_test2.data().size());
  for(int i=0; i<reply_for_test2.data().size(); i++){ tmp2_2[i] = reply_for_test2.data()[i];}
  for(int i=0; i<reply_for_test2.data().size(); i++){ printf("%f, ", tmp2_2[i]);}
  printf("[Client] test2 done.\n");

  //================================================
  printf("[Client] test3 called.\n");
  ClientContext context_for_test3;
  PB_Data pb_send_for_test3;
  PB_Data reply_for_test3;

  vector<PB_DoubleList> tmp3;
  for(int i=0; i<3; i++){
    PB_DoubleList tmp4;
    google::protobuf::RepeatedField<double> tmp5{tmp1.begin(), tmp1.end()};
    tmp4.data() = tmp5;
    tmp3.push_back(tmp4);
  }
  google::protobuf::RepeatedPtrField<PB_DoubleList> tmp6{tmp3.begin(), tmp3.end()};
  pb_send_for_test3.data() = tmp6;

  stub->test3(&context_for_test3, pb_send_for_test3, &reply_for_test3);
  printf("[Client] test3 done.\n");
}
