#pragma once
#include <chrono>
#include <Tank/System/Entity.hpp>
#include <Tank/Utility/Timer.hpp>

class Hittable : public tank::Entity
{
    int maxHealth_;
    int health_;

    tank::Timer flashTimer, damageTimer;
    int flashHalfFrames = 0;
    const std::chrono::milliseconds damageTime {300}, flashTime {damageTime/6};

public:
    Hittable(tank::Vectorf pos = {}, int health = 1);

    virtual void checkHit();
    virtual void heal(int health = 1);
    virtual void hit(int damage = 1);
    virtual void die();

    int getHealth() {return health_;}

    void flash(int frames);

    virtual void update() override;
};
