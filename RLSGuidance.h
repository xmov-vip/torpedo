#ifndef RLSGUIDANCE_H
#define RLSGUIDANCE_H


#include "Guidance.h"
#include <math.h>

// 递归最小二乘算法的自动导引算法类
class RLSGuidance : public Guidance {
public:
    RLSGuidance() {
        m_guidanceParams.timeStep = 0.1;
        m_guidanceParams.kp = 0.5;
        m_guidanceParams.ki = 0.05;
        m_guidanceParams.kd = 0.1;
        m_guidanceParams.maxSpeed = 50;
    }

    virtual void setGuidanceParams(GuidanceParams params) {
        m_guidanceParams = params;
    }

    virtual void initialize(TorpedoParams params) {
        m_torpedoParams = params;
        m_torpedoState.position = params.initialPosition;
        m_torpedoState.velocity = params.initialVelocity;
    }

    virtual void setTarget(TargetState target) {
        m_targetState = target;
    }

    virtual void setTargetArea(TargetArea area) {
        m_targetArea = area;
    }

    virtual void setHitEvaluator(HitEvaluator* evaluator) {
        m_hitEvaluator = evaluator;
    }

    // 计算导引命令
    virtual TorpedoCommand calculateCommand(double time) {
        // 计算目标和鱼雷的位置和速度
        predictTargetPosition(m_guidanceParams.timeStep);
        predictTorpedoPosition(m_guidanceParams.timeStep);
        predictTorpedoVelocity(m_guidanceParams.timeStep);

        // 计算距离和速度误差
        double distanceError = m_targetPosition.distanceTo(m_torpedoPosition);
        double speedError = m_torpedoVelocity.norm() - m_guidanceParams.targetSpeed;

        // 计算误差的导数
        double distanceErrorDeriv = (distanceError - m_lastDistanceError) / m_guidanceParams.timeStep;
        double speedErrorDeriv = (speedError - m_lastSpeedError) / m_guidanceParams.timeStep;

        // 计算误差的积分
        m_distanceErrorIntegral += distanceError * m_guidanceParams.timeStep;
        m_speedErrorIntegral += speedError * m_guidanceParams.timeStep;

        // 更新上一次的误差
        m_lastDistanceError = distanceError;
        m_lastSpeedError = speedError;

        // 计算控制命令
        double headingCommand = m_distanceErrorGain * distanceError
                              + m_distanceErrorDerivGain * distanceErrorDeriv
                              + m_distanceErrorIntegralGain * m_distanceErrorIntegral;
        double speedCommand = m_speedErrorGain * speedError
                            + m_speedErrorDerivGain * speedErrorDeriv
                            + m_speedErrorIntegralGain * m_speedErrorIntegral;

        // 限制控制命令的范围
        if (headingCommand > m_guidanceParams.maxHeadingChange) {
            headingCommand = m_guidanceParams.maxHeadingChange;
        } else if (headingCommand < -m_guidanceParams.maxHeadingChange) {
            headingCommand = -m_guidanceParams.maxHeadingChange;
        }
        if (speedCommand > m_guidanceParams.maxSpeedChange) {
            speedCommand = m_guidanceParams.maxSpeedChange;
        } else if (speedCommand < -m_guidanceParams.maxSpeedChange) {
            speedCommand = -m_guidanceParams.maxSpeedChange;
        }

        // 返回控制命令
        return TorpedoCommand(headingCommand, speedCommand);
    }
};


#endif // RLSGUIDANCE_H
