#include "player.h"
#include "card.h"
#include<iostream>
using namespace std;
//Ż��ó��
void Player::setNoneAvailable() {
    available = false;
    cout << playerNum << "�� ����ڰ� Ż���Ǿ����ϴ�." << endl;
    //���� ī�� ����
    while (!front.empty()) front.pop();
    while (!back.empty()) back.pop();
}
bool Player::getAvailable() {
    return available;
}
//���
void Player::getInfo() {
    cout << "[ " << playerNum << " ]" << endl;
    cout << "front [";
    for (int i = 0; i < front.size(); i++) {
        front.pop();
    }
    cout << " ]" << endl;
    cout << "back [";
    for (int i = 0; i < back.size(); i++) {
        back.pop();
    }
    cout << " ]";
}
int Player::getPlayerNum() {
    return playerNum;
}
//�ʹ� ī�� �� ����
Player::Player(int num) {
    playerNum = num;
    available = true;
}
//������ ī�彺���� ���� �� ī�� ��ȯ
Card Player::getFrontTopCard() {
    if (front.empty()) return Card();
    return front.top();
}
//������ ���� ī�彺���� ���� �� ī�� ��ȯ
Card Player::getBackTopCard() {
    //if (back.empty()) return Card();
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
void Player::pushBack(const Card& card) {
    //cout << "push��, "<< getBackCount() << endl;
    back.push(card);
}
void Player::pushFront(const Card& card) {
    front.push(card);
}
//ī�� ������
void Player::popBack() {
    back.pop();
}
void Player::popFront() {
    front.pop();
}
//back -> front ī�� ������
int Player::open() {
    if (back.empty()) {
        setNoneAvailable();
        return -1;
    }
    pushFront(getBackTopCard());
    popBack();
    return 0;
}
bool Player::backIsEmpty() {
    return back.empty();
}
bool Player::frontIsEmpty() {
    return front.empty();
}