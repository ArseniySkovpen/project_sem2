#include <iostream>
#include <cstdlib>
#include <fstream>
#include <limits>
#include <string>
#include <vector>

#include "Circles.h"
#include "Enemy.h"
#include "Item.h"
#include "Player.h"
#include "Weapon.h"
#include "Combat.h"

#include "json.hpp"
using json = nlohmann::json;

using namespace std;

extern Player player;
extern int current_circle;

static json circle_asset;
json items_asset;

void ClearScreen() {
  system("clear || cls");
}

void WaitKey() {
  if (cin.rdbuf()->in_avail()) {
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
  }
  cin.get();
}

bool LoadItemsAsset(const std::string& filename) {
  ifstream file(filename);
  if (!file.is_open()) {
    cerr << circle_asset["errors"]["items_load_failed"].get<string>() << filename << endl;
    return false;
  }
  try {
    file >> items_asset;
  }
  catch (json::parse_error& e) {
    cerr << circle_asset["errors"]["json_parse_error"].get<string>() << e.what() << endl;
    return false;
  }
  return true;
}

bool LoadCircleAsset(const std::string& filename) {
  ifstream file(filename);
  if (!file.is_open()) {
    cerr << circle_asset["errors"]["circle_load_failed"].get<string>() << filename << endl;
    return false;
  }
  try {
    file >> circle_asset;
  }
  catch (json::parse_error& e) {
    cerr << circle_asset["errors"]["json_parse_error"].get<string>() << e.what() << endl;
    return false;
  }
  return true;
}

void PrintArray(const json& arr) {
  for (const auto& line : arr) {
  cout << line.get<string>() << "\n";
  }
}

void PrintDelay(const json& arr) {
  for (const auto& line : arr) {
    cout << line.get<string>() << "\n";
    WaitKey();
  }
}

void Circle1()  {
  if (!LoadCircleAsset("assets/circle1.json")) {
    cerr << "Ошибка: не удалось загрузить circle1.json!" << endl;
    return;
  }
  if (!LoadItemsAsset("assets/items.json")) {
    cerr << "Failed to load items.json!" << endl;
    return;
  }
  ClearScreen();
  PrintArray(circle_asset["title"]);
  
  PrintArray(circle_asset["description_intro"]);
  
  int choice;
  cin >> choice;
  
  if (choice == 1) {
    ClearScreen();
    cout << circle_asset["path_light_text"].get<string>() << "\n";
    WaitKey();
  }
  else {
    ClearScreen();
    cout << circle_asset["path_stay_text"].get<string>() << "\n";
    WaitKey();
  }
  
  ClearScreen();
  cout << circle_asset["after_light_description"].get<string>() << "\n\n";
  
  PrintDelay(circle_asset["dialogues"]);
  
  PrintArray(circle_asset["description_after_dialog"]);
  
  cin >> choice;
  
  if (choice == 1) {
    ClearScreen();
    PrintDelay(circle_asset["find_potions"]);
     
    player.AddItem(Item(
      items_asset["potions"]["healing_potion"]["name"].get<string>(),
      items_asset["potions"]["healing_potion"]["value"].get<int>()
    ));
    player.AddItem(Item(
      items_asset["potions"]["healing_potion"]["name"].get<string>(),
      items_asset["potions"]["healing_potion"]["value"].get<int>()
    ));
    
    player.EquipWeapon(std::make_unique<Weapon>(
      items_asset["weapons"]["rusty_dagger"]["name"].get<string>(),
      items_asset["weapons"]["rusty_dagger"]["damage"].get<int>(),
      items_asset["weapons"]["rusty_dagger"]["equip_text"].get<string>()
    ));
    WaitKey();
  }

  else {
    ClearScreen();
    PrintDelay(circle_asset["talk_to_people"]);
    
    player.AddItem(Item(
      items_asset["potions"]["healing_potion"]["name"].get<string>(),
      items_asset["potions"]["healing_potion"]["value"].get<int>()
    ));
    player.AddItem(Item(
      items_asset["potions"]["healing_potion"]["name"].get<string>(),
      items_asset["potions"]["healing_potion"]["value"].get<int>()
    ));
    
    WaitKey();
    
    player.EquipWeapon(std::make_unique<Weapon>(
      items_asset["weapons"]["rusty_dagger"]["name"].get<string>(),
      items_asset["weapons"]["rusty_dagger"]["damage"].get<int>(),
      items_asset["weapons"]["rusty_dagger"]["equip_text"].get<string>()
    ));
    WaitKey();
    }
  
  ClearScreen();
  
  PrintArray(circle_asset["pier"]);
  
  cin >> choice;
  
  if (choice == 1) {
    ClearScreen();
    PrintDelay(circle_asset["rope_choice1_fail"]);
    player.TakeDamage(10);
    player.ChangeHonor(-10);
  }
  else {
    ClearScreen();
    PrintDelay(circle_asset["rope_choice2_success"]);
    player.ChangeHonor(5);
  }
  
  ClearScreen();
  PrintDelay(circle_asset["charon_dialog"]);
  
  current_circle = 2;
  SetCheckpoint();
  Circle2();
  return;
}

