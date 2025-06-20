#ifndef COMBAT_H
#define COMBAT_H

#include "Player.h"
#include "Enemy.h"
#include "json.hpp"
#include <string>
#include <memory>

using json = nlohmann::json;

class Combat {
public:
  static bool LoadData(const std::string& combat_file,
  const std::string& enemies_file,
  const std::string& player_texts_file = "assets/player_texts.json");
  
  static bool StartBattle(Player& player, const std::string& enemy_id,
    const std::string& win_message = "");

private:
  static json combat_data_;
  static json enemies_data_;
  static json player_texts_;
  
  static void PrintUi(const Player& player, const Enemy& enemy);
  static void PlayerTurn(Player& player, Enemy& enemy);
  static void EnemyTurn(Player& player, Enemy& enemy);
  static void PrintMessage(const std::string& key,
    const std::string& arg1 = "",
    const std::string& arg2 = "",
    int arg3 = 0);
  static void ShowInventory(Player& player);
  static std::string GetText(const std::string& key);
};

#endif  // COMBAT_H