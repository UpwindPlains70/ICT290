#include "Enemy.h"

#include <string>
#include <iostream>
using namespace std;

Enemy::Enemy() {
	reset();
}

Enemy::Enemy(string newName, int newMaxHP, int newArmor, int newStun, int newPosX, int newPosZ, int newMovement, int newTurn) {

	name = newName;
	maxHP = newMaxHP;
	armor = newArmor;
	hp = maxHP;
	stun = newStun;
	posX = newPosX;
	posZ = newPosZ;
	movement = newMovement;
	turn = newTurn;
	numAbilities = 0;
}

Enemy::~Enemy() {

}

void Enemy::setName(string newName) {
	name = newName;
}

string Enemy::getName() {
	return name;
}

void Enemy::setMaxHP(int newMaxHP) {
	maxHP = newMaxHP;
}

int Enemy::getMaxHP() {
	return maxHP;
}

void Enemy::setArmor(int newArmor) {
	armor = newArmor;
}

int Enemy::getArmor() {
	return armor;
}

int Enemy::getNumAbilities() {
	return numAbilities;
}

void Enemy::resetHP() {
	hp = maxHP;
}

int Enemy::getHP() {
	return hp;
}

void Enemy::damageEnemy(int dam) {
	hp -= dam;
	if (hp < 0)
	{
		hp = 0;
	}
}

void Enemy::healEnemy(int heal) {
	hp += heal;
	if (hp > maxHP)
	{
		hp = maxHP;
	}
}

void Enemy::setStun(int newStun) {
	stun = newStun;
}

int Enemy::getStun() {
	return stun;
}

void Enemy::setPosX(int newPosX) {
	posX = newPosX;
}

int Enemy::getPosX() {
	return posX;
}

void Enemy::setPosZ(int newPosZ) {
	posZ = newPosZ;
}

int Enemy::getPosZ() {
	return posZ;
}

void Enemy::setMovement(int newMovement) {
	movement = newMovement;
}

int Enemy::getMovement() {
	return movement;
}

void Enemy::setTurn(int newTurn) {
	turn = newTurn;
}

int Enemy::getTurn() {
	return turn;
}

void Enemy::pushAbility(EntityAbility newAbility) {
	abilities.push_back(newAbility);
	numAbilities++;
}

void Enemy::popAbility() {
	abilities.pop_back();
	numAbilities--;
}

void Enemy::setAbility(EntityAbility newAbility, int num) {
	abilities.at(num) = newAbility;
}

EntityAbility Enemy::getAbility(int num) {
	return abilities[num];
}

void Enemy::reset()
{
	abilities.clear();
	name = "";
	numAbilities = 0;
	hp = 0;
	stun = 0;
	posX = 0;
	posZ = 0;
	movement = 0;
	turn = 0;
	armor = 0;
	maxHP = 0;
}