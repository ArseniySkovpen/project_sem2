#include "Weapon.h"

Weapon::Weapon(const std::string& name, int damage, const std::string& equip_text)
  : name_(name), damage_(damage), equip_text_(equip_text) {}

const std::string& Weapon::get_name() const {
  return name_;
}

int Weapon::get_damage() const {
  return damage_;
}

const std::string& Weapon::get_equip_text() const {
  return equip_text_;
}