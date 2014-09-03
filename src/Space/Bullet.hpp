#pragma once
#include <Tank/System/Entity.hpp>
#include <Tank/Utility/Vector.hpp>
#include <Tank/Utility/Timer.hpp>
#include <Tank/Audio/SoundEffect.hpp>

class Bullet : public tank::Entity
{
	tank::Timer lifeTimer;
    tank::Vectorf velocity {0, 0};
    tank::SoundEffect blast;

public:
    Bullet(tank::Vectorf pos, tank::Vectorf vel, tank::Vectorf direction);

    void update() override;
    void setRotation(float angle) override;

    static const float speed;
};
