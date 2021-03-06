#include "Player.h"
#include <cstring>

Player::Player(int x, int y, unsigned id) {
	char name[8] = { 'P','l','a','y','e','r',' ','\0' };
	name[6] = id + '1';
	strcpy(this->name, name);
	letter = id + '1';
	this->x = x;
	this->y = y;
	healt = 4;
	moves = 5;
	maxMoves = 5;
	damage = 1;
	last_move = DIR_NULL;
	this->id = id;
	stats_changed = false;
	inventory_changed = false;
	inventory.push_back(0);
	inventory.push_back(1);
}
void Player::setName(char name[8]) {
	strcpy(this->name, name);
}
void Player::setLetter(char letter) {
	this->letter = letter;
}
void Player::setHealt(int healt) {
	this->healt = healt;
}
void Player::setX(unsigned x) {
	this->x = x;
}
void Player::setY(unsigned y) {
	this->y = y;
}
void Player::setMoves(unsigned moves) {
	this->moves = moves;
}
void Player::setMaxMoves(unsigned maxMoves) {
	this->maxMoves = maxMoves;
}
void Player::setDamage(unsigned damage) {
	this->damage = damage;
}
void Player::setLastMove(Dir dir) {
	last_move = dir;
}
void Player::setStatsChanged(bool changed) {
	stats_changed = changed;
}
void Player::setInventoryChanged(bool changed) {
	inventory_changed = changed;
}
bool Player::addObject(unsigned object) {
	if (inventory.size() < INVENTORY) {
		inventory.push_back(object);
		return true;
	}
	return false;
}
void Player::printColor() const {
	switch (id) {
	case 0:
		printf(ANSI_COLOR_BOLDYELLOW);
		break;
	case 1:
		printf(ANSI_COLOR_BOLDGREEN);
		break;
	case 2:
		printf(ANSI_COLOR_BOLDMAGENTA);
		break;
	case 3:
		printf(ANSI_COLOR_BOLDCYAN);
		break;
	case 4:
		printf(ANSI_COLOR_BOLDRED);
		break;
	case 5:
		printf(ANSI_COLOR_YELLOW);
		break;
	case 6:
		printf(ANSI_COLOR_GREEN);
		break;
	case 7:
		printf(ANSI_COLOR_RED);
		break;
	default:
		printf(ANSI_COLOR_CYAN);
		break;
	}
}
void Player::printInfo() const {
	printf("\x1b[10;60H" ANSI_COLOR_GREEN "->Moves: %u " ANSI_COLOR_RESET, moves + 1);
}
void Player::printStats() const {
	printf("\x1b[7;2H| ----- Player %u ----- |", id+1);
	// Player name
	printf("\x1b[9;2HName: ");
	printColor();
	printf("%s        ", name);
	// Healt
	printf("\x1b[12;2H" ANSI_COLOR_BOLDRED "Healt: %d", healt);
	// Damage
	printf("\x1b[14;2H" ANSI_COLOR_RED "Damage: %u" ANSI_COLOR_RESET, damage);
	// Inventory text
	printf("\x1b[16;2H| Inventory: %lu items\x1b[16;25H|", inventory.size());
}
void Player::removeObject(unsigned object) {
	for (unsigned i = 0;i < inventory.size();i++)
		if (object == inventory[i])
			inventory.erase(inventory.begin() + i);
}

unsigned Player::getObject(unsigned index) {
	unsigned object = inventory[index];
	removeObject(object);

	return object;
}
void Player::printInventory(unsigned index) const {
	unsigned i;
	for (i = 0;i < INVENTORY;i++) {
		printf("\x1b[%d;3H", 18 + i * 2);
		if (i < getInventorySize()) {
			if (i == index) printf(ANSI_COLOR_BOLDRED);
			switch (inventory[i]) {
			case 0:
				printf("-Add 2 moves      ");
				break;
			case 1:
				printf("-Add 3 moves     ");
				break;
			case 2:
				printf("-Add 4 moves     ");
				break;
			case 3:
				printf("-[P] Add 1 move  ");
				break;
			case 4:
				printf("-[P] Add 2 moves  ");
				break;
			case 5:
				printf("-[P] Add 1 damage");
				break;
			case 6:
				printf("-[P] Add 1 health");
				break;
			case 7:
				printf("-[P] Add 2 healt");
				break;
			default:
				printf("-Undefined object");
				break;
			}
			if (i == index) printf(ANSI_COLOR_RESET);
		}
		else printf("                 ");
	}
}
