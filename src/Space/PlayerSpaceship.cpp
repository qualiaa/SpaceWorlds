#include "PlayerSpaceship.hpp"
#include <Tank/System/Game.hpp>
#include <Tank/System/Keyboard.hpp>
#include <limits>

const float PlayerSpaceship::acceleration {0.1};

PlayerSpaceship::PlayerSpaceship()
{
    setType("PlayerSpaceship");
    graphic = makeGraphic("assets/graphics/ship_beetle.png");
    setPos({90,90});

    setOrigin(graphic->getSize()/2);
    graphic->centreOrigin();
    setLayer(std::numeric_limits<int>::max());

    // centre hitbox, turning {0,0,w,h} into {-w,-h,w,h} / 2
    const auto oldHitbox = getHitbox();
    tank::Vectord newHitbox = {oldHitbox.w / 2, oldHitbox.y / 2};
    setHitbox({-newHitbox.x, -newHitbox.y, newHitbox.x, newHitbox.y});
}

void PlayerSpaceship::onAdded()
{
    using kbd = tank::Keyboard;
    using key = tank::Key;

    auto right = kbd::KeyDown(key::Right) || kbd::KeyDown(key::D);
    connect(right, [this](){
        setRotation(getRotation()+rotationAngle);
    });

    auto left = kbd::KeyDown(key::Left) || kbd::KeyDown(key::A);
    connect(left, [this](){
        setRotation(getRotation()-rotationAngle);
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
    moveBy(velocity);
    velocity /= 1.1;
    tank::Camera& cam = tank::Game::world()->camera;
    cam.setPos(getPos() - cam.getOrigin());
}

void PlayerSpaceship::setRotation(float angle)
{
    auto rot = getRotation();
    Transformable::setRotation(angle);
    direction = direction.rotate(angle - rot);
}
