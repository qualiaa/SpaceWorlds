#ifndef SHIP_HPP
#define SHIP_HPP

#include <random>
#include <Tank/Graphics/FrameList.hpp>
#include <Tank/Audio/SoundEffect.hpp>
#include "Hittable.hpp"

class Ship : public Hittable
{
    std::mt19937_64 randomGenerator;
    tank::SoundEffect thruster;
protected:
    tank::Vectorf velocity {0,0};
    tank::Vectorf direction {0,-1};
    float angularVelocity{0};
    bool engineOn {false}, moving {false}, rotating {false};

    tank::observing_ptr<tank::FrameList> sprite;

    void initAnimations(std::string const& filename);

public:
    static const float acceleration;
    static const float maxSpeed;
    static const float maxSpeedSquared;
    static const float angularAcceleration;
    static const float maxAngularSpeed;
    static const float angularDrag;
    static const float breakDrag;
    static const float drag;

    Ship(tank::Vectorf pos = {}, int health = 1);

    virtual void update() override;
    virtual void setRotation(float angle) override;

    tank::Vectorf getDirection() const { return direction; }
    void setDirection(tank::Vectorf d) { direction = d; }
    tank::Vectorf getVelocity() const { return velocity; }
    void setVelocity(tank::Vectorf v) { velocity = v; }

    void rotate(double factor);
    void rotateCW() {rotate(1);};
    void rotateCCW() {rotate(-1);};
    void halt();
    void thrust();
    void shoot();

    void engineStop();
private:
    void engineStart();
    void engineSustain();
    void engineIdle();
    void engineRotate();

    void shake();
};

#endif /* SHIP_HPP */
