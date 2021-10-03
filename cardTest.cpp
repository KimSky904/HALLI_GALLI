#include<stack>
#include<iostream>	
using namespace std;
#define CARDCOUNT 20*4
class Card {
    int type;
    int num;
public:
    Card() {
        this->type = 0;
        this->num = 0;
    }
    Card(int type, int num) {
        this->type = type;
        this->num = num;
    }
    int getType() {
        return type;
    }
    int getNumber() {
        return num;
    }
    //���
    void getInfo() {
        cout <<"[ " << type << " , "<<num << " ]";
    }
};
class Player {
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
    void setNoneAvailable() {
        available = false;
        cout << playerNum << "�� ����ڰ� Ż���Ǿ����ϴ�." << endl;
        //���� ī�� ����
        while (!front.empty()) front.pop();
        while (!back.empty()) back.pop();
    }
    bool getAvailable() {
        return available;
    }
    //���
    void getInfo() {
        cout << "[ " << playerNum<<" ]" << endl;
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
    int getPlayerNum() {
        return playerNum;
    }
    //�ʹ� ī�� �� ����
    Player(int num) {
        playerNum = num;
        available = true;
    }
    //������ ī�彺���� ���� �� ī�� ��ȯ
    Card getFrontTopCard() {
        if (front.empty()) return Card();
        return front.top();
    }
    //������ ���� ī�彺���� ���� �� ī�� ��ȯ
    Card getBackTopCard() {
        //if (back.empty()) return Card();
        return back.top();
    }
    //������/������ ���� ī���� ���� ��ȯ
    int getFrontCount() {
        return front.size();
    }
    int getBackCount() {
        return back.size();
    }
    //ī�� �߰�
    void pushBack(const Card& card) {
        //cout << "push��, "<< getBackCount() << endl;
        back.push(card);
    }
    void pushFront(const Card& card) {
        front.push(card);
    }
    //ī�� ������
    void popBack() {
        back.pop();
    }
    void popFront() {
        front.pop();
    }
    //back -> front ī�� ������
    int open() {
        if (back.empty()) {
            setNoneAvailable();
            return -1;
        }
        pushFront(getBackTopCard());
        popBack();
        return 0;
    }
    bool backIsEmpty() {
        return back.empty();
    }
    bool frontIsEmpty() {
        return front.empty();
    }
};
//ī��
Card cards[CARDCOUNT] = { //���Ϻ� ī�� 20�� (1:6,2:5,3:4,4:3,5:2)
    //���
    Card(1,1),Card(1,1),Card(1,1),Card(1,1),Card(1,1),
    Card(1,1),Card(1,2),Card(1,2),Card(1,2),Card(1,2),
    Card(1,2),Card(1,3),Card(1,3),Card(1,3),Card(1,3),
    Card(1,4),Card(1,4),Card(1,4),Card(1,5),Card(1,5),
    //�ٳ���
    Card(2,1),Card(2,1),Card(2,1),Card(2,1),Card(2,1),
    Card(2,1),Card(2,2),Card(2,2),Card(2,2),Card(2,2),
    Card(2,2),Card(2,3),Card(2,3),Card(2,3),Card(2,3),
    Card(2,4),Card(2,4),Card(2,4),Card(2,5),Card(2,5),
    //��
    Card(3,1),Card(3,1),Card(3,1),Card(3,1),Card(3,1),
    Card(3,1),Card(3,2),Card(3,2),Card(3,2),Card(3,2),
    Card(3,2),Card(3,3),Card(3,3),Card(3,3),Card(3,3),
    Card(3,4),Card(3,4),Card(3,4),Card(3,5),Card(3,5),
    //ü��
    Card(4,1),Card(4,1),Card(4,1),Card(4,1),Card(4,1),
    Card(4,1),Card(4,2),Card(4,2),Card(4,2),Card(4,2),
    Card(4,2),Card(4,3),Card(4,3),Card(4,3),Card(4,3),
    Card(4,4),Card(4,4),Card(4,4),Card(4,5),Card(4,5),
};
void swap(Card* A, Card* B)
{
    Card temp;
    temp = *A;
    *A = *B;
    *B = temp;
}
void randomCard(Card* card){   // ���⼭ �ָ� �ؾ� �� �Լ�.
    int i;  // �ݺ����� ���� ����
    for (i = 0; i < CARDCOUNT; i++)
    {
        // ���� ��ġ�� ī��� ���� ��ġ�� ������ġ���� �����ϰ� ���� ī�带 �ٲ۴�.
        swap(&card[i], &card[(rand() % (CARDCOUNT - i)) + i]);
    }
}
void setInitCard(Player& p1, Player& p2, Player& p3, Player& p4) {
    randomCard(cards);
    //�� �÷��̾�� ī�� �й�
    for (int i = 0; i < 20; i++) {
        p1.pushBack(cards[i]);
    }
    for (int i = 20; i < 40; i++) {
        p2.pushBack(cards[i]);
    }
    for (int i = 40; i < 60; i++) {
        p3.pushBack(cards[i]);
    }
    for (int i = 60; i < 80; i++) {
        p4.pushBack(cards[i]);
    }
}
//���� 5�� ���� �޼ҵ�
bool checkFiveCard(Player& user,Player& p1,Player& p2,Player& p3) {
    //�� ���Ͽ� ���� ���� �迭
    int fruitCount[] = {0,0,0,0};
    fruitCount[user.getFrontTopCard().getType() - 1]+= user.getFrontTopCard().getNumber();
    fruitCount[p1.getFrontTopCard().getType() - 1] += p1.getFrontTopCard().getNumber();
    fruitCount[p2.getFrontTopCard().getType() - 1] += p2.getFrontTopCard().getNumber();
    fruitCount[p3.getFrontTopCard().getType() - 1] += p3.getFrontTopCard().getNumber();

    for (int i = 0; i < 4; i++) {
        if (fruitCount[i] == 5) return true;
    }
    return false;
}
//[���� ���� ���] front ī�带 ��� ������ back���� �̵� (=> �̵��ߴµ� ���̺� ������ �����ִ°� �ذ�)
void getAllFrontCard(Player& winner,Player& looser1, Player& looser2, Player& looser3) {
    cout << "���� �ƽ��ϴ�. ���̺��� ī�带 ����ϴ�." << endl;
    //�ڽ��� �� ī�� ȸ��
    int cnt1 = winner.getFrontCount();
    for (int i = 0; i < cnt1; i++) {
        winner.pushBack(winner.getFrontTopCard());
        winner.popFront();
    }
    //������ ����� ī�� ȸ��
    int cnt2 = looser1.getFrontCount();
    for (int i = 0; i < cnt2; i++) {
        winner.pushBack(looser1.getFrontTopCard());
        looser1.popFront();
    }
    int cnt3 = looser2.getFrontCount();
    for (int i = 0; i < cnt3; i++) {
        winner.pushBack(looser2.getFrontTopCard());
        looser2.popFront();
    }
    int cnt4 = looser3.getFrontCount();
    for (int i = 0; i < cnt4; i++) {
        winner.pushBack(looser3.getFrontTopCard());
        looser3.popFront();
    }
}

//[���� �߸����� ���] back ī�带 ��� ������� back�� ���徿 ��
void missRinging(Player& p1, Player& p2, Player& p3, Player& p4) {
    cout << "���� �߸������Ƿ� ī�带 �������ݴϴ�." << endl;
    //�÷��� ������ �ο� �� ����
    int cnt = 0;
    if (p1.getAvailable()) cnt++;
    if (p2.getAvailable()) cnt++;
    if (p3.getAvailable()) cnt++;
    if (p4.getAvailable()) cnt++;
    //back ī�尡 ���� ���,������ ��� Ż��
    if (p1.backIsEmpty() || p1.getBackCount() < cnt-1) {
        cout << "��뿡�� �� ī�尡 �����Ͽ� Ż���Ǿ����ϴ�." << endl;
        p1.setNoneAvailable();
        return;
    }
    //�����÷��� ������ �ο� ī�� �����ֱ�
    if (p2.getAvailable()) {
        p2.pushBack(p1.getBackTopCard());
        p1.popBack();
    }
    if (p3.getAvailable()) {
        p3.pushBack(p1.getBackTopCard());
        p1.popBack();
    }
    if (p4.getAvailable()) {
        p4.pushBack(p1.getBackTopCard());
        p1.popBack();
    }

    //ī�带 �� �Ŀ� ī�尡 ���� ��� Ż��
    if (p1.backIsEmpty()) {
        cout << "ī�带 �ְ� ���� ī�尡 ���� Ż���Ǿ����ϴ�." << endl;
        p1.setNoneAvailable();
    }
    return;
}

void printTableInfo(Player& user,Player& p1,Player& p2,Player& p3) {
    cout << "���� ���̺� ī�� [";
    user.getFrontTopCard().getInfo(); cout << ", ";
    p1.getFrontTopCard().getInfo(); cout << ", ";
    p2.getFrontTopCard().getInfo(); cout << ", ";
    p3.getFrontTopCard().getInfo();
    cout << "]" << endl;
}
void printBackInfo(Player& user, Player& p1, Player& p2, Player& p3) {
    cout << "���� ����� ī�� [";
    if (user.getBackCount() != 0){ user.getBackTopCard().getInfo(); cout << ", "; }
    else { cout << "[ 0 , 0 ], ";  }
    if (p1.getBackCount() != 0) { p1.getBackTopCard().getInfo(); cout << ", "; }
    else { cout << "[ 0 , 0 ], "; }
    if (p2.getBackCount() != 0) { p2.getBackTopCard().getInfo(); cout << ", "; }
    else { cout << "[ 0 , 0 ], "; }
    if (p3.getBackCount() != 0) { p3.getBackTopCard().getInfo(); }
    else { cout << "[ 0 , 0 ]"; }
    cout << "]" << endl;
}

int main() {
    //����� ����
    Player user(1), p1(2), p2(3), p3(4);
    //ī�� ������ġ,����ڿ��� ī�� �й�
    setInitCard(user, p1, p2, p3);
    //������ ī�� Ȯ��
    //cout << "==========user==========" << endl;
    //for (int i = 0; i < 10 ; i++) {
    //    user.getBackTopCard().getInfo();
    //    user.popBack();
    //}
    //cout << "==========p1==========" << endl;
    //for (int i = 0; i < 10; i++) {
    //    p1.getBackTopCard().getInfo();
    //    p1.popBack();
    //}
    //cout << "==========p2==========" << endl;
    //for (int i = 0; i < 10; i++) {
    //    p2.getBackTopCard().getInfo();
    //    p2.popBack();
    //}
    //cout << "==========p3==========" << endl;
    //for (int i = 0; i < 10; i++) {
    //    p3.getBackTopCard().getInfo();
    //    p3.popBack();
    //}
    //���� ���ư��� ī�� ������ �� (back -> front)
    int input = 0;
    int turn = -1;
    while(true) {
        // (1:1:1:1) �Ѹ��� �÷��̾ ������ ���
        if ((int)user.getAvailable() + (int)p1.getAvailable() + (int)p2.getAvailable() + (int)p3.getAvailable() == 1) {
            if (user.getAvailable()) {
                cout << "���ڴ� Player1 �Դϴ�." << endl;
            } 
            else if (p1.getAvailable()) {
                cout << "���ڴ� Player2 �Դϴ�." << endl;
            }
            else if (p2.getAvailable()) {
                cout << "���ڴ� Player3 �Դϴ�." << endl;
            }
            else if (p3.getAvailable()) {
                cout << "���ڴ� Player4 �Դϴ�." << endl;
            }
            
            break;
        }

        turn++;
        if (turn % 4 == 0) {
            if (!user.getAvailable()) {
                cout << "[ 1���� Ż���Ǿ� skip�Ǿ����ϴ�. ]" << endl;
                continue;
            }
            else {
                cout << "[ " << user.getPlayerNum() << "�� ���� ]" << endl;
                if(user.open()==-1) continue;
                printTableInfo(user, p1, p2, p3);
                printBackInfo(user, p1, p2, p3);
                cout << "���̺� ī�� ���� : " << user.getFrontCount() << endl;
                cout << "����� ī�� ���� : " << user.getBackCount() << endl;
                cin >> input;
                if (input == 1) {
                    cout << "���� �ƽ��ϴ�." << endl;
                    //���� 5���϶� ���� ���
                    if (checkFiveCard(user, p1, p2, p3)) {
                        //���̺� ���� ī�� ��� ������
                        getAllFrontCard(user, p1, p2, p3);
                    }
                    //�߸� ���� ���
                    else {
                        missRinging(user, p1, p2, p3);
                    }
                }
                else {
                    cout << "���� ġ�� �ʾҽ��ϴ�. ���� ������ �Ѿ�ϴ�." << endl;
                }
            }
        }
        else if (turn % 4 == 1) {
            if (!p1.getAvailable()) {
                cout << "[ 2���� Ż���Ǿ� skip�Ǿ����ϴ�. ]" << endl;
                continue;
            }
            else {
                cout << "[ " << p1.getPlayerNum() << "�� ���� ]" << endl;
                if (p1.open() == -1) continue;
                printTableInfo(user, p1, p2, p3);
                printBackInfo(user, p1, p2, p3);
                cout << "���̺� ī�� ���� : " << p1.getFrontCount() << endl;
                cout << "����� ī�� ���� : " << p1.getBackCount() << endl;
                cin >> input;
                if (input == 1) {
                    cout << "���� �ƽ��ϴ�." << endl;
                    //���� 5���϶� ���� ���
                    if (checkFiveCard(p1, user, p2, p3)) {
                        //���̺� ���� ī�� ��� ������
                        getAllFrontCard(p1, user, p2, p3);
                    }
                    //�߸� ���� ���
                    else {
                        missRinging(p1, user, p2, p3);
                    }
                }
                else {
                    cout << "���� ġ�� �ʾҽ��ϴ�. ���� ������ �Ѿ�ϴ�." << endl;
                }
            }
        }
        else if (turn % 4 == 2) {
            if (!p2.getAvailable()) {
                cout << "[ 3���� Ż���Ǿ� skip�Ǿ����ϴ�. ]" << endl;
                continue;
            }
            else {
                cout << "[ " << p2.getPlayerNum() << "�� ���� ]" << endl;
                if (p2.open() == -1) continue;
                printTableInfo(user, p1, p2, p3);
                printBackInfo(user, p1, p2, p3);
                cout << "���̺� ī�� ���� : " << p2.getFrontCount() << endl;
                cout << "����� ī�� ���� : " << p2.getBackCount() << endl;
                cin >> input;
                if (input == 1) {
                    cout << "���� �ƽ��ϴ�." << endl;
                    //���� 5���϶� ���� ���
                    if (checkFiveCard(p2, user, p1, p3)) {
                        //���̺� ���� ī�� ��� ������
                        getAllFrontCard(p2, user, p1, p3);
                    }
                    //�߸� ���� ���
                    else {
                        missRinging(p2, user, p1, p3);
                    }
                }
                else {
                    cout << "���� ġ�� �ʾҽ��ϴ�. ���� ������ �Ѿ�ϴ�." << endl;
                }
            }
        }else if(turn %4 == 3){
            if (!p3.getAvailable()) {
                cout << "[ 4���� Ż���Ǿ� skip�Ǿ����ϴ�. ]" << endl;
                continue;
            }
            else {
                cout << "[ " << p3.getPlayerNum() << "�� ���� ]" << endl;
                if (p3.open() == -1) continue;
                printTableInfo(user, p1, p2, p3);
                printBackInfo(user, p1, p2, p3);
                cout << "���̺� ī�� ���� : " << p3.getFrontCount() << endl;
                cout << "����� ī�� ���� : " << p3.getBackCount() << endl;
                cin >> input;
                if (input == 1) {

                    cout << "���� �ƽ��ϴ�." << endl;
                    //���� 5���϶� ���� ���
                    if (checkFiveCard(p3, p1, p2, user)) {
                        //���̺� ���� ī�� ��� ������
                        getAllFrontCard(p3, p1, p2, user);
                    }
                    //�߸� ���� ���
                    else {
                        //�� �ο����� ī�� �ϳ��� ��, ī��� ������ �� Ż��
                        missRinging(p3, p1, p2, user);
                    }
                }
                else {
                    cout << "���� ġ�� �ʾҽ��ϴ�. ���� ������ �Ѿ�ϴ�." << endl;
                }
            }
        }
        cout << "==========================================================" << endl;
    }


}