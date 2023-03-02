#ifndef TORPEDOSIMULATOR_H
#define TORPEDOSIMULATOR_H

#include <vector>
#include "Target.h"
#include "Searcher.h"
#include "Guidance.h"
#include "HitEvaluator.h"



// 鱼雷弹道模拟器类，负责鱼雷弹道运动的模拟和计算
class TorpedoSimulator {
public:
    // 初始化函数，设置鱼雷的起始参数
    virtual void initialize(TorpedoParams params) = 0;

    // 设置搜索模式
    virtual void setSearchMode(SearchMode mode) = 0;

    // 进行一次模拟计算，返回当前时刻的鱼雷状态
    virtual TorpedoState simulate(double timeStep) = 0;
};

// 鱼雷弹道模拟器类
class TorpedoSimulatorImpl : public TorpedoSimulator {
public:
  // 初始化函数，设置鱼雷的起始参数
  void initialize(TorpedoParams params) override;

  // 设置搜索模式
  void setSearchMode(SearchMode mode) override;

  // 进行一次模拟计算，返回当前时刻的鱼雷状态
  TorpedoState simulate(double timeStep) override;

private:
  TorpedoParams m_params;         // 鱼雷初始参数
  SearchMode m_searchMode;        // 搜索模式
  Position m_targetPosition;      // 目标位置
  Velocity m_targetVelocity;      // 目标速度
  double m_targetSize;            // 目标大小
  Searcher m_searcher;            // 搜索器
  Guidance m_guidance;            // 自动导引
  HitEvaluator m_hitEvaluator;    // 命中评估器
};

#endif // TORPEDOSIMULATOR_H
