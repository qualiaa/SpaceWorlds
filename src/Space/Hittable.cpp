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

void Hittable::heal(int amt) {
	health_ += amt;
	if(health_ + amt > maxHealth_) {
		health_ = maxHealth_;
	}
}