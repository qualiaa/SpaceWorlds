#ifndef SHIP_HPP
#define SHIP_HPP

#include <random>
#include <Tank/Graphics/FrameList.hpp>
#include <Tank/Audio/SoundEffect.hpp>
#include "Hittable.hpp"

class Ship : public Hittable
{
    tank::observing_ptr<tank::FrameList> sprite;
    std::mt19937_64 randomGenerator;
    tank::SoundEffect thruster;
protected:
    tank::Vectorf velocity {0,0};
    tank::Vectorf direction {0,-1};
    float angularVelocity{0};
    bool engineOn {false}, moving {false}, rotating {false};

public:
    static const float acceleration;
    static const float maxSpeed;
    static const float maxSpeedSquared;
    static const float angularAcceleration;
    static const float maxAngularSpeed;
    static const float angularDrag;
    static const float breakDrag;
    static const float drag;

    Ship(tank::Vectorf pos, int health = 1);

    virtual void update() override;
    virtual void setRotation(float angle) override;

    void rotate(double factor);
    void rotateCW() {rotate(1);};
    void rotateCCW() {rotate(-1);};
    void halt();
    void thrust();
    void shoot();

    void engineStart();
    void engineStop();
    void engineSustain();
    void engineIdle();
    void engineRotate();

    void shake();
};

#endif /* SHIP_HPP */
