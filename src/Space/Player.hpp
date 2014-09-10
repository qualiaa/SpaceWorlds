#pragma once
#include "Ship.hpp"

class Player : public Ship
{
public:
    Player();

    void onAdded() override;
    void onRemoved() override;
    void update() override;
};
