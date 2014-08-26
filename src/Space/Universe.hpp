#pragma once
#include <Tank/System/World.hpp>
#include <Tank/Audio/Music.hpp>
#include "../HudDialog.hpp"

class PlayerSpaceship;

class Universe : public tank::World
{
    tank::Music fightMusic_;
    tank::observing_ptr<PlayerSpaceship> player_;
	tank::observing_ptr<HudDialog> hud;

public:
    Universe();
    virtual ~Universe();

    void update() override;

    static const int worldWidth;
    static const int worldHeight;
    
    auto getPlayer() {return player_;}

private:
    void genWorld();

};
