cmake_minimum_required(VERSION 3.10)
project(NEURAL_NETWORK_SEAL VERSION 1.1.0 LANGUAGES CXX)

set(CMAKE_CXX_FLAGS "-g -fpermissive")

include(common.cmake)


###=======================================================================
add_library(server_grpc_proto
  "${CMAKE_CURRENT_BINARY_DIR}/server.pb.cc"
  "${CMAKE_CURRENT_BINARY_DIR}/server.pb.h"
  "${CMAKE_CURRENT_BINARY_DIR}/server.grpc.pb.cc"
  "${CMAKE_CURRENT_BINARY_DIR}/server.grpc.pb.h"

  "${CMAKE_CURRENT_BINARY_DIR}/model/doubleList.pb.cc"
  "${CMAKE_CURRENT_BINARY_DIR}/model/doubleList.pb.h"
  "${CMAKE_CURRENT_BINARY_DIR}/model/doubleList.grpc.pb.cc"
  "${CMAKE_CURRENT_BINARY_DIR}/model/doubleList.grpc.pb.h"

  "${CMAKE_CURRENT_BINARY_DIR}/model/data.pb.cc"
  "${CMAKE_CURRENT_BINARY_DIR}/model/data.pb.h"
  "${CMAKE_CURRENT_BINARY_DIR}/model/data.grpc.pb.cc"
  "${CMAKE_CURRENT_BINARY_DIR}/model/data.grpc.pb.h"

  "${CMAKE_CURRENT_BINARY_DIR}/model/message.pb.cc"
  "${CMAKE_CURRENT_BINARY_DIR}/model/message.pb.h"
  "${CMAKE_CURRENT_BINARY_DIR}/model/message.grpc.pb.cc"
  "${CMAKE_CURRENT_BINARY_DIR}/model/message.grpc.pb.h"

  )


target_link_libraries(server_grpc_proto
  ${_REFLECTION}
  ${_GRPC_GRPCPP}
  ${_PROTOBUF_LIBPROTOBUF}
  )


##################################################
## server

add_executable(server
  controller/server.cpp
)

include_directories(${CMAKE_CURRENT_BINARY_DIR})

target_link_libraries(server PRIVATE

  server_grpc_proto

  ${_REFLECTION}
  ${_GRPC_GRPCPP}
  ${_PROTOBUF_LIBPROTOBUF}

)


target_include_directories(server
  PUBLIC ${PROJECT_SOURCE_DIR}/include
  ${PROJECT_SOURCE_DIR}/build
  )

target_sources(server
    PRIVATE
)

##################################################
## Test Client

add_executable(client
  client.cpp
)

include_directories(${CMAKE_CURRENT_BINARY_DIR})

target_link_libraries(client PRIVATE
  server_grpc_proto

  ${_REFLECTION}
  ${_GRPC_GRPCPP}
  ${_PROTOBUF_LIBPROTOBUF}

)


target_include_directories(client
  PUBLIC ${PROJECT_SOURCE_DIR}/include
  ${PROJECT_SOURCE_DIR}/build
  )

target_sources(client
    PRIVATE
)



