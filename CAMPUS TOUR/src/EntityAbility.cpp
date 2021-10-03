#include "EntityAbility.h"

using namespace std;

EntityAbility::EntityAbility() {
	
	tohit = 0;
	duplicate = 0;
	damage = 0;
	range = 0;
	aoe = 0;
	name = " ";
	cooldown = 0;
	cooldownCounter = 1;
	stun = 0;
	unique = 0;
}

EntityAbility::EntityAbility(string newName, int newRange, int newAOE, int newDuplicate, int newStun, int newCooldown, int newUnique, int newToHit, int newDamage) {

	name = newName;
	range = newRange;
	aoe = newAOE;
	duplicate = newDuplicate;
	stun = newStun;
	cooldown = newCooldown;
	cooldownCounter = 1;
	tohit = newToHit;
	damage = newDamage;
	unique = newUnique;
}

EntityAbility::~EntityAbility() {

}

void EntityAbility::setToHit(int newToHit) {
	tohit = newToHit;
}

int EntityAbility::getToHit() {
	return tohit;
}

void EntityAbility::setDuplicate(int newDuplicate) {
	duplicate = newDuplicate;
}

int EntityAbility::getDuplicate() {
	return duplicate;
}

void EntityAbility::setDamage(int newDamage) {
	damage = newDamage;
}

int EntityAbility::getDamage() {
	return damage;
}

void EntityAbility::setUnique(int newUnique) {
	unique = newUnique;
}

int EntityAbility::getUnique() {
	return unique;
}

void EntityAbility::used() {
	cooldownCounter = cooldown;
}

void EntityAbility::setName(string newName) {
	name = newName;
}

string EntityAbility::getName() {
	return name;
}

void EntityAbility::setRange(int newRange) {
	range = newRange;
}

int EntityAbility::getRange() {
	return range;
}

void EntityAbility::setAOE(int newAOE) {
	aoe = newAOE;
}

int EntityAbility::getAOE() {
	return aoe;
}

bool EntityAbility::isAOE() {
	return (aoe > 1);
}

void EntityAbility::setStun(int newStun) {
	stun = newStun;
}

int EntityAbility::getStun() {
	return stun;
}

void EntityAbility::setCooldown(int newCooldown) {
	cooldown = newCooldown;
}

int EntityAbility::getCooldown() {
	return cooldown;
}

void EntityAbility::resetCooldownCounter() {
	cooldownCounter = 1;
}

void EntityAbility::roundPassed()
{
	cooldownCounter--;
	if (cooldownCounter < 1)
	{
		cooldownCounter = 1;
	}
}

bool EntityAbility::canUseAbility() {
	if (cooldownCounter == 1)
	{
		return true;
	}
	else
	{
		return false;
	}
}