#include "TorpedoSimulator.h"

#include <vector>



// 实现TorpedoSimulator类
class TorpedoSimulatorImpl : public TorpedoSimulator {
public:
  // 初始化函数，设置鱼雷的起始参数
  virtual void initialize(TorpedoParams params) {
    m_params = params;
    m_currentState.position = params.initialPosition;
    m_currentState.velocity = params.initialVelocity;
    m_currentState.time = 0.0;
  }

  // 设置搜索模式
  virtual void setSearchMode(SearchMode mode) {
    m_searchMode = mode;
  }

  // 进行一次模拟计算，返回当前时刻的鱼雷状态
  virtual TorpedoState simulate(double timeStep) {
    // 更新当前状态
    m_currentState.position.x += m_currentState.velocity.vx * timeStep;
    m_currentState.position.y += m_currentState.velocity.vy * timeStep;
    m_currentState.position.z += m_currentState.velocity.vz * timeStep;
    m_currentState.time += timeStep;

    // 搜索目标
    TargetSearchResult searchResult;
    if (m_searchMode == SEARCH_MODE_ACTIVE) {
      searchResult = m_searcher.search(m_currentState.position, m_params.target, timeStep);
    } else {
      searchResult.target = m_params.target;
      searchResult.timeToTarget = INFINITY;
    }

    // 导引鱼雷
    GuidanceCommand guidanceCommand = m_guidance.computeGuidanceCommand(m_currentState, searchResult);

    // 更新速度
    m_currentState.velocity.vx += guidanceCommand.ax * timeStep;
    m_currentState.velocity.vy += guidanceCommand.ay * timeStep;
    m_currentState.velocity.vz += guidanceCommand.az * timeStep;

    // 判断命中目标
    if (m_hitEvaluator.isHit(m_params.target, m_currentState)) {
      m_currentState.hit = true;
    }

    return m_currentState;
  }
private:
  TorpedoParams m_params;
  SearchMode m_searchMode;
  TorpedoState m_currentState;
  Searcher m_searcher;
  Guidance m_guidance;
  HitEvaluator m_hitEvaluator;
};
