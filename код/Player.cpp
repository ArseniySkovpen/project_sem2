#include "Player.h"
#include <iostream>
#include <algorithm>

Player::Player()
    : health_(100), max_health_(100), honor_(50) {}

int Player::health() const { return health_; }
int Player::max_health() const { return max_health_; }
int Player::honor() const { return honor_; }
bool Player::IsAlive() const { return health_ > 0; }

void Player::TakeDamage(int damage) {
    health_ -= damage;
    if (health_ < 0) health_ = 0;
}

void Player::Heal(int amount) {
    health_ = std::min(health_ + amount, max_health_);
}

void Player::ChangeHonor(int amount) {
    honor_ += amount;
    honor_ = std::max(0, std::min(honor_, 100));
}

int Player::AttackDamage() const {
    return weapon_ ? weapon_->get_damage() : 1;
}

const Weapon* Player::weapon() const { return weapon_.get(); }

void Player::EquipWeapon(std::unique_ptr<Weapon> weapon) {
    weapon_ = std::move(weapon);
    if (weapon_) {
        std::cout << weapon_->get_equip_text() << std::endl;
    }
}

const std::vector<Item>& Player::inventory() const { return inventory_; }
size_t Player::inventory_count() const { return inventory_.size(); }

void Player::AddItem(const Item& item) {
    inventory_.push_back(item);
}

void Player::UseItem(int index) {
    if (index < 0 || static_cast<size_t>(index) >= inventory_.size()) {
        throw std::out_of_range("Invalid item index");
    }

    int heal_value = inventory_[index].value();
    inventory_.erase(inventory_.begin() + index);
    Heal(heal_value);
}

void Player::ShowInventory() const {
    std::cout << player_texts["inventory"]["inventory_header"].get<std::string>() << "\n";
    std::cout << player_texts["inventory"]["health_label"].get<std::string>()
        << health_ << "/" << max_health_ << "\n";
    std::cout << player_texts["inventory"]["honor_label"].get<std::string>() << honor_ << "\n";

    std::cout << player_texts["inventory"]["weapon_label"].get<std::string>();
    if (weapon_) {
        std::cout << weapon_->get_name()
            << " (" << player_texts["inventory"]["damage_label"].get<std::string>()
            << ": " << weapon_->get_damage() << ")";
    }
    else {
        std::cout << player_texts["inventory"]["weapon_none"].get<std::string>();
    }
    std::cout << "\n";

    std::cout << player_texts["inventory"]["items_label"].get<std::string>()
        << inventory_.size() << "):\n";
    for (size_t i = 0; i < inventory_.size(); ++i) {
        std::cout << (i + 1) << ". " << inventory_[i].name()
            << " (+" << inventory_[i].value() << " HP)\n";
    }

    if (inventory_.empty()) {
        std::cout << player_texts["inventory"]["inventory_empty"].get<std::string>() << "\n";
    }
}

const Item& Player::GetItem(size_t index) const {
    if (index >= inventory_.size()) {
        throw std::out_of_range("Item index out of range");
    }
    return inventory_[index];
}