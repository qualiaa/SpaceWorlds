#include "Hittable.hpp"
#include <Tank/Utility/Timer.hpp>

void Hittable::checkHit()
{
    auto bullets = collide(bulletType_);
    for (auto& bullet : bullets) {
        health_ -= 1;
        bullet->remove();
        tank::Timer::delay(std::chrono::milliseconds(10));
    }
    if (health_ <= 0) {
        remove();
    }
}
