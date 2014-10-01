#include "Player.hpp"

#include <functional>
#include <SFML/Audio/Listener.hpp>
#include <Tank/System/Game.hpp>
#include <Tank/System/Keyboard.hpp>
#include "Universe.hpp"

unsigned Player::numPlayers = 0;

Player::Player(tank::observing_ptr<tank::Controller> c)
    : Ship({90,90}, 10)
    , controller_(c)
    , id_(numPlayers++)
{
    using namespace std::literals;
    setLayer(100);
    setType("player");
    addType("player"s + std::to_string(id_));
    initAnimations("assets/graphics/beetle.png");
}

void Player::onAdded()
{
    using kbd = tank::Keyboard;
    using Key = tank::Key;
    using C = tank::Controller;
    using Btn = tank::Controller::Button;
    using Axis = tank::Controller::Axis;

    // set up controls
    if (not controller_) {
        auto move = kbd::KeyDown(Key::Up) || kbd::KeyDown(Key::W);
        connect(move, std::bind(&Ship::thrust, this));

        auto halt = kbd::KeyDown(Key::Down) || kbd::KeyDown(Key::S);
        connect(halt, std::bind(&Ship::halt, this));

        auto shoot = kbd::KeyPress(Key::Space);
        connect(shoot, std::bind(&Ship::shoot, this));

        auto interact = kbd::KeyPress(Key::E);
        connect(interact, std::bind(&Player::interact, this));

        auto clockwise = kbd::KeyDown(Key::Right) || kbd::KeyDown(Key::D);
        connect(clockwise, std::bind(&Ship::rotateCW, this));

        auto counterclockwise = kbd::KeyDown(Key::Left) || kbd::KeyDown(Key::A);
        connect(counterclockwise, std::bind(&Ship::rotateCCW, this));

        auto engineStop = kbd::KeyRelease(Key::Up) || kbd::KeyRelease(Key::W);
        connect(engineStop, std::bind(&Ship::engineStop, this));
    } else {
        auto move = controller_->ButtonDown(Btn::A);
        connect(move, std::bind(&Ship::thrust, this));

        auto halt = controller_->ButtonDown(Btn::B);
        connect(halt, std::bind(&Ship::halt, this));

        auto shoot = controller_->ButtonPress(Btn::BUMPER_RIGHT) ||
                     controller_->ButtonPress(Btn::BUMPER_LEFT);
        connect(shoot, std::bind(&Ship::shoot, this));

        auto interact = controller_->ButtonPress(Btn::X);
        connect(interact, std::bind(&Player::interact, this));

        auto engineStop = controller_->ButtonRelease(Btn::A);
        connect(engineStop, std::bind(&Ship::engineStop, this));

        /* THis needs work
        auto stick = controller_->AxisMoved(Axis::STICK_LEFT_X) ||
                     controller_->AxisMoved(Axis::STICK_LEFT_Y);
        connect(stick, std::bind(&Player::controlStick, this));
        */
    }

    // set up camera
    camera_ = getWorld()->camera;
}

void Player::onRemoved()
{
    tank::Game::popWorld();
    tank::Game::makeWorld<Universe>();
}

void Player::update()
{
    Ship::update();

    /* Handle gamepad rotation */
    if (controller_) {
        constexpr double threshold = 0.25;
        constexpr double thresholdSqr = threshold*threshold;

        const auto ls = controller_->leftStick();
        auto x = ls.x;
        if (x*x > thresholdSqr) {
            if (x > 0) {
                rotateCW();
            } else {
                rotateCCW();
            }
        }
    }

    // update camera
    tank::Camera& cam = camera_;//tank::Game::world()->camera;
    cam.setPos(getPos() - cam.getOrigin());

    /*
    //Camera bounding
    auto camPos = cam.getPos();
    //cam.setOrigin({200.0,200.0});
    auto camOri = cam.getOrigin();
    auto windowSize = tank::Game::window()->getSize();

    if(camPos.x + camOri.x/2 < 0) {
        camPos.x = -camOri.x/2;
    }
    else if (camPos.x + windowSize.x - camOri.x/2 > Universe::worldWidth) {
        camPos.x = Universe::worldWidth - windowSize.x + camOri.x/2;
    }
    if(camPos.y + camOri.y/2 < 0) {
        camPos.y = -camOri.y/2;
    }
    else if (camPos.y + windowSize.y - camOri.y/2 > Universe::worldHeight) {
        camPos.y = Universe::worldHeight - windowSize.y + camOri.y/2;
    }

    cam.setPos(camPos);
    */

    auto planets = collide("Planet");
    if (not planets.empty() > 0) {
        auto planet = planets.back();
        if (planet->isType("RedPlanet")) {
            die();
        }
        if (interacting_) {
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

    interacting_ = false;
}

void Player::interact()
{
    interacting_ = true;
}
