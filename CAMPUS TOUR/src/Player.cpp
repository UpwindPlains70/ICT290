#include "Player.h"

#include <string>
#include <iostream>
using namespace std;
	
Player::Player() {
	name = "";
	classType = "";
	hp = 0;
	stun = 0;
	posX = 0;
	posZ = 0;
	movementLeft = 0;
	turn = 0;
	numAbilities = 0;
	movement = 0;
	maxHP = 0;
	armor = 0;
	damageBoost = false;
}

Player::Player(string newName, string newclassType, int newMaxHP, int newMovement, int newArmor) {
	name = newName;
	classType = newclassType;
	maxHP = newMaxHP;
	hp = maxHP;
	stun = 0;
	posX = 0;
	posZ = 0;
	movement = newMovement;
	movementLeft = movement;
	turn = 0;
	armor = newArmor;
	originalAC = armor;
	numAbilities = 0;
	damageBoost = false;
}

Player::~Player() {

}

void Player::setName(string newName) {
	name = newName;
}

string Player::getName() {
	return name;
}

void Player::setClassName(string newName) {
	classType = newName;
}

string Player::getClassName() {
	return classType;
}

void Player::setMaxHP(int newMaxHP) {
	maxHP = newMaxHP;
}

int Player::getMaxHP() {
	return maxHP;
}

void Player::setArmor(int newArmor) {
	armor = newArmor;
	originalAC = armor;
}

int Player::getArmor() {
	return armor;
}

int Player::getNumAbilities() {
	return numAbilities;
}

void Player::resetHP() {
	hp = maxHP;
}

int Player::getHP() {
	return hp;
}

void Player::damagePlayer(int dam) {
	hp -= dam;
	if (hp < 0)
	{
		hp = 0;
	}
}

void Player::healPlayer(int heal) {
	hp += heal;
	if (hp > maxHP)
	{
		hp = maxHP;
	}
}

void Player::setStun(int newStun) {
	stun = newStun;
}

int Player::getStun() {
	return stun;
}

void Player::setPosX(int newPosX) {
	posX = newPosX;
}

int Player::getPosX() {
	return posX;
}

void Player::setPosZ(int newPosZ) {
	posZ = newPosZ;
}

int Player::getPosZ() {
	return posZ;
}

void Player::setMovement(int newMovement) {
	movement = newMovement;
}

int Player::getMovement() {
	return movement;
}

int Player::getMovementLeft() {
	return movementLeft;
}

void Player::resetMovementLeft()
{
	movementLeft = movement;
}

void Player::noMovementLeft()
{
	movementLeft = 0;
}

void Player::movePlayer()
{
	if (canMove())
	{
		movementLeft--;
	}
}

bool Player::canMove()
{
	if (movementLeft > 0)
	{
		return true;
	}
	return false;
}

void Player::setTurn(int newTurn) {
	turn = newTurn;
}

int Player::getTurn() {
	return turn;
}

void Player::pushAbility(EntityAbility newAbility) {
	abilities.push_back(newAbility);
	numAbilities++;
}

void Player::setAbilities(vector<EntityAbility> newList) {
	abilities = newList;
	numAbilities = abilities.size();
}

void Player::popAbility() {
	abilities.pop_back();
	numAbilities--;
}

void Player::setAbility(EntityAbility newAbility, int num) {
	abilities.at(num) = newAbility;
}

EntityAbility Player::getAbility(int num) {
	return abilities[num];
}

int Player::getNumberOfAbilities()
{
	return abilities.size();
}

void Player::shield(int AC)
{
	originalAC = armor;
	armor = AC;
}

void Player::unshield()
{
	armor = originalAC;
}

bool Player::damageBoosted()
{
	return damageBoost;
}

void Player::setDamageBoost(bool dB)
{
	damageBoost = dB;
}