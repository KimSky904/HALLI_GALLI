#include<iostream>
#include<string>
#include<ctime>
#include<cstdlib>
#include<string>
#include<conio.h>
#include<Windows.h>
#include<time.h>	
#include<list>
#include<stack>
using namespace std;
#define RED         (FOREGROUND_RED | FOREGROUND_INTENSITY)
#define BLUE        (FOREGROUND_BLUE | FOREGROUND_INTENSITY)
#define PINK        (RED | BLUE)
#define GREEN       (FOREGROUND_GREEN | FOREGROUND_INTENSITY)
#define YELLOW      (RED | GREEN)
#define WHITE       (RED | GREEN | BLUE)
#define CARDCOUNT 20*4

//�ܼ� ����
void SetConsoleView()
{
    system("mode con cols=120 lines=41 | title Halli Galli");   //ȭ��ũ��,�����̸�
}
//Ŀ���̵� �Լ�
void gotoxy(int x, int y)
{
    COORD Pos;
    Pos.X = 2 * x;
    Pos.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}
//keyboard �Է°� ��ȯ��
int GetKeyValue()
{
    if (_kbhit() != 0) {
        return _getch();
    }
    return 0;
}
//��������
void PrintString(HANDLE hStdOut, WORD Attribute)
{
    SetConsoleTextAttribute(hStdOut, Attribute);
}

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
        cout << "[ " << type << " , " << num << " ]";
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
    }
    bool getAvailable() {
        return available;
    }
    //���
    void getInfo() {
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


//�� ī��
void emptyCardPrint() {
    cout << "                                               "
        << "��������������������������������" << endl;
    for (int i = 0; i < 7; ++i)
        cout << "                                               "
        << "��           ��" << endl;

    cout << "                                               "
        << "��������������������������������" << endl;
}

//�տ� �ִ� ī�� ��
void frontCardPrint(Card card,Player player) {
    HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
    //ī�� Ÿ��
    int type = card.getType();
    char fruit = 'e';
    switch (type) {
        case 1: fruit = '@';
            PrintString(hStdOut, RED);
            break; //���
        case 2: fruit = '@';
            PrintString(hStdOut, YELLOW);
            break; //�ٳ���
        case 3: fruit = '@'; 
            PrintString(hStdOut, GREEN);
            break; //����
        case 4: fruit = '@'; 
            PrintString(hStdOut, RED);
            break; //����
    }
    //ī�� ��� ��ġ
    int x;
    int y = 14;
    switch (player.getPlayerNum()){
        case 1: x = 10; break;
        case 2 : x = 20; break;
        case 3 : x = 30; break;
        case 4 : x = 40; break;
    }

    switch (card.getNumber()) {
    case 1:
        gotoxy(x, y);
        cout << "��������������������������������" << endl;
        gotoxy(x, y + 1);
        cout << "��              ��" << endl;
        gotoxy(x, y + 2);
        cout << "��              ��" << endl;
        gotoxy(x, y + 3);
        cout << "��              ��" << endl;
        gotoxy(x, y + 4);
        cout << "��              ��" << endl;
        gotoxy(x, y + 5);
        cout << "��       "<< fruit <<"       ��" << endl;
        gotoxy(x, y + 6);
        cout << "��              ��" << endl;
        gotoxy(x, y + 7);
        cout << "��              ��" << endl;
        gotoxy(x, y + 8);
        cout << "��              ��" << endl;
        gotoxy(x, y + 9);
        cout << "��              ��" << endl;
        gotoxy(x, y + 10);
        cout << "��������������������������������" << endl;
        break;
    case 2:
        gotoxy(x, y);
        cout << "��������������������������������" << endl;
        gotoxy(x, y + 1);
        cout << "��              ��" << endl;
        gotoxy(x, y + 2);
        cout << "��              ��" << endl;
        gotoxy(x, y + 3);
        cout << "��       " << fruit << "      ��" << endl;
        gotoxy(x, y + 4);
        cout << "��              ��" << endl;
        gotoxy(x, y + 5);
        cout << "��              ��" << endl;
        gotoxy(x, y + 6);
        cout << "��              ��" << endl;
        gotoxy(x, y + 7);
        cout << "��       " << fruit << "      ��" << endl;
        gotoxy(x, y + 8);
        cout << "��              ��" << endl;
        gotoxy(x, y + 9);
        cout << "��              ��" << endl;
        gotoxy(x, y + 10);
        cout << "��������������������������������" << endl;
        break;
    case 3:
        gotoxy(x, y);
        cout << "��������������������������������" << endl;
        gotoxy(x, y + 1);
        cout << "��              ��" << endl;
        gotoxy(x, y + 2);
        cout << "��   " << fruit << "           ��" << endl;
        gotoxy(x, y + 3);
        cout << "��              ��" << endl;
        gotoxy(x, y + 4);
        cout << "��              ��" << endl;
        gotoxy(x, y + 5);
        cout << "��       " << fruit << "       ��" << endl;
        gotoxy(x, y + 6);
        cout << "��              ��" << endl;
        gotoxy(x, y + 7);
        cout << "��              ��" << endl;
        gotoxy(x, y + 8);
        cout << "��           " << fruit << "  ��" << endl;
        gotoxy(x, y + 9);
        cout << "��              ��" << endl;
        gotoxy(x, y + 10);
        cout << "��������������������������������" << endl;
        break;
    case 4:
        gotoxy(x, y);
        cout << "��������������������������������" << endl;
        gotoxy(x, y + 1);
        cout << "��              ��" << endl;
        gotoxy(x, y + 2);
        cout << "��    " << fruit << "     " << fruit << "     ��" << endl;
        gotoxy(x, y + 3);
        cout << "��              ��" << endl;
        gotoxy(x, y + 4);
        cout << "��              ��" << endl;
        gotoxy(x, y + 5);
        cout << "��              ��" << endl;
        gotoxy(x, y + 6);
        cout << "��              ��" << endl;
        gotoxy(x, y + 7);
        cout << "��              ��" << endl;
        gotoxy(x, y + 8);
        cout << "��    " << fruit << "     " << fruit << "     ��" << endl;
        gotoxy(x, y + 9);
        cout << "��              ��" << endl;
        gotoxy(x, y + 10);
        cout << "��������������������������������" << endl;
        break;
    case 5:
        gotoxy(x, y);
        cout << "��������������������������������" << endl;
        gotoxy(x, y + 1);
        cout << "��              ��" << endl;
        gotoxy(x, y + 2);
        cout << "��    " << fruit << "     " << fruit << "     ��" << endl;
        gotoxy(x, y + 3);
        cout << "��              ��" << endl;
        gotoxy(x, y + 4);
        cout << "��              ��" << endl;
        gotoxy(x, y + 5);
        cout << "��       " << fruit << "       ��" << endl;
        gotoxy(x, y + 6);
        cout << "��              ��" << endl;
        gotoxy(x, y + 7);
        cout << "��              ��" << endl;
        gotoxy(x, y + 8);
        cout << "��    " << fruit << "     " << fruit << "     ��" << endl;
        gotoxy(x, y + 9);
        cout << "��              ��" << endl;
        gotoxy(x, y + 10);
        cout << "��������������������������������" << endl;
        break;
    default:
        emptyCardPrint();
    }
}


//�ܼ� ����
void SetConsoleView();
//Ŀ���̵� �Լ�
void gotoxy(int x, int y);
//keyboard �Է°� ��ȯ��
int GetKeyValue();
//��������
void PrintString(HANDLE hStdOut, WORD Attribute);
//ȭ��ε� draw
void DrawLoading();
//����ȭ�� draw
void DrawIntro();
//����ȭ�� draw
void DrawStartGame();
//����ȭ�� draw
void DrawInfoScreen();
//[��������] ī��й�
void setInitCard(Player& p1, Player& p2, Player& p3, Player& p4);
//�޴�����
int ReadyGame();
//���� ���� Ű
int GameKey();
//���� ����
void StartGame();
//���� ����
void ShowInfo();
//����
int main(void);


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

//ȭ��ε� draw
void DrawLoading() {

}
//����ȭ�� draw
void DrawIntro()
{
    HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);

    PrintString(hStdOut, WHITE);
    system("cls");
    gotoxy(5, 4);
    cout << "##   ##    ##     ####     ####      ####               ####     ##     ####     ####      ####";
    gotoxy(5, 5);
    cout << "##   ##   ####     ##       ##        ##               ##  ##   ####     ##       ##        ##";
    gotoxy(5, 6);
    cout << "##   ##  ##  ##    ##       ##        ##              ##       ##  ##    ##       ##        ##";
    gotoxy(5, 7);
    cout << "#######  ##  ##    ##       ##        ##              ##       ##  ##    ##       ##        ##";
    gotoxy(5, 8);
    cout << "##   ##  ######    ##   #   ##   #    ##              ##  ###  ######    ##   #   ##   #    ##";
    gotoxy(5, 9);
    cout << "##   ##  ##  ##    ##  ##   ##  ##    ##               ##  ##  ##  ##    ##  ##   ##  ##    ##";
    gotoxy(5, 10);
    cout << "##   ##  ##  ##   #######  #######   ####               #####  ##  ##   #######  #######   ####";


    PrintString(hStdOut, GREEN);
    gotoxy(26, 18);
    cout << "     ~,";
    gotoxy(26, 19);
    cout << "     ~-. ";
    gotoxy(26, 20);
    cout << "     .~- ~     ";
    gotoxy(26, 21);
    cout << "      --:   ";
    PrintString(hStdOut, RED);
    gotoxy(25, 22);
    cout << "     �ɢɢɢ�";
    gotoxy(25, 23);
    cout << "    �ɢɢɢɢ�";
    gotoxy(25, 24);
    cout << "   �ɢɢɢɢɢ�";
    gotoxy(25, 25);
    cout << "   �ɢɢɢɢɢ�";
    gotoxy(25, 26);
    cout << "    �ɢɢɢɢ� ";
    gotoxy(25, 27);
    cout << "     �ɢɢɢ� ";
                         

    PrintString(hStdOut, WHITE);
    gotoxy(24, 29);
    cout << "�� Game Rule for 'r'";
    gotoxy(24, 31);
    cout << "�� Game Start for 's'";
    gotoxy(24, 33);
    cout << "�� Exit for 'e'";
}
//����ȭ�� draw
void DrawStartGame()
{
    //120 41
    system("cls");

    //�÷��̾� 1 (�����) (���� ���)
    gotoxy(0, 0);
    cout << "�ɦ�����������������������������";
    for (int i = 1; i < 7; i++) {
        gotoxy(0, i);
        cout << "��              ��";
    }
    gotoxy(0, 7);
    cout << "�ɦ�����������������������������";
    gotoxy(0, 8);
    cout << "���� ī�� �� : -";
    gotoxy(0, 9);
    cout << "�ǿ� ���� ī�� �� : -";

    //�÷��̾� 2 (������ ���)
    gotoxy(51, 0);
    cout << "�ɦ�����������������������������";
    for (int i = 1; i < 7; i++) {
        gotoxy(51, i);
        cout << "��              ��";
    }
    gotoxy(51, 7);
    cout << "�ɦ�����������������������������";
    gotoxy(48, 8);
    cout << "���� ī�� �� : -";
    gotoxy(48, 9);
    cout << "�ǿ� ���� ī�� �� : -";

    //�÷��̾� 3 (���� �ϴ�)
    gotoxy(0, 30);
    cout << "���� ī�� �� : -";
    gotoxy(0, 31);
    cout << "�ǿ� ���� ī�� �� : -";
    gotoxy(0, 32);
    cout << "�ɦ�����������������������������";
    for (int i = 33; i < 40; i++) {
        gotoxy(0, i);
        cout << "��              ��";
    }
    gotoxy(0, 40);
    cout << "�ɦ�����������������������������";


    //�÷��̾� 4 (������ �ϴ�)
    gotoxy(48, 30);
    cout << "���� ī�� �� : -";
    gotoxy(48, 31);
    cout << "�ǿ� ���� ī�� �� : -";
    gotoxy(51, 32);
    cout << "�ɦ�����������������������������";
    for (int i = 33; i < 40; i++) {
        gotoxy(51, i);
        cout << "��              ��";
    }
    gotoxy(51, 40);
    cout << "�ɦ�����������������������������";


    //ī�� 1
    gotoxy(10, 14);
    cout << "��������������������������������";
    for (int i = 15; i < 25; i++) {
        gotoxy(10, i);
        cout << "��              ��";
    }
    gotoxy(10, 25);
    cout << "��������������������������������";

    //ī�� 2
    gotoxy(20, 14);
    cout << "��������������������������������";
    for (int i = 15; i < 25; i++) {
        gotoxy(20, i);
        cout << "��              ��";
    }
    gotoxy(20, 25);
    cout << "��������������������������������";

    //ī�� 3
    gotoxy(30, 14);
    cout << "��������������������������������";
    for (int i = 15; i < 25; i++) {
        gotoxy(30, i);
        cout << "��              ��";
    }
    gotoxy(30, 25);
    cout << "��������������������������������";

    //ī�� 4
    gotoxy(40, 14);
    cout << "��������������������������������";
    for (int i = 15; i < 25; i++) {
        gotoxy(40, i);
        cout << "��              ��";
    }
    gotoxy(40, 25);
    cout << "��������������������������������";


}
//����ȭ�� draw
void DrawInfoScreen() {
    HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
    system("cls");
    PrintString(hStdOut, YELLOW);
    gotoxy(3, 2);
    cout << "                           ,--,";
    gotoxy(3, 3);
    cout << "                           ,--,";
    gotoxy(3, 4);
    cout << "                         ,--.'|";
    gotoxy(3, 5);
    cout << "  __  ,-.          ,--,  |  | :";
    gotoxy(3, 6);
    cout << ",' ,'/ /|        ,'_ /|  :  : '";
    gotoxy(3, 7);
    cout << "'  | |' |   .--. |  | :  |  ' |       ,---.";
    gotoxy(3, 8);
    cout << "|  |   ,' ,'_ /| :  . |  '  | |      /     \\";
    gotoxy(3, 9);
    cout << "'  :  /   |  ' | |  . .  |  | :     /    /  |";
    gotoxy(3, 10);
    cout << "|  | '    |  | ' |  | |  '  : |__  .    ' / |";
    gotoxy(3, 11);
    cout << ";  : |    :  | : ;  ; |  |  | '.'| '   ;   /|";
    gotoxy(3, 12);
    cout << "|  , ;    '  :  `--'   \ ;  :    ; '   |  / |";
    gotoxy(3, 13);
    cout << " ---'     :  ,     .-./ |  ,   /  |   :    |";
    gotoxy(3, 14);
    cout << "           `--`----'      ---`-'    \   \  /";
    gotoxy(3, 15);
    cout << "                                     `----'";
    PrintString(hStdOut, WHITE);
    for (int i = 20; i < 40; i++) {
        if (i % 2 == 0) {
            gotoxy(3, i);
            cout << "��                                                                                                    ��";
        }
    }
    gotoxy(3, 19);
    cout << "�����������������������������������������������������";
    gotoxy(3, 21);
    cout << "��  �� �⺻ �������� ������� '�Ҹ�����'�� �����մϴ�.                                              ��";
    gotoxy(3, 23);
    cout << "��  �� ī�带 ��� ������ Ż��, ������ ���� ����� �¸��ϰ� �˴ϴ�.                                   ��";
    gotoxy(3, 25);
    cout << "��  �� �� 4���� �÷��̾ ������, �� �÷��̾�� 28���� ī�尡 �־����ϴ�.                          ��";
    gotoxy(3, 27);
    cout << "��  �� ������ ���� 'space'�� ī�带 �������ϴ�.                                                       ��";
    gotoxy(3, 29);
    cout << "��  �� ���� ���� ī���� ���� ���� 5���� �Ǹ� 'enter'�� ���� Ĩ�ϴ�.                                   ��";
    gotoxy(3, 31);
    cout << "��  �� ���� ���� ���� ģ ����� ���� ī�带 ��� �������ϴ�.                                          ��";
    gotoxy(3, 33);
    cout << "��  �� ���� 5���� �ƴ� ���¿��� ���� ġ��, ������ �÷��̾�� ī�带 1�徿 �ݳ��մϴ�.               ��";
    gotoxy(3, 35);
    cout << "��  �� �� �տ� ���� �ִ� ī��� ���� ������ �Ѿ�ϴ�.                                               ��";
    gotoxy(3, 37);
    cout << "��  �� ī�带 ��� ����� �÷��̾�� ��� Ż��ó���˴ϴ�.                   �� ������ : esc           ��";
    gotoxy(3, 39);
    cout << "�����������������������������������������������������";

}


