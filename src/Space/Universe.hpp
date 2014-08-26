#pragma once
#include <Tank/System/World.hpp>
#include <Tank/Audio/Music.hpp>

class Universe : public tank::World
{
    tank::Music fightMusic_;

public:
    Universe();
    virtual ~Universe();

    static const int worldWidth;
    static const int worldHeight;

private:
	void genWorld();

};
