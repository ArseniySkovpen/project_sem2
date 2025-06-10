#include "Enemy.h"

Enemy::Enemy(const std::string& name, int health, int damage, const std::string& description, std::string weak_spot)
    : name_(name), health_(health), max_health_(health), damage_(damage),
    description_(description), weak_spot_(weak_spot) {}

std::string Enemy::GetName() const { return name_; }
int Enemy::GetHealth() const { return health_; }
int Enemy::GetMaxHealth() const { return max_health_; }
int Enemy::GetDamage() const { return damage_; }
std::string Enemy::GetDescription() const { return description_; }
std::string Enemy::GetWeakSpot() const { return weak_spot_; }

void Enemy::TakeDamage(int damage) {
    health_ -= damage;
    if (health_ < 0) health_ = 0;
}

bool Enemy::IsAlive() const { return health_ > 0; }