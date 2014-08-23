#pragma once
#include <Tank/System/Entity.hpp>
#include <Tank/Graphics/Graphic.hpp>

class Planet : public tank::Entity
{
    tank::observing_ptr<tank::Graphic> graphic;

public:
    Planet(tank::Vectorf pos);
};