//[ī��й�] swap
void swap(Card* A, Card* B)
{
    Card temp;
    temp = *A;
    *A = *B;
    *B = temp;
}
//[ī��й�] ī�� ������ġ
void randomCard(Card* card) {
    for (int i = 0; i < CARDCOUNT; i++) swap(&card[i], &card[(rand() % (CARDCOUNT - i)) + i]);
}
//[ī��й�] ����ڿ��� ī�� �й�
void setInitCard(Player& p1, Player& p2, Player& p3, Player& p4) {
    randomCard(cards);
    //�� �÷��̾�� ī�� �й�
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

//[�Ǻ�] ���� �� 5�� �Ǻ�
bool checkFiveCard(Player& user, Player& p1, Player& p2, Player& p3) {
    //�� ���Ͽ� ���� ���� �迭
    int fruitCount[] = { 0,0,0,0 };
    fruitCount[user.getFrontTopCard().getType() - 1] += user.getFrontTopCard().getNumber();
    fruitCount[p1.getFrontTopCard().getType() - 1] += p1.getFrontTopCard().getNumber();
    fruitCount[p2.getFrontTopCard().getType() - 1] += p2.getFrontTopCard().getNumber();
    fruitCount[p3.getFrontTopCard().getType() - 1] += p3.getFrontTopCard().getNumber();

    for (int i = 0; i < 4; i++) {
        if (fruitCount[i] == 5) return true;
    }
    return false;
}
//[�Ǻ�] ������ ��� - ��� front�� ������ back���� �̵�
void getAllFrontCard(Player& winner, Player& looser1, Player& looser2, Player& looser3) {
    cout << "[ "<<winner.getPlayerNum() <<"�� ����ڰ� ���̺� ���� ��� ī�带 ȹ���մϴ�. ]" << endl;
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
//[�Ǻ�] �� �߸����� ��� - �� player���� ī�� ���徿 back�� �ѱ�
void missRinging(Player& p1, Player& p2, Player& p3, Player& p4) {
    //cout << "���� �߸������Ƿ� ī�带 �������ݴϴ�." << endl;
    //�÷��� ������ �ο� �� ����
    int cnt = 0;
    if (p1.getAvailable()) cnt++;
    if (p2.getAvailable()) cnt++;
    if (p3.getAvailable()) cnt++;
    if (p4.getAvailable()) cnt++;
    //back ī�尡 ���� ���,������ ��� Ż��
    if (p1.backIsEmpty() || p1.getBackCount() < cnt - 1) {
        //cout << "��뿡�� �� ī�尡 �����Ͽ� Ż���Ǿ����ϴ�." << endl;
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
       // cout << "ī�带 �ְ� ���� ī�尡 ���� Ż���Ǿ����ϴ�." << endl;
        p1.setNoneAvailable();
    }
    return;
}


//[���] ���̺� ���� ī�� ����
void printTableInfo(Player& user, Player& p1, Player& p2, Player& p3) {
    cout << "���� ���̺� ī�� [";
    user.getFrontTopCard().getInfo(); cout << ", ";
    p1.getFrontTopCard().getInfo(); cout << ", ";
    p2.getFrontTopCard().getInfo(); cout << ", ";
    p3.getFrontTopCard().getInfo();
    cout << "]" << endl;
}
//[���] ����� ī�� ����
void printBackInfo(Player& user, Player& p1, Player& p2, Player& p3) {
    cout << "���� ����� ī�� [";
    if (user.getBackCount() != 0) { user.getBackTopCard().getInfo(); cout << ", "; }
    else { cout << "[ 0 , 0 ], "; }
    if (p1.getBackCount() != 0) { p1.getBackTopCard().getInfo(); cout << ", "; }
    else { cout << "[ 0 , 0 ], "; }
    if (p2.getBackCount() != 0) { p2.getBackTopCard().getInfo(); cout << ", "; }
    else { cout << "[ 0 , 0 ], "; }
    if (p3.getBackCount() != 0) { p3.getBackTopCard().getInfo(); }
    else { cout << "[ 0 , 0 ]"; }
    cout << "]" << endl;
}

//�޴�����
int ReadyGame()
{
    //����ȭ�� �׸���
    DrawIntro();
    while (true) {
        //Ű�� �޾ƿ���
        int key = GetKeyValue();
        if (key == 'r' || key == 'R') {         //rule = 1
            return 1;
        }
        else if (key == 's' || key == 'S') {    //start = 2
            return 2;
        }
        else if (key == 'e' || key == 'E') {    //exit = 0
            break;
        }
    }
    return 0;
}
//���� ���� Ű
int GameKey()
{
    while (true) {
        //Ű�� �޾ƿ��� (��ġ�� : 1, ī�� ���� : 2, ������ : 0)
        int key = _getch();
        if (key == 13) {         //��ġ�� = 1 (enter)
            return 1;
        }
        else if (key == 32) {    //ī�� ���� = 2 (space)
            return 2;
        }
        else if (key == 27) {    //exit = 0 (esc)
            return 3;
        }
    }
    return 0;
}

void printPlayersCardInfo(Player &p1,Player &p2,Player &p3,Player &p4) {
    gotoxy(0, 8);
    cout << "���� ī�� �� : " << p1.getBackCount() << "  ";
    gotoxy(0, 9);
    cout << "�ǿ� ���� ī�� �� : " << p1.getFrontCount() << "  ";

    gotoxy(48, 8);
    cout << "���� ī�� �� : " << p2.getBackCount() << "  ";
    gotoxy(48, 9);
    cout << "�ǿ� ���� ī�� �� : " << p2.getFrontCount() << "  ";

    gotoxy(0, 30);
    cout << "���� ī�� �� : " << p3.getBackCount() << "  ";
    gotoxy(0, 31);
    cout << "�ǿ� ���� ī�� �� : " << p3.getFrontCount() << "  ";

    gotoxy(48, 30);
    cout << "���� ī�� �� : " << p4.getBackCount() << "  ";
    gotoxy(48, 31);
    cout << "�ǿ� ���� ī�� �� : " << p4.getFrontCount() << "  ";
}

//���� ����
void StartGame()
{
    DrawStartGame();
    //����� ����
    Player user(1), p1(2), p2(3), p3(4);
    //ī�� ������ġ,����ڿ��� ī�� �й�
    setInitCard(user, p1, p2, p3);
    //�ݺ�
    int input = 0;
    int turn = -1;
    while (true) {
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
            printPlayersCardInfo(user, p1, p2, p3);
            if (!user.getAvailable()) {
                continue;
            }
            else {
                gotoxy(26, 7);
                cout << "                                         ";
                gotoxy(26, 7);
                cout << "[ " << user.getPlayerNum() << "�� ���� ]";
                if (user.open() == -1) continue;
                gotoxy(10, 14);
                frontCardPrint(user.getFrontTopCard(),user);
                //printTableInfo(user, p1, p2, p3);
                //printBackInfo(user, p1, p2, p3);
                //cout << "���̺� ī�� ���� : " << user.getFrontCount() << endl;
                //cout << "����� ī�� ���� : " << user.getBackCount() << endl;
                input = GameKey();
                if (input == 1) {
                    gotoxy(24, 9);
                    cout << "                                                          ";
                    gotoxy(24, 9);
                    cout << "[ 1�� player : ���� �ƽ��ϴ� ]";
                    //���� 5���϶� ���� ���
                    if (checkFiveCard(user, p1, p2, p3)) {
                        //���̺� ���� ī�� ��� ������
                        getAllFrontCard(user, p1, p2, p3);
                        printPlayersCardInfo(user, p1, p2, p3);
                    }
                    //�߸� ���� ���
                    else {
                        missRinging(user, p1, p2, p3);
                        printPlayersCardInfo(user, p1, p2, p3);
                    }
                }
                else if(input==2){
                    gotoxy(15, 9);
                    cout << "                                                          ";
                    gotoxy(15, 9);
                    cout << "[ 1�� player : ���� ġ�� �ʾҽ��ϴ�. ���� ������ �Ѿ�ϴ�. ]";
                }
            }
        }
        else if (turn % 4 == 1) {
            printPlayersCardInfo(user, p1, p2, p3);
            if (!p1.getAvailable()) {
                continue;
            }
            else {
                gotoxy(26, 7);
                cout << "                                         ";
                gotoxy(26, 7);
                cout << "[ " << p1.getPlayerNum() << "�� ���� ]";
                if (p1.open() == -1) continue;
                gotoxy(20, 14);
                frontCardPrint(user.getFrontTopCard(),p1);
                //printTableInfo(user, p1, p2, p3);
                //printBackInfo(user, p1, p2, p3);
                //cout << "���̺� ī�� ���� : " << p1.getFrontCount() << endl;
                //cout << "����� ī�� ���� : " << p1.getBackCount() << endl;
                input = GameKey();
                if (input == 1) {
                    gotoxy(24, 9);
                    cout << "                                                          ";
                    gotoxy(24, 9);
                    cout << "[ 2�� player : ���� �ƽ��ϴ� ]";
                    //���� 5���϶� ���� ���
                    if (checkFiveCard(p1, user, p2, p3)) {
                        //���̺� ���� ī�� ��� ������
                        getAllFrontCard(p1, user, p2, p3);
                        printPlayersCardInfo(user, p1, p2, p3);
                    }
                    //�߸� ���� ���
                    else {
                        missRinging(p1, user, p2, p3);
                        printPlayersCardInfo(user, p1, p2, p3);
                    }
                }
                else {
                    gotoxy(15, 9);
                    cout << "                                                          ";
                    gotoxy(15, 9);
                    cout << "[ 2�� player : ���� ġ�� �ʾҽ��ϴ�. ���� ������ �Ѿ�ϴ�. ]";
                }
            }
        }
        else if (turn % 4 == 2) {
            printPlayersCardInfo(user, p1, p2, p3);
            if (!p2.getAvailable()) {
                continue;
            }
            else {
                gotoxy(26, 7);
                cout << "                                         ";
                gotoxy(26, 7);
                cout << "[ " << p2.getPlayerNum() << "�� ���� ]";
                if (p2.open() == -1) continue;
                gotoxy(30, 14);
                frontCardPrint(user.getFrontTopCard(),p2);
                //printTableInfo(user, p1, p2, p3);
                //printBackInfo(user, p1, p2, p3);
                //cout << "���̺� ī�� ���� : " << p2.getFrontCount() << endl;
                //cout << "����� ī�� ���� : " << p2.getBackCount() << endl;
                input = GameKey();
                if (input == 1) {
                    gotoxy(24, 9);
                    cout << "                                                          ";
                    gotoxy(24, 9);
                    cout << "[ 3�� player : ���� �ƽ��ϴ� ]";
                    //���� 5���϶� ���� ���
                    if (checkFiveCard(p2, user, p1, p3)) {
                        //���̺� ���� ī�� ��� ������
                        getAllFrontCard(p2, user, p1, p3);
                        printPlayersCardInfo(user, p1, p2, p3);
                    }
                    //�߸� ���� ���
                    else {
                        missRinging(p2, user, p1, p3);
                        printPlayersCardInfo(user, p1, p2, p3);
                    }
                }
                else {
                    gotoxy(15, 9);
                    cout << "                                                          ";
                    gotoxy(15, 9);
                    cout << "[ 3�� player : ���� ġ�� �ʾҽ��ϴ�. ���� ������ �Ѿ�ϴ�. ]";
                }
            }
        }
        else if (turn % 4 == 3) {
            printPlayersCardInfo(user, p1, p2, p3);
            if (!p3.getAvailable()) {
                continue;
            }
            else {
                gotoxy(26, 7);
                cout << "                                         ";
                gotoxy(26, 7);
                cout << "[ " << p3.getPlayerNum() << "�� ���� ]";
                if (p3.open() == -1) continue;
                gotoxy(40, 14);
                frontCardPrint(user.getFrontTopCard(),p3);
                //printTableInfo(user, p1, p2, p3);
                //printBackInfo(user, p1, p2, p3);
                //cout << "���̺� ī�� ���� : " << p3.getFrontCount() << endl;
                //cout << "����� ī�� ���� : " << p3.getBackCount() << endl;
                input = GameKey();
                if (input == 1) {
                    gotoxy(24, 9);
                    cout << "                                                          ";
                    gotoxy(24, 9);
                    cout << "[ 4�� player : ���� �ƽ��ϴ� ]";
                    //���� 5���϶� ���� ���
                    if (checkFiveCard(p3, p1, p2, user)) {
                        //���̺� ���� ī�� ��� ������
                        getAllFrontCard(p3, p1, p2, user);
                        printPlayersCardInfo(user, p1, p2, p3);
                    }
                    //�߸� ���� ���
                    else {
                        //�� �ο����� ī�� �ϳ��� ��, ī��� ������ �� Ż��
                        missRinging(p3, p1, p2, user);
                        printPlayersCardInfo(user, p1, p2, p3);
                    }
                }
                else {
                    gotoxy(15, 9);
                    cout << "                                                          ";
                    gotoxy(15, 9);
                    cout << "[ 4�� player : ���� ġ�� �ʾҽ��ϴ�. ���� ������ �Ѿ�ϴ�. ]";
                }
            }
        }
        //  cout << "==========================================================" << endl;
        //���� ������ (��������)
        if (GetKeyValue() == 27) break;    
    }


    while (true) {
        if (GetKeyValue() == 27)
            break;
    }
}
//���� ����
void ShowInfo()
{
    DrawInfoScreen();
    while (true) {
        if (GetKeyValue() == 27)
            break;
    }
}
//����
int main(void)
{
    SetConsoleView(); //�ּܼ���
    int menuValue = -1;
    while (true)
    {
        menuValue = ReadyGame();    //��Ʈ��, Ű �Է�
        if (menuValue == 1) {       //rule
            ShowInfo();
        }
        else if (menuValue == 2) {    //start
            StartGame();
        }
        else {
            exit(1);
        }
        system("cls");
    }
    return 0;
}