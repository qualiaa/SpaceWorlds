#include "Bullet.hpp"
#include <functional>
#include <Tank/System/Game.hpp>
#include <Tank/Utility/Resources.hpp>
#include <Tank/Graphics/Image.hpp>
#include <Tank/Utility/Vector.hpp>
#include <Tank/Audio/SoundEffect.hpp>

const float Bullet::speed     {2};

Bullet::Bullet(tank::Vectorf pos, tank::Vectorf vel, tank::Vectorf direction, const std::string& type)
    : Entity(pos)
    , velocity{vel + direction * speed}
{

    setType(type);

    makeGraphic(Resources::get<tank::Image>("assets/graphics/bullet.png"));

    setRotation(tank::Vectorf{0,-1}.getAngle(direction));
    
    auto blast = Resources::get<tank::SoundEffect>("assets/sounds/shoot_sound.wav");
    //blast.setVolume(10);
    //blast.setRelativeToListener(false);
    blast.play();
}

void Bullet::update()
{

    moveBy(velocity);

}

void Bullet::setRotation(float angle)
{
    Transformable::setRotation(angle);
}