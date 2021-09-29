#include "player.h"
#include "card.h"
//����� ��ȣ
Player::Player(int num) { 
	playerNum = num; 
}
int Player::getPlayerNum() {
	return playerNum;
}
//������ ī�彺���� ���� �� ī�� ��ȯ
Card Player::getFrontTopCard() {
	if (front.empty()) return Card();
	return front.top();
}
//������ ���� ī�彺���� ���� �� ī�� ��ȯ
Card Player::getBackTopCard() {
	if (back.empty()) return Card();
	return back.top();
}
//������/������ ���� ī���� ���� ��ȯ
int Player::getFrontCount() {
	return front.size();
}
int Player::getBackCount() {
	return back.size();
}
//ī�� �߰�
void Player::pushFront(const Card& c) {
	front.push(c);
}
void Player::pushBack(const Card& c) {
	back.push(c);
}
//ī�� ����
void Player::popFront() {
	front.pop();
}
void Player::popBack() {
	back.pop();
}
//back -> front ī�� ������
int Player::open() {
	if (back.empty()) {
		return -1;
	}
	pushFront(getBackTopCard());
	popBack();
	return 0;
}