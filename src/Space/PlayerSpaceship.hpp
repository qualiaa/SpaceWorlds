#pragma once
#include <random>
#include <Tank/System/Entity.hpp>
#include <Tank/Graphics/FrameList.hpp>
#include "Hittable.hpp"

class PlayerSpaceship : public Hittable
{
    tank::observing_ptr<tank::FrameList> sprite;

    tank::Vectorf velocity {0,0};
    tank::Vectorf direction {0,-1};
    float angularVelocity{0};
    std::mt19937_64 randomGenerator;
    bool engineOn {false};

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
    void sustainEngine();
    void idleEngine();
    void rotateEngine();

    void shake();
};
