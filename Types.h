#ifndef POSITION_H
#define POSITION_H

// 位置信息
struct Position {
    double x;   // x坐标
    double y;   // y坐标
    double z;   // z坐标
};

// 速度信息
struct Velocity {
    double vx;  // x方向速度
    double vy;  // y方向速度
    double vz;  // z方向速度
};

// 鱼雷参数结构体
struct TorpedoParams {
    Position position;  // 鱼雷的起始位置
    Velocity velocity;  // 鱼雷的起始速度
    double maxSpeed;    // 鱼雷的最大速度
    double maxTurnRate; // 鱼雷的最大转向率
    double maxAcceleration; // 鱼雷的最大加速度
    double maxAngularAcceleration; // 鱼雷的最大角加速度
    double maxAngularVelocity; // 鱼雷的最大角速度
    double radius;  // 鱼雷的半径
};

// 鱼雷状态结构体
struct TorpedoState {
    Position position;  // 鱼雷当前的位置
    Velocity velocity;  // 鱼雷当前的速度
    double heading;     // 鱼雷当前的航向
    double angularVelocity; // 鱼雷当前的角速度
};

// 目标状态结构体
struct TargetState {
    Position position;  // 目标当前的位置
    Velocity velocity;  // 目标当前的速度
    double heading;     // 目标当前的航向
    double angularVelocity; // 目标当前的角速度
};

// 导引命令结构体
struct GuidanceCommand {
    double thrust;  // 推力大小
    double rudder;  // 舵角
};

// 导引参数结构体
struct GuidanceParams {
    double timeStep;    // 时间步长
    double targetRadius; // 目标的半径
    double torpedoRadius; // 鱼雷的半径
    double searchRadius; // 搜索半径
    double maxTime;  // 最大追踪时间
};

// 导引命令
struct GuidanceCommand {
    double ax;  // x方向加速度
    double ay;  // y方向加速度
    double az;  // z方向加速度
};

// 导引参数
struct GuidanceParams {
    double kx;  // x方向比例系数
    double ky;  // y方向比例系数
    double kz;  // z方向比例系数
};


// 命中评估参数结构体
struct HitEvalParams {
    double accuracyThreshold; // 命中精度阈值
};

// 搜寻区域
struct SearchArea {
    Position center;    // 中心点
    double radius;      // 半径
};

// 搜寻参数
struct SearchParams {
    double accuracy;    // 搜寻精度
};

// 搜寻模式枚举
enum SearchMode {
    Random,  // 随机搜索
    ParticleFilter // 基于粒子滤波的搜索
};

// 目标搜寻结果结构体
struct TargetSearchResult {
    Target target;  // 搜寻到的目标
    bool found;     // 是否搜寻到目标
};

// 目标区域
struct TargetArea {
    Position center;    // 中心点
    double radius;      // 半径
};

// 命中评估参数
struct HitEvalParams {
    double accuracy;    // 命中精度
};

#endif // POSITION_H

