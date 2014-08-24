#include "Universe.hpp"
#include "PlayerSpaceship.hpp"
#include "Planet.hpp"
#include "../Dialog.hpp"

Universe::Universe()
{
    makeEntity<PlayerSpaceship>();
    makeEntity<Planet>(tank::Vectorf{100,100});
    makeEntity<Dialog>(tank::Vectorf{0,0}, "heya");
}
