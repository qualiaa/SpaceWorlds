#include "PlayerSpaceship.hpp"
#include <Tank/System/Game.hpp>
#include <Tank/System/Keyboard.hpp>
#include <limits>

const float PlayerSpaceship::angularAcceleration     {0.1};
const float PlayerSpaceship::maxAngularSpeed         {1.5}; 
const float PlayerSpaceship::acceleration            {0.05};
const float PlayerSpaceship::maxSpeed                {6.4};
const float PlayerSpaceship::maxSpeedSquared         {maxSpeed * maxSpeed};

PlayerSpaceship::PlayerSpaceship()
{
    setType("PlayerSpaceship");
    sprite = makeGraphic<tank::FrameList>(tank::Image{"assets/graphics/beetle.png"}, tank::Vectoru{16, 20});
    setPos({90,90});

    setOrigin(sprite->getSize()/2);
    sprite->centreOrigin();
    setLayer(std::numeric_limits<int>::max());

    // centre hitbox, turning {0,0,w,h} into {-w,-h,w,h} / 2
    const auto oldHitbox = getHitbox();
    
    //todo: hitbox seems a bit off
    tank::Vectord newHitbox = {oldHitbox.w / 2, oldHitbox.h / 2};
    setHitbox({-newHitbox.x, -newHitbox.y, newHitbox.x, newHitbox.y});
}

void PlayerSpaceship::onAdded()
{
    using kbd = tank::Keyboard;
    using key = tank::Key;

    auto right = kbd::KeyDown(key::Right) || kbd::KeyDown(key::D);
    connect(right, [this](){
        angularVelocity += angularAcceleration;
    });

    auto left = kbd::KeyDown(key::Left) || kbd::KeyDown(key::A);
    connect(left, [this](){
        angularVelocity -= angularAcceleration;
    });

    auto up = kbd::KeyDown(key::Up) || kbd::KeyDown(key::W);
    connect(up, [this](){
        velocity += acceleration * direction;
    });

    auto down = kbd::KeyDown(key::Down) || kbd::KeyDown(key::S);
    connect(down, [this](){
        velocity -= acceleration * direction;
    });
}

void PlayerSpaceship::update()
{
    //Update position
    float m = velocity.magnitudeSquared();
    if(m > maxSpeedSquared) {
        velocity = velocity.unit() * maxSpeed;
    }
    moveBy(velocity);

    if(!(tank::Keyboard::isKeyDown(tank::Key::W)
     ||  tank::Keyboard::isKeyDown(tank::Key::S)
     ||  tank::Keyboard::isKeyDown(tank::Key::Up)
     ||  tank::Keyboard::isKeyDown(tank::Key::Down))) {
        velocity /= 1.08;
    }

    //Update angle
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

    tank::Camera& cam = tank::Game::world()->camera;
    cam.setPos(getPos() - cam.getOrigin());
}

void PlayerSpaceship::setRotation(float angle)
{
    auto rot = getRotation();
    Transformable::setRotation(angle);
    direction = direction.rotate(angle - rot);
}
