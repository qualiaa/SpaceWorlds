#include <Tank/System/Game.hpp>
#include "Space/Universe.hpp"

int main()
{
    tank::Game::initialize({800,600});
    tank::Game::window()->setCaption("Worlds somehow not in space?.jpg");
    tank::Game::makeWorld<Universe>();
    tank::Game::run();
}
