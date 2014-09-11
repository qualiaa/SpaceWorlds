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
    using res = tank::Resources;
    using namespace std::literals;
    //Nothing to see here please move on
    std::uniform_int_distribution<unsigned> rand_dist {1,3};
    type_ = static_cast<Type>(rand_dist(Universe::randEng));
    std::stringstream planettype;
    planettype << "assets/graphics/planet" << type_ << ".png";
    makeGraphic(res::get<tank::Image>(planettype.str()));
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

    overlay_ = makeGraphic<tank::CircleShape>(getGraphic(0)->getSize().x / 2);
    overlay_->setFillColor({0,0,0,0});
}

void Planet::onAdded()
{
    label_ = getWorld()->makeEntity<Dialog>(getPos()-(tank::Vectorf{50,50}/3.0),
                                            name_);
    setNameVisible(false);
}

void Planet::update()
{
    if (uses_ < 1) {
       if (type_ == Green) {
           removeType("GreenPlanet");
           addType("GreenPlanetDepleted");
       }
    }
    auto players = collide("player");

    if (!players.empty()) {
        setNameVisible(true);
        if (tank::Keyboard::isKeyPressed(tank::Key::E)) {
            --uses_;
            overlay_->
        }
    } else {
        setNameVisible(false);
    }
}
