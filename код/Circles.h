#ifndef CIRCLES_H
#define CIRCLES_H

#include "Player.h"
#include "Enemy.h"

// Вспомогательные функции
void clearScreen(); // Прототип функции для очистки экрана
void waitForKeyEmpty();

void MainMenu(); // Прототип для главного меню
void SetCheckpoint(); // Прототип для установки контрольной точки
void LoadCheckpoint(); // Прототип для загрузки контрольной точки
void CheckEnding(); // Прототип для проверки конца игры

void Circle1(); // Лимб
void Circle2(); // Похоть
void Circle3(); // Чревоугодие
void Circle4(); // Жадность
void Circle5(); // Гнев
void Circle6(); // Ересь
void Circle7(); // Насилие
void Circle8(); // Обман
void Circle9(); // Предательство
void FinalBattle(); // Финальная битва
void Combat(Enemy& enemy); // Боевая система

#endif // CIRCLES_H