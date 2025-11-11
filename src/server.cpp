//
// Created by wu on 25-11-10.
//
// 标准库头文件
#include <iostream>
#include <memory>
#include <string>
#include <grpcpp/grpcpp.h>
#include "calculator.grpc.pb.h"

// 实现 Calculator 服务
class CalculatorServiceImpl final : public Calculator::Service {
  // 重写 Add 方法：处理加法请求
  grpc::Status Add(grpc::ServerContext* context, const AddRequest* request,
             AddResponse* response) override {
    int32_t result = request->a() + request->b();  // 计算 a + b
    response->set_result(result);                  // 设置响应结果
    std::cout << "收到加法请求：" << request->a() << " + " << request->b() 
              << " = " << result << std::endl;
    return grpc::Status::OK;  // 返回成功状态
  }

  // 重写 Subtract 方法：处理减法请求
  grpc::Status Subtract(grpc::ServerContext* context, const SubtractRequest* request,
                  SubtractResponse* response) override {
    int32_t result = request->a() - request->b();  // 计算 a - b
    response->set_result(result);                  // 设置响应结果
    std::cout << "收到减法请求：" << request->a() << " - " << request->b() 
              << " = " << result << std::endl;
    return grpc::Status::OK;  // 返回成功状态
  }
};

// 启动服务端
void RunServer() {
  std::string server_address("0.0.0.0:50051");  // 监听地址和端口
  CalculatorServiceImpl service;                // 实例化服务实现

  // 配置服务端
  grpc::ServerBuilder builder;
  builder.AddListeningPort(server_address, grpc::InsecureServerCredentials());  // 不加密连接
  builder.RegisterService(&service);  // 注册服务

  // 启动服务
  std::unique_ptr<grpc::Server> server(builder.BuildAndStart());
  std::cout << "服务端启动，监听地址：" << server_address << std::endl;

  // 阻塞等待服务结束（按 Ctrl+C 退出）
  server->Wait();
}

int main(int argc, char**argv) {
  RunServer();
  return 0;
}