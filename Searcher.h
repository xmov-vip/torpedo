#ifndef SEARCHER_H
#define SEARCHER_H

#include "Target.h"
#include "SearchArea.h"
#include "SearchParams.h"
#include "TargetSearchResult.h"

// 搜索器类，负责搜索水下目标并确定其位置信息
class Searcher {
public:
    // 设置搜索区域和搜索参数
    virtual void setSearchArea(SearchArea area) = 0;
    virtual void setSearchParams(SearchParams params) = 0;

    // 在目标区域进行搜索，返回搜寻结果
    virtual TargetSearchResult search(TargetArea area, double time) = 0;
};

#endif // SEARCHER_H
