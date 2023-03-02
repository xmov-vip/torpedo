#ifndef MODELPREDICTIVECONTROL_H
#define MODELPREDICTIVECONTROL_H

#include "Types.h"


// 模型预测控制算法实现
class ModelPredictiveControl {
public:
  // 初始化模型预测控制器，设置参数
  void initialize(const MPCParams& params);
  // 计算最优控制输入
  GuidanceCommand calculateControlInput(const TorpedoState& state, const TargetState& target);
private:
  // 计算目标的运动模型
  void calculateTargetModel(const TargetState& target, const double& timeStep);
  // 计算预测目标的位置
  void predictTargetPosition(const double& timeStep);

  // 计算预测鱼雷的位置
  void predictTorpedoPosition(const double& timeStep);




};

#endif // MODELPREDICTIVECONTROL_H
