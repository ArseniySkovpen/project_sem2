#include "Weapon.h"

Weapon::Weapon(const std::string& name, int damage, std::string weak_spot)
    : name_(name), damage_(damage), weak_spot_(weak_spot) {}

std::string Weapon::GetName() const { return name_; }
int Weapon::GetDamage() const { return damage_; }
std::string Weapon::GetWeakSpot() const { return weak_spot_; }