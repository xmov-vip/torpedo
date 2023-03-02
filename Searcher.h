#ifndef SEARCHER_H
#define SEARCHER_H

#include "Target.h"
#include "Types.h"
#include "math.h"


// 搜索器类，负责搜索水下目标并确定其位置信息
class Searcher {
public:
  // 设置搜索区域和搜索参数
  virtual void setSearchArea(SearchArea area);
  virtual void setSearchParams(SearchParams params);

  // 在目标区域进行搜索，返回搜寻结果
  virtual TargetSearchResult search(TargetArea area, double time);

  // 计算搜索的概率密度函数
  double computeGaussian(const double& mu, const double& sigma, const double& x);
};

#endif // SEARCHER_H
