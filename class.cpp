#include<list>
#include<iostream>
#include<string>
#include <time.h>	
using namespace std;
class Player {
	//.�÷��� ���� ����
	bool isPlayAvailable;
	//.ī�� ����
	int cardCount;
	//.������ �ִ� ī�� ����Ʈ (����) - 
	list<int> cardList;
protected:
	//�ʿ��� �޼ҵ� - ī�� �߰�(���� �Ҵ�), ī�� ���, 
	int addCard() {
		srand(time(NULL));
		int cardNum;
		cardNum = rand() % 10;
		return cardNum;
	}
};