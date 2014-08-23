#include "Planet.hpp"

Planet::Planet(tank::Vectorf pos) : Entity{pos, "assets/graphics/planet.png"}
{
    setType("Planet");
}
