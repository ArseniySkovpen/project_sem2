#ifndef WEAPON_H
#define WEAPON_H

#include <string>

class Weapon {
public:
	Weapon(const std::string& name, int damage, const std::string& equip_text);

	const std::string& get_name() const;
	int get_damage() const;
	const std::string& get_equip_text() const;

private:
	std::string name_;
	int damage_;
	std::string equip_text_;
};

#endif  // WEAPON_H