#include "PlayerClass.h"

#include <string>
#include <iostream>
using namespace std;

PlayerClass::PlayerClass() {
	maxhp = 0;
	armor = 0;
	movement = 0;
	ability1 = "";
	ability2 = "";
	ability3 = "";
}

PlayerClass::PlayerClass(int newMaxHP, int newArmor, int newMovement, string newAbility1, string newAbility2, string newAbility3) {
	maxhp = newMaxHP;
	armor = newArmor;
	movement = newMovement;
	ability1 = newAbility1;
	ability2 = newAbility2;
	ability3 = newAbility3;
}

PlayerClass::~PlayerClass() {

}

void PlayerClass::setMaxHP(int newMaxHP) {
	maxhp = newMaxHP;
}

int PlayerClass::getMaxHP() {
	return maxhp;
}

void PlayerClass::setArmor(int newArmor) {
	armor = newArmor;
}

int PlayerClass::getArmor() {
	return armor;
}

void PlayerClass::setMovement(int newMovement) {
	movement = newMovement;
}

int PlayerClass::getMovement() {
	return movement;
}

void PlayerClass::setAbility1(string newAbility1) {
	ability1 = newAbility1;
}

string PlayerClass::getAbility1() {
	return ability1;
}

void PlayerClass::setAbility2(string newAbility2) {
	ability2 = newAbility2;
}

string PlayerClass::getAbility2() {
	return ability2;
}

void PlayerClass::setAbility3(string newAbility3) {
	ability3 = newAbility3;
}

string PlayerClass::getAbility3() {
	return ability3;
}