#include <iostream>
#include "Player.h"

using namespace std;

Player::Player() : health_(100), max_health_(100), honor_(50), equipped_weapon_(nullptr) {}

int Player::GetHealth() const { return health_; }
int Player::GetMaxHealth() const { return max_health_; }
int Player::GetHonor() const { return honor_; }
const vector<Item>& Player::GetInventory() const { return inventory_; }
int Player::GetInventoryCount() const { return inventory_.size(); }
Weapon* Player::GetWeapon() const { return equipped_weapon_; }

void Player::Heal(int amount) {
    health_ += amount;
    if (health_ > max_health_) health_ = max_health_;
}

void Player::TakeDamage(int damage) {
    health_ -= damage;
    if (health_ < 0) health_ = 0;
}

void Player::ChangeHonor(int amount) {
    honor_ += amount;
    if (honor_ > 100) honor_ = 100;
    if (honor_ < 0) honor_ = 0;
}

bool Player::IsAlive() const { return health_ > 0; }

void Player::AddItem(const Item& item) {
    if (inventory_.size() < 10) {
        inventory_.push_back(item);
    }
    else {
        cout << "��������� �����! ���������� �������� " << item.GetName() << ".\n";
    }
}

void Player::UseItem(int index) {
    if (index >= 0 && index < inventory_.size()) {
        if (inventory_[index].GetName() == "����� �������") {
            Heal(30);
            cout << "�� ������������ ����� ������� � ������������ 30 ��������!\n";
            inventory_.erase(inventory_.begin() + index); // ������� ����� �� ���������
        }
        else {
            cout << "�� �� ������ ������������ ���� �������!\n";
        }
    }
    else {
        cout << "�������� ������ ��������!\n";
    }
}

void Player::ShowInventory() const {
    cout << "=== ��������� ===\n";
    cout << "��������: " << health_ << "/" << max_health_ << "\n";
    cout << "�����: " << honor_ << "/100\n";
    if (equipped_weapon_) {
        cout << "������: " << equipped_weapon_->GetName() << " (����: " << equipped_weapon_->GetDamage() << ")";
        if (!equipped_weapon_->GetWeakSpot().empty()) {
            cout << " [�����������: " << equipped_weapon_->GetWeakSpot() << "]";
        }
        cout << "\n";
    }
    else {
        cout << "������: ��� (����: 1)\n";
    }

    cout << "\n�������� (" << inventory_.size() << "/10):\n";
    for (size_t i = 0; i < inventory_.size(); ++i) {
        cout << i + 1 << ". " << inventory_[i].GetName();
        if (inventory_[i].GetName() == "����� �������") {
            cout << " (+30 HP)";
        }
        cout << "\n";
    }
}

void Player::EquipWeapon(Weapon* weapon) {
    equipped_weapon_ = weapon;
}

int Player::AttackDamage() const {
    return equipped_weapon_ ? equipped_weapon_->GetDamage() : 1;
}