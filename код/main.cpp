#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <limits>
#include <cstdlib>
#include <ctime>
#include "Player.h"
#include "Enemy.h"
#include "Item.h"
#include "Weapon.h"
#include "Circles.h"

using namespace std;

// Глобальные переменные
Player player;
int current_circle = 1;

// Прототипы функций
void MainMenu();
void NewGame();
void LoadGame();
void SaveGame();
void Combat(Enemy& enemy);
void GameOver();
void SetCheckpoint();
void LoadCheckpoint();

// Вспомогательные функции объявлены в Circles.h, определения в Circles.cpp
extern void clearScreen();
extern void waitForKeyEmpty();


void MainMenu() {
    clearScreen();
    cout << "========================================\n";
    cout << "|                                      |\n";
    cout << "|          VISITING THE DEVIL          |\n";
    cout << "|                                      |\n";
    cout << "========================================\n";
    cout << "1. Новая игра\n";
    cout << "2. Загрузить последний чекпойнт\n";
    cout << "3. Выйти из игры\n";
    cout << "========================================\n";

    int choice;
    cin >> choice;

    switch (choice) {
    case 1:
        NewGame();
        break;
    case 2:
        LoadCheckpoint();
        break;
    case 3:
        exit(0);
    default:
        MainMenu();
    }
}

void NewGame() {
    player = Player();
    current_circle = 1;
    Circle1();
}

void LoadGame() {
    ifstream save("save.txt");
    if (save) {
        save >> current_circle;
        int health, max_health, honor;
        save >> health >> max_health >> honor;

        player = Player();
        player.TakeDamage(100 - health);
        player.ChangeHonor(honor - 50);

        int weapon_damage;
        string weapon_name, weapon_weak_spot;
        save.ignore();
        getline(save, weapon_name);
        save >> weapon_damage;
        save.ignore();
        getline(save, weapon_weak_spot);

        if (weapon_name != "nullptr") {
            Weapon* weapon = new Weapon(weapon_name, weapon_damage, weapon_weak_spot);
            player.EquipWeapon(weapon);
        }
        else {
            player.EquipWeapon(nullptr);
        }

        int item_count;
        save >> item_count;
        for (int i = 0; i < item_count; ++i) {
            string item_name;
            int item_value;
            save.ignore();
            getline(save, item_name);
            save >> item_value;
            player.AddItem(Item(item_name, item_value));
        }

        save.close();
        cout << "Игра загружена!\n";
        waitForKeyEmpty();

        switch (current_circle) {
        case 1: Circle1(); break;
        case 2: Circle2(); break;
        case 3: Circle3(); break;
        case 4: Circle4(); break;
        case 5: Circle5(); break;
        case 6: Circle6(); break;
        case 7: Circle7(); break;
        case 8: Circle8(); break;
        case 9: Circle9(); break;
        default: MainMenu();
        }
    }
    else {
        cout << "Сохранение не найдено!\n";
        waitForKeyEmpty();
        MainMenu();
    }
}

void SaveGame() {
    ofstream save("save.txt");
    if (save) {
        save << current_circle << "\n";
        save << player.GetHealth() << " " << player.GetMaxHealth() << " " << player.GetHonor() << "\n";

        if (player.GetWeapon()) {
            save << player.GetWeapon()->GetName() << "\n";
            save << player.GetWeapon()->GetDamage() << "\n";
            save << player.GetWeapon()->GetWeakSpot() << "\n";
        }
        else {
            save << "nullptr\n0\n\n";
        }

        save << player.GetInventoryCount() << "\n";
        for (const auto& item : player.GetInventory()) {
            save << item.GetName() << "\n";
            save << item.GetValue() << "\n";
        }

        save.close();
    }
    else {
        cout << "Ошибка сохранения!\n";
    }
}

void SetCheckpoint() {
    SaveGame();
    waitForKeyEmpty();
}

void LoadCheckpoint() {
    LoadGame();
}

