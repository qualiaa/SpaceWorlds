#include <Tank/System/Game.hpp>
#include "Space/MainMenuWorld.hpp"

int main()
{
    tank::Game::initialize({800,600});
    tank::Game::window()->setCaption("Worlds somehow not in space?.jpg");
    tank::Game::makeWorld<MainMenuWorld>();
    tank::Game::run();
}
