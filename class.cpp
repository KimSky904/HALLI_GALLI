#include<list>
#include<iostream>
#include<string>
#include <time.h>	
using namespace std;
class Player {
	//.플레이 가능 여부
	bool isPlayAvailable;
	//.카드 개수
	int cardCount;
	//.가지고 있는 카드 리스트 (누적) - 
	list<int> cardList;
protected:
	//필요한 메소드 - 카드 추가(랜덤 할당), 카드 사용, 
	int addCard() {
		srand(time(NULL));
		int cardNum;
		cardNum = rand() % 10;
		return cardNum;
	}
};