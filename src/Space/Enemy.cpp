#include "Enemy.hpp"
#include <chrono>
#include "Universe.hpp"
#include <Tank/Utility/Resources.hpp>

const float Enemy::speed = 1;

Enemy::Enemy() : Hittable(5, "PlayerBullet")
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
    auto angle = angles(rand_eng);
    direction = direction.rotate(angle);
}

void Enemy::update()
{
    using namespace std::literals;
    if (timer.getTime() > 10s) {
        timer.start();
        auto angle = angles(rand_eng);
        direction = direction.rotate(angle);
    }
    
    velocity = direction * speed;
    moveBy(velocity);
}