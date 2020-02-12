#pragma once
#include <iostream>
#include <string>
using namespace std;

class Item
{
public:
	Item();
	Item(int tipe);
	Item(int zone, int rar, int tipe);
	void Copy(Item one);
	//protected:
		//�������������� ��������
	int itemStrength;
	int itemAgility;
	int itemStamina;
	int itemFortune;
	//��� �������� �� 1 �� 5 � ����������� �� ��������
	int tipe;
};

class Pouch
{
public:
	Pouch();
	int GetStrength();
	int GetAgility();
	int GetStamina();
	int GetFortune();
	//protected:
	Item head;	//������
	Item torso;	//��������
	Item belt;	//����
	Item pants;	//�����
	Item boots;	//������
};


class Players
{
public:
	Players();
	Players(string nameCin);
	string GetName();
	float Attack();
	void InfoPlayer();
	string InfoPlayerString();
	void LevelUpPlayer();

	Pouch casePlayer;
//protected:
	string name;

	int hitPoint;
	int level;
	int exp;
	int expUp;
	bool live;

	int strength;
	int agility;
	int stamina;
	int fortune;

	string location;
};

