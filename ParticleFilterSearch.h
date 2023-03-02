#ifndef PARTICLEFILTERSEARCH_H
#define PARTICLEFILTERSEARCH_H

#include <vector>
#include "Types.h"
#include "Searcher.h"

// 粒子滤波器目标搜索算法类
class ParticleFilterSearch : public Searcher {
public:
  ParticleFilterSearch() {}

  virtual ~ParticleFilterSearch() {}

  // 设置搜索区域和搜索参数
  virtual void setSearchArea(SearchArea area) { m_searchArea = area; }

  virtual void setSearchParams(SearchParams params) { m_searchParams = params; }

  // 在目标区域进行搜索，返回搜寻结果
  virtual TargetSearchResult search(TargetArea area, double time);

private:
  // 粒子
  struct Particle {
    Position position; // 位置
    Velocity velocity; // 速度
    double weight;     // 权重
  };

  // 粒子数
  const int m_numParticles = 100;

  // 粒子集合
  std::vector<Particle> m_particles;

  // 搜索区域和搜索参数
  SearchArea m_searchArea;
  SearchParams m_searchParams;

  // 运动模型方差
  const double m_motionModelVariance = 0.1;

  // 观测模型方差
  const double m_observationModelVariance = 0.5;

  // 粒子滤波器
  std::vector<Position> filter(const TargetArea& area, double time);
};


#endif // PARTICLEFILTERSEARCH_H
