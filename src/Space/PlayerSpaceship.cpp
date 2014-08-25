#include "PlayerSpaceship.hpp"
#include <Tank/System/Game.hpp>
#include <Tank/System/Keyboard.hpp>
#include <limits>

const float PlayerSpaceship::acceleration {0.1};

PlayerSpaceship::PlayerSpaceship()
{
    setType("PlayerSpaceship");
    sprite = makeGraphic<tank::FrameList>(tank::Image{"assets/graphics/beetle.png"}, tank::Vectoru{16, 20});
    setPos({90,90});

    setOrigin(sprite->getSize()/2);
    sprite->centreOrigin();
    setLayer(std::numeric_limits<int>::max());
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