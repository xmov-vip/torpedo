#include "HitEvaluator.h"

void SimpleHitEvaluator::setHitEvalParams(HitEvalParams params) {
  m_params = params;
}

bool SimpleHitEvaluator::isHit(TargetState target, TorpedoState state) {
  // 计算鱼雷和目标之间的距离
  double distance = sqrt(pow(state.position.x - target.position.x, 2)
                         + pow(state.position.y - target.position.y, 2)
                         + pow(state.position.z - target.position.z, 2));

  // 判断距离是否小于目标大小和鱼雷大小的一半之和
  return distance <= (target.size + m_params.torpedoSize) / 2;
}

double SimpleHitEvaluator::computeAccuracy(TargetState target, TorpedoState state) {
  // 计算鱼雷和目标之间的距离
  double distance = sqrt(pow(state.position.x - target.position.x, 2)
                         + pow(state.position.y - target.position.y, 2)
                         + pow(state.position.z - target.position.z, 2));

  // 如果鱼雷未命中目标，返回负无穷
  if (!isHit(target, state)) {
    return -std::numeric_limits<double>::infinity();
  }
  // 计算命中精度
  return m_params.accuracyConstant - m_params.accuracyFactor * distance;
}
