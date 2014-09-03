#pragma once
#include <SFML/Audio/Listener.hpp>
#include "Ship.hpp"

class PlayerSpaceship : public Ship
{
    sf::Listener listener;

public:
    PlayerSpaceship();

    void onAdded() override;
    void onRemoved() override;
    void update() override;
};
