#pragma once
#include "card.h"
#include <stack>
using namespace std;
class Player{
	//�� ī��
	stack<Card> front;
	//���� ���� ī��
	stack<Card> back;
	//�÷��̾� ��ȣ
	int playerNum;
	//�÷��� ���� ����
	bool available;
public:
    //Ż��ó��
    void setNoneAvailable();
    bool getAvailable();
    //���
    void getInfo();
    int getPlayerNum();
    //�ʹ� ī�� �� ����
    Player(int num);
    //������ ī�彺���� ���� �� ī�� ��ȯ
    Card getFrontTopCard();
    //������ ���� ī�彺���� ���� �� ī�� ��ȯ
    Card getBackTopCard();
    //������/������ ���� ī���� ���� ��ȯ
    int getFrontCount();
    int getBackCount();
    //ī�� �߰�
    void pushBack(const Card& card);
    void pushFront(const Card& card);
    //ī�� ������
    void popBack();
    void popFront();
    //back -> front ī�� ������
    int open();
    bool backIsEmpty();
    bool frontIsEmpty();
};