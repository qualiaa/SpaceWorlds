#include "Planet.hpp"

#include <Tank/System/World.hpp>
#include <random>
#include <sstream>
#include <Tank/Utility/Resources.hpp>
#include <Tank/System/Keyboard.hpp>
#include "Universe.hpp"

Planet::Planet(tank::Vectorf pos, const std::string& name)
    : Entity{pos}
    , name_{name}
{
    using namespace std::literals;
    //Nothing to see here please move on
    std::uniform_int_distribution<unsigned> rand_dist {1,3};
    type_ = static_cast<decltype(type_)>(rand_dist(Universe::randEng));
    std::stringstream planettype;
    planettype << "assets/graphics/planet" << type_ << ".png";
    makeGraphic(Resources::get<tank::Image>(planettype.str()));
    setType("Planet");

    switch (type_) {
    case Blue:
        addType("BluePlanet");
        break;
    case Red:
        addType("RedPlanet");
        break;
    case Green:
        addType("GreenPlanet");
        break;
    }
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
