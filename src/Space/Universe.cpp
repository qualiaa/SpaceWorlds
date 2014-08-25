#include "Universe.hpp"
#include "PlayerSpaceship.hpp"
#include "Planet.hpp"
#include <Tank/System/Game.hpp>
#include "../Dialog.hpp"

Universe::Universe()
{
    makeEntity<PlayerSpaceship>();
    makeEntity<Planet>(tank::Vectorf{100,100}, "heya");
    camera.setScale(3);
    tank::Game::window()->setBackgroundColor({9,21,31});
}
