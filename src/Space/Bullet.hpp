#pragma once
#include <Tank/System/Entity.hpp>
#include <Tank/Utility/Vector.hpp>
#include <Tank/Utility/Timer.hpp>

class Bullet : public tank::Entity
{
	tank::Timer lifeTimer;
    tank::Vectorf velocity 	{0, 0};

public:
    Bullet(tank::Vectorf pos, tank::Vectorf vel, tank::Vectorf direction, const std::string& type);

    void update() override;
    void setRotation(float angle) override;

    static const float speed;

};
