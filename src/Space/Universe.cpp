#include "Universe.hpp"
#include "PlayerSpaceship.hpp"
#include "Planet.hpp"

Universe::Universe()
{
    makeEntity<PlayerSpaceship>();
    makeEntity<Planet>(tank::Vectorf{100,100});
}
