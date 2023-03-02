#ifndef TARGET_H
#define TARGET_H

#include "Position.h"
#include "Velocity.h"

// 水下目标类，包括目标位置、速度、大小等属性信息
class Target {
public:
    // 获取目标位置
    virtual Position getPosition() = 0;

    // 获取目标速度
    virtual Velocity getVelocity() = 0;

    // 获取目标大小
    virtual double getSize() = 0;
};

#endif // TARGET_H
