#ifndef CIRCLES_H
#define CIRCLES_H

#include "Player.h"
#include "Enemy.h"

// ��������������� �������
void clearScreen(); // �������� ������� ��� ������� ������
void waitForKeyEmpty();

void MainMenu(); // �������� ��� �������� ����
void SetCheckpoint(); // �������� ��� ��������� ����������� �����
void LoadCheckpoint(); // �������� ��� �������� ����������� �����
void CheckEnding(); // �������� ��� �������� ����� ����

void Circle1(); // ����
void Circle2(); // ������
void Circle3(); // �����������
void Circle4(); // ��������
void Circle5(); // ����
void Circle6(); // �����
void Circle7(); // �������
void Circle8(); // �����
void Circle9(); // �������������
void FinalBattle(); // ��������� �����
void Combat(Enemy& enemy); // ������ �������

#endif // CIRCLES_H