#include "player.h"
#include "card.h"
//사용자 번호
Player::Player(int num) { 
	playerNum = num; 
}
int Player::getPlayerNum() {
	return playerNum;
}
//뒤집은 카드스택의 가장 위 카드 반환
Card Player::getFrontTopCard() {
	if (front.empty()) return Card();
	return front.top();
}
//뒤집지 않은 카드스택의 가장 위 카드 반환
Card Player::getBackTopCard() {
	if (back.empty()) return Card();
	return back.top();
}
//뒤집은/뒤집지 않은 카드의 숫자 반환
int Player::getFrontCount() {
	return front.size();
}
int Player::getBackCount() {
	return back.size();
}
//카드 추가
void Player::pushFront(const Card& c) {
	front.push(c);
}
void Player::pushBack(const Card& c) {
	back.push(c);
}
//카드 잃음
void Player::popFront() {
	front.pop();
}
void Player::popBack() {
	back.pop();
}
//back -> front 카드 뒤집음
int Player::open() {
	if (back.empty()) {
		return -1;
	}
	pushFront(getBackTopCard());
	popBack();
	return 0;
}