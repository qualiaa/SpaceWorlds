#pragma once
#include <Tank/System/World.hpp>

class Universe : public tank::World
{
	void genWorld();


public:
    Universe();

    const int worldWidth  = 500;
    const int worldHeight = 500;

};
