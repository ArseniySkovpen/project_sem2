#include "Item.h"

Item::Item(const std::string& name, int value):
  name_(name), value_(value) {
}

const std::string& Item::name() const {
  return name_;
}

int Item::value() const {
  return value_;
}

std::string Item::Use() const {
  return "Использован предмет: " + name_ + " (+" + std::to_string(value_) + " HP)";
}