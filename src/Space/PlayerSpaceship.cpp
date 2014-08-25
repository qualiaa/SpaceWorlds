#include "PlayerSpaceship.hpp"
#include <limits>
#include <functional>
#include <random>
#include <Tank/System/Game.hpp>
#include <Tank/System/Keyboard.hpp>

const float PlayerSpaceship::angularAcceleration     {0.1};
const float PlayerSpaceship::maxAngularSpeed         {1.5};
const float PlayerSpaceship::acceleration            {0.01};
const float PlayerSpaceship::maxSpeed                {1};
const float PlayerSpaceship::maxSpeedSquared         {maxSpeed * maxSpeed};

PlayerSpaceship::PlayerSpaceship()
{
    setType("PlayerSpaceship");
    sprite = makeGraphic<tank::FrameList>(tank::Image{"assets/graphics/beetle.png"},
                                          tank::Vectoru{16, 20}, tank::Vectoru{1, 1});
    setPos({90,90});

    sprite->add("idle", {0}, std::chrono::milliseconds(0));
    sprite->add("engine_start", {4,5,6,7}, std::chrono::milliseconds(250));
    sprite->add("engine_stop", {7,6,5,4,4}, std::chrono::milliseconds(125));
    sprite->add("engine_run", {6,7}, std::chrono::milliseconds(250));
    sprite->select("idle");
    sprite->start();

    setOrigin(sprite->getSize() / 2);
    sprite->centreOrigin();
    setLayer(std::numeric_limits<int>::max());

    // centre hitbox, turning {0,0,w,h} into {-w,-h,w,h} / 2
    const auto oldHitbox = getHitbox();

    //todo: hitbox seems a bit off
    setHitbox({-oldHitbox.w / 2, -oldHitbox.h / 2, oldHitbox.w, oldHitbox.h});
}

void PlayerSpaceship::onAdded()
{
    using kbd = tank::Keyboard;
    using Key = tank::Key;

    auto clockwise = kbd::KeyDown(Key::Right) || kbd::KeyDown(Key::D);
    connect(clockwise, [this](){
        angularVelocity += angularAcceleration;
    });

    auto counterclockwise = kbd::KeyDown(Key::Left) || kbd::KeyDown(Key::A);
    connect(counterclockwise, [this](){
        angularVelocity -= angularAcceleration;
    });

    auto move = kbd::KeyDown(Key::Up) || kbd::KeyDown(Key::W);
    connect(move, [this](){
        velocity += acceleration * direction;
        shake();
    });

    auto startEngine = kbd::KeyPress(Key::Up) || kbd::KeyPress(Key::W);
    connect(startEngine, std::bind(&PlayerSpaceship::startEngine, this));

    auto stopEngine = kbd::KeyRelease(Key::Up) || kbd::KeyRelease(Key::W);
    connect(stopEngine, std::bind(&PlayerSpaceship::stopEngine, this));

    auto halt = kbd::KeyDown(Key::Down) || kbd::KeyDown(Key::S);
    connect(halt, [this]() {
        velocity -= acceleration * direction;
    });
}

void PlayerSpaceship::update()
{
    // Update position
    const float speedSqr = velocity.magnitudeSquared();
    if(speedSqr > maxSpeedSquared) {
        velocity = velocity.unit() * maxSpeed;
    }
    moveBy(velocity);

    // update velocity
    if(!(tank::Keyboard::isKeyDown(tank::Key::W)
     ||  tank::Keyboard::isKeyDown(tank::Key::S)
     ||  tank::Keyboard::isKeyDown(tank::Key::Up)
     ||  tank::Keyboard::isKeyDown(tank::Key::Down))) {
        velocity /= 1.001;
    }

    if (speedSqr < acceleration*acceleration*0.01) {
        velocity = {};
    }

    // Update angle
    if(angularVelocity > maxAngularSpeed) {
        angularVelocity = maxAngularSpeed;
    }
    else if(angularVelocity < -maxAngularSpeed) {
        angularVelocity = -maxAngularSpeed;
    }
    setRotation(getRotation()+angularVelocity);
    if(!(tank::Keyboard::isKeyDown(tank::Key::A)
      || tank::Keyboard::isKeyDown(tank::Key::S)
      || tank::Keyboard::isKeyDown(tank::Key::Left)
      || tank::Keyboard::isKeyDown(tank::Key::Right))) {
        angularVelocity /= 1.1;
    }

    // update camera
    tank::Camera& cam = tank::Game::world()->camera;
    cam.setPos(getPos() - cam.getOrigin());
}

void PlayerSpaceship::setRotation(float angle)
{
    auto rot = getRotation();
    Transformable::setRotation(angle);
    direction = direction.rotate(angle - rot);
}

void PlayerSpaceship::startEngine()
{
    sprite->select("engine_start", false,
                  std::bind(&PlayerSpaceship::sustainEngine, this));
}

void PlayerSpaceship::stopEngine()
{
    sprite->select("engine_stop", false,
                  std::bind(&PlayerSpaceship::idleEngine, this));
}

void PlayerSpaceship::sustainEngine()
{
    sprite->select("engine_run");
    sprite->start();
}

void PlayerSpaceship::idleEngine()
{
    const auto graphicRotation = sprite->getRotation();
    const auto rotation = getRotation();

    this->setRotation(graphicRotation + rotation);
    sprite->setRotation(0);
    sprite->select("idle");
    sprite->start();
}

void PlayerSpaceship::shake()
{
    auto rotation = sprite->getRotation();
    const auto d0 = std::uniform_real_distribution<float>{-0.5,0.5}(randomGenerator);

    sprite->setRotation(rotation + d0);
}
