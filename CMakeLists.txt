cmake_minimum_required(VERSION 3.14)
project(ServiceControl)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt5Widgets CONFIG REQUIRED)
find_package(CapnProto)

set(SERVICECONTROL_SRC
  src/ui/main.cpp
  src/ui/servicecontrol.cpp
)
add_executable(servicecontrol ${SERVICECONTROL_SRC})
target_link_libraries(servicecontrol Qt5::Widgets)
install(TARGETS servicecontrol DESTINATION bin)

capnp_generate_cpp(CAPNP_SRCS CAPNP_HDRS src/worker/proto.capnp)
set(SERVICECONTROL_WORKER_SRC
  src/worker/main.cpp
)
add_executable(servicecontrol-worker ${SERVICECONTROL_WORKER_SRC} ${CAPNP_SRCS})
target_link_libraries(servicecontrol-worker PRIVATE Qt5::Core CapnProto::capnp-rpc)
target_include_directories(servicecontrol-worker PRIVATE ${CMAKE_CURRENT_BINARY_DIR})
install(TARGETS servicecontrol-worker DESTINATION bin)
