#ifndef GUIDANCE_H
#define GUIDANCE_H


#include "Types.h"


///
/// 自动导引类 负责计算鱼雷弹道的航向和速度等信息以实现自动导引
///
class Guidance
{
public:
  ///
  /// \brief setGuidanceParams 设置导引参数
  /// \param params 导引参数
  ///
  virtual void setGuidanceParams(GuidanceParams params);

  ///
  /// \brief computeGuidanceCommand 计算鱼雷弹道信息
  /// \param state
  /// \param target
  /// \return 返回导引命令
  ///
  virtual GuidanceCommand computeGuidanceCommand(TorpedoState state, TargetState target);

private:
  GuidanceParams m_guidanceParams;     // 导引参数
  TorpedoState m_torpedoState;
  TargetState m_targetState;

  ///
  /// \brief predictTargetPosition 计算预测目标的位置
  /// \param timeStep 下一时刻
  ///
  void predictTargetPosition(const double& timeStep);


  ///
  /// \brief predictTorpedoPosition 计算预测鱼雷的位置
  /// \param timeStep 下一时刻
  ///
  void predictTorpedoPosition(const double& timeStep);


  ///
  /// \brief predictTorpedoVelocity 计算预测鱼雷的速度
  /// \param timeStep 下一时刻
  ///
  void predictTorpedoVelocity(const double& timeStep);
};


#endif // GUIDANCE_H
