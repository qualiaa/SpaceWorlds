#pragma once
#include <Tank/System/Entity.hpp>
#include <Tank/Graphics/FrameList.hpp>

class PlayerSpaceship : public tank::Entity
{
    tank::observing_ptr<tank::FrameList> sprite;

    tank::Vectorf velocity {0,0};
    tank::Vectorf direction {0,-1};
    float angularVelocity{0};

public:
    static const float acceleration;
    static const float maxSpeed;
    static const float maxSpeedSquared;
    static const float angularAcceleration;
    static const float maxAngularSpeed;

    PlayerSpaceship();

    void onAdded() override;
    void update() override;
    void setRotation(float angle) override;

    void startEngine();
    void stopEngine();
    void runEngine();
    void idleEngine();
};
