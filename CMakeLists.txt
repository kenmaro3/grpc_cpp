cmake_minimum_required(VERSION 3.10)
project(NEURAL_NETWORK_SEAL VERSION 1.1.0 LANGUAGES CXX)

set(CMAKE_CXX_FLAGS "-g -fpermissive")

include(common.cmake)


###=======================================================================
add_library(myserver_grpc_proto
  "${CMAKE_CURRENT_BINARY_DIR}/myserver.pb.cc"
  "${CMAKE_CURRENT_BINARY_DIR}/myserver.pb.h"
  "${CMAKE_CURRENT_BINARY_DIR}/myserver.grpc.pb.cc"
  "${CMAKE_CURRENT_BINARY_DIR}/myserver.grpc.pb.h"

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


target_link_libraries(myserver_grpc_proto
  ${_REFLECTION}
  ${_GRPC_GRPCPP}
  ${_PROTOBUF_LIBPROTOBUF}
  )


##################################################
## myserver

add_executable(myserver
  controller/myserver.cpp
)

include_directories(${CMAKE_CURRENT_BINARY_DIR})

target_link_libraries(myserver PRIVATE

  myserver_grpc_proto

  ${_REFLECTION}
  ${_GRPC_GRPCPP}
  ${_PROTOBUF_LIBPROTOBUF}

)


target_include_directories(myserver
  PUBLIC ${PROJECT_SOURCE_DIR}/include
  ${PROJECT_SOURCE_DIR}/build
  )

target_sources(myserver
    PRIVATE
)

##################################################
## Test Client

add_executable(client
  client.cpp
)

include_directories(${CMAKE_CURRENT_BINARY_DIR})

target_link_libraries(client PRIVATE
  myserver_grpc_proto

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



