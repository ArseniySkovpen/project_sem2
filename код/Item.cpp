#include "Item.h"

Item::Item(const std::string& name, int value) : name_(name), value_(value) {}
std::string Item::GetName() const { return name_; }
int Item::GetValue() const { return value_; }