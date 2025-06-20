#ifndef ENEMY_H
#define ENEMY_H

#include <string>

class Enemy {
public:
  Enemy(const std::string& name, int health, int damage,
    const std::string& description, const std::string& weak_spot);
  
  const std::string& name() const;
  int health() const;
  int max_health() const;
  int damage() const;
  const std::string& description() const;
  const std::string& weak_spot() const;
  
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

#endif  // ENEMY_H