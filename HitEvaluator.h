#ifndef HITEVALUATOR_H
#define HITEVALUATOR_H

struct HitEvalParams {
    double hitRadius;  // 命中半径
};


// 命中评估器类，负责判断鱼雷是否命中目标以及命中的精度等信息
class HitEvaluator {
public:
  // 设置命中评估参数
  virtual void setHitEvalParams(HitEvalParams params) = 0;

  // 计算鱼雷是否命中目标
  virtual bool isHit(TargetState target, TorpedoState state) = 0;

  // 计算命中精度
  virtual double computeAccuracy(TargetState target, TorpedoState state) = 0;
};




// 命中评估器的具体实现类
class SimpleHitEvaluator : public HitEvaluator {
public:
  // 设置命中评估参数
  virtual void setHitEvalParams(HitEvalParams params);

  // 计算鱼雷是否命中目标
  virtual bool isHit(TargetState target, TorpedoState state);

  // 计算命中精度
  virtual double computeAccuracy(TargetState target, TorpedoState state);
private:
  HitEvalParams m_params;
};


#endif // HITEVALUATOR_H
