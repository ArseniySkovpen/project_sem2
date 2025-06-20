#ifndef PLAYER_H
#define PLAYER_H

#include "Item.h"
#include "Weapon.h"
#include <vector>
#include <memory>
#include "json.hpp"

using json = nlohmann::json;
extern json player_texts;

class Player {
public:
	Player();

	int health() const;
	int max_health() const;
	int honor() const;
	bool IsAlive() const;
	void TakeDamage(int damage);
	void Heal(int amount);
	void ChangeHonor(int amount);
	int AttackDamage() const;
	const Weapon* weapon() const;
	void EquipWeapon(std::unique_ptr<Weapon> weapon);

	const std::vector<Item>& inventory() const;
	size_t inventory_count() const;
	void AddItem(const Item& item);
	void UseItem(int index);
	void ShowInventory() const;

	const Item& GetItem(size_t index) const;

private:
	int health_;
	int max_health_;
	int honor_;
	std::unique_ptr<Weapon> weapon_;
	std::vector<Item> inventory_;
};

#endif  // PLAYER_H