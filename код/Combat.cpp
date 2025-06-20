#include "Combat.h"
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <limits>


json Combat::combat_data_;
json Combat::enemies_data_;
json Combat::player_texts_;

bool Combat::LoadData(const std::string& combat_file, const std::string& enemies_file, const std::string& player_texts_file) {
  try {
    std::ifstream combat_stream(combat_file);
    if (!combat_stream.is_open()) {
      std::cerr << "Failed to open: " << combat_file << std::endl;
      return false;
    }
    combat_stream >> combat_data_;
    
    std::ifstream enemies_stream(enemies_file);
    if (!enemies_stream.is_open()) {
      std::cerr << "Failed to open: " << enemies_file << std::endl;
      return false;
    }
    enemies_stream >> enemies_data_;
    
    std::ifstream player_texts_stream(player_texts_file);
    if (player_texts_stream.is_open()) {
      player_texts_stream >> player_texts_;
    }
    else {
      std::cerr << "Warning: Could not open " << player_texts_file << " (optional)" << std::endl;
    }
    return true;
  }
  catch (const std::exception& e) {
    std::cerr << "JSON parsing error: " << e.what() << std::endl;
    return false;
  }
}

bool Combat::StartBattle(Player& player, const std::string& enemy_id,
  const std::string& win_message) {
  if (!enemies_data_["enemies"].contains(enemy_id)) {
    return false;
  }
  
  auto& enemy_json = enemies_data_["enemies"][enemy_id];
  Enemy enemy(
    enemy_json["name"].get<std::string>(),
    enemy_json["health"].get<int>(),
    enemy_json["damage"].get<int>(),
    enemy_json["description"].get<std::string>(),
    enemy_json["weak_spot"].get<std::string>()
  );
  
  srand(static_cast<unsigned>(time(nullptr)));
  
  while (player.IsAlive() && enemy.IsAlive()) {
    PrintUi(player, enemy);
    PlayerTurn(player, enemy);
    if (!enemy.IsAlive()) break;
    EnemyTurn(player, enemy);
  }
  
  if (player.IsAlive()) {
    if (!win_message.empty()) {
      std::cout << win_message << "\n";
    }
    else {
      PrintMessage("enemy_defeated", enemy.name());
    }
    player.ChangeHonor(5);
    return true;
  }
  PrintMessage("game_over");
  return false;
}

void Combat::PrintUi(const Player& player, const Enemy& enemy)  {
  system("cls || clear");
  std::cout << GetText("combat.ui.header");
  std::cout << GetText("combat.ui.player_health") << player.health()
    << "/" << player.max_health() << "\n";
  std::cout << GetText("combat.ui.enemy_health") << enemy.name()
    << ": " << enemy.health() << "/" << enemy.max_health() << "\n";
  std::cout << GetText("combat.ui.separator") << "\n";
  
  if (!enemy.weak_spot().empty()) {
    std::cout << GetText("combat.ui.weak_spot_hint") << enemy.weak_spot() << "\n";
  }
}

void Combat::PlayerTurn(Player& player, Enemy& enemy) {
  for (const auto& action : combat_data_["combat"]["ui"]["choose_action"]) {
    std::cout << action.get<std::string>() << "\n";
  }
  
  int choice;
  while (!(std::cin >> choice) || choice < 1 || choice > 3) {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cout << GetText("combat.ui.errors.invalid_choice") << "\n";
  }
  
  switch (choice) {
  case 1: {
    std::cout << "\n" << GetText("combat.ui.attack_place_prompt") << "\n";
    for (const auto& option : combat_data_["combat"]["ui"]["attack_place_options"]) {
      std::cout << option.get<std::string>() << "\n";
    }
    
    int attack_type;
    while (!(std::cin >> attack_type) || attack_type < 1 || attack_type > 3) {
      std::cin.clear();
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
      std::cout << GetText("combat.ui.errors.invalid_choice") << "\n";
    }
    
    auto& attack = combat_data_["combat"]["system"]["attack_types"][attack_type - 1];
    float multiplier = attack["damage_multiplier"].get<float>();
    float hit_chance = attack["hit_chance"].get<float>();
    
    if ((rand() % 100) >= (hit_chance * 100)) {
      PrintMessage("miss");
      return;
    }
    
    int damage = static_cast<int>(player.AttackDamage() * multiplier);
    
    if (attack_type == 2) {
      int counter_damage = enemy.damage() / 2;
      player.TakeDamage(counter_damage);
      std::cout << GetText("combat.ui.powerful_attack_warning") << "\n";
      PrintMessage("enemy_attack", enemy.name(), "", counter_damage);
    }
    else if (attack_type == 3) {
      PrintMessage("critical_hit");
      PrintMessage("weak_spot_hit");
    }
    
    enemy.TakeDamage(damage);
    PrintMessage("player_attack", enemy.name(), "", damage);
    break;
  }
  case 2:
    ShowInventory(player);
    break;
  case 3:
    if ((rand() % 100) < (combat_data_["combat"]["system"]["escape_chance"].get<float>() * 100)) {
      PrintMessage("escape_success");
      return;
    }
    PrintMessage("escape_fail");
    break;
  }
  
  std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
  std::cin.get();
}

