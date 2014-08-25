#include "Planet.hpp"
#include <Tank/System/World.hpp>

Planet::Planet(tank::Vectorf pos, const std::string& name)
    : Entity{pos}
    , name_{name}
{
    makeGraphic("assets/graphics/planet.png");
    setType("Planet");
}

void Planet::onAdded()
{
    label_ = getWorld()->makeEntity<Dialog>(getPos()-(tank::Vectorf{50,50}/3.0),
                                            name_);
    setNameVisible(false);
}

void Planet::update()
{
    auto players = collide("PlayerSpaceship");
    
    if (!players.empty()) {
        setNameVisible(true);
    } else {
        setNameVisible(false);
    }
}
