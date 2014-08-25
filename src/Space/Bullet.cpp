#include "Bullet.hpp"
#include <functional>
#include <Tank/System/Game.hpp>
#include <Tank/Utility/Resources.hpp>
#include <Tank/Graphics/Image.hpp>
#include <Tank/Utility/Vector.hpp>

const float Bullet::speed     {2};

Bullet::Bullet(tank::Vectorf pos, tank::Vectorf direction, const std::string& type)
    : Entity(pos)
    , velocity{direction * speed}
{

    setType(type);

    makeGraphic(Resources::get<tank::Image>("assets/graphics/bullet.png"));

    setRotation(tank::Vectorf{0,-1}.getAngle(direction));

}

void Bullet::update()
{

    moveBy(velocity);

}

void Bullet::setRotation(float angle)
{
    Transformable::setRotation(angle);
}