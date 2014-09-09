#pragma once
#include <random>
#include <Tank/Graphics/FrameList.hpp>
#include <Tank/Utility/Timer.hpp>
#include "Ship.hpp"
#include "Universe.hpp"

class PlayerSpaceship;

class Enemy : public Ship
{
    tank::Timer timer_;
    tank::Timer bulletTimer_;

    tank::observing_ptr<PlayerSpaceship> player_;

public:
    Enemy();

    static const float speed;

    void onAdded() override;
    void onRemoved() override {
        Universe::score++;
        getWorld()->makeEntity<Enemy>();
    }

    void update() override;
};
