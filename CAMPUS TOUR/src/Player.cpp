#include "Player.h"

#include <string>
#include <iostream>
using namespace std;
	
Player::Player() {
	id = 0;
	name = "";
	classtype = "";
	hp = 0;
	stun = 0;
	posX = 0;
	posZ = 0;
	movementleft = 0;
	turn = 0;
}

Player::Player(int newID, string newName, string newClassType, int newHP, int newStun, int newPosX, int newPosZ, int newMovementLeft, int newTurn) {
	id = newID;
	name = newName;
	classtype = newClassType;
	hp = newHP;
	stun = newStun;
	posX = newPosX;
	posZ = newPosZ;
	movementleft = newMovementLeft;
	turn = newTurn;
}

Player::~Player() {

}

void Player::setID(int newID) {
	id = newID;
}

int Player::getID() {
	return id;
}

void Player::setName(string newName) {
	name = newName;
}

string Player::getName() {
	return name;
}

void Player::setClassType(string newClassType) {
	classtype = newClassType;
}

string Player::getClassType() {
	return classtype;
}

void Player::setHP(int newHP) {
	hp = newHP;
}

int Player::getHP() {
	return hp;
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

void Player::setMovementLeft(int newMovementLeft) {
	movementleft = newMovementLeft;
}

int Player::getMovementLeft() {
	return movementleft;
}

void Player::setTurn(int newTurn) {
	turn = newTurn;
}

int Player::getTurn() {
	return turn;
}