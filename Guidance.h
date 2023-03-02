#ifndef GUIDANCE_H
#define GUIDANCE_H


#include "GuidanceParams.h"
#include "GuidanceCommand.h"
#include "TargetState.h"
#include "TorpedoState.h"

// 自动导引类，负责计算鱼雷弹道的航向和速度等信息以实现自动导引
class Guidance {
public:
    // 设置导引参数
    virtual void setGuidanceParams(GuidanceParams params) = 0;

    // 计算鱼雷弹道信息，返回导引命令
    virtual GuidanceCommand computeGuidanceCommand(TorpedoState state, TargetState target) = 0;
};


#endif // GUIDANCE_H
