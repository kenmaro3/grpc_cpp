DEST_DIR=../build

#
protoc \
 --proto_path=. \
 --grpc_out=${DEST_DIR} --plugin=protoc-gen-grpc=`which grpc_cpp_plugin` server.proto

protoc \
 --proto_path=. \
 --cpp_out=${DEST_DIR} server.proto

##############################################################################
#
protoc \
 --proto_path=. \
 --grpc_out=${DEST_DIR} --plugin=protoc-gen-grpc=`which grpc_cpp_plugin` model/data.proto

protoc \
 --proto_path=. \
 --cpp_out=${DEST_DIR} model/data.proto

#
protoc \
 --proto_path=. \
 --grpc_out=${DEST_DIR} --plugin=protoc-gen-grpc=`which grpc_cpp_plugin` model/doubleList.proto

protoc \
 --proto_path=. \
 --cpp_out=${DEST_DIR} model/doubleList.proto


#
protoc \
 --proto_path=. \
 --grpc_out=${DEST_DIR} --plugin=protoc-gen-grpc=`which grpc_cpp_plugin` model/message.proto

protoc \
 --proto_path=. \
 --cpp_out=${DEST_DIR} model/message.proto