void Circle2() {
  if (!LoadCircleAsset("assets/circle2.json")) {
    cerr << "Ошибка: не удалось загрузить circle2.json!" << endl;
    return;
  }
  if (!LoadItemsAsset("assets/items.json")) {
    cerr << "Failed to load items.json!" << endl;
    return;
  }
  if (!Combat::LoadData("assets/combat_system.json", "assets/enemies.json")) {
    cerr << "Ошибка загрузки боевых данных!" << endl;
    return;
  }
  
  ClearScreen();
  PrintArray(circle_asset["title"]);
  
  PrintArray(circle_asset["description"]);
  
  WaitKey();
  ClearScreen();
  
  PrintArray(circle_asset["minos_dialog"]);
  
  int choice;
  cin >> choice;
  
  if (choice == 1) {
    ClearScreen();
    PrintDelay(circle_asset["convince_success"]);
    player.ChangeHonor(10);
  }
  if (choice == 2) {
    bool result = Combat::StartBattle(player, "minos", circle_asset["win_minos"].get<string>());
    if (result) {
      WaitKey();
      ClearScreen();
    }
  }
  if(choice==3) {
    if (player.honor() > 60) {
      PrintDelay(circle_asset["request_success"]);
      player.ChangeHonor(5);
      WaitKey();
    }
    else {
      PrintArray(circle_asset["request_fail"]);
      WaitKey();
      choice = 2;
    }
  }
  ClearScreen();
  PrintArray(circle_asset["francesca_encounter"]);
  
  cin >> choice;
  
  if (choice == 1) {
    PrintArray(circle_asset["francesca_story"]);
        
    cin >> choice;
    
    if (choice == 1) {
      player.ChangeHonor(-10);
      PrintArray(circle_asset["comfort_response"]);
    }
    else {
      player.ChangeHonor(5);
      cout << circle_asset["judge_response"].get<string>() << "\n";
    }
  }
  else {
    cout << circle_asset["leave"].get<string>() << "\n";
  }
  
  WaitKey();
    
  PrintDelay(circle_asset["francesca_end"]);
  
  player.AddItem(Item(
    items_asset["potions"]["healing_potion"]["name"].get<string>(),
    items_asset["potions"]["healing_potion"]["value"].get<int>()
  ));
  player.AddItem(Item(
    items_asset["potions"]["healing_potion"]["name"].get<string>(),
    items_asset["potions"]["healing_potion"]["value"].get<int>()
  ));
  
  ClearScreen();
  PrintDelay(circle_asset["circle_travel"]);
  
  player.EquipWeapon(std::make_unique<Weapon>(
    items_asset["weapons"]["wanderer_staff"]["name"].get<string>(),
    items_asset["weapons"]["wanderer_staff"]["damage"].get<int>(),
    items_asset["weapons"]["wanderer_staff"]["equip_text"].get<string>()
  ));

  WaitKey();
  
  cout << circle_asset["circle_end"].get<string>();

  current_circle = 3;
  SetCheckpoint();
  Circle3();
  return;
}

