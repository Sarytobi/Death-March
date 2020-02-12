#include "Players.h"

Pouch::Pouch()
{
	Item head1(1);
	Item torso1(2);
	Item belt1(3);
	Item pants1(4);
	Item boots1(5);
	head.Copy(head1);
	torso.Copy(torso1);
	belt.Copy(belt1);
	pants.Copy(pants1);
	boots.Copy(boots1);
}

int Pouch::GetStrength()
{
	int summaItem;
	summaItem = head.itemStrength + torso.itemStrength + belt.itemStrength + pants.itemStrength + boots.itemStrength;
	return summaItem;
}

int Pouch::GetAgility()
{
	int summaItem;
	summaItem = head.itemAgility + torso.itemAgility + belt.itemAgility + pants.itemAgility + boots.itemAgility;
	return summaItem;
}

int Pouch::GetStamina()
{
	int summaItem;
	summaItem = head.itemStamina + torso.itemStamina + belt.itemStamina + pants.itemStamina + boots.itemStamina;
	return summaItem;
}

int Pouch::GetFortune()
{
	int summaItem;
	summaItem = head.itemFortune + torso.itemFortune + belt.itemFortune + pants.itemFortune + boots.itemFortune;
	return summaItem;
}

Item::Item()
{
	this->itemStrength = 1;
	this->itemAgility = 1;
	this->itemStamina = 1;
	this->itemFortune = 1;
	tipe = 0;
}

Item::Item(int tipe)
{
	//набор по умолчанию
	this->tipe = tipe;
	this->itemStrength = 1;
	this->itemAgility = 1;
	this->itemStamina = 1;
	this->itemFortune = 1;
}

Item::Item(int zone, int rar, int tipe)
{
	itemStrength = (rand() % zone) * rar;
	itemAgility = (rand() % zone) * rar;
	itemStamina = (rand() % zone) * rar;
	itemFortune = (rand() % zone) * rar;
	this->tipe = tipe;
}

void Item::Copy(Item one)
{
	this->itemStrength = one.itemStrength;
	this->itemAgility = one.itemAgility;
	this->itemStamina = one.itemStamina;
	this->itemFortune = one.itemFortune;
	this->tipe = one.tipe;
}

Players::Players()
{
	name = "Имя не задано";
}

Players::Players(string newPayers)
{
	hitPoint = 100;
	level = 1;
	live = true;
	expUp = 1000;

	name = newPayers;

	strength = 1;
	agility = 1;
	stamina = 1;
	fortune = 1;

	location = "square";
}

string Players::GetName()
{
	return name;
}

float Players::Attack()
{
	float resultAttaack;
	resultAttaack =  ((strength + casePlayer.GetStrength()) + 2 * (agility + casePlayer.GetAgility()));
	return resultAttaack;
}

void Players::InfoPlayer()
{
	cout << "HP " << hitPoint << endl;
	cout << "Level " << level << endl;
	cout << "ExpUp " << expUp << endl;
	cout << "Live " << live << endl;

	cout << "Strength " << strength << "(+All Item " << casePlayer.GetStrength() << ")" << endl;
	cout << "Agility " << agility << "(+All Item " << casePlayer.GetAgility() << ")" << endl;
	cout << "Stamina " << stamina << "(+All Item " << casePlayer.GetStamina() << ")" << endl;
	cout << "Fortune " << fortune << "(+All Item " << casePlayer.GetFortune() << ")" << endl;
}

string Players::InfoPlayerString()
{
	string result;
	result = "HP " + to_string(hitPoint) + "\n" + "Level " + to_string(level) + "\n" + "ExpUp " + 
		to_string(expUp) + "\n" + "Live " + to_string(live) + "\n" + "Strength " + to_string(strength) +
		"(+All Item " + to_string(casePlayer.GetStrength())+ ")\n" + "Agility " + to_string(agility) + "(+All Item " +
		to_string(casePlayer.GetAgility()) + ")\n" + "Stamina " + to_string(stamina) + "(+All Item " +
		to_string(casePlayer.GetStamina()) + ")\n" + "Fortune " + to_string(fortune) + "(+All Item " + 
		to_string(casePlayer.GetFortune()) + ")\n";

	return result;
}

void Players::LevelUpPlayer()
{
	if (exp >= expUp)
	{
		exp -= expUp;
		level++;
		expUp = expUp * 2;
	}
}