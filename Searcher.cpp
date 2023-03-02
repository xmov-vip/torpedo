#include "Searcher.h"


// 设置搜索区域和搜索参数
void Searcher::setSearchArea(SearchArea area) {
  m_searchArea = area;
}

void Searcher::setSearchParams(SearchParams params) {
  m_searchParams = params;
}

// 模拟搜索器在目标区域进行搜索
TargetSearchResult Searcher::search(TargetArea area, double time)
{
  // 在搜索区域内随机选择一个点
  double x = area.center.x + (double)rand() / RAND_MAX * 2.0 * m_searchArea.radius - m_searchArea.radius;
  double y = area.center.y + (double)rand() / RAND_MAX * 2.0 * m_searchArea.radius - m_searchArea.radius;
  double z = area.center.z + (double)rand() / RAND_MAX * 2.0 * m_searchArea.radius - m_searchArea.radius;

  // 计算距离
  double distance = sqrt(pow(x - area.center.x, 2) + pow(y - area.center.y, 2) + pow(z - area.center.z, 2));

  // 判断是否搜索到目标
  if (distance <= area.radius) {
    // 模拟搜索到目标
    Position position = {x, y, z};
    Velocity velocity = {0, 0, 0};
    double size = 1.0;
    TargetState state = {position, velocity, size};
    return {true, state};
  } else {
    // 模拟未搜索到目标
    return {false, {}};
  }
}

double Searcher::computeGaussian(const double &mu, const double &sigma, const double &x)
{
  const double exponent = -(x - mu) * (x - mu) / (2.0 * sigma * sigma);
  return exp(exponent) / (sigma * sqrt(2.0 * M_PI));
}
