#include "EntityAbility.h"

#include <string>
#include <iostream>
using namespace std;

EntityAbility::EntityAbility() {
	tohit = 0;
	num = 0;
	damage = 0;
	used = false;
}

EntityAbility::EntityAbility(int newToHit, int newNum, int newDamage, bool newUsed) {
	tohit = newToHit;
	num = newNum;
	damage = newDamage;
	used = newUsed;
}

EntityAbility::~EntityAbility() {

}

void EntityAbility::setToHit(int newToHit) {
	tohit = newToHit;
}

int EntityAbility::getToHit() {
	return tohit;
}

void EntityAbility::setNum(int newNum) {
	num = newNum;
}

int EntityAbility::getNum() {
	return num;
}

void EntityAbility::setDamage(int newDamage) {
	damage = newDamage;
}

int EntityAbility::getDamage() {
	return damage;
}

void EntityAbility::setUsed(bool newUsed) {
	used = newUsed;
}

bool EntityAbility::getUsed() {
	return used;
}