void Circle3() {
  if (!LoadCircleAsset("assets/circle3.json")) {
    cerr << "Ошибка: не удалось загрузить circle3.json!" << endl;
    return;
  }
  if (!LoadItemsAsset("assets/items.json")) {
    cerr << "Failed to load items.json!" << endl;
    return;
  }
  if (!Combat::LoadData("assets/combat_system.json", "assets/enemies.json")) {
    cerr << "Failed to load combat data!" << endl;
    return;
  }
  
  ClearScreen();
  PrintArray(circle_asset["title"]);
  cout << circle_asset["description"].get<string>() << "\n\n";
  WaitKey();
  
  PrintArray(circle_asset["pre_choice"]);
  
  int choice;
  cin >> choice;
  
  if (choice == 1) {
    cout << circle_asset["lire_play"].get<string>() << "\n";
    WaitKey();
    cout << circle_asset["sleep_cerberus"].get<string>() << "\n";
  }
  else {
    cout << circle_asset["meat_throw"].get<string>() << "\n";
    WaitKey();
    
    bool result = Combat::StartBattle(player, "cerberus", circle_asset["win_cerberus"].get<string>());
    if (result) {
      WaitKey();
      ClearScreen();
    }
  }
  
  WaitKey();
  player.EquipWeapon(std::make_unique<Weapon>(
    items_asset["weapons"]["butcher_axe"]["name"].get<string>(),
    items_asset["weapons"]["butcher_axe"]["damage"].get<int>(),
    items_asset["weapons"]["butcher_axe"]["equip_text"].get<string>()
  ));
  WaitKey();
  ClearScreen();
 
  PrintDelay(circle_asset["circle_travel"]);
  
  player.AddItem(Item(
    items_asset["potions"]["healing_potion"]["name"].get<string>(),
    items_asset["potions"]["healing_potion"]["value"].get<int>()
  ));
  player.AddItem(Item(
    items_asset["potions"]["healing_potion"]["name"].get<string>(),
    items_asset["potions"]["healing_potion"]["value"].get<int>()
  ));
    
  PrintArray(circle_asset["sinner_encounter"]);
  
  cin >> choice;
  
  if (choice == 1) {
    cout << circle_asset["help_sinner_text_yes"].get<string>();
    player.ChangeHonor(-5);
  }
  else {
    cout << circle_asset["help_sinner_text_no"].get<string>();
    player.ChangeHonor(5);
  }
  WaitKey();
  cout << circle_asset["circle_end"].get<string>();
  
  current_circle = 4;
  SetCheckpoint();
  Circle4();
  return;
}

void Circle4() {
  if (!LoadCircleAsset("assets/circle4.json")) {
    cerr << "Ошибка: не удалось загрузить circle4.json!" << endl;
    return;
  }
  if (!LoadItemsAsset("assets/items.json")) {
    cerr << "Failed to load items.json!" << endl;
    return;
  }
  if (!Combat::LoadData("assets/combat_system.json", "assets/enemies.json")){
    cerr << "Failed to load combat data!" << endl;
    return;
  }
  
  ClearScreen();
  PrintArray(circle_asset["title"]);
  
  cout << circle_asset["description"].get<string>() << "\n\n";
  
  PrintArray(circle_asset["plutos_words"]);
  
  int choice;
  cin >> choice;
  
  if (choice == 2) {
    bool result = Combat::StartBattle(player, "plutus", circle_asset["win_plutus"].get<string>());
    if (result) {
      WaitKey();
      ClearScreen();
    }
  }
  if (choice == 1) {
    ClearScreen();
    PrintDelay(circle_asset["plutos_dialog"]);
        
    PrintArray(circle_asset["plutos_question"]);
    cin >> choice;
    
    if (choice == 1) {
      PrintDelay(circle_asset["incorrect"]);
      WaitKey();
      choice = 2;
    }
    else {
      cout << circle_asset["correct"].get<string>();
      WaitKey();
    }
  }
  if (choice == 3) {
    ClearScreen();
    PrintDelay(circle_asset["becom_sinner"]);
  }
  
  ClearScreen();
  PrintDelay(circle_asset["circle_travel"]);
  WaitKey();
  
  player.EquipWeapon(std::make_unique<Weapon>(
    items_asset["weapons"]["golden_dagger"]["name"].get<string>(),
    items_asset["weapons"]["golden_dagger"]["damage"].get<int>(),
    items_asset["weapons"]["golden_dagger"]["equip_text"].get<string>()
  ));
  WaitKey();
  
  player.AddItem(Item(
    items_asset["potions"]["healing_potion"]["name"].get<string>(),
    items_asset["potions"]["healing_potion"]["value"].get<int>()
  ));
  player.AddItem(Item(
    items_asset["potions"]["healing_potion"]["name"].get<string>(),
    items_asset["potions"]["healing_potion"]["value"].get<int>()
  ));
  
  WaitKey();
  cout << circle_asset["circle_end"].get<string>();
  
  current_circle = 5;
  SetCheckpoint();
  Circle5();
  return;
}

