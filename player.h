#pragma once
#include "card.h"
#include <stack>
using namespace std;
class Player{
	//낸 카드
	stack<Card> front;
	//내지 않은 카드
	stack<Card> back;
	//플레이어 번호
	int playerNum;
	//플레이 가능 여부
	bool available;
public:
    //탈락처리
    void setNoneAvailable();
    bool getAvailable();
    //출력
    void getInfo();
    int getPlayerNum();
    //초반 카드 수 지정
    Player(int num);
    //뒤집은 카드스택의 가장 위 카드 반환
    Card getFrontTopCard();
    //뒤집지 않은 카드스택의 가장 위 카드 반환
    Card getBackTopCard();
    //뒤집은/뒤집지 않은 카드의 숫자 반환
    int getFrontCount();
    int getBackCount();
    //카드 추가
    void pushBack(const Card& card);
    void pushFront(const Card& card);
    //카드 잃음ㄴ
    void popBack();
    void popFront();
    //back -> front 카드 뒤집음
    int open();
    bool backIsEmpty();
    bool frontIsEmpty();
};