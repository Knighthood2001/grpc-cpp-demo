//
// Created by wu on 25-11-10.
//
#include <iostream>
#include <memory>
#include <string>
#include <grpcpp/grpcpp.h>
#include "calculator.grpc.pb.h"

// 客户端类：封装 gRPC 调用
class CalculatorClient {
 public:
  // 构造函数：接收 gRPC 通道（用于连接服务端）
  CalculatorClient(std::shared_ptr<grpc::Channel> channel) : stub_(Calculator::NewStub(channel)) {}

  // 调用远程 Add 方法
  int32_t Add(int32_t a, int32_t b) {
    AddRequest request;
    request.set_a(a);
    request.set_b(b);

    AddResponse response;
    grpc::ClientContext context;  // 显式指定grpc命名空间

    // 调用远程服务的 Add 方法
    grpc::Status status = stub_->Add(&context, request, &response);  // 显式指定grpc命名空间

    // 检查调用是否成功
    if (status.ok()) {
      return response.result();
    } else {
      std::cout << "调用失败：" << status.error_code() << ": " << status.error_message() << std::endl;
      return -1;
    }
  }

  // 调用远程 Subtract 方法
  int32_t Subtract(int32_t a, int32_t b) {
    SubtractRequest request;
    request.set_a(a);
    request.set_b(b);

    SubtractResponse response;
    grpc::ClientContext context;  // 显式指定grpc命名空间

    grpc::Status status = stub_->Subtract(&context, request, &response);  // 显式指定grpc命名空间

    if (status.ok()) {
      return response.result();
    } else {
      std::cout << "调用失败：" << status.error_code() << ": " << status.error_message() << std::endl;
      return -1;
    }
  }

 private:
  std::unique_ptr<Calculator::Stub> stub_;  // gRPC 客户端 stub（自动生成）
};

int main(int argc, char**argv) {
  // 连接服务端（地址需与服务端一致）
  CalculatorClient client(grpc::CreateChannel(
      "localhost:50051", grpc::InsecureChannelCredentials()));  // 不加密连接

  // 测试加法
  int32_t add_result = client.Add(10, 20);
  std::cout << "10 + 20 = " << add_result << std::endl;

  // 测试减法
  int32_t sub_result = client.Subtract(50, 30);
  std::cout << "50 - 30 = " << sub_result << std::endl;

  return 0;
}