void Circle5() {
  if (!LoadCircleAsset("assets/circle5.json")) {
    cerr << "Ошибка: не удалось загрузить circle5.json!" << endl;
    return;
  }
  if (!LoadItemsAsset("assets/items.json")) {
    cerr << "Failed to load items.json!" << endl;
    return;
  }
  if (!Combat::LoadData("assets/combat_system.json", "assets/enemies.json")) {
    cerr << "Failed to load combat data!" << endl;
    return;
  }
  
  ClearScreen();
  PrintArray(circle_asset["title"]);
  cout << circle_asset["description"].get<string>() << "\n\n";
  
  PrintArray(circle_asset["phlegyas_intro"]);
    
  int choice;
  cin >> choice;
  
  if (choice == 2) {
    PrintDelay(circle_asset["refuse_boat"]);
    
    bool result = Combat::StartBattle(player, "phlegyas", circle_asset["win_phlegyas"].get<string>());
    if (result) {
      WaitKey();
      ClearScreen();
    }
    
    player.EquipWeapon(std::make_unique<Weapon>(
      items_asset["weapons"]["silver_sword"]["name"].get<string>(),
      items_asset["weapons"]["silver_sword"]["damage"].get<int>(),
      items_asset["weapons"]["silver_sword"]["equip_text"].get<string>()
    ));
    WaitKey();
    }
  else {
    ClearScreen();
    PrintArray(circle_asset["sit_boat"]);
    
    cin >> choice;
    
    if (choice == 1) {
      PrintDelay(circle_asset["explain_mission"]);
      player.ChangeHonor(10);
      
      player.EquipWeapon(std::make_unique<Weapon>(
        items_asset["weapons"]["silver_sword"]["name"].get<string>(),
        items_asset["weapons"]["silver_sword"]["damage"].get<int>(),
        items_asset["weapons"]["silver_sword"]["equip_text"].get<string>()
      ));
      
      player.AddItem(Item(
        items_asset["potions"]["healing_potion"]["name"].get<string>(),
        items_asset["potions"]["healing_potion"]["value"].get<int>()
      ));
      player.AddItem(Item(
        items_asset["potions"]["healing_potion"]["name"].get<string>(),
        items_asset["potions"]["healing_potion"]["value"].get<int>()
      ));
      WaitKey();
    }
    else {
      bool result = Combat::StartBattle(player, "phlegyas", circle_asset["win_phlegyas"].get<string>());
      if (result) {
        WaitKey();
        ClearScreen();
      }
      
      player.EquipWeapon(std::make_unique<Weapon>(
        items_asset["weapons"]["silver_sword"]["name"].get<string>(),
        items_asset["weapons"]["silver_sword"]["damage"].get<int>(),
        items_asset["weapons"]["silver_sword"]["equip_text"].get<string>()
      ));
         
      player.AddItem(Item(
        items_asset["potions"]["healing_potion"]["name"].get<string>(),
        items_asset["potions"]["healing_potion"]["value"].get<int>()
      ));
      player.AddItem(Item(
        items_asset["potions"]["healing_potion"]["name"].get<string>(),
        items_asset["potions"]["healing_potion"]["value"].get<int>()
      ));
      WaitKey();
    }
  }
  ClearScreen();
  PrintArray(circle_asset["stix_spirit_encounter"]);
    
  cin >> choice;
  
  if (choice == 1) {
    PrintDelay(circle_asset["hit_spirit"]);
    player.ChangeHonor(5);
  }
  else {
    PrintDelay(circle_asset["calm_spirit"]);
    player.ChangeHonor(-5);
  }
  
  PrintArray(circle_asset["fallen_angel_encounter"]);
   
  cin >> choice;
  
  if (choice == 1) {
    PrintDelay(circle_asset["use_silver"]);
    player.ChangeHonor(-10);
  }
  else {
    PrintDelay(circle_asset["convince_angel"]);
    player.ChangeHonor(10);
  }
  
  cout << circle_asset["circle_end"].get<string>();
  
  current_circle = 6;
  SetCheckpoint();
  Circle6();
  return;
}

