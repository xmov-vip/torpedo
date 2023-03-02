#include "ParticleFilterSearch.h"



TargetSearchResult ParticleFilterSearch::search(TargetArea area, double time) {
  // 使用粒子滤波器进行搜索
  std::vector<Position> positions = filter(area, time);

  // 根据粒子权重计算估计的目标位置
  double weightSum = 0.0;
  Position estimatedPos = {0, 0};
  for (int i = 0; i < m_particles.size(); ++i) {
    weightSum += m_particles[i].weight;
    estimatedPos.x += m_particles[i].position.x * m_particles[i].weight;
    estimatedPos.y += m_particles[i].position.y * m_particles[i].weight;
  }
  if (weightSum > 0.0) {
    estimatedPos.x /= weightSum;
    estimatedPos.y /= weightSum;
  }

  // 返回结果
  TargetSearchResult result;
  result.estimatedPosition = estimatedPos;
  result.positions = positions;

  return result;
}

std::vector<Position> ParticleFilterSearch::filter(const TargetArea &area, double time)
{
  // 生成初始的粒子
  std::vector<Particle> particles(m_numParticles);
  for (int i = 0; i < m_numParticles; i++)
  {
    particles[i].pos = Position(area.center.x + (double)rand() / RAND_MAX * 2.0 * m_searchArea.radius - m_searchArea.radius,
                                area.center.y + (double)rand() / RAND_MAX * 2.0 * m_searchArea.radius - m_searchArea.radius);
    particles[i].vel = Velocity(0.0, 0.0);
    particles[i].weight = 1.0 / m_numParticles;
  }
  // 迭代更新粒子
  for (int t = 0; t < m_numIterations; t++) {
    // 预测粒子位置和速度
    for (int i = 0; i < m_numParticles; i++) {
      particles[i].predict(m_timeStep);
    }

    // 更新粒子权重
    for (int i = 0; i < m_numParticles; i++) {
      particles[i].weight = calculateParticleWeight(particles[i], area, time);
    }

    // 根据粒子权重进行选择和重采样
    std::vector<Particle> resampledParticles(m_numParticles);
    double beta = 0.0;
    int index = rand() % m_numParticles;
    double maxWeight = *std::max_element(particles.begin(), particles.end(), [](const Particle& p1, const Particle& p2) { return p1.weight < p2.weight; }).weight;

    for (int i = 0; i < m_numParticles; i++) {
      beta += (double)rand() / RAND_MAX * 2.0 * maxWeight;
      while (beta > particles[index].weight) {
        beta -= particles[index].weight;
        index = (index + 1) % m_numParticles;
      }
      resampledParticles[i] = particles[index];
      resampledParticles[i].weight = 1.0 / m_numParticles;
    }
    particles = resampledParticles;
  }

  // 计算粒子的平均值作为最终估计
  std::vector<Position> estimatedPositions(m_numParticles);
  for (int i = 0; i < m_numParticles; i++) {
    estimatedPositions[i] = particles[i].pos;
  }

  return estimatedPositions;

}
