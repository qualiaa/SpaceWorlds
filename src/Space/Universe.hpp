#pragma once
#include <Tank/System/World.hpp>

class Universe : public tank::World
{
	void genWorld();


public:
    Universe();

    static const int worldWidth;
    static const int worldHeight;

};