void Combat(Enemy& enemy) {
    SetCheckpoint(); // Сохраняем перед боем

    while (player.IsAlive() && enemy.IsAlive()) {
        clearScreen();
        cout << "========================================\n";
        cout << "               БОЕВАЯ СИСТЕМА           \n";
        cout << "========================================\n";
        cout << "Ваше здоровье: " << player.GetHealth() << "/" << player.GetMaxHealth() << "\n";
        cout << enemy.GetName() << ": " << enemy.GetHealth() << "/" << enemy.GetMaxHealth() << "\n";
        cout << "----------------------------------------\n";
        cout << enemy.GetDescription() << "\n";
        if (!enemy.GetWeakSpot().empty()) {
            cout << "Подсказка: " << enemy.GetWeakSpot() << "\n";
        }
        cout << "========================================\n";
        cout << "1. Атаковать\n";
        cout << "2. Использовать предмет\n";
        cout << "3. Попытаться убежать\n";

        int choice;
        cin >> choice;

        switch (choice) {
        case 1: {
            cout << "Выберите место для атаки:\n";
            cout << "1. Корпус (обычный урон)\n";
            cout << "2. Голова (повышенный урон)\n";
            if (!enemy.GetWeakSpot().empty()) {
                cout << "3. Уязвимое место (двойной урон, но сложнее попасть)\n";
            }

            int attack_choice;
            cin >> attack_choice;

            int damage = player.AttackDamage();
            bool is_critical = false;

            switch (attack_choice) {
            case 1:
                break;
            case 2:
                damage = static_cast<int>(damage * 1.5);
                player.TakeDamage(enemy.GetDamage() / 2);
                cout << "Вы наносите мощный удар, но получаете ответный удар!\n";
                break;
            case 3:
                if (rand() % 100 < 60) {
                    damage *= 2;
                    is_critical = true;
                    cout << "Вы попадаете в уязвимое место! Критический урон!\n";
                }
                else {
                    cout << "Вы промахнулись по уязвимому месту!\n";
                    damage = 0;
                }
                break;
            default:
                damage = 0;
                cout << "Вы замешкались и пропустили ход!\n";
            }

            if (damage > 0) {
                enemy.TakeDamage(damage);
                cout << "Вы атаковали " << enemy.GetName() << " и нанесли " << damage << " урона!";
                if (is_critical) cout << " [КРИТИЧЕСКИЙ УДАР]";
                cout << "\n";
            }

            if (enemy.IsAlive()) {
                int enemy_damage = enemy.GetDamage();
                player.TakeDamage(enemy_damage);
                cout << enemy.GetName() << " атаковал вас и нанес " << enemy_damage << " урона!\n";
            }
            else {
                cout << "Вы победили " << enemy.GetName() << "!\n";
                player.ChangeHonor(5);
                SetCheckpoint(); // Сохраняем после победы
            }
            break;
        }
        case 2:
            player.ShowInventory();
            if (!player.IsAlive()) return;

            cout << "Выберите предмет для использования: ";
            int item_choice;
            cin >> item_choice;
            player.UseItem(item_choice - 1);
            break;
        case 3: {
            int chance = rand() % 100;
            if (chance < 30) {
                cout << "Вам удалось сбежать!\n";
                waitForKeyEmpty();
                return;
            }
            else {
                cout << "Попытка побега не удалась!\n";
                int half_damage = enemy.GetDamage() / 2;
                player.TakeDamage(half_damage);
                cout << enemy.GetName() << " атаковал вас и нанёс " << half_damage << " урона!\n";
            }
            break;
        }
        default:
            continue;
        }

        waitForKeyEmpty();
    }

    if (!player.IsAlive()) {
        GameOver();
    }
}

void GameOver() {
    clearScreen();
    cout << "========================================\n";
    cout << "            ВЫ ПОГИБЛИ                 \n";
    cout << "========================================\n\n";
    cout << "Ваше путешествие по аду закончилось. Возможно, в следующий раз вам повезёт больше.\n\n";
    waitForKeyEmpty();
    MainMenu();
}

// Прототипы для кругов (реализация в Circles.cpp)
void Circle1();
void Circle2();
void Circle3();
void Circle4();
void Circle5();
void Circle6();
void Circle7();
void Circle8();
void Circle9();
void FinalBattle();

int main() {
    srand(static_cast<unsigned int>(time(0)));
    setlocale(LC_ALL, "Russian");
    MainMenu();
    return 0;
}