void Circle6() {
  if (!LoadCircleAsset("assets/circle6.json")) {
    cerr << "Ошибка: не удалось загрузить circle6.json!" << endl;
    return;
  }
  if (!LoadItemsAsset("assets/items.json")) {
    cerr << "Failed to load items.json!" << endl;
    return;
  }
  if (!Combat::LoadData("assets/combat_system.json", "assets/enemies.json")) {
    cerr << "Failed to load combat data!" << endl;
    return;
  }
  ClearScreen();
  PrintArray(circle_asset["title"]);
  cout << circle_asset["description"].get<string>() << "\n\n";
  WaitKey();
  
  PrintArray(circle_asset["farinata_dialog"]);
  
  int choice;
  cin >> choice;

  if (choice == 1) {
    PrintDelay(circle_asset["tell_truth"]);
  }
  else {
    PrintDelay(circle_asset["ask_sin"]);
  }
  
  PrintDelay(circle_asset["epicure_shadow"]);
  
  cin >> choice;
  
  if (choice == 1) {
    cout << circle_asset["agree_shadow"].get<string>() << "\n";
    player.ChangeHonor(-10);
  }
  else {
    PrintDelay(circle_asset["disagree_shadow"]);
    player.ChangeHonor(5);
  }
  ClearScreen();
  PrintArray(circle_asset["fury_encounter"]);
    
  cin >> choice;
  
  if (choice == 1) {
    player.EquipWeapon(std::make_unique<Weapon>(
      items_asset["weapons"]["flaming_sword"]["name"].get<string>(),
      items_asset["weapons"]["flaming_sword"]["damage"].get<int>(),
      items_asset["weapons"]["flaming_sword"]["equip_text"].get<string>()
    ));
    
    WaitKey();
    PrintArray(circle_asset["take_fire"]);
      
    cin >> choice;
    
    if (choice == 1) {
      PrintDelay(circle_asset["fire_omit"]);
      player.ChangeHonor(5);
      
      player.AddItem(Item(
        items_asset["potions"]["healing_potion"]["name"].get<string>(),
        items_asset["potions"]["healing_potion"]["value"].get<int>()
      ));
      player.AddItem(Item(
        items_asset["potions"]["healing_potion"]["name"].get<string>(),
        items_asset["potions"]["healing_potion"]["value"].get<int>()
      ));
    }
    else{
      PrintDelay(circle_asset["scare"]);
      player.ChangeHonor(-10);
    }
  }
  if(choice==2) {
    bool result = Combat::StartBattle(player, "fury", circle_asset["win_fury"].get<string>());
    if (result) {
      WaitKey();
      ClearScreen();
    }
  }
  else {
    PrintDelay(circle_asset["convince_fury"]);
    choice = 2;
  }

  cout << circle_asset["circle_end"].get<string>();
  
  current_circle = 7;
  SetCheckpoint();
  Circle7();
  return;
}

