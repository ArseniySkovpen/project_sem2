#include <iostream>
#include <fstream>
#include <memory>
#include "Player.h"
#include "Combat.h"
#include "Circles.h"
#include "json.hpp"

using json = nlohmann::json;

Player player;
int current_circle;
json player_texts;
json ui_texts;

void MainMenu();
void NewGame();
void LoadGame();
void SaveGame();
void GameOver();

void SetCheckpoint() {
    std::ofstream file("save.txt");
    if (file.is_open()) {
        file << current_circle; // Сохраняем текущий круг
        file.close();
    }
}

void NewGame() {
    current_circle = 1;
    Circle1(); // Начинаем игру с первого круга
}

void MainMenu() {
    ClearScreen();

    // Загрузка текстов меню
    std::ifstream file("assets/ui_texts.json");
    json ui_texts;
    if (file.is_open()) {
        file >> ui_texts;
        file.close();
    }

    // Вывод меню
    for (const auto& line : ui_texts["main_menu"]) {
        std::cout << line.get<std::string>() << "\n";
    }

    int choice;
    std::cin >> choice;

    switch (choice) {
    case 1:
        NewGame();
        break;
    case 2:
        LoadGame();
        break;
    case 3:
        exit(0);
    default:
        std::cout << "Неверный выбор!\n";
        WaitKey();
        MainMenu();
    }
}

bool LoadUiText() {
    std::ifstream file("assets/ui_texts.json");
    if (!file.is_open()) {
        std::cerr << "Failed to load UI texts!\n";
        return false;
    }
    try {
        file >> ui_texts;
        return true;
    }
    catch (json::parse_error& e) {
        std::cerr << "JSON parse error: " << e.what() << "\n";
        return false;
    }
}

void LoadGame() {
    std::ifstream file("save.txt");
    if (file.is_open()) {
        file >> current_circle;
        file.close();
        std::cout << "Игра загружена! Текущий круг: " << current_circle << "\n";

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
        default: Circle1();
        }
    }
    else {
        std::cout << "Сохранение не найдено!\n";
        WaitKey();
        MainMenu();
    }
}

void GameOver() {
    std::ifstream combat_file("assets/combat_system.json");
    json combat_data;
    if (combat_file.is_open()) {
        combat_file >> combat_data;
        combat_file.close();
    }
    else {
        std::cerr << "Ошибка загрузки combat_system.json!\n";
        return;
    }
    ClearScreen();
    for (const auto& line : combat_data["combat"]["system"]["messages"]["game_over"]) {
        std::cout << line.get<std::string>() << "\n";
    }
    WaitKey();
    MainMenu();
}

void SaveGame() {
    std::ofstream file("savegame.sav");
    if (file.is_open()) {
        file << current_circle;
        file.close();
        std::cout << "Игра сохранена!\n";
    }
    else {
        std::cout << "Ошибка сохранения!\n";
    }
    WaitKey();
}

int main() {
    setlocale(LC_ALL, "ru_RU.UTF-8");
    srand(static_cast<unsigned>(time(nullptr)));

    if (!LoadUiText()) {
        std::cerr << "Error loading UI texts!" << std::endl;
        return -1;
    }

    if (!Combat::LoadData("assets/combat_system.json", "assets/enemies.json")) {
        std::cerr << "Error loading combat data!" << std::endl;
        return -1;
    }

    MainMenu();
    return 0;
}