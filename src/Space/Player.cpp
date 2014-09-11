#include "Player.hpp"

#include <functional>
#include <SFML/Audio/Listener.hpp>
#include <Tank/System/Game.hpp>
#include <Tank/System/Keyboard.hpp>
#include "Universe.hpp"

Player::Player()
    : Ship({90,90}, 10)
{
    setLayer(100);
    setType("player");
    initAnimations("assets/graphics/beetle.png");
    tank::Game::world()->camera.setOrigin({0,0});
}

void Player::onAdded()
{
    using kbd = tank::Keyboard;
    using Key = tank::Key;

    auto move = kbd::KeyDown(Key::Up) || kbd::KeyDown(Key::W);
    connect(move, std::bind(&Ship::thrust, this));

    auto halt = kbd::KeyDown(Key::Down) || kbd::KeyDown(Key::S);
    connect(halt, std::bind(&Ship::halt, this));

    auto clockwise = kbd::KeyDown(Key::Right) || kbd::KeyDown(Key::D);
    connect(clockwise, std::bind(&Ship::rotateCW, this));

    auto counterclockwise = kbd::KeyDown(Key::Left) || kbd::KeyDown(Key::A);
    connect(counterclockwise, std::bind(&Ship::rotateCCW, this));

    auto shoot = kbd::KeyPress(Key::Space);
    connect(shoot, std::bind(&Ship::shoot, this));

    auto engineStop = kbd::KeyRelease(Key::Up) || kbd::KeyRelease(Key::W);
    connect(engineStop, std::bind(&Ship::engineStop, this));
}

void Player::onRemoved()
{
    tank::Game::popWorld();
    tank::Game::makeWorld<Universe>();
}

void Player::update()
{
    Ship::update();

    // update camera
    tank::Camera& cam = tank::Game::world()->camera;
    cam.setPos(getPos() - cam.getOrigin());

    //Camera bounding
    tank::Vectorf pos = cam.getPos();
    tank::Vectorf size = cam.getOrigin();

    if(pos.x < -size.x) {
        pos = tank::Vectorf(-size.x, pos.y);
    }
    else if (pos.x > Universe::worldWidth-size.x) {
        pos = tank::Vectorf(Universe::worldWidth-size.x, pos.y);
    }
    if(pos.y < -size.y) {
        pos = tank::Vectorf(pos.x, -size.y);
    }
    else if (pos.y > Universe::worldHeight-size.y) {
        pos = tank::Vectorf(pos.x, Universe::worldHeight-size.y);
    }
    cam.setPos(pos);

    auto planets = collide("Planet");
    if (not planets.empty() > 0) {
        auto planet = planets.back();
        if (planet->isType("RedPlanet")) {
            die();
        }
        if (tank::Keyboard::isKeyPressed(tank::Key::E)) {
            if(planet->isType("BluePlanet") > 0) {
                //Blue stuff
            }
            if(planet->isType("RedPlanet") > 0) {
                //Red stuff
            }
            if(planet->isType("GreenPlanet") > 0) {
                //Green stuff
                heal();
            }
        }
    }

    // update listener
    sf::Listener::setPosition({getPos().x,getPos().y,0});

    //Check for using planets
}
