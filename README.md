鱼雷弹道模拟器
这是一个鱼雷弹道模拟器，可以模拟鱼雷在水下的弹道运动。该模拟器基于C++编写，提供了简单易用的接口。

功能
该模拟器提供以下功能：

模拟鱼雷的弹道运动；
搜索水下目标，并计算弹道导引信息；
判断鱼雷是否命中目标，并计算命中精度。
快速开始
环境要求
操作系统：Windows、Linux或MacOS；
编译器：支持C++98的编译器。
安装
下载代码仓库；
打开终端或命令提示符；
进入代码仓库目录；
编译代码：make。
使用方法
创建鱼雷模拟器对象：TorpedoSimulator simulator = TorpedoSimulator();；
设置鱼雷参数：TorpedoParams params = {...};；simulator.initialize(params);；
设置搜索模式：simulator.setSearchMode(SearchMode::Active);；
进行模拟计算：TorpedoState state = simulator.simulate(0.1);。
接口说明
该模拟器提供以下接口：

TorpedoSimulator
void initialize(TorpedoParams params)：初始化鱼雷模拟器；
void setSearchMode(SearchMode mode)：设置搜索模式；
TorpedoState simulate(double timeStep)：进行一次模拟计算。
Target
Position getPosition()：获取目标位置；
Velocity getVelocity()：获取目标速度；
double getSize()：获取目标大小。
Searcher
void setSearchArea(SearchArea area)：设置搜索区域；
void setSearchParams(SearchParams params)：设置搜索参数；
TargetSearchResult search(TargetArea area, double time)：在目标区域进行搜索。
Guidance
void setGuidanceParams(GuidanceParams params)：设置导引参数；
GuidanceCommand computeGuidanceCommand(TorpedoState state, TargetState target)：计算鱼雷弹道信息。
HitEvaluator
void setHitEvalParams(HitEvalParams params)：设置命中评估参数；
bool isHit(TargetState target, TorpedoState state)：判断鱼雷是否命中目标；
double computeAccuracy(TargetState target, TorpedoState state)：计算命中精度。
贡献者
张三：开发者；
李四：测试员；
王五：文档编写者。
许可证
该项目基于MIT许可证开源。





项目简介
本项目旨在开发一个鱼雷弹道模拟器，可以模拟鱼雷在不同水深、温度、盐度和海流等环境下的运动轨迹。同时，本项目还包括水下目标搜索器、自动导引系统和命中评估器等功能，可为鱼雷的使用和测试提供便利。

项目设计
本项目采用面向对象的设计思路，将整个项目分为五个模块：鱼雷模拟器模块、水下目标模块、搜索器模块、自动导引模块和命中评估器模块。各模块之间使用接口进行通信，以提高模块之间的独立性和灵活性。具体接口设计如下：

鱼雷模拟器接口
负责鱼雷弹道运动的模拟和计算。

class TorpedoSimulator {
public:
    // 初始化函数，设置鱼雷的起始参数
    virtual void initialize(TorpedoParams params) = 0;

    // 设置搜索模式
    virtual void setSearchMode(SearchMode mode) = 0;

    // 进行一次模拟计算，返回当前时刻的鱼雷状态
    virtual TorpedoState simulate(double timeStep) = 0;
};


水下目标接口
包括目标位置、速度、大小等属性信息。

class Target {
public:
    // 获取目标位置
    virtual Position getPosition() = 0;

    // 获取目标速度
    virtual Velocity getVelocity() = 0;

    // 获取目标大小
    virtual double getSize() = 0;
};


搜索器接口
负责搜索水下目标并确定其位置信息。

class Searcher {
public:
    // 设置搜索区域和搜索参数
    virtual void setSearchArea(SearchArea area) = 0;
    virtual void setSearchParams(SearchParams params) = 0;

    // 在目标区域进行搜索，返回搜寻结果
    virtual TargetSearchResult search(TargetArea area, double time) = 0;
};


自动导引接口
负责计算鱼雷弹道的航向和速度等信息以实现自动导引。

class Guidance {
public:
    // 设置导引参数
    virtual void setGuidanceParams(GuidanceParams params) = 0;

    // 计算鱼雷弹道信息，返回导引命令
    virtual GuidanceCommand computeGuidanceCommand(TorpedoState state, TargetState target) = 0;
};


命中评估器接口
负责判断鱼雷是否命中目标以及命中的精度等信息。

class HitEvaluator {
public:
  // 设置命中评估参数
  virtual void setHitEvalParams(HitEvalParams params) = 0;

  // 计算鱼雷是否命中目标
  virtual bool isHit(TargetState target, TorpedoState state) = 0;

  // 计算命中精度
  virtual double computeAccuracy(TargetState target, TorpedoState state) = 0;
};