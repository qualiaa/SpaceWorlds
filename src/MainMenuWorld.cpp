#include "MainMenuWorld.hpp"
#include <Tank/System/Game.hpp>
#include <Tank/System/Mouse.hpp>
#include <Tank/Utility/Resources.hpp>
#include "MainMenuPlay.hpp"
#include "Space/Universe.hpp"

MainMenuWorld::MainMenuWorld()
{
    using res = tank::Resources;
    //auto backgroundImage = 
        //res::get<tank::Image>("assets/graphics/mainmenu_background.png");
    //makeEntity<tank::Entity>()->makeGraphic(backgroundImage);

    auto button = makeEntity<MainMenuPlay>(
            tank::Vectorf{tank::Game::window()->getSize().x/2.f, 400});
    connect(tank::Mouse::InEntity(button) && tank::Mouse::ButtonRelease(),
            std::bind(&MainMenuWorld::startGame, this));

    music_ = res::get<tank::Music>("assets/music/title1.ogg");
    music_.setLoop(true);
    music_.play();
}

MainMenuWorld::~MainMenuWorld()
{
    music_.stop();
}

void MainMenuWorld::startGame()
{
    music_.stop();
    tank::Game::makeWorld<Universe>();
}
