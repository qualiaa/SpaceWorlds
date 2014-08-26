#include "Enemy.hpp"
#include <chrono>
#include "Universe.hpp"
#include <Tank/Utility/Resources.hpp>
#include "PlayerSpaceship.hpp"
#include "Bullet.hpp"

const float Enemy::speed = 1;

Enemy::Enemy() : Hittable(1, "PlayerBullet")
{
    std::uniform_real_distribution<float> rand_x {0,
        static_cast<float>(Universe::worldWidth)};
    
    std::uniform_real_distribution<float> rand_y {0,
        static_cast<float>(Universe::worldHeight)};
    
    auto& image = Resources::get<tank::Image>("assets/graphics/beetle2.png");
    
    sprite_ = makeGraphic<tank::FrameList>(image,
                                           tank::Vectoru{16,20},
                                           tank::Vectoru{1,1});
    
    sprite_->add("idle", {0}, std::chrono::milliseconds(1));
    sprite_->add("engine_start", {4,5,6,7}, std::chrono::milliseconds(250));
    sprite_->add("engine_stop", {7,6,5,4,4}, std::chrono::milliseconds(125));
    sprite_->add("engine_run", {6,7}, std::chrono::milliseconds(250));
    sprite_->add("engine_rotate", {4}, std::chrono::milliseconds(1));
    sprite_->select("idle", false);
    sprite_->start();
    
    setPos({rand_x(rand_eng), rand_y(rand_eng)});
}

void Enemy::onAdded()
{
    timer.start();
    bulletTimer.start();
    auto angle = angles(rand_eng);
    direction = direction.rotate(angle);
    player_ = static_cast<Universe&>(*getWorld()).getPlayer();
}

void Enemy::update()
{
    Hittable::update();
    using namespace std::literals;
    if (timer.getTime() > 5s) {
        timer.start();
        auto angle = angles(rand_eng);
        direction = direction.rotate(angle);
    }
    if (bulletTimer.getTime() > 500ms && (getPos() - player_->getPos()).magnitude() < 200) {
        bulletTimer.start();
        auto dir = (player_->getPos() - getPos()).unit();
        getWorld()->makeEntity<Bullet>(getPos(), velocity, dir, "EnemyBullet");
    }
    
    velocity = direction * speed;
    moveBy(velocity);
}