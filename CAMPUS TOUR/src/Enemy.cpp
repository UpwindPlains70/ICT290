#include "Enemy.h"

#include <string>
#include <iostream>
using namespace std;

Enemy::Enemy() {
	id = 0;
	name = "";
	numAbilities = 0;
	hp = 0;
	stun = 0;
	posX = 0;
	posZ = 0;
	movement = 0;
	turn = 0;
	armor = 0;
	maxhp = 0;
}

Enemy::Enemy(int newID, string newName, int newMaxHP, int newArmor, int newHP, int newStun, int newPosX, int newPosZ, int newMovement, int newTurn) {
	id = newID;
	name = newName;
	maxhp = newMaxHP;
	armor = newArmor;
	hp = newHP;
	stun = newStun;
	posX = newPosX;
	posZ = newPosZ;
	movement = newMovement;
	turn = newTurn;
}

Enemy::~Enemy() {

}

void Enemy::setID(int newID) {
	id = newID;
}

int Enemy::getID() {
	return id;
}

void Enemy::setName(string newName) {
	name = newName;
}

string Enemy::getName() {
	return name;
}

void Enemy::setMaxHP(int newMaxHP) {
	maxhp = newMaxHP;
}

int Enemy::getMaxHP() {
	return maxhp;
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

void Enemy::setHP(int newHP) {
	hp = newHP;
}

int Enemy::getHP() {
	return hp;
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