cmake_minimum_required(VERSION 3.8)
set(CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE)

project(zmq_protobuf CXX C)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup(TARGETS)

include(${CMAKE_CURRENT_LIST_DIR}/cmake/protobuf.cmake)

set(PROTO_FILES
  proto/formation.proto)
add_proto_cc_library(shared_protobuf
  PROTO_FILES ${PROTO_FILES}
  PROTO_LIB CONAN_PKG::protobuf)
add_executable(formation_server src/formation_server.cc)
target_link_libraries(formation_server shared_protobuf)


install(TARGETS formation_server
  RUNTIME DESTINATION bin
  LIBRARY DESTINATION lib)
