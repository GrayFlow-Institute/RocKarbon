# RocKarbon

[![Build Status](https://travis-ci.org/GrayFlow-Institute/RocKarbon.svg?branch=master)](https://travis-ci.org/GrayFlow-Institute/RocKarbon)

A distributed safe box server.

## 介绍

### 为什么起一个这个名字

「要硬一点！要强一点！」

所以想了想，比较硬的东西应该就是钻石了！但是写钻石又感觉太僵硬了，于是就想到了「碳」这种元素，但是转头一想——这么简单的，要是和别人冲突了怎么办？岂不是没有新意了吗？于是就结合了「岩」字——于是乎，这个项目就有了一个奇怪的名字——

Rock 岩石 + Carbon 碳 = RocKarbon 岩碳

希望单元测试能让它硬起来！

`> <`

### 功能介绍

一个用 C++ 编写的安全传输的同步服务器，使用了分层架构来编写

- [x] 底层负责安全、存储、日志和通用型工具
- [x] 领域层负责网络和全局环境变量
- [ ] 应用层负责通过配置文件、参数等初始化环境变量，再启动服务器

## 项目结构

```text
.
├── CMakeLists.txt                  // 总 CMakeLists 文件
├── config                          // 一些实例配置(未完成)
├── LICENSE
├── README.md
├── script                          // 一些简单的配置脚本——例如开机启动等等(未完成)
│   ├── python
│   └── shell
├── src                             // 源码目录
│   ├── app                         // 应用层(未完成)
│   ├── base                        // 提供服务的底层
│   │   ├── log                     // Logger 接口和实现，一共两种，Debug 调试模式，一个是 Release 生产模式，并提供工厂返回抽象的 LoggerBase
│   │   │   ├── CMakeLists.txt
│   │   │   ├── DebugLogger.cpp
│   │   │   ├── DebugLogger.h
│   │   │   ├── LoggerFactory.cpp
│   │   │   ├── LoggerFactory.h
│   │   │   └── ReleaseLogger.h
│   │   ├── security                // 安全模块，使用了 cryptopp 库来实现 AES 对称加密，RSA 因为分发公钥的问题暂时没有实现
│   │   │   ├── AESGuard.cpp
│   │   │   ├── AESGuard.h
│   │   │   ├── CMakeLists.txt
│   │   │   ├── HashGuard.cpp
│   │   │   ├── HashGuard.h
│   │   │   ├── RSAGuard.cpp
│   │   │   └── RSAGuard.h
│   │   ├── storage                 // 存储模块，提供了一个基于文件的存储模式，并提供工厂返回抽象 StorageBase
│   │   │   ├── CMakeLists.txt
│   │   │   ├── FileStorage.cpp
│   │   │   ├── FileStorage.h
│   │   │   ├── StorageFactory.cpp
│   │   │   └── StorageFactory.h
│   │   └── tools                   // 一些底层工具，方便上层直接调用
│   │       ├── CMakeLists.txt
│   │       ├── StringUtils.cpp
│   │       └── StringUtils.h
│   ├── CMakeLists.txt              // Run 可执行文件的 CMakeLists
│   ├── field                       // 领域层，用来提供网络和环境变量
│   │   ├── network                 // 主要使用 Boost::asio 网络库来实现同步阻塞的数据交换
│   │   │   ├── CMakeLists.txt
│   │   │   ├── DataExcClient.cpp
│   │   │   ├── DataExcClient.h     // 数据交换的连接，用来实现同步
│   │   │   ├── DataExcService.cpp
│   │   │   ├── DataExcService.h    // 数据交换的服务端，用来实现创建和处理连接
│   │   │   ├── DiscService.cpp
│   │   │   └── DiscService.h       // 发现服务器，用于接受 UDP 广播，并提供 TCP 同步的端口地址——准备和 HiKaRi 的服务注册中心对接
│   │   └── system
│   │       ├── CMakeLists.txt
│   │       ├── Daemon.cpp
│   │       ├── Daemon.h            // 将服务器变成守护进程的接口
│   │       ├── Env.cpp
│   │       └── Env.h               // 环境变量接口，单例，和服务器进程同生命周期
│   ├── interface                   // 各种抽象基类接口、状态、协议常量等等
│   │   ├── ClientBase.h            // 客户端接口
│   │   ├── ClientStatus.h          // 客户端状态类型枚举常量
│   │   ├── LoggerBase.h            // Logger 接口
│   │   ├── LoggerType.h            // Logger 类型枚举常量
│   │   ├── rockarbon_protocol.h    // 协议字符串
│   │   ├── ServerStatus.h          // 服务器状态类型枚举常量
│   │   ├── ServiceBase.h           // 服务器接口
│   │   ├── StorageBase.h           // 存储接口
│   │   └── StorageType.h           // Storage 类型枚举常量
│   └── main.cpp                    // 主程序，加载环境变量、启动服务器等等
└── test                            // 单元测试目录
    ├── CMakeLists.txt              // Test 可执行文件的 CMakeLists
    ├── main_test.cpp               // 启动 GTest
    ├── network                     // 网络模块单元测试
    │   └── test.cpp
    ├── security                    // 安全模块单元测试
    │   └── test.cpp
    ├── storage                     // 存储模块单元测试
    │   └── test.cpp
    ├── system                      // 环境变量模块单元测试
    │   └── test.cpp
    └── tools                       // 工具模块单元测试
        └── test.cpp
```

## 服务器启动流程

1. 从命令行参数中读取配置/加载配置文件到环境变量中
2. 开启一个线程启动发现服务器
3. 开启一个线程启动同步服务器
4. 注册信号处理器函数等等，用来保证数据及时被存储到硬盘
5. 收尾操作
6. 结束

## 同步原理

把所有客户端的所有操作都记录下来，当需要的时候，可以通过操作历史，来复现数据的增删改

同步数据的存储——以 **当前系统时间作为键**，以 **操作记录作为值**，存储在**哈希表**中，并使用一个**辅助有序双链表来**实现记录存在哪些键，以方便找出客户端缺少的同步数据

同步是基于以下几个假设

1. 所有操作的时间都不相等——以毫秒为单位，则两个操作时间重复的概率十分低，可以近似认为唯一——在少量客户端的情况下，当客户端数量增大，则可以使用**按时间排序的** UUID 来作为键
2. 在终端上，时间是同步的——少量客户端的时候，问题不大，如果客户端上升，则可以以服务器端收到数据的时间为基准设置

原理即让客户端逐步发送数据，当服务器不存在这些数据的时候，就将它们保存起来，如果存在，则让客户端停止发送——即已经同步了，如果客户端发送的数据服务器全都有/部分有，则服务器会把自己多出来的数据返回给客户端——即双方都实现了同步的流程

具体的可以参照代码 [网络模块](./src/field/network/DataExcClient.cpp)，和这里[存储模块](./src/base/storage/FileStorage.cpp) 。