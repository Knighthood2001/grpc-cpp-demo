cmake_minimum_required(VERSION 3.10)
project(calculator_grpc)

# 设置 C++ 标准（gRPC 需要 C++11 及以上）
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 查找 gRPC 和 protobuf 库（确保系统中已安装）
find_package(Protobuf REQUIRED)
find_package(gRPC REQUIRED)

# -------------------------- 路径配置 --------------------------
# 生成的代码目录（.pb.h/.pb.cc/.grpc.pb.h/.grpc.pb.cc 所在目录）
set(GENERATED_DIR "${CMAKE_CURRENT_SOURCE_DIR}/src/generated")
# 源文件目录（client.cpp 和 server.cpp 所在目录）
set(SRC_DIR "${CMAKE_CURRENT_SOURCE_DIR}/src")
# proto 文件目录（.proto 所在目录，可选，用于后续重新生成代码）
set(PROTO_DIR "${CMAKE_CURRENT_SOURCE_DIR}/proto")

# -------------------------- 文件列表 --------------------------
# 生成的 gRPC 和 protobuf 代码文件
set(GENERATED_FILES
        "${GENERATED_DIR}/calculator.pb.h"
        "${GENERATED_DIR}/calculator.pb.cc"
        "${GENERATED_DIR}/calculator.grpc.pb.h"
        "${GENERATED_DIR}/calculator.grpc.pb.cc"
)

# 服务端和客户端源文件
set(SERVER_SRC "${SRC_DIR}/server.cpp")
set(CLIENT_SRC "${SRC_DIR}/client.cpp")

# -------------------------- 编译配置 --------------------------
# 添加头文件搜索目录（让编译器能找到 generated 里的 .h 文件）
include_directories(${GENERATED_DIR})

# 生成服务端可执行文件
add_executable(server
        ${SERVER_SRC}
        ${GENERATED_FILES}  # 包含生成的代码
)

# 生成客户端可执行文件
add_executable(client
        ${CLIENT_SRC}
        ${GENERATED_FILES}  # 包含生成的代码
)

# -------------------------- 链接依赖 --------------------------
# 服务端链接 gRPC 和 protobuf 库
target_link_libraries(server
        gRPC::grpc++          # gRPC 核心库
        gRPC::grpc++_reflection  # 可选：服务反射（调试用）
        protobuf::libprotobuf   # protobuf 库
)

# 客户端链接相同的库（和服务端依赖一致）
target_link_libraries(client
        gRPC::grpc++
        gRPC::grpc++_reflection
        protobuf::libprotobuf
)