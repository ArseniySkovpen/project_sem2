#include "Enemy.h"

Enemy::Enemy(const std::string& name, int health, int damage,
    const std::string& description, const std::string& weak_spot)
    : name_(name), health_(health), max_health_(health),
    damage_(damage), description_(description),
    weak_spot_(weak_spot) {}

const std::string& Enemy::name() const { return name_; }
int Enemy::health() const { return health_; }
int Enemy::max_health() const { return max_health_; }
int Enemy::damage() const { return damage_; }
const std::string& Enemy::description() const { return description_; }
const std::string& Enemy::weak_spot() const { return weak_spot_; }

void Enemy::TakeDamage(int damage) {
    health_ -= damage;
    if (health_ < 0) health_ = 0;
}

bool Enemy::IsAlive() const {
    return health_ > 0;
}