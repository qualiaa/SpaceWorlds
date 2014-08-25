#include "Hittable.hpp"

void Hittable::checkHit()
{
    auto bullets = collide(bulletType_);
    for (auto& bullet : bullets) {
        health_ -= 1;
        bullet->remove();
    }
    if (health_ <= 0) {
        remove();
    }
}