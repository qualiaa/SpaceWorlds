#include "PlayerSpaceship.hpp"
#include <Tank/System/Game.hpp>
#include <Tank/System/Keyboard.hpp>

PlayerSpaceship::PlayerSpaceship()
{
    setType("PlayerSpaceship");
    graphic = makeGraphic("assets/graphics/ship_beetle.png");
    graphic->setScale(3);
    setPos({400,300});

    setOrigin(graphic->getSize()/2);
}

void PlayerSpaceship::onAdded()
{
    using kbd = tank::Keyboard;
    using key = tank::Key;
    using namespace tank::literals;

    auto right = kbd::KeyDown(key::Right) || kbd::KeyDown(key::D);
    connect(right, &PlayerSpaceship::moveBy, 5_x);
    auto left = kbd::KeyDown(key::Left) || kbd::KeyDown(key::A);
    connect(left, &PlayerSpaceship::moveBy, -5_x);
    auto up = kbd::KeyDown(key::Up) || kbd::KeyDown(key::W);
    connect(up, &PlayerSpaceship::moveBy, -5_y);
    auto down = kbd::KeyDown(key::Down) || kbd::KeyDown(key::S);
    connect(down, &PlayerSpaceship::moveBy, 5_y);
}

void PlayerSpaceship::update()
{
    tank::Camera& cam = tank::Game::world()->camera;
    cam.setPos(getPos() - cam.getOrigin() + getOrigin());
}
