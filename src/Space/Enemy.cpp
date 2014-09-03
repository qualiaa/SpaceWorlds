#include "Enemy.hpp"

#include <chrono>
#include <Tank/System/Game.hpp>
#include <Tank/Utility/Resources.hpp>
#include "Universe.hpp"
#include "PlayerSpaceship.hpp"
#include "Bullet.hpp"

const float Enemy::speed = 1;

Enemy::Enemy() : Hittable()
{
    using res = tank::Resources;
    std::uniform_real_distribution<float> rand_x {0,
        static_cast<float>(Universe::worldWidth)};

    std::uniform_real_distribution<float> rand_y {0,
        static_cast<float>(Universe::worldHeight)};

    auto& image = res::get<tank::Image>("assets/graphics/beetle2.png");

    sprite_ = makeGraphic<tank::FrameList>(image,
                                           tank::Vectoru{16,20},
                                           tank::Vectoru{1,1});

    sprite_->add("idle", {0}, std::chrono::milliseconds(1));
    sprite_->add("engine_start", {4,5,6,7}, std::chrono::milliseconds(250));
    sprite_->add("engine_stop", {7,6,5,4,4}, std::chrono::milliseconds(125));
    sprite_->add("engine_run", {6,7}, std::chrono::milliseconds(250));
    sprite_->add("engine_rotate", {4}, std::chrono::milliseconds(1));
    sprite_->select("engine_run");
    sprite_->start();

    setOrigin(sprite_->getSize() / 2);
    sprite_->centreOrigin();
    setLayer(99);

    setType("enemy");

    // centre hitbox
    const auto oldHitbox = getHitbox();
    setHitbox({-oldHitbox.w / 2, -oldHitbox.h / 2, oldHitbox.w, oldHitbox.h});

    setPos({rand_x(Universe::randEng), rand_y(Universe::randEng)});
}

void Enemy::onAdded()
{
    timer.start();
    bulletTimer.start();
    auto angle = angles(Universe::randEng);
    setRotation(angle);
    player_ = static_cast<Universe&>(*getWorld()).getPlayer();
}

void Enemy::setRotation(float angle)
{
    auto rot = getRotation();
    Transformable::setRotation(angle);
    direction = direction.rotate(angle - rot);
}

void Enemy::update()
{
    Hittable::update();
    using namespace std::literals;
    if (timer.getTime() > 5s) {
        timer.start();
        auto angle = angles(Universe::randEng);
        setRotation(angle);
    }
    if (bulletTimer.getTime() > 500ms && (getPos() - player_->getPos()).magnitude() < 200) {
        bulletTimer.start();
        auto dir = (player_->getPos() - getPos()).unit();
        getWorld()->makeEntity<Bullet>(getPos(), velocity, dir)->addType(getType());
    }

    velocity = direction * speed;
    moveBy(velocity);

    tank::Camera& cam = tank::Game::world()->camera;
    auto size = cam.getOrigin();

    //Thing Wrapping
    if(getPos().x < -size.x/2) {
        setPos(tank::Vectorf(Universe::worldWidth+size.x/2, getPos().y));
    }
    if(getPos().y < -size.y/2) {
        setPos(tank::Vectorf(getPos().x, Universe::worldWidth+size.y/2));
    }
    if(getPos().x > Universe::worldWidth + size.x/2) {
        setPos(tank::Vectorf(-size.x/2, getPos().y));
    }
    if(getPos().y > Universe::worldHeight + size.y/2) {
        setPos(tank::Vectorf(getPos().x, -size.y/2));
    }
}
