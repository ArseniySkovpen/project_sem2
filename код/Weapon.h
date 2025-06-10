#pragma once
#ifndef WEAPON_H
#define WEAPON_H

#include <string>

class Weapon {
public:
    Weapon(const std::string& name, int damage, std::string weak_spot = "");
    std::string GetName() const;
    int GetDamage() const;
    std::string GetWeakSpot() const;

private:
    std::string name_;
    int damage_;
    std::string weak_spot_;
};

#endif // WEAPON_H