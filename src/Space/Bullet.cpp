#include "Bullet.hpp"
#include <functional>
#include <Tank/System/Game.hpp>
#include <Tank/Utility/Resources.hpp>
#include <Tank/Graphics/Image.hpp>
#include <Tank/Utility/Vector.hpp>

const float Bullet::speed     {2};

Bullet::Bullet(tank::Vectorf pos, tank::Vectorf vel, tank::Vectorf direction)
    : Entity(pos)
    , velocity{vel + direction * speed}
{
    using res = tank::Resources;
    setType("bullet");
    makeGraphic(res::get<tank::Image>("assets/graphics/bullet.png"));
    setRotation(tank::Vectorf{0,-1}.getAngle(direction));

    lifeTimer.start();

    blast = res::get<tank::SoundEffect>("assets/sounds/shoot_sound.wav");
    blast.setVolume(100);
    blast.setPosition(getPos());
    blast.play();
}

void Bullet::update()
{
    using namespace std::literals;
    if (lifeTimer.getTime() > 3s)
    {
        remove();
    }
    moveBy(velocity);
}