void Circle7() {
  if (!LoadCircleAsset("assets/circle7.json")) {
    cerr << "Ошибка: не удалось загрузить circle7.json!" << endl;
    return;
  }
  if (!LoadItemsAsset("assets/items.json")) {
    cerr << "Failed to load items.json!" << endl;
    return;
  }
  if (!Combat::LoadData("assets/combat_system.json", "assets/enemies.json")) {
    cerr << "Failed to load combat data!" << endl;
    return;
  }
  ClearScreen();
  PrintArray(circle_asset["title"]);
  cout << circle_asset["description"].get<string>() << "\n\n";
  
  PrintArray(circle_asset["first_belt_intro"]);
   
  int choice;
  cin >> choice;
  
  if (choice == 1) {
    PrintDelay(circle_asset["pay_success"]);
    player.ChangeHonor(-10);
  }
  if (choice == 2) {
    PrintDelay(circle_asset["wade_fail"]);
    player.TakeDamage(30);
    player.ChangeHonor(-5);
  }
  else {
    bool result = Combat::StartBattle(player, "nessus", circle_asset["win_nessus"].get<string>());
    if (result) {
      WaitKey();
      ClearScreen();
    }
  }
  
  PrintArray(circle_asset["second_belt_intro"]);
  
  cin >> choice;
  if (choice == 1) {
    PrintDelay(circle_asset["chop_tree"]);
    player.ChangeHonor(-15);
  }
  if (choice == 2) {
    PrintDelay(circle_asset["ignore"]);
    player.ChangeHonor(5);
  }
  else {
    PrintDelay(circle_asset["fight_harpies"]);
    player.ChangeHonor(+10);
  }
  
  PrintArray(circle_asset["third_belt_intro"]);
  
  cin >> choice;
  
  if (choice == 3) {
    bool result = Combat::StartBattle(player, "minotaur", circle_asset["win_minotaur"].get<string>());
    if (result) {
      WaitKey();
      ClearScreen();
    }
    
    player.AddItem(Item(
      items_asset["potions"]["healing_potion"]["name"].get<string>(),
      items_asset["potions"]["healing_potion"]["value"].get<int>()
    ));
    player.AddItem(Item(
      items_asset["potions"]["healing_potion"]["name"].get<string>(),
      items_asset["potions"]["healing_potion"]["value"].get<int>()
    ));
    player.EquipWeapon(std::make_unique<Weapon>(
      items_asset["weapons"]["bone_sword"]["name"].get<string>(),
      items_asset["weapons"]["bone_sword"]["damage"].get<int>(),
      items_asset["weapons"]["bone_sword"]["equip_text"].get<string>()
    ));
        
    WaitKey();
    }
  
  if (choice == 1) {
    PrintDelay(circle_asset["sneak_success"]);
  }
  if (choice == 2) {
    PrintDelay(circle_asset["sneak_fail"]);
    choice = 3;
  }
  
  cout << circle_asset["circle_end"].get<string>();
  
  current_circle = 8;
  SetCheckpoint();
  Circle8();
  return;
}

void Circle8() {
  if (!LoadCircleAsset("assets/circle8.json")) {
    cerr << "Ошибка: не удалось загрузить circle8.json!" << endl;
    return;
  }
  if (!LoadItemsAsset("assets/items.json")) {
    cerr << "Failed to load items.json!" << endl;
    return;
  }
  if (!Combat::LoadData("assets/combat_system.json", "assets/enemies.json")) {
    cerr << "Failed to load combat data!" << endl;
    return;
  }
  ClearScreen();
  PrintArray(circle_asset["title"]);
  cout << circle_asset["description"].get<string>() << "\n\n";
  
  PrintArray(circle_asset["gerion_encounter"]);
  
  int choice;
  cin >> choice;
  
  if (choice == 1) {
    PrintDelay(circle_asset["offer_honor"]);
    player.ChangeHonor(-20);
  }
  if (choice == 2) {
    PrintDelay(circle_asset["refuse_pay"]);
    
    bool result = Combat::StartBattle(player, "gerion", circle_asset["win_gerion"].get<string>());
    if (result) {
      WaitKey();
      ClearScreen();
    }
      
    player.EquipWeapon(std::make_unique<Weapon>(
      items_asset["weapons"]["poisoned_dagger"]["name"].get<string>(),
      items_asset["weapons"]["poisoned_dagger"]["damage"].get<int>(),
      items_asset["weapons"]["poisoned_dagger"]["equip_text"].get<string>()
    ));
       
    WaitKey();
  }
  if (choice == 3) {
    PrintDelay(circle_asset["trick_gerion"]);
    player.ChangeHonor(-15);
    
    bool result = Combat::StartBattle(player, "gerion", circle_asset["win_gerion"].get<string>());
    if (result) {
      WaitKey();
      ClearScreen();
    }
    
    player.EquipWeapon(std::make_unique<Weapon>(
      items_asset["weapons"]["poisoned_dagger"]["name"].get<string>(),
      items_asset["weapons"]["poisoned_dagger"]["damage"].get<int>(),
      items_asset["weapons"]["poisoned_dagger"]["equip_text"].get<string>()
    ));
      
    WaitKey();
  }
  
  PrintArray(circle_asset["encounter_sinners"]);
  
  cin >> choice;
  
  if (choice == 1) {
    PrintDelay(circle_asset["forgive"]);
    player.ChangeHonor(20);
  }
  else {
    PrintDelay(circle_asset["condemn"]);
    player.ChangeHonor(-10);
  }
  
  cout << circle_asset["circle_end"].get<string>();
  
  current_circle = 9;
  SetCheckpoint();
  Circle9();
  return;
}

