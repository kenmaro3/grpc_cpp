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

  stub->test1(&context_for_test1, pb_send_for_test1, &reply_for_test1);
  printf("[Client] test1 done.\n");
  
  //================================================
  printf("[Client] test2 called.\n");
  ClientContext context_for_test2;
  PB_DoubleList pb_send_for_test2;
  PB_DoubleList reply_for_test2;

  stub->test2(&context_for_test2, pb_send_for_test2, &reply_for_test2);
  printf("[Client] test2 done.\n");

  //================================================
  printf("[Client] test3 called.\n");
  ClientContext context_for_test3;
  PB_Data pb_send_for_test3;
  PB_Data reply_for_test3;

  stub->test3(&context_for_test3, pb_send_for_test3, &reply_for_test3);
  printf("[Client] test3 done.\n");
}
