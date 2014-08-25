#include "Planet.hpp"
#include <Tank/System/World.hpp>

Planet::Planet(tank::Vectorf pos, const std::string& name)
    : Entity{pos}
    , name_{name}
{
    //Nothing to see here please move on
    makeGraphic("assets/graphics/planet"+std::to_string(std::rand()%3+1)+".png");
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