void Combat::EnemyTurn(Player& player, Enemy& enemy) {
  if (!enemy.IsAlive()) return;
  int damage = enemy.damage();
  player.TakeDamage(damage);
  PrintMessage("enemy_attack", enemy.name(), "", damage);
  
  std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
  std::cin.get();
}

void Combat::PrintMessage(const std::string& key, const std::string& arg1,
  const std::string& arg2, int arg3) {
  try {
    std::string message = combat_data_["combat"]["system"]["messages"][key].get<std::string>();
    
    size_t pos;
    while ((pos = message.find("{player_name}")) != std::string::npos) {
      message.replace(pos, 13, "You");
    }
    while ((pos = message.find("{enemy_name}")) != std::string::npos) {
      message.replace(pos, 12, arg1);
    }
    while ((pos = message.find("{damage}")) != std::string::npos) {
      message.replace(pos, 8, std::to_string(arg3));
    }
    
    std::cout << message << "\n";
  }
  catch (...) {
    std::cout << "[Message not found: " << key << "]\n";
  }
}

void Combat::ShowInventory(Player& player) {
  if (player.inventory_count() == 0) {
    std::cout << GetText("errors.no_items") << "\n";
    return;
  }
  
  std::cout << "\n" << GetText("inventory.header") << "\n";
  std::cout << GetText("inventory.health_label") << player.health()
    << "/" << player.max_health() << "\n";
  std::cout << GetText("inventory.honor_label") << player.honor() << "\n";
  
  std::cout << GetText("inventory.weapon_label");
  if (player.weapon()) {
    std::cout << player.weapon()->get_name()
      << " (" << GetText("inventory.damage_label")
      << ": " << player.weapon()->get_damage() << ")";
  }
  else {
    std::cout << GetText("inventory.weapon_none");
  }
  std::cout << "\n";
  
  std::cout << GetText("inventory.items_label") << player.inventory_count() << "):\n";
  for (size_t i = 0; i < player.inventory_count(); ++i) {
    const Item& item = player.GetItem(i);
    std::cout << (i + 1) << ". " << item.name()
      << " (+" << item.value() << " HP)\n";
  }
  
  std::cout << "\n" << GetText("inventory.choose_inventory_item");
  int choice;
  while (!(std::cin >> choice) || choice < 1 || choice > player.inventory_count()) {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cout << GetText("errors.invalid_item_index") << "\n";
  }
  
  player.UseItem(choice - 1);
}

std::string Combat::GetText(const std::string& key) {
  try {
    if (player_texts_.contains(key)) {
      return player_texts_[key].get<std::string>();
    }
    
    std::vector<std::string> parts;
    size_t start = 0;
    size_t end = key.find('.');
    
    while (end != std::string::npos) {
      parts.push_back(key.substr(start, end - start));
      start = end + 1;
      end = key.find('.', start);
    }
    parts.push_back(key.substr(start));
    
    json* current = &combat_data_;
    for (size_t i = 0; i < parts.size(); ++i) {
      if (!current->contains(parts[i])) break;
      if (i == parts.size() - 1) {
        if ((*current)[parts[i]].is_string()) {
          return (*current)[parts[i]].get<std::string>();
        }
        else if ((*current)[parts[i]].is_array()) {
          std::string result;
          for (const auto& line : (*current)[parts[i]]) {
            result += line.get<std::string>() + "\n";
          }
          return result;
        }
      }
      current = &(*current)[parts[i]];
    }
    return "[" + key + " not found]";
  }
  catch (...) {
      return "[Text loading error]";
  }
}