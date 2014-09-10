#pragma once
#include <random>
#include <Tank/Graphics/FrameList.hpp>
#include <Tank/Utility/Timer.hpp>
#include "Ship.hpp"
#include "Universe.hpp"

class Player;

class Enemy : public Ship
{
    tank::Timer thrustTimer_;
    tank::Timer bulletTimer_;

    tank::observing_ptr<Player> player_;

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
