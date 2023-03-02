#include "Guidance.h"

void Guidance::setGuidanceParams(GuidanceParams params)
{
    m_guidanceParams = params;
}

// 计算下一时刻目标的位置和速度
void Guidance::predictTargetPosition(const double& timeStep)
{
  Velocity velocity = m_target->getVelocity();
  Position position = m_target->getPosition();

  double x = position.x + velocity.vx * timeStep;
  double y = position.y + velocity.vy * timeStep;
  double z = position.z + velocity.vz * timeStep;

  m_targetState.position = {x, y, z};
  m_targetState.velocity = velocity;
}

// 计算下一时刻鱼雷的位置和速度
void Guidance::predictTorpedoPosition(const double& timeStep)
{
  Velocity velocity = m_torpedoState.velocity;
  Position position = m_torpedoState.position;

  double x = position.x + velocity.vx * timeStep;
  double y = position.y + velocity.vy * timeStep;
  double z = position.z + velocity.vz * timeStep;

  m_torpedoState.position = {x, y, z};
}

// 计算下一时刻鱼雷的速度
void Guidance::predictTorpedoVelocity(const double& timeStep)
{
  // 暂时采用简单模型进行预测
  double ax = m_guidanceCommand.ax;
  double ay = m_guidanceCommand.ay;
  double az = m_guidanceCommand.az;

  Velocity velocity = m_torpedoState.velocity;

  double vx = velocity.vx + ax * timeStep;
  double vy = velocity.vy + ay * timeStep;
  double vz = velocity.vz + az * timeStep;

  m_torpedoState.velocity = {vx, vy, vz};
}


// 计算鱼雷弹道信息，返回导引命令
GuidanceCommand Guidance::computeGuidanceCommand(TorpedoState state, TargetState target)
{
  // 更新当前鱼雷状态和目标状态
  m_torpedoState = state;
  m_targetState = target;

  // 计算预测目标和鱼雷的位置和速度
  predictTargetPosition(m_guidanceParams.timeStep);
  predictTorpedoPosition(m_guidanceParams.timeStep);
  predictTorpedoVelocity(m_guidanceParams.timeStep);

  // 计算目标相对鱼雷的速度和位置
  double dx = m_currentTargetPosition.x - m_currentTorpedoPosition.x;
  double dy = m_currentTargetPosition.y - m_currentTorpedoPosition.y;
  double dz = m_currentTargetPosition.z - m_currentTorpedoPosition.z;
  double dvx = m_currentTargetVelocity.vx - m_currentTorpedoVelocity.vx;
  double dvy = m_currentTargetVelocity.vy - m_currentTorpedoVelocity.vy;
  double dvz = m_currentTargetVelocity.vz - m_currentTorpedoVelocity.vz;

  // 计算命令
  GuidanceCommand command;
  command.ax = m_guidanceParams.Kp * dx + m_guidanceParams.Kv * dvx;
  command.ay = m_guidanceParams.Kp * dy + m_guidanceParams.Kv * dvy;
  command.az = m_guidanceParams.Kp * dz + m_guidanceParams.Kv * dvz;

  // 返回命令
  return command;
}

