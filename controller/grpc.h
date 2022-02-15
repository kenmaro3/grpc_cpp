#pragma once

#include <grpcpp/ext/proto_server_reflection_plugin.h>
#include <grpcpp/grpcpp.h>
#include <grpcpp/health_check_service_interface.h>

#include "myserver.grpc.pb.h"

#include <grpc/grpc.h>
#include <grpcpp/channel.h>
#include <grpcpp/client_context.h>
#include <grpcpp/create_channel.h>
#include <grpcpp/security/credentials.h>

#include "model/doubleList.grpc.pb.h"
#include "model/data.grpc.pb.h"
#include "model/message.grpc.pb.h"

using grpc::Server;
using grpc::ServerBuilder;
using grpc::ServerContext;
using grpc::Status;

using grpc::ClientContext;
using grpc::Status;
using grpc::CreateChannel;
using grpc::CreateCustomChannel;
using grpc::InsecureChannelCredentials;
using grpc::ChannelArguments;
using grpc::Channel;
using grpc::ClientContext;


