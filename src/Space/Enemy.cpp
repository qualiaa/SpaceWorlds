#include "Enemy.hpp"

#include <chrono>
#include <Tank/System/Game.hpp>
#include <Tank/Utility/Resources.hpp>
#include "Universe.hpp"
#include "Player.hpp"
#include "Bullet.hpp"

const float Enemy::speed = 1;
std::uniform_real_distribution<float> angles {0, 360};

Enemy::Enemy() : Ship()
{
    std::uniform_int_distribution<int> rand {0, Universe::worldWidth};

    initAnimations("assets/graphics/beetle2.png");
    setType("enemy");
    setLayer(99);

    setPos({rand(Universe::randEng), rand(Universe::randEng)});
}

void Enemy::onAdded()
{
    bulletTimer_.start();
    auto angle = angles(Universe::randEng);
    setRotation(angle);
    player_ = static_cast<Universe&>(*getWorld()).getPlayer();
}

void Enemy::update()
{
    using namespace std::literals;

    //thrust();

    auto playerDisplacement = player_->getPos() - getPos();
    auto playerDistance = playerDisplacement.magnitude();
    auto playerAngle = direction.getAngle(playerDisplacement);

    if (playerDistance < 200) {
        if (playerAngle*playerAngle > 25) {
            rotate((playerAngle > 0) - (playerAngle < 0));
        } else {
            thrust();
            if (bulletTimer_.getTime() > 500ms) {
                shoot();
                bulletTimer_.start();
            }
        }
    } else {
        if (velocity.magnitude() > 2) {
            thrustTimer_.start();
        } else if (not thrustTimer_.isStarted()
                || thrustTimer_.getTime() > 500ms) {
            thrust();
            thrustTimer_.stop();
        }
    }


    Ship::update();
}
