#pragma once
#include <Tank/System/World.hpp>

class PlayerSpaceship;

class Universe : public tank::World
{
	void genWorld();
    tank::observing_ptr<PlayerSpaceship> player_;

public:
    Universe();

    static const int worldWidth;
    static const int worldHeight;
    
    auto getPlayer() {return player_;}

};
