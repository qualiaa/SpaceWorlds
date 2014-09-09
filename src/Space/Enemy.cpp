#include "Enemy.hpp"

#include <chrono>
#include <Tank/System/Game.hpp>
#include <Tank/Utility/Resources.hpp>
#include "Universe.hpp"
#include "PlayerSpaceship.hpp"
#include "Bullet.hpp"

const float Enemy::speed = 1;
std::uniform_real_distribution<float> angles {0, 360};

Enemy::Enemy() : Ship()
{
    std::uniform_int_distribution<int> rand {0, Universe::worldWidth};

    initAnimations("assets/graphics/beetle2.png");
    setType("enemy");

    setPos({rand(Universe::randEng), rand(Universe::randEng)});
}

void Enemy::onAdded()
{
    timer_.start();
    bulletTimer_.start();
    auto angle = angles(Universe::randEng);
    setRotation(angle);
    player_ = static_cast<Universe&>(*getWorld()).getPlayer();
}

void Enemy::update()
{
    using namespace std::literals;

    thrust();
    Ship::update();

    if (timer_.getTime() > 5s) {
        setRotation(angles(Universe::randEng));
        timer_.start();
    }
    if (bulletTimer_.getTime() > 500ms && (getPos() - player_->getPos()).magnitude() < 200) {
        shoot();
        bulletTimer_.start();
    }
}
