#include "card.h"

Card::Card() {
	this->type = 'e';
	this->num = 0;
}
Card::Card(int type, int num) {
	this->type = type;
	this->num = num;
}
int Card::getType() {
	return type;
}
int Card::getNumber() {
	return num;
}