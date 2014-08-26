#pragma once
#include <Tank/System/World.hpp>
#include "../HudDialog.hpp"

class PlayerSpaceship;

class Universe : public tank::World
{
	void genWorld();
    tank::observing_ptr<PlayerSpaceship> player_;
	tank::observing_ptr<HudDialog> hud;

public:
    Universe();

    void update() override;

    static const int worldWidth;
    static const int worldHeight;
    
    auto getPlayer() {return player_;}

};
