#include<iostream>
#include<string>
#include<ctime>
#include<cstdlib>
#include<string>
#include<conio.h>
#include<Windows.h>
#include<time.h>	
#include<list>
#include <stack>
using namespace std;
#define RED         (FOREGROUND_RED | FOREGROUND_INTENSITY)
#define BLUE        (FOREGROUND_BLUE | FOREGROUND_INTENSITY)
#define PINK        (RED | BLUE)
#define GREEN       (FOREGROUND_GREEN | FOREGROUND_INTENSITY)
#define YELLOW      (RED | GREEN)
#define WHITE       (RED | GREEN | BLUE)
#define CARDCOUNT 28*4


class Card {
    int type;
    int num;
public:
    Card() {
        this->type = 'e';
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
};
class Player {
    //�� ī��
    stack<Card> front;
    //���� ���� ī��
    stack<Card> back;
    //�÷��̾� ��ȣ
    int playerNum;
public:
    int getPlayerNum() {
        return playerNum;
    }
    //�ʹ� ī�� �� ����
    Player(int num) {
        playerNum = num;
    }
    //������ ī�彺���� ���� �� ī�� ��ȯ
    Card getFrontTopCard() {
        if (front.empty()) return Card();
        return front.top();
    }
    //������ ���� ī�彺���� ���� �� ī�� ��ȯ
    Card getBackTopCard() {
        if (back.empty()) return Card();
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
        front.push(card);
    }
    void pushFront(const Card& card) {
        back.push(card);
    }
    //ī�� ������
    void popBack() {
        front.pop();
    }
    void popFront() {
        back.pop();
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
void frontCardPrint(Card card) {
    //ī�� Ÿ��
    int type = card.getType();
    char fruit = 'e';
    switch (type) {
    case 1: fruit = '!'; break;
    case 2: fruit = '@'; break;
    case 3: fruit = '#'; break;
    case 4: fruit = '$'; break;
    }

    switch (card.getNumber()) {
    case 1:
        cout << "                                               "
            << "��������������������������������" << endl;
        cout << "                                               "
            << "��           ��" << endl;
        cout << "                                               "
            << "��           ��" << endl;
        cout << "                                               "
            << "��           ��" << endl;
        cout << "                                               "
            << "��     " << fruit << "     ��" << endl;
        cout << "                                               "
            << "��           ��" << endl;
        cout << "                                               "
            << "��           ��" << endl;
        cout << "                                               "
            << "��           ��" << endl;
        cout << "                                               "
            << "��������������������������������" << endl;
        break;
    case 2:
        cout << "                                               "
            << "��������������������������������" << endl;
        cout << "                                               "
            << "��           ��" << endl;
        cout << "                                               "
            << "��           ��" << endl;
        cout << "                                               "
            << "��     " << fruit << "     ��" << endl;
        cout << "                                               "
            << "��           ��" << endl;
        cout << "                                               "
            << "��     " << fruit << "     ��" << endl;
        cout << "                                               "
            << "��           ��" << endl;
        cout << "                                               "
            << "��           ��" << endl;
        cout << "                                               "
            << "��������������������������������" << endl;
        break;
    case 3:
        cout << "                                               "
            << "��������������������������������" << endl;
        cout << "                                               "
            << "��           ��" << endl;
        cout << "                                               "
            << "��           ��" << endl;
        cout << "                                               "
            << "��     " << fruit << "     ��" << endl;
        cout << "                                               "
            << "��           ��" << endl;
        cout << "                                               "
            << "��   " << fruit << "   " << fruit << "   ��" << endl;
        cout << "                                               "
            << "��           ��" << endl;
        cout << "                                               "
            << "��           ��" << endl;
        cout << "                                               "
            << "��������������������������������" << endl;
        break;
    case 4:
        cout << "                                               "
            << "��������������������������������" << endl;
        cout << "                                               "
            << "��           ��" << endl;
        cout << "                                               "
            << "��   " << fruit << "   " << fruit << "   ��" << endl;
        cout << "                                               "
            << "��           ��" << endl;
        cout << "                                               "
            << "��           ��" << endl;
        cout << "                                               "
            << "��           ��" << endl;
        cout << "                                               "
            << "��   " << fruit << "   " << fruit << "   ��" << endl;
        cout << "                                               "
            << "��           ��" << endl;
        cout << "                                               "
            << "��������������������������������" << endl;
        break;
    case 5:
        cout << "                                               "
            << "��������������������������������" << endl;
        cout << "                                               "
            << "��           ��" << endl;
        cout << "                                               "
            << "��   " << fruit << "   " << fruit << "   ��" << endl;
        cout << "                                               "
            << "��           ��" << endl;
        cout << "                                               "
            << "��     " << fruit << "     ��" << endl;
        cout << "                                               "
            << "��           ��" << endl;
        cout << "                                               "
            << "��   " << fruit << "   " << fruit << "   ��" << endl;
        cout << "                                               "
            << "��           ��" << endl;
        cout << "                                               "
            << "��������������������������������" << endl;
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
    gotoxy(30, 20);
    cout << "��";
    gotoxy(29, 21);
    cout << "/��";
    PrintString(hStdOut, RED);
    gotoxy(28, 22);
    cout << "�ɢɢ�";
    gotoxy(27, 23);
    cout << "�ɢɢɢ�";
    gotoxy(27, 24);
    cout << "�ɢɢɢɢɢɢ�";
    gotoxy(28, 25);
    cout << "�ɢɢɢ�";


    PrintString(hStdOut, WHITE);
    gotoxy(24, 28);
    cout << "�� Game Rule for 'r'";
    gotoxy(24, 30);
    cout << "�� Game Start for 's'";
    gotoxy(24, 32);
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
    cout << "���� ī�� �� : " << " ��";
    gotoxy(0, 9);
    cout << "�ǿ� ���� ī�� �� : " << " ��";

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
    cout << "���� ī�� �� : " << " ��";
    gotoxy(48, 9);
    cout << "�ǿ� ���� ī�� �� : " << " ��";

    //�÷��̾� 3 (���� �ϴ�)
    gotoxy(0, 30);
    cout << "���� ī�� �� : " << " ��";
    gotoxy(0, 31);
    cout << "�ǿ� ���� ī�� �� : " << " ��";
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
    cout << "���� ī�� �� : " << " ��";
    gotoxy(48, 31);
    cout << "�ǿ� ���� ī�� �� : " << " ��";
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


//[��������] ī��й�
void setInitCard(Player& p1, Player& p2, Player& p3, Player& p4) {
    srand((unsigned int)time(NULL));
    
 
    
    
    //�� �÷��̾�� ī�� �й�
    for (int i = 0; i < CARDCOUNT / 4; i++) {
        p1.pushBack(cards[i]);
    }
    for (int i = CARDCOUNT / 4; i < CARDCOUNT / 2; i++) {
        p2.pushBack(cards[i]);
    }
    for (int i = CARDCOUNT / 2; i < CARDCOUNT * (3 / 4); i++) {
        p3.pushBack(cards[i]);
    }
    for (int i = CARDCOUNT * (3 / 4); i < CARDCOUNT; i++) {
        p4.pushBack(cards[i]);
    }
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
        int key = GetKeyValue();
        if (key == '\n') {         //��ġ�� = 1 (enter)
            return 1;
        }
        else if (key == ' ') {    //ī�� ���� = 2 (space)
            return 2;
        }
        else if (key == 'e' || key == 'E') {    //exit = 0 (esc)
            break;
        }
    }
    return 0;
}
//���� ����
void StartGame()
{
    DrawStartGame();
    int keyValue = GameKey();

    //�� ����� ��ü ����
    Player user(1);
    Player com1(2), com2(3), com3(4);
    //�� ����� ī�� �й�
    setInitCard(user, com1, com2, com3);
    int turn = 1;


    /* while (true) {






         turn++;
     }*/

     //switch (keyValue) {
     //    //��ġ��
     //case 1:
     //    break;
     //    //ī�� ����
     //case 2:
     //    break;
     //    //���� ����
     //case 0:
     //    return;
     //default:
     //    break;
     //}


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