#include "Ship.hpp"

#include <Tank/Utility/Resources.hpp>
#include <Tank/System/World.hpp>
#include <Tank/System/Game.hpp>
#include "Universe.hpp"
#include "Bullet.hpp"

const float Ship::acceleration            {0.175};
const float Ship::angularAcceleration     {0.115};
const float Ship::maxAngularSpeed         {1.5};
const float Ship::maxSpeed                {3.2};
const float Ship::maxSpeedSquared         {maxSpeed * maxSpeed};
const float Ship::angularDrag             {1.075};
const float Ship::breakDrag               {1.05};
const float Ship::drag                    {1.0285};


Ship::Ship(tank::Vectorf pos, int health)
    : Hittable(pos, health)
{
    using res = tank::Resources;
    auto& image = res::get<tank::Image>("assets/graphics/beetle.png");
    sprite = makeGraphic<tank::FrameList>(image,
                                          tank::Vectoru{16, 20},
                                          tank::Vectoru{1, 1});

    sprite->add("idle", {0}, std::chrono::milliseconds(0));
    sprite->add("engine_start", {4,5,6,7}, std::chrono::milliseconds(250));
    sprite->add("engine_stop", {7,6,5,4,4}, std::chrono::milliseconds(125));
    sprite->add("engine_run", {6,7}, std::chrono::milliseconds(250));
    sprite->add("engine_rotate", {4}, std::chrono::milliseconds(0));
    //sprite->select("idle", false);
    sprite->start();

    setOrigin(sprite->getSize() / 2);
    sprite->centreOrigin();
    setLayer(100);

    // centre hitbox
    const auto oldHitbox = getHitbox();
    setHitbox({-oldHitbox.w / 2, -oldHitbox.h / 2, oldHitbox.w, oldHitbox.h});

    // load sfx
    thruster = res::get<tank::SoundEffect>("assets/sounds/thruster2.ogg");
    thruster.setVolume(10);
    thruster.setLoop(true);
}

void Ship::update()
{
    Hittable::update();
    // Update position
    const float speedSqr = velocity.magnitudeSquared();
    if(speedSqr > maxSpeedSquared) {
        velocity = velocity.unit() * maxSpeed;
    }
    moveBy(velocity);

    // update velocity
    //if(!(tank::Keyboard::isKeyDown(tank::Key::W)
     //||  tank::Keyboard::isKeyDown(tank::Key::Up))) {
    if (not moving) {
        velocity /= drag;
    }

    if (speedSqr < 0.000001) {
        velocity = {};
    }

    // Update angle
    const auto angularSpeedCap = maxAngularSpeed * (engineOn ? 1.0 : 5.0);
    if(angularVelocity > angularSpeedCap) {
        angularVelocity = angularSpeedCap;
    } else if (angularVelocity < -angularSpeedCap) {
        angularVelocity = -angularSpeedCap;
    }
    setRotation(getRotation()+angularVelocity);
    if (not rotating) {
        angularVelocity /= angularDrag;
    }

    // update camera
    tank::Camera& cam = tank::Game::world()->camera;
    tank::Vectorf size = cam.getOrigin();

    //Player Wrapping
    if(getPos().x < -size.x/2) {
        setPos(tank::Vectorf(Universe::worldWidth+size.x/2, getPos().y));
    }
    else if(getPos().x > Universe::worldWidth + size.x/2) {
        setPos(tank::Vectorf(-size.x/2, getPos().y));
    }
    if(getPos().y < -size.y/2) {
        setPos(tank::Vectorf(getPos().x, Universe::worldWidth+size.y/2));
    }
    else if(getPos().y > Universe::worldHeight + size.y/2) {
        setPos(tank::Vectorf(getPos().x, -size.y/2));
    }

    rotating = moving = false;
}

void Ship::rotate(double factor)
{
    rotating=true;
    angularVelocity += angularAcceleration * factor;
    engineRotate();
}

void Ship::halt()
{
    velocity /= breakDrag;
}
void Ship::thrust()
{
    moving=true;
    velocity += acceleration * direction;
    shake();

    if (not engineOn) {
        engineStart();
    }
}

void Ship::shoot()
{
    tank::Vectorf p = getPos() + direction * 3 + direction.rotate(-90)*4;
    getWorld()->makeEntity<Bullet>(p,velocity, direction)->addType(getType());
    p += direction.rotate(90) * 8;
    getWorld()->makeEntity<Bullet>(p,velocity, direction)->addType(getType());
}

void Ship::engineStart()
{
    sprite->select("engine_start", false,
                   std::bind(&Ship::engineSustain, this));
    sprite->start();
    engineOn = true;
    thruster.play();
}

void Ship::engineStop()
{
    sprite->select("engine_stop", false,
                   std::bind(&Ship::engineIdle, this));
    sprite->start();
    engineOn = false;
    thruster.stop();
}

void Ship::engineSustain()
{
    sprite->select("engine_run");
    sprite->start();
}

void Ship::engineIdle()
{
    const auto graphicRotation = sprite->getRotation();
    const auto rotation = getRotation();

    this->setRotation(graphicRotation + rotation);
    sprite->setRotation(0);
    sprite->select("idle", false);
    sprite->start();
}

void Ship::engineRotate()
{
    /* not quite working */
    if (not sprite->playing()) {
        sprite->select("engine_rotate", false);
        sprite->start();
    }
}

void Ship::shake()
{
    auto rotation = sprite->getRotation();
    const auto d0 = std::uniform_real_distribution<float>{-0.5,0.5}(randomGenerator);

    sprite->setRotation(rotation + d0);
}

void Ship::setRotation(float angle)
{
    auto rot = getRotation();
    Transformable::setRotation(angle);
    direction = direction.rotate(angle - rot);
}
