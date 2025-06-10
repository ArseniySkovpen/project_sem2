#pragma once
#ifndef ENEMY_H
#define ENEMY_H

#include <string>

class Enemy {
public:
    Enemy(const std::string& name, int health, int damage, const std::string& description, std::string weak_spot = "");
    std::string GetName() const;
    int GetHealth() const;
    int GetMaxHealth() const;
    int GetDamage() const;
    std::string GetDescription() const;
    std::string GetWeakSpot() const;

    void TakeDamage(int damage);
    bool IsAlive() const;

private:
    std::string name_;
    int health_;
    int max_health_;
    int damage_;
    std::string description_;
    std::string weak_spot_;
};

#endif // ENEMY_H