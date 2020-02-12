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
		//характеристики предвета
	int itemStrength;
	int itemAgility;
	int itemStamina;
	int itemFortune;
	//тип предмета от 1 до 5 в зависимости от предмета
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
	Item head;	//голова
	Item torso;	//туловище
	Item belt;	//пояс
	Item pants;	//штаны
	Item boots;	//сапоги
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

