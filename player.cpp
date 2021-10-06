#include "player.h"
#include "card.h"
#include<iostream>
using namespace std;
//탈락처리
void Player::setNoneAvailable() {
    available = false;
    cout << playerNum << "번 사용자가 탈락되었습니다." << endl;
    //남은 카드 제거
    while (!front.empty()) front.pop();
    while (!back.empty()) back.pop();
}
bool Player::getAvailable() {
    return available;
}
//출력
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
//초반 카드 수 지정
Player::Player(int num) {
    playerNum = num;
    available = true;
}
//뒤집은 카드스택의 가장 위 카드 반환
Card Player::getFrontTopCard() {
    if (front.empty()) return Card();
    return front.top();
}
//뒤집지 않은 카드스택의 가장 위 카드 반환
Card Player::getBackTopCard() {
    //if (back.empty()) return Card();
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
void Player::pushBack(const Card& card) {
    //cout << "push됨, "<< getBackCount() << endl;
    back.push(card);
}
void Player::pushFront(const Card& card) {
    front.push(card);
}
//카드 잃음ㄴ
void Player::popBack() {
    back.pop();
}
void Player::popFront() {
    front.pop();
}
//back -> front 카드 뒤집음
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