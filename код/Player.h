#pragma once
#ifndef PLAYER_H
#define PLAYER_H

#include <vector>
#include <string>
#include "Item.h"
#include "Weapon.h"

class Player {
public:
    Player();
    int GetHealth() const;
    int GetMaxHealth() const;
    int GetHonor() const;
    const std::vector<Item>& GetInventory() const;
    int GetInventoryCount() const;
    Weapon* GetWeapon() const;

    void Heal(int amount);
    void TakeDamage(int damage);
    void ChangeHonor(int amount);
    bool IsAlive() const;

    void AddItem(const Item& item);
    void UseItem(int index);
    void ShowInventory() const;
    void EquipWeapon(Weapon* weapon);
    int AttackDamage() const;

private:
    int health_;
    int max_health_;
    int honor_;
    std::vector<Item> inventory_;
    Weapon* equipped_weapon_;
};

#endif 