void Circle9() {
  if (!LoadCircleAsset("assets/circle9.json")) {
    cerr << "Ошибка: не удалось загрузить circle9.json!" << endl;
    return;
  }
  if (!LoadItemsAsset("assets/items.json")) {
    cerr << "Failed to load items.json!" << endl;
    return;
  }
  if (!Combat::LoadData("assets/combat_system.json", "assets/enemies.json")) {
    cerr << "Failed to load combat data!" << endl;
    return;
  }
  
  ClearScreen();
  PrintArray(circle_asset["title"]);
  
  cout << circle_asset["description"].get<string>() << "\n\n";
  PrintArray(circle_asset["ugolino_intro"]);
  
  int choice;
  cin >> choice;
  
  if (choice == 1) {
    PrintDelay(circle_asset["ask_path"]);
    player.EquipWeapon(std::make_unique<Weapon>(
      items_asset["weapons"]["ice_sword"]["name"].get<string>(),
      items_asset["weapons"]["ice_sword"]["damage"].get<int>(),
      items_asset["weapons"]["ice_sword"]["equip_text"].get<string>()
    ));   
    WaitKey();
  }
  if (choice == 2) {
    PrintDelay(circle_asset["ask_path"]);
    
    player.EquipWeapon(std::make_unique<Weapon>(
      items_asset["weapons"]["ice_sword"]["name"].get<string>(),
      items_asset["weapons"]["ice_sword"]["damage"].get<int>(),
      items_asset["weapons"]["ice_sword"]["equip_text"].get<string>()
    ));
    WaitKey();
  }
  else {
    PrintArray(circle_asset["anteus_encounter"]);
    
    bool result = Combat::StartBattle(player, "anteus", circle_asset["win_anteus"].get<string>());
    if (result) {
      WaitKey();
      ClearScreen();
    }
  }
  player.EquipWeapon(std::make_unique<Weapon>(
    items_asset["weapons"]["ice_sword"]["name"].get<string>(),
    items_asset["weapons"]["ice_sword"]["damage"].get<int>(),
    items_asset["weapons"]["ice_sword"]["equip_text"].get<string>()
  ));
  WaitKey();

  ClearScreen();
  PrintArray(circle_asset["lucifer_final"]);
  
  cin >> choice;
  
  if (choice == 1) {
    cout << circle_asset["use_weapons"].get<string>()<<"\n";
    WaitKey();
    choice = 2;
  }
  if (choice == 2) {
    PrintDelay(circle_asset["secons_chance"]);
    if (player.honor() <= 50) {
      PrintDelay(circle_asset["low_honor"]);
    }
    if (player.honor() > 50 and player.honor() <= 70) {
      PrintDelay(circle_asset["medium_honor"]);
    }
    if (player.honor() > 70) {
      PrintDelay(circle_asset["high_honor"]);
    }
  }
  
  WaitKey();
  CheckEnding();
  return;
}

void CheckEnding() {
  ClearScreen();
  if (!LoadCircleAsset("assets/ending.json")) {
    cerr << "Ошибка загрузки финала!\n";
    return;
  }
  
  PrintArray(circle_asset["title"]);
  cout << circle_asset["end_game"].get<string>() << "\n\n";
  cout << circle_asset["honor_message"].get<string>() << player.honor() << "/100\n";
  cout << circle_asset["return_menu"].get<string>() << "\n";
  WaitKey();
  MainMenu();
  return;
}