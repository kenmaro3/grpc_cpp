#include "common.h"

using namespace std;
using namespace grpc;

class MyServerServiceImpl final : public MyServer::Service {

  Status test1(ServerContext* context, const PB_Message* request, PB_Message* reply) override {
    printf("[ServerService: test1] called.\n");


    printf("[ServerService: test1] done.\n");
   
    return Status::OK;
  }

  Status test2(ServerContext* context, const PB_DoubleList* request, PB_DoubleList* reply) override {
    printf("[ServerService: test2] called.\n");


    printf("[ServerService: test2] done.\n");
   
    return Status::OK;
  }

  Status test3(ServerContext* context, const PB_Data* request, PB_Data* reply) override {
    printf("[ServerService: test3] called.\n");


    printf("[ServerService: test3] done.\n");
   
    return Status::OK;
  }



};

void RunServer() {
  std::string server_address("0.0.0.0:5001");
  MyServerServiceImpl service;

  grpc::EnableDefaultHealthCheckService(true);
  grpc::reflection::InitProtoReflectionServerBuilderPlugin();
  ServerBuilder builder;
  // Listen on the given address without any authentication mechanism.
  builder.AddListeningPort(server_address, grpc::InsecureServerCredentials());
  builder.SetMaxReceiveMessageSize(2000000000);
  builder.SetSyncServerOption(ServerBuilder::SyncServerOption::NUM_CQS, 1);
  builder.SetSyncServerOption(ServerBuilder::SyncServerOption::MIN_POLLERS, 3);
  builder.SetSyncServerOption(ServerBuilder::SyncServerOption::MAX_POLLERS, 4);
  builder.SetSyncServerOption(ServerBuilder::SyncServerOption::CQ_TIMEOUT_MSEC, 10000);
  // Register "service" as the instance through which we'll communicate with
  // clients. In this case it corresponds to an *synchronous* service.
  builder.RegisterService(&service);
  // Finally assemble the server.
  std::unique_ptr<Server> server(builder.BuildAndStart());
  std::cout << "Server listening on " << server_address << std::endl;

  // Wait for the server to shutdown. Note that some other thread must be
  // responsible for shutting down the server for this call to ever return.
  server->Wait();
}


int main(int argc, char** argv) {
  printf("hello, world\n");
  RunServer();
  return 0;
}



