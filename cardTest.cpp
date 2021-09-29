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
    //출력
    void getInfo() {
        cout <<"[ " << type << " , "<<num << " ]";
    }
};
class Player {
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
    void setNoneAvailable() {
        available = false;
        cout << playerNum << "번 사용자가 탈락되었습니다." << endl;
    }
    bool getAvailable() {
        return available;
    }
    //출력
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
    //초반 카드 수 지정
    Player(int num) {
        playerNum = num;
    }
    //뒤집은 카드스택의 가장 위 카드 반환
    Card getFrontTopCard() {
        if (front.empty()) return Card();
        return front.top();
    }
    //뒤집지 않은 카드스택의 가장 위 카드 반환
    Card getBackTopCard() {
        //if (back.empty()) return Card();
        return back.top();
    }
    //뒤집은/뒤집지 않은 카드의 숫자 반환
    int getFrontCount() {
        return front.size();
    }
    int getBackCount() {
        return back.size();
    }
    //카드 추가
    void pushBack(const Card& card) {
        //cout << "push됨, "<< getBackCount() << endl;
        back.push(card);
    }
    void pushFront(const Card& card) {
        front.push(card);
    }
    //카드 잃음ㄴ
    void popBack() {
        back.pop();
    }
    void popFront() {
        front.pop();
    }
    //back -> front 카드 뒤집음
    int open() {
        if (back.empty()) {
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
//카드
Card cards[CARDCOUNT] = { //과일별 카드 20장 (1:6,2:5,3:4,4:3,5:2)
    //사과
    Card(1,1),Card(1,1),Card(1,1),Card(1,1),Card(1,1),
    Card(1,1),Card(1,2),Card(1,2),Card(1,2),Card(1,2),
    Card(1,2),Card(1,3),Card(1,3),Card(1,3),Card(1,3),
    Card(1,4),Card(1,4),Card(1,4),Card(1,5),Card(1,5),
    //바나나
    Card(2,1),Card(2,1),Card(2,1),Card(2,1),Card(2,1),
    Card(2,1),Card(2,2),Card(2,2),Card(2,2),Card(2,2),
    Card(2,2),Card(2,3),Card(2,3),Card(2,3),Card(2,3),
    Card(2,4),Card(2,4),Card(2,4),Card(2,5),Card(2,5),
    //배
    Card(3,1),Card(3,1),Card(3,1),Card(3,1),Card(3,1),
    Card(3,1),Card(3,2),Card(3,2),Card(3,2),Card(3,2),
    Card(3,2),Card(3,3),Card(3,3),Card(3,3),Card(3,3),
    Card(3,4),Card(3,4),Card(3,4),Card(3,5),Card(3,5),
    //체리
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
void randomCard(Card* card){   // 여기서 주목 해야 할 함수.
    int i;  // 반복문에 쓰일 변수
    for (i = 0; i < CARDCOUNT; i++)
    {
        // 현재 위치의 카드와 현재 위치의 다음위치에서 랜덤하게 뽑은 카드를 바꾼다.
        swap(&card[i], &card[(rand() % (CARDCOUNT - i)) + i]);
    }
}
void setInitCard(Player& p1, Player& p2, Player& p3, Player& p4) {
    randomCard(cards);
    //각 플레이어에게 카드 분배
    for (int i = 0; i < 10; i++) {
        p1.pushBack(cards[i]);
    }
    for (int i = 10; i < 20; i++) {
        p2.pushBack(cards[i]);
    }
    for (int i = 20; i < 30; i++) {
        p3.pushBack(cards[i]);
    }
    for (int i = 30; i < 40; i++) {
        p4.pushBack(cards[i]);
    }
}
//과일 5개 세는 메소드
bool checkFiveCard(Player& user,Player& p1,Player& p2,Player& p3) {
    if (user.getFrontCount() * p1.getFrontCount() * p2.getFrontCount() * p3.getFrontCount()) return false;
    //각 과일에 대한 개수 배열
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
//[종을 쳤을 경우] front 카드를 모두 승자의 back으로 이동
void getAllFrontCard(Player& winner,Player& looser1, Player& looser2, Player& looser3) {
    cout << "종을 쳤습니다. 테이블의 카드를 얻습니다." << endl;
    //자신이 낸 카드 회수
    int cnt1 = winner.getFrontCount();
    for (int i = 0; i < cnt1; i++) {
        winner.pushBack(winner.getFrontTopCard());
        winner.popFront();
    }
    //나머지 사용자 카드 회수
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

//[종을 잘못쳤을 경우] back 카드를 모든 사용자의 back에 한장씩 줌
void missRinging(Player& p1, Player& p2, Player& p3, Player& p4) {
    cout << "종을 잘못쳤으므로 카드를 나누어줍니다." << endl;
    //back 카드가 없을 경우,부족한 경우 탈락
    if (p1.backIsEmpty() || p1.getBackCount() < 3) {
        cout << "상대에게 줄 카드가 부족하여 탈락되었습니다." << endl;
        p1.setNoneAvailable();
        return;
    }
    //카드 나눠주기
    p2.pushBack(p1.getBackTopCard());
    p1.popBack();
    p3.pushBack(p1.getBackTopCard());
    p1.popBack();
    p4.pushBack(p1.getBackTopCard());
    p1.popBack();
    //카드를 준 후에 카드가 없을 경우 탈락
    if (p1.backIsEmpty()) {
        cout << "카드를 주고 남은 카드가 없어 탈락되었습니다." << endl;
        p1.setNoneAvailable();
    }
    return;
}


int main() {
    //사용자 생성
    Player user(1), p1(2), p2(3), p3(4);
    //카드 랜덤배치,사용자에게 카드 분배
    setInitCard(user, p1, p2, p3);
    //나눠진 카드 확인
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
    //순서 돌아가며 카드 앞으로 냄 (back -> front)
    int input = 0;
    for (int i = 0; i < CARDCOUNT; i++) {
        if (i % 4 == 0) {
            cout <<"[ " << user.getPlayerNum() << "번 차례 ]" << endl;
            user.open();
            cout << "현재 테이블 카드 [";
            user.getFrontTopCard().getInfo(); cout << ", ";
            p1.getFrontTopCard().getInfo(); cout << ", ";
            p2.getFrontTopCard().getInfo(); cout << ", ";
            p3.getFrontTopCard().getInfo();
            cout << "]" << endl;
            cin >> input;
            if (input == 1) {
                cout << "종을 쳤습니다." << endl;
                //과일 5개일때 쳤을 경우
                if (checkFiveCard(user, p1, p2, p3)) {
                    //테이블 위의 카드 모두 가져감
                    getAllFrontCard(user, p1, p2, p3);
                }
                //잘못 쳤을 경우
                else {
                    missRinging(user, p1, p2, p3);
                }
            }
            else {
                cout << "종을 치지 않았습니다. 다음 턴으로 넘어갑니다." << endl;
            }

        }
        else if (i % 4 == 1) {
            cout << "[ " << p1.getPlayerNum() << "번 차례 ]" << endl;
            p1.open();
            cout << "현재 테이블 카드 [";
            user.getFrontTopCard().getInfo(); cout << ", ";
            p1.getFrontTopCard().getInfo(); cout << ", ";
            p2.getFrontTopCard().getInfo(); cout << ", ";
            p3.getFrontTopCard().getInfo();
            cout << "]" << endl;
            cin >> input;
            if (input == 1) {
                cout << "종을 쳤습니다." << endl;
                //과일 5개일때 쳤을 경우
                if (checkFiveCard(p1, user, p2, p3)) {
                    //테이블 위의 카드 모두 가져감
                    getAllFrontCard(p1, user, p2, p3);
                }
                //잘못 쳤을 경우
                else {
                    missRinging(p1, user, p2, p3);
                }
            }
            else {
                cout << "종을 치지 않았습니다. 다음 턴으로 넘어갑니다." << endl;
            }
        }
        else if (i % 4 == 2) {
            cout << "[ " << p2.getPlayerNum() << "번 차례 ]" << endl;
            p2.open();
            cout << "현재 테이블 카드 [";
            user.getFrontTopCard().getInfo(); cout << ", ";
            p1.getFrontTopCard().getInfo(); cout << ", ";
            p2.getFrontTopCard().getInfo(); cout << ", ";
            p3.getFrontTopCard().getInfo();
            cout << "]" << endl;
            cin >> input;
            if (input == 1) {
                cout << "종을 쳤습니다." << endl;
                //과일 5개일때 쳤을 경우
                if (checkFiveCard(p2, user, p1, p3)) {
                    //테이블 위의 카드 모두 가져감
                    getAllFrontCard(p2, user, p1, p3);
                }
                //잘못 쳤을 경우
                else {
                    missRinging(p2, user, p1, p3);
                }
            }
            else {
                cout << "종을 치지 않았습니다. 다음 턴으로 넘어갑니다." << endl;
            }
        }else if(i%4 == 3){
            cout << "[ " << p3.getPlayerNum() << "번 차례 ]" << endl;
            p3.open(); 
            cout << "현재 테이블 카드 [";
            user.getFrontTopCard().getInfo(); cout << ", ";
            p1.getFrontTopCard().getInfo(); cout << ", ";
            p2.getFrontTopCard().getInfo(); cout << ", ";
            p3.getFrontTopCard().getInfo();
            cout << "]" << endl;
            cin >> input;
            if (input == 1) {
                cout << "종을 쳤습니다." << endl;
                //과일 5개일때 쳤을 경우
                if (checkFiveCard(p3, p1, p2, user)) {
                    //테이블 위의 카드 모두 가져감
                    getAllFrontCard(p3, p1, p2, user);
                }
                //잘못 쳤을 경우
                else {
                    missRinging(p3, p1, p2, user);
                }
            }
            else {
                cout << "종을 치지 않았습니다. 다음 턴으로 넘어갑니다." << endl;
            }
        }
        cout << "==========================================================" << endl;
    }


}