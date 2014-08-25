#include "Planet.hpp"
#include <Tank/System/World.hpp>
#include <random>
#include <sstream>
#include <Tank/Utility/Resources.hpp>

Planet::Planet(tank::Vectorf pos, const std::string& name)
    : Entity{pos}
    , name_{name}
{
    using namespace std::literals;
    //Nothing to see here please move on
    std::mt19937 rand_eng {std::random_device()()};
    std::uniform_int_distribution<> rand_dist {1,3};
    std::stringstream planettype;
    planettype << "assets/graphics/planet" << rand_dist(rand_eng) << ".png";
    makeGraphic(Resources::get<tank::Image>(planettype.str()));
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
