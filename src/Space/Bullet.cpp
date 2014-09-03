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
    
    blast = res::get<tank::SoundEffect>("assets/sounds/shoot_sound.wav");
    blast.setVolume(100);
    blast.setRelativeToListener(true);
    blast.play();
    lifeTimer.start();
}

void Bullet::update()
{
    using namespace std::literals;
    if (lifeTimer.getTime() > 10s)
    {
        remove();
    }
    moveBy(velocity);

}

void Bullet::setRotation(float angle)
{
    Transformable::setRotation(angle);
}
