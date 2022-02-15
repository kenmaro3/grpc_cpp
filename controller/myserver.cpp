#include "common.h"

using namespace std;
using namespace grpc;

template<typename T>
void print_vec(vector<T> x){
  for(int i=0; i<x.size(); i++){
    cout << x[i] << ", ";
  }
  cout << endl;
}


class MyServerServiceImpl final : public MyServer::Service {

  Status test1(ServerContext* context, const PB_Message* request, PB_Message* reply) override {
    printf("[ServerService: test1] called.\n");

    string message = request->message();
    printf("message: %s\n", message.c_str());

    string message_reply = "this is reply";
    reply->set_message(message_reply);

    printf("[ServerService: test1] done.\n");
    return Status::OK;
  }

  Status test2(ServerContext* context, const PB_DoubleList* request, PB_DoubleList* reply) override {
    printf("[ServerService: test2] called.\n");

    vector<double> tmp(request->data().size());
    for(int i=0; i<request->data().size(); i++) { tmp[i] = request->data()[i];}
    for(int i=0; i<request->data().size(); i++) { tmp[i] += 1;}
    google::protobuf::RepeatedField<double> tmp_field{tmp.begin(), tmp.end()};
    reply->data() = tmp_field;

    printf("[ServerService: test2] done.\n");
   
    return Status::OK;
  }

  Status test3(ServerContext* context, const PB_Data* request, PB_Data* reply) override {
    printf("[ServerService: test3] called.\n");

    vector<vector<double>> tmp1;
    for(int i=0; i<request->data().size(); i++){
      vector<double> tmp2;
      for(int j=0; j<request->data()[i].data().size(); j++){
        tmp2.push_back(request->data()[i].data()[j]);
      }
      tmp1.push_back(tmp2);
    }

    for(int i=0; i<tmp1.size(); i++){
      print_vec<double>(tmp1[i]);
    }

    
    vector<PB_DoubleList> tmp3;
    for(int i=0; i<tmp1.size(); i++){
      PB_DoubleList tmp4;
      google::protobuf::RepeatedField<double> tmp5{tmp1[i].begin(), tmp1[i].end()};
      tmp4.data() = tmp5;
      tmp3.push_back(tmp4);
    }
    google::protobuf::RepeatedPtrField<PB_DoubleList> tmp6{tmp3.begin(), tmp3.end()};

    reply->data() = tmp6;

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



