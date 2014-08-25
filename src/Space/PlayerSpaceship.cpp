#include "PlayerSpaceship.hpp"
#include <functional>
#include <Tank/System/Game.hpp>
#include <Tank/System/Keyboard.hpp>
#include <Tank/Utility/Resources.hpp>
#include <Tank/Utility/Vector.hpp>
#include "Universe.hpp"
#include "Bullet.hpp"

const float PlayerSpaceship::angularAcceleration     {0.115};
const float PlayerSpaceship::maxAngularSpeed         {1.5};
const float PlayerSpaceship::acceleration            {0.175};
const float PlayerSpaceship::maxSpeed                {3.2};
const float PlayerSpaceship::maxSpeedSquared         {maxSpeed * maxSpeed};

PlayerSpaceship::PlayerSpaceship() : Hittable(10, "enemyBullet")
{
    setType("PlayerSpaceship");
    auto& image = Resources::get<tank::Image>("assets/graphics/beetle.png");
    sprite = makeGraphic<tank::FrameList>(image,
                                          tank::Vectoru{16, 20},
                                          tank::Vectoru{1, 1});
    setPos({90,90});

    sprite->add("idle", {0}, std::chrono::milliseconds(0));
    sprite->add("engine_start", {4,5,6,7}, std::chrono::milliseconds(250));
    sprite->add("engine_stop", {7,6,5,4,4}, std::chrono::milliseconds(125));
    sprite->select("idle");
    sprite->start();

    setOrigin(sprite->getSize() / 2);
    sprite->centreOrigin();
    setLayer(100);

    // centre hitbox
    const auto oldHitbox = getHitbox();
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
        //shake();
    });

    auto startEngine = kbd::KeyPress(Key::Up) || kbd::KeyPress(Key::W);
    connect(startEngine, std::bind(&PlayerSpaceship::startEngine, this));

    auto stopEngine = kbd::KeyRelease(Key::Up) || kbd::KeyRelease(Key::W);
    connect(stopEngine, std::bind(&PlayerSpaceship::stopEngine, this));

    auto halt = kbd::KeyDown(Key::Down) || kbd::KeyDown(Key::S);
    connect(halt, [this]() {
        velocity /= 1.06;
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
     ||  tank::Keyboard::isKeyDown(tank::Key::Up))) {
        velocity /= 1.0285;
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
      || tank::Keyboard::isKeyDown(tank::Key::D)
      || tank::Keyboard::isKeyDown(tank::Key::Left)
      || tank::Keyboard::isKeyDown(tank::Key::Right))) {
        angularVelocity /= 1.05;
    }

    // update camera
    tank::Camera& cam = tank::Game::world()->camera;
    cam.setPos(getPos() - cam.getOrigin());

    //Camera bounding
    tank::Vectorf pos = cam.getPos();
    tank::Vectorf size = cam.getOrigin();

    if(pos.x < -size.x) {
        pos = tank::Vectorf(-size.x, pos.y);
        cam.setPos(pos);
    }
    if(pos.y < -size.y) {
        pos = tank::Vectorf(pos.x, -size.y);
        cam.setPos(pos);
    }
    if(pos.x > Universe::worldWidth-size.x) {
        pos = tank::Vectorf(Universe::worldWidth-size.x, pos.y);
        cam.setPos(pos);
    }
    if(pos.y > Universe::worldHeight-size.y) {
        pos = tank::Vectorf(pos.x, Universe::worldHeight-size.y);
        cam.setPos(pos);
    }

    //Player Wrapping
    if(getPos().x < -size.x/2) {
        setPos(tank::Vectorf(Universe::worldWidth+size.x/2, getPos().y));
    }
    if(getPos().y < -size.y/2) {
        setPos(tank::Vectorf(getPos().x, Universe::worldWidth+size.y/2));
    }
    if(getPos().x > Universe::worldWidth + size.x/2) {
        setPos(tank::Vectorf(-size.x/2, getPos().y));
    }
    if(getPos().y > Universe::worldHeight + size.y/2) {
        setPos(tank::Vectorf(getPos().x, -size.y/2));
    }

    //Add bullet
    if(tank::Keyboard::isKeyPressed(tank::Key::Space)) {
        getWorld()->makeEntity<Bullet>(getPos(), direction, "PlayerBullet");
    }

    //Check for using on planets
    if(tank::Keyboard::isKeyDown(tank::Key::E)) {
        auto bluePlanets = collide("BluePlanet");
        if(bluePlanets.size()>0) {
            //Blue effect
        }
        auto redPlanets = collide("RedPlanet");
        if(redPlanets.size()>0) {
            //Red effect
        }
        auto greenPlanets = collide("GreenPlanet");
        if(greenPlanets.size()>0) {
            //Green effect
            heal(1);
        }
    }

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
