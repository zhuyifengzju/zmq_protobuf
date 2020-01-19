cmake_minimum_required(VERSION 3.8)
set(CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE)

project(zmq_protobuf CXX C)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup(TARGETS)

include(${CMAKE_CURRENT_LIST_DIR}/cmake/protobuf.cmake)

set(PROTO_FILES
  proto/formation.proto
  proto/img.proto)
add_proto_cc_library(shared_protobuf
  PROTO_FILES ${PROTO_FILES}
  PROTO_LIB CONAN_PKG::protobuf)

# CIMG
set(CIMG_REQ pthread X11)
set(CIMG_LIB lib/CImg.h)

# add_executable(formation_server src/formation_server.cc)
# target_link_libraries(formation_server shared_protobuf CONAN_PKG::zmq CONAN_PKG::cppzmq)

add_executable(example_pub src/example_pub.cc)
target_include_directories(example_pub PUBLIC lib)
target_link_libraries(example_pub shared_protobuf CONAN_PKG::zmq CONAN_PKG::cppzmq ${CIMG_REQ})

add_executable(example_sub src/example_sub.cc)
target_include_directories(example_sub PUBLIC lib)
target_link_libraries(example_sub shared_protobuf CONAN_PKG::zmq CONAN_PKG::cppzmq ${CIMG_REQ})

install(TARGETS example_pub
  example_sub
  RUNTIME DESTINATION bin
  LIBRARY DESTINATION lib)
