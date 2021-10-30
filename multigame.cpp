#define _CRT_SECURE_NO_WARNINGS
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
#include<fstream>
#include <mmsystem.h>
#pragma comment(lib,"winmm.lib")
using namespace std;
#define RED         (FOREGROUND_RED | FOREGROUND_INTENSITY)
#define BLUE        (FOREGROUND_BLUE | FOREGROUND_INTENSITY)
#define PINK        (RED | BLUE)
#define GREEN       (FOREGROUND_GREEN | FOREGROUND_INTENSITY)
#define YELLOW      (RED | GREEN)
#define PURPLE      (RED | BLUE | BLUE)
#define WHITE       (RED | GREEN | BLUE)
//ī�� ��ǥ
#define CARDCOUNT 20*4
#define CARD1X 5
#define CARD2X 15
#define CARD3X 25
#define CARD4X 35
#define CARDY 12
//���� ��ǥ
#define longInfoX 8
#define longInfoY 7

//�ܼ� ����
void SetConsoleView()
{
    system("mode con cols=135 lines=45 | title Halli Galli");   //ȭ��ũ��,�����̸�
}
//Ŀ���̵� �Լ�
void gotoxy(int x, int y)
{
    COORD Pos;
    Pos.X = 2 * x;
    Pos.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}
void CursorView()
{
    CONSOLE_CURSOR_INFO cursorInfo = { 0, };
    cursorInfo.dwSize = 1;
    cursorInfo.bVisible = FALSE;
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
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
    //����
    int score;
public:
    //���� ȹ��
    void plusScore() {
        score += 20;
    }
    //���� ����
    void minusScore() {
        score -= 20;
    }
    //���� ��ȯ
    int getScore() {
        return score;
    }
    //�Ҹ���
    ~Player() {};
    //Ż��ó��
    void setNoneAvailable() {
        available = false;
        int x = 57, y = 4;
        switch (playerNum)
        {
        case 1: y = 4; break;
        case 2: y = 14; break;
        case 3: y = 24; break;
        case 4: y = 34; break;
        }
        gotoxy(x, y);
        cout << "[Ż��] Player " << playerNum;
    }
    //�÷��� ���� ����
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
        score = 0;
    }
    //������ ī�彺���� ���� �� ī�� ��ȯ
    Card getFrontTopCard() {
        if (front.empty()) return Card();
        return front.top();
    }
    //������ ���� ī�彺���� ���� �� ī�� ��ȯ
    Card getBackTopCard() {
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


//ī��
Card cards[CARDCOUNT] = {
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
void SetConsoleView();
//Ŀ���̵� �Լ�
void gotoxy(int x, int y);
//keyboard �Է°� ��ȯ��
int GetKeyValue();
//��������
void PrintString(HANDLE hStdOut, WORD Attribute);
//[ȭ�� DRAW]
//��Ʈ�� ȭ�� draw
void DrawIntro();
//���� ȭ�� draw
void DrawStartGame();
//���� ȭ�� draw
void DrawInfoScreen();
//���� ȭ�� draw
void DrawRankingScreen();


//[����� ���� ���� �޼���]
void makeFaceSmile(Player& player);
void makeFaceAngry(Player& player);
void makeAllFaceDefault(Player& player);

//[ī�� ��� �޼���]
//�� ī�� ���
void emptyCardPrint(Player& player);
//��ü �� ī�� ���
void emptyCardPrint(Player& one, Player& two, Player& three, Player& four);
//���̺�� �� ī�� ���
void frontCardPrint(Card& card, Player& player);

//[ī�� ���� �޼���]
//����ڿ��� ī�� ���� �й�
int* makeRandArr(int size);
void setInitCard(Player& p1, Player& p2, Player& p3, Player& p4);
//[Ring] ��� front ������ back���� �̵�
void getAllFrontCard(Player& winner, Player& looser1, Player& looser2, Player& looser3);
//[MissRing] �� player���� ���徿 back���� �̵�
void missRinging(Player& p1, Player& p2, Player& p3, Player& p4);

//[ī�� �Ǻ� �޼���]
//���� �� 5�� �Ǻ�
bool checkFiveCard(Player& user, Player& p1, Player& p2, Player& p3);

//[ī�� ���� ��� �޼���]
//���� ī�� && ���̺� ī�� ���
void printPlayersCardInfo(Player& p1, Player& p2, Player& p3, Player& p4);

//[�޴� ����]
int ReadyGame();
//[���� ���� Ű]
int GameKey();
//[���� ����]
int main();
void StartGameAlone();
void StartGameMulti();
//[���� ����]
void ShowInfo();

//----------------------------[ī�� ��� �޼���]----------------------------
//�� ī��
void emptyCardPrint(Player& player) {
    //ī�� ��� ��ġ
    int x;
    int y = CARDY;
    switch (player.getPlayerNum()) {
    case 1: x = CARD1X; break;
    case 2: x = CARD2X; break;
    case 3: x = CARD3X; break;
    case 4: x = CARD4X; break;
    }
    gotoxy(x, y);
    cout << "��������������������������������";
    for (int i = 0; i < 10; ++i) {
        gotoxy(x, y + i);
        cout << "��           ��";
    }
    gotoxy(x, y + 7);
    cout << "��������������������������������" << endl;
}
//��ü �� ī�� ���
void emptyCardPrint(Player& one, Player& two, Player& three, Player& four) {
    //ī�� ��� ��ġ
    int x;
    int y = CARDY;
    //1
    x = CARD1X;
    gotoxy(x, y);
    cout << "��������������������������������";
    for (int i = 0; i < 11; ++i) {
        gotoxy(x, y + i + 1);
        cout << "��              ��";
    }
    gotoxy(x, y + 12);
    cout << "��������������������������������" << endl;
    //2
    x = CARD2X;
    gotoxy(x, y);
    cout << "��������������������������������";
    for (int i = 0; i < 11; ++i) {
        gotoxy(x, y + i + 1);
        cout << "��              ��";
    }
    gotoxy(x, y + 12);
    cout << "��������������������������������" << endl;
    //3
    x = CARD3X;
    gotoxy(x, y);
    cout << "��������������������������������";
    for (int i = 0; i < 11; ++i) {
        gotoxy(x, y + i + 1);
        cout << "��              ��";
    }
    gotoxy(x, y + 12);
    cout << "��������������������������������" << endl;
    //4
    x = CARD4X;
    gotoxy(x, y);
    cout << "��������������������������������";
    for (int i = 0; i < 11; ++i) {
        gotoxy(x, y + i + 1);
        cout << "��              ��";
    }
    gotoxy(x, y + 12);
    cout << "��������������������������������" << endl;
}
//�տ� �ִ� ī�� ��
void frontCardPrint(Card card, Player player) {
    HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
    //ī�� Ÿ��
    int type = card.getType();
    char fruit = 'e';
    int Color = RED;
    switch (type) {
    case 1: fruit = '@';
        //PrintString(hStdOut, RED);
        Color = RED;
        break; //���
    case 2: fruit = '@';
        //PrintString(hStdOut, YELLOW);
        Color = YELLOW;
        break; //�ٳ���
    case 3: fruit = '@';
        //PrintString(hStdOut, GREEN);
        Color = GREEN;
        break; //����
    case 4: fruit = '@';
        //PrintString(hStdOut, RED);
        Color = PURPLE;
        break; //����
    }
    //ī�� ��� ��ġ
    int x;
    int y = CARDY;
    switch (player.getPlayerNum()) {
    case 1: x = CARD1X; break;
    case 2: x = CARD2X; break;
    case 3: x = CARD3X; break;
    case 4: x = CARD4X; break;
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
        cout << "��              ��" << endl;
        gotoxy(x, y + 6);
        PrintString(hStdOut, WHITE);
        cout << "��       ";
        PrintString(hStdOut, Color);
        cout << fruit;
        PrintString(hStdOut, WHITE);
        cout << "      ��" << endl;
        gotoxy(x, y + 7);
        cout << "��              ��" << endl;
        gotoxy(x, y + 8);
        cout << "��              ��" << endl;
        gotoxy(x, y + 9);
        cout << "��              ��" << endl;
        gotoxy(x, y + 10);
        cout << "��              ��" << endl;
        gotoxy(x, y + 11);
        cout << "��              ��" << endl;
        gotoxy(x, y + 12);
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
        PrintString(hStdOut, WHITE);
        cout << "��       ";
        PrintString(hStdOut, Color);
        cout << fruit;
        PrintString(hStdOut, WHITE);
        cout << "      ��" << endl;
        gotoxy(x, y + 4);
        cout << "��              ��" << endl;
        gotoxy(x, y + 5);
        cout << "��              ��" << endl;
        gotoxy(x, y + 6);
        cout << "��              ��" << endl;
        gotoxy(x, y + 7);
        cout << "��              ��" << endl;
        gotoxy(x, y + 8);
        cout << "��              ��" << endl;
        gotoxy(x, y + 9);
        PrintString(hStdOut, WHITE);
        cout << "��       ";
        PrintString(hStdOut, Color);
        cout << fruit;
        PrintString(hStdOut, WHITE);
        cout << "      ��" << endl;
        gotoxy(x, y + 10);
        cout << "��              ��" << endl;
        gotoxy(x, y + 11);
        cout << "��              ��" << endl;
        gotoxy(x, y + 12);
        cout << "��������������������������������" << endl;
        break;
    case 3:
        gotoxy(x, y);
        cout << "��������������������������������" << endl;
        gotoxy(x, y + 1);
        cout << "��              ��" << endl;
        gotoxy(x, y + 2);
        cout << "��              ��" << endl;
        gotoxy(x, y + 3);
        PrintString(hStdOut, WHITE);
        cout << "��    ";
        PrintString(hStdOut, Color);
        cout << fruit;
        PrintString(hStdOut, WHITE);
        cout << "         ��" << endl;
        gotoxy(x, y + 4);
        cout << "��              ��" << endl;
        gotoxy(x, y + 5);
        cout << "��              ��" << endl;
        gotoxy(x, y + 6);
        PrintString(hStdOut, WHITE);
        cout << "��       ";
        PrintString(hStdOut, Color);
        cout << fruit;
        PrintString(hStdOut, WHITE);
        cout << "      ��" << endl;
        gotoxy(x, y + 7);
        cout << "��              ��" << endl;
        gotoxy(x, y + 8);
        cout << "��              ��" << endl;
        gotoxy(x, y + 9);
        PrintString(hStdOut, WHITE);
        cout << "��          ";
        PrintString(hStdOut, Color);
        cout << fruit;
        PrintString(hStdOut, WHITE);
        cout << "   ��" << endl;
        gotoxy(x, y + 10);
        cout << "��              ��" << endl;
        gotoxy(x, y + 11);
        cout << "��              ��" << endl;
        gotoxy(x, y + 12);
        cout << "��������������������������������" << endl;
        break;
    case 4:
        gotoxy(x, y);
        cout << "��������������������������������" << endl;
        gotoxy(x, y + 1);
        cout << "��              ��" << endl;
        gotoxy(x, y + 2);
        cout << "��              ��" << endl;
        gotoxy(x, y + 3);
        PrintString(hStdOut, WHITE);
        cout << "��    ";
        PrintString(hStdOut, Color);
        cout << fruit << "     " << fruit;
        PrintString(hStdOut, WHITE);
        cout << "   ��" << endl;
        gotoxy(x, y + 4);
        cout << "��              ��" << endl;
        gotoxy(x, y + 5);
        cout << "��              ��" << endl;
        gotoxy(x, y + 6);
        cout << "��              ��" << endl;
        gotoxy(x, y + 7);
        cout << "��              ��" << endl;
        gotoxy(x, y + 8);
        cout << "��              ��" << endl;
        gotoxy(x, y + 9);
        PrintString(hStdOut, WHITE);
        cout << "��    ";
        PrintString(hStdOut, Color);
        cout << fruit << "     " << fruit;
        PrintString(hStdOut, WHITE);
        cout << "   ��" << endl;
        gotoxy(x, y + 10);
        cout << "��              ��" << endl;
        gotoxy(x, y + 11);
        cout << "��              ��" << endl;
        gotoxy(x, y + 12);
        cout << "��������������������������������" << endl;
        break;
    case 5:
        gotoxy(x, y);
        cout << "��������������������������������" << endl;
        gotoxy(x, y + 1);
        cout << "��              ��" << endl;
        gotoxy(x, y + 2);
        cout << "��              ��" << endl;
        gotoxy(x, y + 3);
        PrintString(hStdOut, WHITE);
        cout << "��    ";
        PrintString(hStdOut, Color);
        cout << fruit << "     " << fruit;
        PrintString(hStdOut, WHITE);
        cout << "   ��" << endl;
        gotoxy(x, y + 4);
        cout << "��              ��" << endl;
        gotoxy(x, y + 5);
        cout << "��              ��" << endl;
        gotoxy(x, y + 6);
        PrintString(hStdOut, WHITE);
        cout << "��       ";
        PrintString(hStdOut, Color);
        cout << fruit;
        PrintString(hStdOut, WHITE);
        cout << "      ��" << endl;
        gotoxy(x, y + 7);
        cout << "��              ��" << endl;
        gotoxy(x, y + 8);
        cout << "��              ��" << endl;
        gotoxy(x, y + 9);
        PrintString(hStdOut, WHITE);
        cout << "��    ";
        PrintString(hStdOut, Color);
        cout << fruit << "     " << fruit;
        PrintString(hStdOut, WHITE);
        cout << "   ��" << endl;
        gotoxy(x, y + 10);
        cout << "��              ��" << endl;
        gotoxy(x, y + 11);
        cout << "��              ��" << endl;
        gotoxy(x, y + 12);
        cout << "��������������������������������" << endl;
        break;
    }
}


//ùȭ�� draw
void DrawIntro()
{
    HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
    int x = 9;
    int y = 8;
    system("cls");
    PrintString(hStdOut, WHITE);
    gotoxy(x, y);
    cout << "##   ##    ##     ####     ####      ####               ####     ##     ####     ####      ####";
    gotoxy(x, y + 1);
    cout << "##   ##   ####     ##       ##        ##               ##  ##   ####     ##       ##        ##";
    gotoxy(x, y + 2);
    cout << "##   ##  ##  ##    ##       ##        ##              ##       ##  ##    ##       ##        ##";
    gotoxy(x, y + 3);
    cout << "#######  ##  ##    ##       ##        ##              ##       ##  ##    ##       ##        ##";
    gotoxy(x, y + 4);
    cout << "##   ##  ######    ##   #   ##   #    ##              ##  ###  ######    ##   #   ##   #    ##";
    gotoxy(x, y + 5);
    cout << "##   ##  ##  ##    ##  ##   ##  ##    ##               ##  ##  ##  ##    ##  ##   ##  ##    ##";
    gotoxy(x, y + 6);
    cout << "##   ##  ##  ##   #######  #######   ####               #####  ##  ##   #######  #######   ####";


    PrintString(hStdOut, WHITE);
    gotoxy(29, 30);
    cout << ">>  Game Rule";
    gotoxy(29, 32);
    cout << "    Game Start";
    gotoxy(29, 34);
    cout << "    Exit";
}
//����ȭ�� draw
void DrawStartGame()
{
    //120 41
    system("cls");

    //ī�� 1
    gotoxy(CARD1X, CARDY);
    cout << "��������������������������������";
    for (int i = CARDY + 1; i < CARDY + 12; i++) {
        gotoxy(CARD1X, i);
        cout << "��              ��";
    }
    gotoxy(CARD1X, CARDY + 12);
    cout << "��������������������������������";

    //ī�� 2
    gotoxy(CARD2X, CARDY);
    cout << "��������������������������������";
    for (int i = CARDY + 1; i < CARDY + 12; i++) {
        gotoxy(CARD2X, i);
        cout << "��              ��";
    }
    gotoxy(CARD2X, CARDY + 12);
    cout << "��������������������������������";

    //ī�� 3
    gotoxy(CARD3X, CARDY);
    cout << "��������������������������������";
    for (int i = CARDY + 1; i < CARDY + 12; i++) {
        gotoxy(CARD3X, i);
        cout << "��              ��";
    }
    gotoxy(CARD3X, CARDY + 12);
    cout << "��������������������������������";

    //ī�� 4
    gotoxy(CARD4X, CARDY);
    cout << "��������������������������������";
    for (int i = CARDY + 1; i < CARDY + 12; i++) {
        gotoxy(CARD4X, i);
        cout << "��              ��";
    }
    gotoxy(CARD4X, CARDY + 12);
    cout << "��������������������������������";

    for (int i = 0; i < 45; i++) {
        gotoxy(48, i);
        cout << "��";
    }

    //����� ���� ����
    gotoxy(57, 4);
    cout << "Player 1";
    gotoxy(50, 3);
    cout << "����������������������";
    gotoxy(50, 4);
    cout << "��  ��  �� ��";
    gotoxy(50, 5);
    cout << "��   =  =  ��";
    gotoxy(50, 6);
    cout << "��         ��";
    gotoxy(50, 7);
    cout << "��    ��   ��";
    gotoxy(50, 8);
    cout << "����������������������";


    gotoxy(57, 14);
    cout << "Player 2";
    gotoxy(50, 13);
    cout << "����������������������";
    gotoxy(50, 14);
    cout << "��  ��  �� ��";
    gotoxy(50, 15);
    cout << "��  ��  �� ��";
    gotoxy(50, 16);
    cout << "��         ��";
    gotoxy(50, 17);
    cout << "��    ��   ��";
    gotoxy(50, 18);
    cout << "����������������������";

    gotoxy(57, 24);
    cout << "Player 3";
    gotoxy(50, 23);
    cout << "����������������������";
    gotoxy(50, 24);
    cout << "��  ��  �� ��";
    gotoxy(50, 25);
    cout << "��  ��  �� ��";
    gotoxy(50, 26);
    cout << "��         ��";
    gotoxy(50, 27);
    cout << "��    ��   ��";
    gotoxy(50, 28);
    cout << "����������������������";

    gotoxy(57, 34);
    cout << "Player 4";
    gotoxy(50, 33);
    cout << "����������������������";
    gotoxy(50, 34);
    cout << "��  ��  �� ��";
    gotoxy(50, 35);
    cout << "��  ��  �� ��";
    gotoxy(50, 36);
    cout << "��         ��";
    gotoxy(50, 37);
    cout << "��    ��   ��";
    gotoxy(50, 38);
    cout << "����������������������";

}
//����ȭ�� draw
void DrawRankingScreen(int gameType) {
    //135 45
    HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
    system("cls");

    //����ü
    struct players {
        char name[20];
        int score;
        int rank;
    } pl[10];
    FILE* fp1;

    //Multi
    if (gameType == 0) {
        //���Ͽ��� �о��
        while (true) {
            fopen_s(&fp1, "database.txt", "r");
            if (fp1 == NULL) {
                gotoxy(0, 0);
                cout << "������ �������� �ʽ��ϴ�." << endl;
            }
            else break;
        }
    }
    //Solo
    else {
        //���Ͽ��� �о��
        while (true) {
            fopen_s(&fp1, "database_solo.txt", "r");
            if (fp1 == NULL) {
                gotoxy(0, 0);
                cout << "������ �������� �ʽ��ϴ�." << endl;
            }
            else break;
        }
    }

    for (int i = 0; i < 10; i++) {
        fscanf_s(fp1, "%s", pl[i].name, 20);
        fscanf_s(fp1, "%d", &(pl[i].score));
    }
    fclose(fp1);


    //���� ����
    for (int i = 0; i < 10; i++) {
        pl[i].rank = 1;
        for (int j = 0; j < 10; j++) {
            if (pl[i].score < pl[j].score) pl[i].rank++;
        }
    }

    //fopen_s(&fp2, "database.txt", "w");
    int x = 14;
    int y = 8;
    gotoxy(x, y);
    cout << "������������������ [  RANKING  ]������������������ ";
    for (int i = 1; i <= 10; i++) {
        for (int j = 0; j < 10; j++) {
            if (pl[j].rank == i) {
                gotoxy(x, ++y);
                cout << "��                              ��";
                gotoxy(x, ++y);
                if (pl[j].score == 0) {
                    PrintString(hStdOut, WHITE);
                    printf("��               -              ��");
                }
                else {
                    switch (i) {
                    case 1:
                        PrintString(hStdOut, WHITE);
                        cout << "��  ";
                        PrintString(hStdOut, YELLOW);
                        printf("%2d     %10s    %4d", pl[j].rank, pl[j].name, pl[j].score);
                        PrintString(hStdOut, WHITE);
                        cout << "   ��";
                        break;
                    case 2:
                        PrintString(hStdOut, WHITE);
                        cout << "��  ";
                        PrintString(hStdOut, 7);
                        printf("%2d     %10s    %4d", pl[j].rank, pl[j].name, pl[j].score);
                        PrintString(hStdOut, WHITE);
                        cout << "   ��";
                        break;
                    case 3:
                        PrintString(hStdOut, WHITE);
                        cout << "��  ";
                        PrintString(hStdOut, 6);
                        printf("%2d     %10s    %4d", pl[j].rank, pl[j].name, pl[j].score);
                        PrintString(hStdOut, WHITE);
                        cout << "   ��";
                        break;
                    default:
                        PrintString(hStdOut, WHITE);
                        printf("��  %2d     %10s    %4d   ��", pl[j].rank, pl[j].name, pl[j].score);
                    }
                }

            }
        }
    }
    gotoxy(x, y + 1);
    cout << "��                              ��";
    gotoxy(x, y + 2);
    cout << "���������������������������������������������������������������� ";


    //����� score ���
    x = 32;
    y = 8;
    gotoxy(x, y);
    cout << "���������������������������� [  INFO  ]�������������������������� ";
    gotoxy(x, y + 1);
    cout << "��                                    ��";
    gotoxy(x, y + 2);
    cout << "��                                    ��";
    gotoxy(x, y + 3);
    cout << "��                                    ��";
    gotoxy(x, y + 4);
    cout << "��                                    ��";
    gotoxy(x, y + 5);
    cout << "��                                    ��";
    gotoxy(x, y + 6);
    cout << "��                                    ��";
    gotoxy(x, y + 7);
    cout << "��                                    ��";
    gotoxy(x, y + 8);
    cout << "��                                    ��";
    gotoxy(x, y + 9);
    cout << "��                                    ��";
    gotoxy(x, y + 10);
    cout << "���������������������������������������������������������������������������� ";

    gotoxy(x, y + 12);
    cout << "������������������ [  DEVELOPE  INFO  ]���������������� ";
    gotoxy(x, y + 13);
    cout << "��                                    ��";
    gotoxy(x, y + 14);
    cout << "��    latest change    2021.10.30     ��";
    gotoxy(x, y + 15);
    cout << "��                                    ��";
    gotoxy(x, y + 16);
    cout << "��    name                 ���ϴ�     ��";
    gotoxy(x, y + 17);
    cout << "��                                    ��";
    gotoxy(x, y + 18);
    cout << "��    sch    �̸������������а���б� ��";
    gotoxy(x, y + 19);
    cout << "��                                    ��";
    gotoxy(x, y + 20);
    cout << "��    eml    KimCloud52@gmail.com     ��";
    gotoxy(x, y + 21);
    cout << "��                                    ��";
    gotoxy(x, y + 22);
    cout << "���������������������������������������������������������������������������� ";

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
    cout << "��  �� �� 4���� �÷��̾ ������, �� �÷��̾�� 20���� ī�尡 �־����ϴ�.                          ��";
    gotoxy(3, 27);
    cout << "��  �� 1�� �Ǵ� 4���� �÷����� �� �ֽ��ϴ�. �⺻ ������ ���۹��� ���� �˷��帳�ϴ�.                   ��";
    gotoxy(3, 29);
    cout << "��  �� ���̺� ���� ī���� ���� ���� 5���� �Ǹ� '���� Ű'�� ���� Ĩ�ϴ�.                             ��";
    gotoxy(3, 31);
    cout << "��  �� ���� ���� ���� ģ ����� ���� ī�带 ��� �������ϴ�.                                          ��";
    gotoxy(3, 33);
    cout << "��  �� ���� 5���� �ƴ� ���¿��� ���� ġ��, ������ �÷��̾�� ī�带 1�徿 �������ݴϴ�.             ��";
    gotoxy(3, 35);
    cout << "��  �� �߰� ����                                                                                      ��";
    gotoxy(3, 37);
    cout << "��  �� ī�带 ��� ����� �÷��̾�� ��� Ż��ó���˴ϴ�.                   �� ������ : esc           ��";
    gotoxy(3, 39);
    cout << "�����������������������������������������������������";

}



//[����� ǥ�� ���� �޼���]
void makeFaceSmile(Player& player) {
    int x = 50, y;
    switch (player.getPlayerNum()) {
    case 1: y = 5; break;
    case 2: y = 15; break;
    case 3: y = 25; break;
    case 4: y = 35; break;
    }
    gotoxy(x, y);
    cout << "��   >  <  ��";
}
void makeFaceAngry(Player& player) {
    int x = 50, y;
    switch (player.getPlayerNum()) {
    case 1: y = 5; break;
    case 2: y = 15; break;
    case 3: y = 25; break;
    case 4: y = 35; break;
    }
    gotoxy(x, y);
    cout << "��  ��  �� ��";
}
void makeAllFaceDefault(Player& player) {
    int x = 50, y;
    switch (player.getPlayerNum()) {
    case 1:
        gotoxy(x, 5);
        cout << "��   =  =  ��";
        break;
    case 2:
        gotoxy(x, 15);
        cout << "��  ��  �� ��";
        break;
    case 3:
        gotoxy(x, 25);
        cout << "��  ��  �� ��";
        break;
    case 4:
        gotoxy(x, 35);
        cout << "��  ��  �� ��";
        break;
    }
}


//[ī������] ����ڿ��� ī�� �й�
int* makeRandArr(int size) {
    int* arr = new int[size] { 0, };
    int* chk = new int[size] { 0, };
    int cnt = 0;

    srand((unsigned int)time(NULL));

    while (cnt < size) {
        int r = rand() % size;      // 0 ~ size ���� ����
        if (!chk[r]) {              // �̹� ���� ���� ���� ���ڸ�
            ++chk[r], arr[cnt] = r; // üũ �� shuffle �迭�� �߰�
            ++cnt;
        }
    }

    delete[] chk;
    return arr;
}
void setInitCard(Player& p1, Player& p2, Player& p3, Player& p4) {

    int* shuffle = makeRandArr(CARDCOUNT);

    for (int i = 0; i < CARDCOUNT / 4; ++i)
        p1.pushBack(cards[shuffle[i]]);

    for (int i = CARDCOUNT / 4; i < CARDCOUNT / 2; ++i)
        p2.pushBack(cards[shuffle[i]]);

    //CARDCOUNT * (3/4)
    for (int i = CARDCOUNT / 2; i < 60; ++i)
        p3.pushBack(cards[shuffle[i]]);

    for (int i = 60; i < CARDCOUNT; ++i)
        p4.pushBack(cards[shuffle[i]]);

    delete[] shuffle;
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
    //���̺� ī�� �ʱ�ȭ
    emptyCardPrint(winner, looser1, looser2, looser3);
    //���� ���
    gotoxy(longInfoX + 4, longInfoY);
    cout << winner.getPlayerNum() << "�� �÷��̾ ���� �ƽ��ϴ�. ���̺��� ��� ī�� ȹ��!";
    Sleep(2000);
    gotoxy(longInfoX, longInfoY);
    cout << "                                                                          ";
}
//[�Ǻ�] �� �߸����� ��� - �� player���� ī�� ���徿 back�� �ѱ�
void missRinging(Player& looser, Player& winner1, Player& winner2, Player& winner3) {
    //�÷��� ������ �ο� �� ����
    int cnt = 0;
    if (looser.getAvailable()) cnt++;
    if (winner1.getAvailable()) cnt++;
    if (winner2.getAvailable()) cnt++;
    if (winner3.getAvailable()) cnt++;
    //back ī�尡 ���� ���,������ ��� Ż��
    if (looser.backIsEmpty() || looser.getBackCount() < cnt - 1) {
        looser.setNoneAvailable();
        //���� ���
        gotoxy(longInfoX + 6, longInfoY);
        cout << looser.getPlayerNum() << "�� �÷��̾�� ī�尡 �����Ͽ� Ż���Ǿ����ϴ�.";
        Sleep(2000);
        gotoxy(longInfoX + 6, longInfoY);
        cout << "                                                      ";
        return;
    }
    //�����÷��� ������ �ο� ī�� �����ֱ�
    if (winner1.getAvailable()) {
        winner1.pushBack(looser.getBackTopCard());
        looser.popBack();
    }
    if (winner2.getAvailable()) {
        winner2.pushBack(looser.getBackTopCard());
        looser.popBack();
    }
    if (winner3.getAvailable()) {
        winner3.pushBack(looser.getBackTopCard());
        looser.popBack();
    }
    //���� ���
    gotoxy(longInfoX, longInfoY);
    cout << looser.getPlayerNum() << "�� �÷��̾ ���� �߸��ƽ��ϴ�. �� �ο����� ī�带 �������ݴϴ�.";
    Sleep(2000);
    gotoxy(longInfoX, longInfoY);
    cout << "                                                                          ";
    return;
}


//�޴�����
int ReadyGame()
{
    //����ȭ�� �׸���
    DrawIntro();
    int result = 0;
    int x = 31;
    int y = 30;
    gotoxy(x, y);
    while (true) {
        int num = _getch();
        switch (num)
        {
            //��
        case 72: {
            if (y > 30) {
                gotoxy(x - 2, y);
                printf("  ");
                gotoxy(x - 2, y -= 2);
                printf(">>");
            }
            break;
        }
               //�Ʒ�
        case 80: {
            if (y < 34) {
                gotoxy(x - 2, y);
                printf("  ");
                gotoxy(x - 2, y += 2);
                printf(">>");
            }
            break;
        }
               //enter
        case 13:
            result = y - 30; //0 �Ǵ� 2 �Ǵ� 4
            gotoxy(0, 0);
            cout << result << "   " << endl;
            return result;
            //exit
        case 27:
            return -1;
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

//���� ī�� && ���̺� ī�� ���
void printPlayersCardInfo(Player& p1, Player& p2, Player& p3, Player& p4) {

    gotoxy(57, 6);
    cout << "���̺�ī�� �� : " << p1.getFrontCount() << "  ";
    gotoxy(57, 7);
    cout << "����ī�� �� : " << p1.getBackCount() << "  ";

    gotoxy(57, 16);
    cout << "���̺�ī�� �� : " << p2.getFrontCount() << "  ";
    gotoxy(57, 17);
    cout << "����ī�� �� : " << p2.getBackCount() << "  ";

    gotoxy(57, 26);
    cout << "���̺�ī�� �� : " << p3.getFrontCount() << "  ";
    gotoxy(57, 27);
    cout << "����ī�� �� : " << p3.getBackCount() << "  ";

    gotoxy(57, 36);
    cout << "���̺�ī�� �� : " << p4.getFrontCount() << "  ";
    gotoxy(57, 37);
    cout << "����ī�� �� : " << p4.getBackCount() << "  ";
}

void DrawChoosePlaying() {
    system("cls");

    int x = 20;
    int y = 17;
    gotoxy(x, y);
    cout << "��������������������������������������������������������������������������������������������������";
    gotoxy(x, y + 1);
    cout << "��                                               ��";
    gotoxy(x, y + 2);
    cout << "��               ���� ���� ��� ����             ��";
    gotoxy(x, y + 3);
    cout << "��                                               ��";
    gotoxy(x, y + 4);
    cout << "��                 >>  1 Players                 ��";
    gotoxy(x, y + 5);
    cout << "��                                               ��";
    gotoxy(x, y + 6);
    cout << "��                     4 Players                 ��";
    gotoxy(x, y + 7);
    cout << "��                                               ��";
    gotoxy(x, y + 8);
    cout << "��������������������������������������������������������������������������������������������������";


}
//Ż������ Ȯ��
void checkPlayerNoneAble(Player& user, Player& p1, Player& p2, Player& p3) {
    if (user.getBackCount() == 0) {
        //ȭ�� ǥ��
        makeAllFaceDefault(p1);
        makeAllFaceDefault(p2);
        makeAllFaceDefault(p3);
        makeFaceAngry(user);
        user.setNoneAvailable();
        printPlayersCardInfo(user, p1, p2, p3);
        gotoxy(longInfoX + 10, longInfoY);
        cout << user.getPlayerNum() << "�� ����ڰ� Ż���Ǿ����ϴ�.";
        Sleep(2000);
        gotoxy(longInfoX + 10, longInfoY);
        cout << "                              ";
    }
}

//���� ���� (1 vs 1 vs 1 vs 1)
void StartGameMulti()
{
    //4���� �÷����� ���(ī�� �ѱ��/��ġ��) : qw  xc  nm  op
    DrawStartGame();
    //���۹� draw
    {
        int x = 12;
        gotoxy(x, 30);
        cout << "������������������������  ���۹� ( NEXT / BELL ) ����������������������";
        gotoxy(x, 31);
        cout << "��                                              ��";
        gotoxy(x, 32);
        cout << "��           Player 1   ��   Q  /  W            ��";
        gotoxy(x, 33);
        cout << "��                                              ��";
        gotoxy(x, 34);
        cout << "��           Player 2   ��   X  /  C            ��";
        gotoxy(x, 35);
        cout << "��                                              ��";
        gotoxy(x, 36);
        cout << "��           Player 3   ��   N  /  M            ��";
        gotoxy(x, 37);
        cout << "��                                              ��";
        gotoxy(x, 38);
        cout << "��           Player 4   ��   O  /  P            ��";
        gotoxy(x, 39);
        cout << "��                                              ��";
        gotoxy(x, 40);
        cout << "������������������������������������������������������������������������������������������������";
    }
    //����� ����
    Player user(1), p1(2), p2(3), p3(4);
    //ī�� ������ġ,����ڿ��� ī�� �й�
    setInitCard(user, p1, p2, p3);
    //�ݺ�
    int input = 0;
    int turn = -1;
    //�� �ܰ迡�� ���ƴ���, ī��Ѱ���� Ȯ��
    boolean pushOk = false;
    while (true) {
        // (1:1:1:1) �Ѹ��� �÷��̾ ������ ���
        if ((int)user.getAvailable() + (int)p1.getAvailable() + (int)p2.getAvailable() + (int)p3.getAvailable() == 1) {
            string winnerName = "";
            if (user.getAvailable() == 1) winnerName = "Player 1";
            else if (p1.getAvailable() == 1) winnerName = "Player 2";
            else if (p2.getAvailable() == 1) winnerName = "Player 3";
            else if (p3.getAvailable() == 1) winnerName = "Player 4";
            //���ȭ��
            {
                int x = 20;
                int y = 17;
                gotoxy(x, y);
                cout << "��������������������������������������������������������������������������������������";
                gotoxy(x, y + 1);
                cout << "��                                         ��";
                gotoxy(x, y + 2);
                cout << "��                GAME OVER                ��";
                gotoxy(x, y + 3);
                cout << "��                                         ��";
                gotoxy(x, y + 4);
                cout << "��             winner :  " << winnerName << "          ��";
                gotoxy(x, y + 5);
                cout << "��                                         ��";
                gotoxy(x, y + 6);
                cout << "��     ����� ����ȭ������ �̵��մϴ�.     ��";
                gotoxy(x, y + 7);
                cout << "��                                         ��";
                gotoxy(x, y + 8);
                cout << "��������������������������������������������������������������������������������������";

                Sleep(5000);
                main();
                break;
            }
        }
        turn++;
        //1�� ����
        if (turn % 4 == 0) {
            //���� ������ �Ѿ�� Ű ����
            int nextKey1 = 88, nextKey2 = 120;
            printPlayersCardInfo(user, p1, p2, p3);
            if (!user.getAvailable()) {
                continue;
            }
            else {
                //Player 1 : ī�� ���� Q, ��ġ�� W (81,113 / 87,119)
                //üũ
                gotoxy(0, 0);
                cout << "1�� ����";
                //���� ���
                gotoxy(longInfoX + 13, longInfoY - 2);
                cout << "                                        ";
                gotoxy(longInfoX + 13, longInfoY - 2);
                cout << "[ " << user.getPlayerNum() << "�� PLAYER ]";


                //�� �Ͽ��� ī�峻�Ⱑ �̹� ���ȴ��� Ȯ��
                if (pushOk == false) {
                    while (true) {
                        int value = _getch();
                        if (value == 81 || value == 113) break;
                    }
                }

                //ī�� ������
                if (user.open() == -1) continue;
                frontCardPrint(user.getFrontTopCard(), user);
                printPlayersCardInfo(user, p1, p2, p3);

                //������ ���
                gotoxy(longInfoX + 13, longInfoY - 2);
                cout << "                                        ";
                gotoxy(longInfoX + 13, longInfoY - 2);
                cout << "[ " << p1.getPlayerNum() << "�� PLAYER ]";

                //���� �� ������ Ű�� ���ϱ� (Ż���� ����)
                if (!p1.getAvailable()) {
                    nextKey1 = 78, nextKey2 = 110;
                    gotoxy(longInfoX + 13, longInfoY - 2);
                    cout << "                                        ";
                    gotoxy(longInfoX + 13, longInfoY - 2);
                    cout << "[ " << p2.getPlayerNum() << "�� PLAYER ]";
                    if (!p2.getAvailable()) {
                        nextKey1 = 79, nextKey2 = 111;
                        gotoxy(longInfoX + 13, longInfoY - 2);
                        cout << "                                        ";
                        gotoxy(longInfoX + 13, longInfoY - 2);
                        cout << "[ " << p3.getPlayerNum() << "�� PLAYER ]";
                        if (!p3.getAvailable()) {
                            nextKey1 = 81, nextKey2 = 113;
                            gotoxy(longInfoX + 13, longInfoY - 2);
                            cout << "                                        ";
                            gotoxy(longInfoX + 13, longInfoY - 2);
                            cout << "[ " << user.getPlayerNum() << "�� PLAYER ]";
                        }
                    }
                }

                //��ġ�ų� ���� ���ʰ� ī��ѱ�
                while (true) {
                    input = _getch();
                    if (input == 87 || input == 119 ||
                        input == 67 || input == 99 ||
                        input == 77 || input == 109 ||
                        input == 80 || input == 112 ||
                        input == nextKey1 || input == nextKey2) break;
                }

                //�������� ī�带 �ѱ� ���
                if (input == nextKey1 || input == nextKey2) {
                    pushOk = true;
                    checkPlayerNoneAble(user, p1, p2, p3);
                    continue;
                }
                else {
                    pushOk = false;
                    //1���� ������ ���
                    if (input == 87 || input == 119) { //user�� �� ģ ���
                        if (user.getAvailable()) {
                            PlaySound(TEXT("ringingBell.wav"), 0, SND_FILENAME | SND_ASYNC);
                            //���� 5���϶� ���� ���
                            if (checkFiveCard(user, p1, p2, p3)) {
                                //���� ���
                                user.plusScore();
                                //(��)���� ǥ��
                                makeAllFaceDefault(p1);
                                makeAllFaceDefault(p2);
                                makeAllFaceDefault(p3);
                                makeFaceSmile(user);
                                //���̺� ���� ī�� ��� ������
                                getAllFrontCard(user, p1, p2, p3);
                                printPlayersCardInfo(user, p1, p2, p3);
                            }
                            //�߸� ���� ���
                            else {
                                //���� ���
                                user.minusScore();
                                //ȭ�� ǥ��
                                makeAllFaceDefault(p1);
                                makeAllFaceDefault(p2);
                                makeAllFaceDefault(p3);
                                makeFaceAngry(user);
                                PlaySound(TEXT("missingBell.wav"), 0, SND_FILENAME | SND_ASYNC);
                                //ī�� ���徿 ��������
                                missRinging(user, p1, p2, p3);
                                printPlayersCardInfo(user, p1, p2, p3);
                            }
                        }
                    }
                    //2���� ������ ���
                    else if (input == 67 || input == 99) { //p1�� �� ģ ���
                        if (p1.getAvailable()) {
                            PlaySound(TEXT("ringingBell.wav"), 0, SND_FILENAME | SND_ASYNC);
                            //���� 5���϶� ���� ���
                            if (checkFiveCard(user, p1, p2, p3)) {
                                //���� ���
                                p1.plusScore();
                                //(��)���� ǥ��
                                makeAllFaceDefault(user);
                                makeAllFaceDefault(p2);
                                makeAllFaceDefault(p3);
                                makeFaceSmile(p1);
                                //���̺� ���� ī�� ��� ������
                                getAllFrontCard(p1, user, p2, p3);
                                printPlayersCardInfo(user, p1, p2, p3);
                            }
                            //�߸� ���� ���
                            else {
                                //���� ���
                                p1.minusScore();
                                //ȭ�� ǥ��, ������ �⺻ ǥ��
                                makeAllFaceDefault(user);
                                makeAllFaceDefault(p2);
                                makeAllFaceDefault(p3);
                                makeFaceAngry(p1);
                                PlaySound(TEXT("missingBell.wav"), 0, SND_FILENAME | SND_ASYNC);
                                //ī�� ���徿 ��������
                                missRinging(p1, user, p2, p3);
                                printPlayersCardInfo(user, p1, p2, p3);
                            }
                        }
                    }
                    //3���� ������ ���
                    else if (input == 77 || input == 109) { //p2�� �� ģ ���
                        if (p2.getAvailable()) {
                            PlaySound(TEXT("ringingBell.wav"), 0, SND_FILENAME | SND_ASYNC);
                            //���� 5���϶� ���� ���
                            if (checkFiveCard(user, p1, p2, p3)) {
                                //���� ���
                                p2.plusScore();
                                //(��)���� ǥ��
                                makeAllFaceDefault(p1);
                                makeAllFaceDefault(user);
                                makeAllFaceDefault(p3);
                                makeFaceSmile(p2);
                                //���̺� ���� ī�� ��� ������
                                getAllFrontCard(p2, p1, user, p3);
                                printPlayersCardInfo(user, p1, p2, p3);
                            }
                            //�߸� ���� ���
                            else {
                                //���� ���
                                p2.minusScore();
                                //ȭ�� ǥ��, ������ �⺻ ǥ��
                                makeAllFaceDefault(p1);
                                makeAllFaceDefault(user);
                                makeAllFaceDefault(p3);
                                makeFaceAngry(p2);
                                PlaySound(TEXT("missingBell.wav"), 0, SND_FILENAME | SND_ASYNC);
                                missRinging(p2, p1, user, p3);
                                printPlayersCardInfo(user, p1, p2, p3);
                            }
                        }
                    }
                    //4���� ������ ���
                    else if (input == 80 || input == 112) { //p3�� �� ģ ���
                        if (p3.getAvailable()) {
                            PlaySound(TEXT("ringingBell.wav"), 0, SND_FILENAME | SND_ASYNC);
                            //���� 5���϶� ���� ���
                            if (checkFiveCard(user, p1, p2, p3)) {
                                //���� ���
                                p3.plusScore();
                                //(��)���� ǥ��
                                makeAllFaceDefault(p1);
                                makeAllFaceDefault(p2);
                                makeAllFaceDefault(user);
                                makeFaceSmile(p3);
                                //���̺� ���� ī�� ��� ������
                                getAllFrontCard(p3, p1, p2, user);
                                printPlayersCardInfo(user, p1, p2, p3);
                            }
                            //�߸� ���� ���
                            else {
                                //���� ���
                                p3.minusScore();
                                //ȭ�� ǥ��, ������ �⺻ ǥ��
                                makeAllFaceDefault(p1);
                                makeAllFaceDefault(p2);
                                makeAllFaceDefault(user);
                                makeFaceAngry(p3);
                                PlaySound(TEXT("missingBell.wav"), 0, SND_FILENAME | SND_ASYNC);
                                missRinging(p3, p1, p2, user);
                                printPlayersCardInfo(user, p1, p2, p3);
                            }
                        }
                    }
                }

                //1�� Ż�� ó��
                if (user.getBackCount() == 0) {
                    //ȭ�� ǥ��
                    makeAllFaceDefault(p1);
                    makeAllFaceDefault(p2);
                    makeAllFaceDefault(p3);
                    makeFaceAngry(user);
                    user.setNoneAvailable();
                    printPlayersCardInfo(user, p1, p2, p3);
                    gotoxy(longInfoX + 10, longInfoY);
                    cout << user.getPlayerNum() << "�� ����ڰ� Ż���Ǿ����ϴ�.";
                    Sleep(2000);
                    gotoxy(longInfoX + 10, longInfoY);
                    cout << "                              ";
                }
                continue;
            }
        }
        //2�� ����
        if (turn % 4 == 1) {
            //���� ������ �Ѿ�� Ű ����
            int nextKey1 = 78, nextKey2 = 110;
            printPlayersCardInfo(user, p1, p2, p3);
            if (!p1.getAvailable()) {
                continue;
            }
            else {
                //Player 2 : ī�� ���� X, ��ġ�� C (88,120 / 67,99)
                //üũ
                gotoxy(0, 0);
                cout << "2�� ����";
                //���� ���
                gotoxy(longInfoX + 13, longInfoY - 2);
                cout << "                                        ";
                gotoxy(longInfoX + 13, longInfoY - 2);
                cout << "[ " << p1.getPlayerNum() << "�� PLAYER ]";

                //�� �Ͽ��� ī�峻�Ⱑ �̹� ���ȴ��� Ȯ��
                if (pushOk == false) {
                    while (true) {
                        int value = _getch();
                        if (value == 88 || value == 120) break;
                    }
                }

                //ī�� ������
                if (p1.open() == -1) continue;
                frontCardPrint(p1.getFrontTopCard(), p1);
                printPlayersCardInfo(user, p1, p2, p3);

                //������ ���
                gotoxy(longInfoX + 13, longInfoY - 2);
                cout << "                                        ";
                gotoxy(longInfoX + 13, longInfoY - 2);
                cout << "[ " << p2.getPlayerNum() << "�� PLAYER ]";

                //���� �� ������ Ű�� ���ϱ� (Ż���� ����)
                if (!p2.getAvailable()) {
                    nextKey1 = 79, nextKey2 = 111;
                    gotoxy(longInfoX + 13, longInfoY - 2);
                    cout << "                                        ";
                    gotoxy(longInfoX + 13, longInfoY - 2);
                    cout << "[ " << p3.getPlayerNum() << "�� PLAYER ]";
                    if (!p3.getAvailable()) {
                        nextKey1 = 81, nextKey2 = 113;
                        gotoxy(longInfoX + 13, longInfoY - 2);
                        cout << "                                        ";
                        gotoxy(longInfoX + 13, longInfoY - 2);
                        cout << "[ " << user.getPlayerNum() << "�� PLAYER ]";
                        if (!user.getAvailable()) {
                            if (!user.getAvailable()) nextKey1 = 88, nextKey2 = 120;
                            gotoxy(longInfoX + 13, longInfoY - 2);
                            cout << "                                        ";
                            gotoxy(longInfoX + 13, longInfoY - 2);
                            cout << "[ " << p1.getPlayerNum() << "�� PLAYER ]";
                        }
                    }
                }

                //��ġ�ų� ���� ���ʰ� ī��ѱ�
                while (true) {
                    input = _getch();
                    if (input == 87 || input == 119 ||
                        input == 67 || input == 99 ||
                        input == 77 || input == 109 ||
                        input == 80 || input == 112 ||
                        input == nextKey1 || input == nextKey2) break;
                }

                //�������� ī�带 �ѱ� ���
                if (input == nextKey1 || input == nextKey2) {
                    pushOk = true;
                    checkPlayerNoneAble(p1, user, p2, p3);
                    continue;
                }
                //������ ��ģ ���
                else {
                    pushOk = false;
                    //1���� ������ ���
                    if (input == 87 || input == 119) { //user�� �� ģ ���
                        if (user.getAvailable()) {
                            PlaySound(TEXT("ringingBell.wav"), 0, SND_FILENAME | SND_ASYNC);
                            //���� 5���϶� ���� ���
                            if (checkFiveCard(user, p1, p2, p3)) {
                                //���� ���
                                user.plusScore();
                                //(��)���� ǥ��
                                makeAllFaceDefault(p1);
                                makeAllFaceDefault(p2);
                                makeAllFaceDefault(p3);
                                makeFaceSmile(user);
                                //���̺� ���� ī�� ��� ������
                                getAllFrontCard(user, p1, p2, p3);
                                printPlayersCardInfo(user, p1, p2, p3);
                            }
                            //�߸� ���� ���
                            else {
                                //���� ���
                                user.minusScore();
                                //ȭ�� ǥ��
                                makeAllFaceDefault(p1);
                                makeAllFaceDefault(p2);
                                makeAllFaceDefault(p3);
                                makeFaceAngry(user);
                                PlaySound(TEXT("missingBell.wav"), 0, SND_FILENAME | SND_ASYNC);
                                //ī�� ���徿 ��������
                                missRinging(user, p1, p2, p3);
                                printPlayersCardInfo(user, p1, p2, p3);
                            }
                        }
                    }
                    //2���� ������ ���
                    else if (input == 67 || input == 99) { //p1�� �� ģ ���
                        if (p1.getAvailable()) {
                            PlaySound(TEXT("ringingBell.wav"), 0, SND_FILENAME | SND_ASYNC);
                            //���� 5���϶� ���� ���
                            if (checkFiveCard(user, p1, p2, p3)) {
                                //���� ���
                                p1.plusScore();
                                //(��)���� ǥ��
                                makeAllFaceDefault(user);
                                makeAllFaceDefault(p2);
                                makeAllFaceDefault(p3);
                                makeFaceSmile(p1);
                                //���̺� ���� ī�� ��� ������
                                getAllFrontCard(p1, user, p2, p3);
                                printPlayersCardInfo(user, p1, p2, p3);
                            }
                            //�߸� ���� ���
                            else {
                                //���� ���
                                p1.minusScore();
                                //ȭ�� ǥ��, ������ �⺻ ǥ��
                                makeAllFaceDefault(user);
                                makeAllFaceDefault(p2);
                                makeAllFaceDefault(p3);
                                makeFaceAngry(p1);
                                PlaySound(TEXT("missingBell.wav"), 0, SND_FILENAME | SND_ASYNC);
                                //ī�� ���徿 ��������
                                missRinging(p1, user, p2, p3);
                                printPlayersCardInfo(user, p1, p2, p3);
                            }
                        }
                    }
                    //3���� ������ ���
                    else if (input == 77 || input == 109) { //p2�� �� ģ ���
                        if (p2.getAvailable()) {
                            PlaySound(TEXT("ringingBell.wav"), 0, SND_FILENAME | SND_ASYNC);
                            //���� 5���϶� ���� ���
                            if (checkFiveCard(user, p1, p2, p3)) {
                                //���� ���
                                p2.plusScore();
                                //(��)���� ǥ��
                                makeAllFaceDefault(p1);
                                makeAllFaceDefault(user);
                                makeAllFaceDefault(p3);
                                makeFaceSmile(p2);
                                //���̺� ���� ī�� ��� ������
                                getAllFrontCard(p2, p1, user, p3);
                                printPlayersCardInfo(user, p1, p2, p3);
                            }
                            //�߸� ���� ���
                            else {
                                //���� ���
                                p2.minusScore();
                                //ȭ�� ǥ��, ������ �⺻ ǥ��
                                makeAllFaceDefault(p1);
                                makeAllFaceDefault(user);
                                makeAllFaceDefault(p3);
                                makeFaceAngry(p2);
                                PlaySound(TEXT("missingBell.wav"), 0, SND_FILENAME | SND_ASYNC);
                                missRinging(p2, p1, user, p3);
                                printPlayersCardInfo(user, p1, p2, p3);
                            }
                        }
                    }
                    //4���� ������ ���
                    else if (input == 80 || input == 112) { //p3�� �� ģ ���
                        if (p3.getAvailable()) {
                            PlaySound(TEXT("ringingBell.wav"), 0, SND_FILENAME | SND_ASYNC);
                            //���� 5���϶� ���� ���
                            if (checkFiveCard(user, p1, p2, p3)) {
                                //���� ���
                                p3.plusScore();
                                //(��)���� ǥ��
                                makeAllFaceDefault(p1);
                                makeAllFaceDefault(p2);
                                makeAllFaceDefault(user);
                                makeFaceSmile(p3);
                                //���̺� ���� ī�� ��� ������
                                getAllFrontCard(p3, p1, p2, user);
                                printPlayersCardInfo(user, p1, p2, p3);
                            }
                            //�߸� ���� ���
                            else {
                                //���� ���
                                p3.minusScore();
                                //ȭ�� ǥ��, ������ �⺻ ǥ��
                                makeAllFaceDefault(p1);
                                makeAllFaceDefault(p2);
                                makeAllFaceDefault(user);
                                makeFaceAngry(p3);
                                PlaySound(TEXT("missingBell.wav"), 0, SND_FILENAME | SND_ASYNC);
                                missRinging(p3, p1, p2, user);
                                printPlayersCardInfo(user, p1, p2, p3);
                            }
                        }
                    }
                }

                //2�� Ż�� ó��
                if (p1.getBackCount() == 0) {
                    //ȭ�� ǥ��
                    makeAllFaceDefault(user);
                    makeAllFaceDefault(p2);
                    makeAllFaceDefault(p3);
                    makeFaceAngry(p1);
                    p1.setNoneAvailable();
                    printPlayersCardInfo(user, p1, p2, p3);
                    gotoxy(longInfoX + 10, longInfoY);
                    cout << p1.getPlayerNum() << "�� ����ڰ� Ż���Ǿ����ϴ�.";
                    Sleep(2000);
                    gotoxy(longInfoX + 10, longInfoY);
                    cout << "                              ";
                }
                continue;

            }
        }
        //3�� ����
        if (turn % 4 == 2) {
            //���� ������ �Ѿ�� Ű ����
            int nextKey1 = 79, nextKey2 = 111;
            printPlayersCardInfo(user, p1, p2, p3);
            if (!p2.getAvailable()) {
                continue;
            }
            else {
                //Player 3 : ī�� ���� N, ��ġ�� M (78,110 / 77,109)
               //üũ
                gotoxy(0, 0);
                cout << "3�� ����";

                //���� ���
                gotoxy(longInfoX + 13, longInfoY - 2);
                cout << "                                        ";
                gotoxy(longInfoX + 13, longInfoY - 2);
                cout << "[ " << p2.getPlayerNum() << "�� PLAYER ]";

                //�� �Ͽ��� ī�峻�Ⱑ �̹� ���ȴ��� Ȯ��
                if (pushOk == false) {
                    while (true) {
                        int value = _getch();
                        if (value == 78 || value == 110) break;
                    }
                }

                //ī�� ������
                if (p2.open() == -1) continue;
                frontCardPrint(p2.getFrontTopCard(), p2);
                printPlayersCardInfo(user, p1, p2, p3);

                //������ ���
                gotoxy(longInfoX + 13, longInfoY - 2);
                cout << "                                        ";
                gotoxy(longInfoX + 13, longInfoY - 2);
                cout << "[ " << p3.getPlayerNum() << "�� PLAYER ]";

                //���� �� ������ Ű�� ���ϱ� (Ż���� ����)
                if (!p3.getAvailable()) {
                    nextKey1 = 81, nextKey2 = 113;
                    gotoxy(longInfoX + 13, longInfoY - 2);
                    cout << "                                        ";
                    gotoxy(longInfoX + 13, longInfoY - 2);
                    cout << "[ " << user.getPlayerNum() << "�� PLAYER ]";
                    if (!user.getAvailable()) {
                        nextKey1 = 88, nextKey2 = 120;
                        gotoxy(longInfoX + 13, longInfoY - 2);
                        cout << "                                        ";
                        gotoxy(longInfoX + 13, longInfoY - 2);
                        cout << "[ " << p1.getPlayerNum() << "�� PLAYER ]";
                        if (!p1.getAvailable()) {
                            nextKey1 = 78, nextKey2 = 110;
                            gotoxy(longInfoX + 13, longInfoY - 2);
                            cout << "                                        ";
                            gotoxy(longInfoX + 13, longInfoY - 2);
                            cout << "[ " << p2.getPlayerNum() << "�� PLAYER ]";
                        }
                    }
                }

                //��ġ�ų� ���� ���ʰ� ī��ѱ�
                while (true) {
                    input = _getch();
                    if (input == 87 || input == 119 ||
                        input == 67 || input == 99 ||
                        input == 77 || input == 109 ||
                        input == 80 || input == 112 ||
                        input == nextKey1 || input == nextKey2) break;
                }

                //�������� ī�带 �ѱ� ���
                if (input == nextKey1 || input == nextKey2) {
                    pushOk = true;
                    checkPlayerNoneAble(p2, p1, user, p3);
                    continue;
                }
                else {
                    pushOk = false;
                    //1���� ������ ���
                    if (input == 87 || input == 119) { //user�� �� ģ ���
                        //Ż���� ������� ��� continue
                        if (user.getAvailable()) {
                            PlaySound(TEXT("ringingBell.wav"), 0, SND_FILENAME | SND_ASYNC);
                            //���� 5���϶� ���� ���
                            if (checkFiveCard(user, p1, p2, p3)) {
                                //���� ���
                                user.plusScore();
                                //(��)���� ǥ��
                                makeAllFaceDefault(p1);
                                makeAllFaceDefault(p2);
                                makeAllFaceDefault(p3);
                                makeFaceSmile(user);
                                //���̺� ���� ī�� ��� ������
                                getAllFrontCard(user, p1, p2, p3);
                                printPlayersCardInfo(user, p1, p2, p3);
                            }
                            //�߸� ���� ���
                            else {
                                //���� ���
                                user.minusScore();
                                //ȭ�� ǥ��
                                makeAllFaceDefault(p1);
                                makeAllFaceDefault(p2);
                                makeAllFaceDefault(p3);
                                makeFaceAngry(user);
                                PlaySound(TEXT("missingBell.wav"), 0, SND_FILENAME | SND_ASYNC);
                                //ī�� ���徿 ��������
                                missRinging(user, p1, p2, p3);
                                printPlayersCardInfo(user, p1, p2, p3);
                            }
                        }
                    }
                    //2���� ������ ���
                    else if (input == 67 || input == 99) { //p1�� �� ģ ���
                        //Ż���� ������� ��� continue
                        if (p1.getAvailable()) {

                            PlaySound(TEXT("ringingBell.wav"), 0, SND_FILENAME | SND_ASYNC);
                            //���� 5���϶� ���� ���
                            if (checkFiveCard(user, p1, p2, p3)) {
                                //���� ���
                                p1.plusScore();
                                //(��)���� ǥ��
                                makeAllFaceDefault(user);
                                makeAllFaceDefault(p2);
                                makeAllFaceDefault(p3);
                                makeFaceSmile(p1);
                                //���̺� ���� ī�� ��� ������
                                getAllFrontCard(p1, user, p2, p3);
                                printPlayersCardInfo(user, p1, p2, p3);
                            }
                            //�߸� ���� ���
                            else {
                                //���� ���
                                p1.minusScore();
                                //ȭ�� ǥ��, ������ �⺻ ǥ��
                                makeAllFaceDefault(user);
                                makeAllFaceDefault(p2);
                                makeAllFaceDefault(p3);
                                makeFaceAngry(p1);
                                PlaySound(TEXT("missingBell.wav"), 0, SND_FILENAME | SND_ASYNC);
                                //ī�� ���徿 ��������
                                missRinging(p1, user, p2, p3);
                                printPlayersCardInfo(user, p1, p2, p3);
                            }
                        }
                    }
                    //3���� ������ ���
                    else if (input == 77 || input == 109) { //p2�� �� ģ ���
                        //Ż���� ������� ��� �� ĥ �� ����
                        if (p2.getAvailable()) {
                            PlaySound(TEXT("ringingBell.wav"), 0, SND_FILENAME | SND_ASYNC);
                            //���� 5���϶� ���� ���
                            if (checkFiveCard(user, p1, p2, p3)) {
                                //���� ���
                                p2.plusScore();
                                //(��)���� ǥ��
                                makeAllFaceDefault(p1);
                                makeAllFaceDefault(user);
                                makeAllFaceDefault(p3);
                                makeFaceSmile(p2);
                                //���̺� ���� ī�� ��� ������
                                getAllFrontCard(p2, p1, user, p3);
                                printPlayersCardInfo(user, p1, p2, p3);
                            }
                            //�߸� ���� ���
                            else {
                                //���� ���
                                p2.minusScore();
                                //ȭ�� ǥ��, ������ �⺻ ǥ��
                                makeAllFaceDefault(p1);
                                makeAllFaceDefault(user);
                                makeAllFaceDefault(p3);
                                makeFaceAngry(p2);
                                PlaySound(TEXT("missingBell.wav"), 0, SND_FILENAME | SND_ASYNC);
                                missRinging(p2, p1, user, p3);
                                printPlayersCardInfo(user, p1, p2, p3);
                            }
                        }
                    }
                    //4���� ������ ���
                    else if (input == 80 || input == 112) { //p3�� �� ģ ���
                        //Ż���� ������� ��� continue
                        if (p3.getAvailable()) {

                            PlaySound(TEXT("ringingBell.wav"), 0, SND_FILENAME | SND_ASYNC);
                            //���� 5���϶� ���� ���
                            if (checkFiveCard(user, p1, p2, p3)) {
                                //���� ���
                                p3.plusScore();
                                //(��)���� ǥ��
                                makeAllFaceDefault(p1);
                                makeAllFaceDefault(p2);
                                makeAllFaceDefault(user);
                                makeFaceSmile(p3);
                                //���̺� ���� ī�� ��� ������
                                getAllFrontCard(p3, p1, p2, user);
                                printPlayersCardInfo(user, p1, p2, p3);
                            }
                            //�߸� ���� ���
                            else {
                                //���� ���
                                p3.minusScore();
                                //ȭ�� ǥ��, ������ �⺻ ǥ��
                                makeAllFaceDefault(p1);
                                makeAllFaceDefault(p2);
                                makeAllFaceDefault(user);
                                makeFaceAngry(p3);
                                PlaySound(TEXT("missingBell.wav"), 0, SND_FILENAME | SND_ASYNC);
                                missRinging(p3, p1, p2, user);
                                printPlayersCardInfo(user, p1, p2, p3);
                            }
                        }
                    }
                }

                //3�� Ż�� ó��
                if (p2.getBackCount() == 0) {
                    //ȭ�� ǥ��
                    makeAllFaceDefault(user);
                    makeAllFaceDefault(p1);
                    makeAllFaceDefault(p3);
                    makeFaceAngry(p2);
                    p2.setNoneAvailable();
                    printPlayersCardInfo(user, p1, p2, p3);
                    gotoxy(longInfoX + 10, longInfoY);
                    cout << p2.getPlayerNum() << "�� ����ڰ� Ż���Ǿ����ϴ�.";
                    Sleep(2000);
                    gotoxy(longInfoX + 10, longInfoY);
                    cout << "                              ";
                }
                continue;
            }
        }
        //4�� ����
        if (turn % 4 == 3) {
            //���� ������ �Ѿ�� Ű ����
            int nextKey1 = 81, nextKey2 = 113;
            printPlayersCardInfo(user, p1, p2, p3);
            if (!p3.getAvailable()) {
                continue;
            }
            else {
                //Player 4 : ī�� ���� O, ��ġ�� P (79,111 / 80,112)
                //üũ
                gotoxy(0, 0);
                cout << "4�� ����";
                //���� ���
                gotoxy(longInfoX + 13, longInfoY - 2);
                cout << "                                        ";
                gotoxy(longInfoX + 13, longInfoY - 2);
                cout << "[ " << p3.getPlayerNum() << "�� PLAYER ]";


                //�� �Ͽ��� ī�峻�Ⱑ �̹� ���ȴ��� Ȯ��
                if (pushOk == false) {
                    while (true) {
                        int value = _getch();
                        if (value == 79 || value == 111) break;
                    }
                }

                //ī�� ������
                if (p3.open() == -1) continue;
                frontCardPrint(p3.getFrontTopCard(), p3);
                printPlayersCardInfo(user, p1, p2, p3);

                //������ ���
                gotoxy(longInfoX + 13, longInfoY - 2);
                cout << "                                        ";
                gotoxy(longInfoX + 13, longInfoY - 2);
                cout << "[ " << user.getPlayerNum() << "�� PLAYER ]";

                //���� �� ������ Ű�� ���ϱ� (Ż���� ����)
                if (!user.getAvailable()) {
                    nextKey1 = 88, nextKey2 = 120;
                    gotoxy(longInfoX + 13, longInfoY - 2);
                    cout << "                                        ";
                    gotoxy(longInfoX + 13, longInfoY - 2);
                    cout << "[ " << p1.getPlayerNum() << "�� PLAYER ]";
                    if (!p1.getAvailable()) {
                        nextKey1 = 78, nextKey2 = 110;
                        gotoxy(longInfoX + 13, longInfoY - 2);
                        cout << "                                        ";
                        gotoxy(longInfoX + 13, longInfoY - 2);
                        cout << "[ " << p2.getPlayerNum() << "�� PLAYER ]";
                        if (!p2.getAvailable()) {
                            nextKey1 = 79, nextKey2 = 111;
                            gotoxy(longInfoX + 13, longInfoY - 2);
                            cout << "                                        ";
                            gotoxy(longInfoX + 13, longInfoY - 2);
                            cout << "[ " << p3.getPlayerNum() << "�� PLAYER ]";
                        }
                    }
                }

                //��ġ�ų� ���� ���ʰ� ī��ѱ�
                while (true) {
                    input = _getch();
                    if (input == 87 || input == 119 ||
                        input == 67 || input == 99 ||
                        input == 77 || input == 109 ||
                        input == 80 || input == 112 ||
                        input == nextKey1 || input == nextKey2) break;
                }

                //�������� ī�带 �ѱ� ���
                if (input == nextKey1 || input == nextKey2) {
                    pushOk = true;
                    checkPlayerNoneAble(p3, p1, p2, user);
                    continue;
                }
                else {
                    pushOk = false;
                    //1���� ��ģ ���
                    if (input == 87 || input == 119) { //user�� �� ģ ���
                        if (user.getAvailable()) {
                            PlaySound(TEXT("ringingBell.wav"), 0, SND_FILENAME | SND_ASYNC);
                            //���� 5���϶� ���� ���
                            if (checkFiveCard(user, p1, p2, p3)) {
                                //���� ���
                                user.plusScore();
                                //(��)���� ǥ��
                                makeAllFaceDefault(p1);
                                makeAllFaceDefault(p2);
                                makeAllFaceDefault(p3);
                                makeFaceSmile(user);
                                //���̺� ���� ī�� ��� ������
                                getAllFrontCard(user, p1, p2, p3);
                                printPlayersCardInfo(user, p1, p2, p3);
                            }
                            //�߸� ���� ���
                            else {
                                //���� ���
                                user.minusScore();
                                //ȭ�� ǥ��
                                makeAllFaceDefault(p1);
                                makeAllFaceDefault(p2);
                                makeAllFaceDefault(p3);
                                makeFaceAngry(user);
                                PlaySound(TEXT("missingBell.wav"), 0, SND_FILENAME | SND_ASYNC);
                                //ī�� ���徿 ��������
                                missRinging(user, p1, p2, p3);
                                printPlayersCardInfo(user, p1, p2, p3);
                            }
                        }
                    }
                    //2���� ��ģ ���
                    else if (input == 67 || input == 99) { //p1�� �� ģ ���
                        if (p1.getAvailable()) {
                            PlaySound(TEXT("ringingBell.wav"), 0, SND_FILENAME | SND_ASYNC);
                            //���� 5���϶� ���� ���
                            if (checkFiveCard(user, p1, p2, p3)) {
                                //���� ���
                                p1.plusScore();
                                //(��)���� ǥ��
                                makeAllFaceDefault(user);
                                makeAllFaceDefault(p2);
                                makeAllFaceDefault(p3);
                                makeFaceSmile(p1);
                                //���̺� ���� ī�� ��� ������
                                getAllFrontCard(p1, user, p2, p3);
                                printPlayersCardInfo(user, p1, p2, p3);
                            }
                            //�߸� ���� ���
                            else {
                                //���� ���
                                p1.minusScore();
                                //ȭ�� ǥ��, ������ �⺻ ǥ��
                                makeAllFaceDefault(user);
                                makeAllFaceDefault(p2);
                                makeAllFaceDefault(p3);
                                makeFaceAngry(p1);
                                PlaySound(TEXT("missingBell.wav"), 0, SND_FILENAME | SND_ASYNC);
                                //ī�� ���徿 ��������
                                missRinging(p1, user, p2, p3);
                                printPlayersCardInfo(user, p1, p2, p3);
                            }
                        }
                    }
                    //3���� ��ģ ���
                    else if (input == 77 || input == 109) { //p2�� �� ģ ���
                        if (p2.getAvailable()) {
                            PlaySound(TEXT("ringingBell.wav"), 0, SND_FILENAME | SND_ASYNC);
                            //���� 5���϶� ���� ���
                            if (checkFiveCard(user, p1, p2, p3)) {
                                //���� ���
                                p2.plusScore();
                                //(��)���� ǥ��
                                makeAllFaceDefault(p1);
                                makeAllFaceDefault(user);
                                makeAllFaceDefault(p3);
                                makeFaceSmile(p2);
                                //���̺� ���� ī�� ��� ������
                                getAllFrontCard(p2, p1, user, p3);
                                printPlayersCardInfo(user, p1, p2, p3);
                            }
                            //�߸� ���� ���
                            else {
                                //���� ���
                                p2.minusScore();
                                //ȭ�� ǥ��, ������ �⺻ ǥ��
                                makeAllFaceDefault(p1);
                                makeAllFaceDefault(user);
                                makeAllFaceDefault(p3);
                                makeFaceAngry(p2);
                                PlaySound(TEXT("missingBell.wav"), 0, SND_FILENAME | SND_ASYNC);
                                missRinging(p2, p1, user, p3);
                                printPlayersCardInfo(user, p1, p2, p3);
                            }
                        }
                    }
                    //4���� ��ģ ���
                    else if (input == 80 || input == 112) { //p3�� �� ģ ���
                        if (p3.getAvailable()) {
                            PlaySound(TEXT("ringingBell.wav"), 0, SND_FILENAME | SND_ASYNC);
                            //���� 5���϶� ���� ���
                            if (checkFiveCard(user, p1, p2, p3)) {
                                //���� ���
                                p3.plusScore();
                                //(��)���� ǥ��
                                makeAllFaceDefault(p1);
                                makeAllFaceDefault(p2);
                                makeAllFaceDefault(user);
                                makeFaceSmile(p3);
                                //���̺� ���� ī�� ��� ������
                                getAllFrontCard(p3, p1, p2, user);
                                printPlayersCardInfo(user, p1, p2, p3);
                            }
                            //�߸� ���� ���
                            else {
                                //���� ���
                                p3.minusScore();
                                //ȭ�� ǥ��, ������ �⺻ ǥ��
                                makeAllFaceDefault(p1);
                                makeAllFaceDefault(p2);
                                makeAllFaceDefault(user);
                                makeFaceAngry(p3);
                                PlaySound(TEXT("missingBell.wav"), 0, SND_FILENAME | SND_ASYNC);
                                missRinging(p3, p1, p2, user);
                                printPlayersCardInfo(user, p1, p2, p3);
                            }
                        }
                    }
                }


                //4�� Ż�� ó��
                if (p3.getBackCount() == 0) {
                    //(��)ȭ�� ǥ��
                    makeAllFaceDefault(user);
                    makeAllFaceDefault(p1);
                    makeAllFaceDefault(p2);
                    makeFaceAngry(p3);

                    p3.setNoneAvailable();
                    printPlayersCardInfo(user, p1, p2, p3);
                    gotoxy(longInfoX + 10, longInfoY);
                    cout << p3.getPlayerNum() << "�� ����ڰ� Ż���Ǿ����ϴ�.";
                    Sleep(2000);
                    gotoxy(longInfoX + 10, longInfoY);
                    cout << "                              ";
                }
                continue;
            }
        }
    }
    while (true) {
        if (GetKeyValue() == 27)
            break;
    }
}
//���� ���� (1 vs com vs com vs com)
void StartGameAlone() {
    DrawStartGame();
    //���۹� draw
    {
        gotoxy(15, 30);
        cout << "������������������������������  ���۹� ������������������������������";
        gotoxy(15, 31);
        cout << "��                                     ��";
        gotoxy(15, 32);
        cout << "��      ī�� �ѱ�� ��  SPACE BAR      ��";
        gotoxy(15, 33);
        cout << "��                                     ��";
        gotoxy(15, 34);
        cout << "��        �� ġ��   ��  ENTER          ��";
        gotoxy(15, 35);
        cout << "��                                     ��";
        gotoxy(15, 36);
        cout << "��        ������    ��  E key          ��";
        gotoxy(15, 37);
        cout << "��                                     ��";
        gotoxy(15, 38);
        cout << "������������������������������������������������������������������������������";
    }
    //����� ����
    Player user(1), com1(2), com2(3), com3(4);
    //ī�� ������ġ,����ڿ��� ī�� �й�
    setInitCard(user, com1, com2, com3);

    //�ݺ�
    int input = 0;
    int turn = -1;
    while (true) {
        turn++;
        if (turn % 4 == 0) {
            printPlayersCardInfo(user, com1, com2, com3);
            if (!user.getAvailable()) {
                //üũ
                gotoxy(0, 0);
                cout << "����� Ż��";
                Sleep(1000);
                gotoxy(0, 0);
                cout << "                          ";
                break;
            }
            else {
                //���� ���
                gotoxy(longInfoX + 13, longInfoY - 2);
                cout << "                                        ";
                gotoxy(longInfoX + 13, longInfoY - 2);
                cout << "[ " << user.getPlayerNum() << "�� PLAYER ]";

                //ī�� �������� ���
                while (true) {
                    int input = _getch();
                    if (input == 32) break;
                }

                //ī�� ������
                if (user.open() == -1) continue;
                gotoxy(10, 14);
                frontCardPrint(user.getFrontTopCard(), user);

                //5������ Ȯ��
                if (checkFiveCard(user, com1, com2, com3)) {
                    //�κ��߿��� �������� ��ħ
                }



                input = GameKey();
                if (input == 1) {
                    PlaySound(TEXT("ringingBell.wav"), 0, SND_FILENAME | SND_ASYNC);
                    //���� 5���϶� ���� ���
                    if (checkFiveCard(user, com1, com2, com3)) {
                        //***(��)���� ǥ��
                        makeAllFaceDefault(com1);
                        makeAllFaceDefault(com2);
                        makeAllFaceDefault(com3);
                        makeFaceSmile(user);
                        //���̺� ���� ī�� ��� ������
                        getAllFrontCard(user, com1, com2, com3);
                        printPlayersCardInfo(user, com1, com2, com3);
                    }
                    //�߸� ���� ���
                    else {
                        //***ȭ�� ǥ��, ������ �⺻ ǥ��
                        makeAllFaceDefault(com1);
                        makeAllFaceDefault(com2);
                        makeAllFaceDefault(com3);
                        makeFaceAngry(user);
                        PlaySound(TEXT("missingBell.wav"), 0, SND_FILENAME | SND_ASYNC);
                        missRinging(user, com1, com2, com3);
                        printPlayersCardInfo(user, com1, com2, com3);
                    }
                }
                else if (input == 2) {
                    //�� ġ�� ����
                }
            }
            if (user.getBackCount() == 0) {
                //***ȭ�� ǥ��
                makeAllFaceDefault(com1);
                makeAllFaceDefault(com2);
                makeAllFaceDefault(com3);
                makeFaceAngry(user);
                user.setNoneAvailable();
                printPlayersCardInfo(user, com1, com2, com3);
                gotoxy(longInfoX + 10, longInfoY);
                cout << user.getPlayerNum() << "�� ����ڰ� Ż���Ǿ����ϴ�.";
                Sleep(2000);
                gotoxy(longInfoX + 10, longInfoY);
                cout << "                              ";

                //����
                int score = 0;
                int x = 20;
                int y = 17;
                gotoxy(x, y);
                cout << "��������������������������������������������������������������������������������������";
                gotoxy(x, y + 1);
                cout << "��                                         ��";
                gotoxy(x, y + 2);
                cout << "��                GAME OVER                ��";
                gotoxy(x, y + 3);
                cout << "��                                         ��";
                gotoxy(x, y + 4);
                cout << "��               score  :                  ��";
                gotoxy(x + 5, y + 4);
                cout << score;
                gotoxy(x, y + 5);
                cout << "��                                         ��";
                gotoxy(x, y + 6);
                cout << "��   ��ŷ�� �ۼ��Ͻðڽ��ϱ�?  [ Y / N ]   ��";
                gotoxy(x, y + 7);
                cout << "��                                         ��";
                gotoxy(x, y + 8);
                cout << "��������������������������������������������������������������������������������������";

                //Y �Ǵ� N ����
                while (true) {
                    if (_getch() == 89 || _getch() == 121) {
                        string userName = "";
                        gotoxy(x, y + 4);
                        cout << "��                                         ��";
                        gotoxy(x, y + 5);
                        cout << "��    �г��� �Է� :                        ��";
                        gotoxy(x, y + 6);
                        cout << "��                                         ��";
                        gotoxy(x + 12, y + 5);
                        cin >> userName;
                        gotoxy(0, 0);
                        cout << userName << endl;

                        //����� �̸�, ���� ���Ͽ� ����
                        ofstream out("database_solo.txt", ios::app);
                        //�ӽ� ����
                        out << userName << " " << score << "\n";
                        out.close();

                        //��ŷ ȭ�� draw
                        DrawRankingScreen(1);
                        break;
                    }
                    else if (_getch() == 78 || _getch() == 110) {
                        gotoxy(x, y);
                        cout << "��������������������������������������������������������������������������������������";
                        gotoxy(x, y + 1);
                        cout << "��                                         ��";
                        gotoxy(x, y + 2);
                        cout << "��                GAME OVER                ��";
                        gotoxy(x, y + 3);
                        cout << "��                                         ��";
                        gotoxy(x, y + 4);
                        cout << "��     ����� ����ȭ������ �̵��մϴ�.     ��";
                        gotoxy(x, y + 5);
                        cout << "��                                         ��";
                        gotoxy(x, y + 6);
                        cout << "��                                         ��";
                        gotoxy(x, y + 7);
                        cout << "��                                         ��";
                        gotoxy(x, y + 8);
                        cout << "��������������������������������������������������������������������������������������";
                        Sleep(2000);
                        //�������� �̵�
                        main();
                        break;
                    }
                }
                break;
            }
        }
        else if (turn % 4 == 1) {
            printPlayersCardInfo(user, com1, com2, com3);
            if (!com1.getAvailable()) {
                continue;
            }
            else {
                //���� ���
                gotoxy(longInfoX + 13, longInfoY - 2);
                cout << "                                        ";
                gotoxy(longInfoX + 13, longInfoY - 2);
                cout << "[ " << com1.getPlayerNum() << "�� PLAYER ]";

                if (com1.open() == -1) continue;
                gotoxy(20, 14);
                frontCardPrint(com1.getFrontTopCard(), com1);
                input = GameKey();
                if (input == 1) {
                    PlaySound(TEXT("ringingBell.wav"), 0, SND_FILENAME | SND_ASYNC);
                    //���� 5���϶� ���� ���
                    if (checkFiveCard(com1, user, com2, com3)) {
                        //***���� ǥ��
                        makeAllFaceDefault(user);
                        makeAllFaceDefault(com2);
                        makeAllFaceDefault(com3);
                        makeFaceSmile(com1);
                        //���̺� ���� ī�� ��� ������
                        getAllFrontCard(com1, user, com2, com3);
                        printPlayersCardInfo(user, com1, com2, com3);
                    }
                    //�߸� ���� ���
                    else {
                        //***ȭ�� ǥ��
                        makeAllFaceDefault(user);
                        makeAllFaceDefault(com2);
                        makeAllFaceDefault(com3);
                        makeFaceAngry(com1);
                        PlaySound(TEXT("missingBell.wav"), 0, SND_FILENAME | SND_ASYNC);
                        missRinging(com1, user, com2, com3);
                        printPlayersCardInfo(user, com1, com2, com3);
                    }
                }
                else {
                    //�� ġ�� ����
                }
            }
            if (com1.getBackCount() == 0) {
                //ȭ�� ǥ��
                makeAllFaceDefault(user);
                makeAllFaceDefault(com2);
                makeAllFaceDefault(com3);
                makeFaceAngry(com1);
                com1.setNoneAvailable();
                printPlayersCardInfo(user, com1, com2, com3);
                gotoxy(longInfoX + 10, longInfoY);
                cout << com1.getPlayerNum() << "�� ����ڰ� Ż���Ǿ����ϴ�.";
                Sleep(2000);
                gotoxy(longInfoX + 10, longInfoY);
                cout << "                              ";
            }
        }
        else if (turn % 4 == 2) {
            printPlayersCardInfo(user, com1, com2, com3);
            if (!com2.getAvailable()) {
                continue;
            }
            else {
                //���� ���
                gotoxy(longInfoX + 13, longInfoY - 2);
                cout << "                                        ";
                gotoxy(longInfoX + 13, longInfoY - 2);
                cout << "[ " << com2.getPlayerNum() << "�� PLAYER ]";

                if (com2.open() == -1) continue;
                gotoxy(30, 14);
                frontCardPrint(com2.getFrontTopCard(), com2);
                input = GameKey();
                if (input == 1) {
                    PlaySound(TEXT("ringingBell.wav"), 0, SND_FILENAME | SND_ASYNC);
                    //���� 5���϶� ���� ���
                    if (checkFiveCard(com2, user, com1, com3)) {
                        //***���� ǥ��
                        makeAllFaceDefault(user);
                        makeAllFaceDefault(com1);
                        makeAllFaceDefault(com3);
                        makeFaceSmile(com2);
                        //���̺� ���� ī�� ��� ������
                        getAllFrontCard(com2, user, com1, com3);
                        printPlayersCardInfo(user, com1, com2, com3);
                    }
                    //�߸� ���� ���
                    else {
                        //ȭ�� ǥ��
                        makeAllFaceDefault(user);
                        makeAllFaceDefault(com1);
                        makeAllFaceDefault(com3);
                        makeFaceAngry(com2);
                        PlaySound(TEXT("missingBell.wav"), 0, SND_FILENAME | SND_ASYNC);
                        missRinging(com2, user, com1, com3);
                        printPlayersCardInfo(user, com1, com2, com3);
                    }
                }
                else {
                    //�� ġ�� ����
                }
            }
            if (com2.getBackCount() == 0) {
                //***ȭ�� ǥ��
                makeAllFaceDefault(user);
                makeAllFaceDefault(com1);
                makeAllFaceDefault(com3);
                makeFaceAngry(com2);
                com2.setNoneAvailable();
                printPlayersCardInfo(user, com1, com2, com3);
                gotoxy(longInfoX + 10, longInfoY);
                cout << com2.getPlayerNum() << "�� ����ڰ� Ż���Ǿ����ϴ�.";
                Sleep(2000);
                gotoxy(longInfoX + 10, longInfoY);
                cout << "                              ";
            }
        }
        else if (turn % 4 == 3) {
            printPlayersCardInfo(user, com1, com2, com3);
            if (!com3.getAvailable()) {
                continue;
            }
            else {
                //���� ���
                gotoxy(longInfoX + 13, longInfoY - 2);
                cout << "                                        ";
                gotoxy(longInfoX + 13, longInfoY - 2);
                cout << "[ " << com3.getPlayerNum() << "�� PLAYER ]";

                if (com3.open() == -1) continue;
                gotoxy(40, 14);
                frontCardPrint(com3.getFrontTopCard(), com3);
                input = GameKey();
                if (input == 1) {
                    PlaySound(TEXT("ringingBell.wav"), 0, SND_FILENAME | SND_ASYNC);
                    //���� 5���϶� ���� ���
                    if (checkFiveCard(com3, com1, com2, user)) {
                        //***(��)���� ǥ��
                        makeAllFaceDefault(user);
                        makeAllFaceDefault(com1);
                        makeAllFaceDefault(com2);
                        makeFaceSmile(com3);

                        //���̺� ���� ī�� ��� ������
                        getAllFrontCard(com3, com1, com2, user);
                        printPlayersCardInfo(user, com1, com2, com3);
                    }
                    //�߸� ���� ���
                    else {
                        //***(��)ȭ�� ǥ��
                        makeAllFaceDefault(user);
                        makeAllFaceDefault(com1);
                        makeAllFaceDefault(com2);
                        makeFaceAngry(com3);
                        //�� �ο����� ī�� �ϳ��� ��, ī��� ������ �� Ż��
                        PlaySound(TEXT("missingBell.wav"), 0, SND_FILENAME | SND_ASYNC);
                        missRinging(com3, com1, com2, user);
                        printPlayersCardInfo(user, com1, com2, com3);
                    }
                }
                else {
                    //�� ġ�� ����
                }
            }
            if (com3.getBackCount() == 0) {
                //***(��)ȭ�� ǥ��
                makeAllFaceDefault(user);
                makeAllFaceDefault(com1);
                makeAllFaceDefault(com2);
                makeFaceAngry(com3);

                com3.setNoneAvailable();
                printPlayersCardInfo(user, com1, com2, com3);
                gotoxy(longInfoX + 10, longInfoY);
                cout << com3.getPlayerNum() << "�� ����ڰ� Ż���Ǿ����ϴ�.";
                Sleep(2000);
                gotoxy(longInfoX + 10, longInfoY);
                cout << "                              ";
            }
        }
        //���� ������ (��������)
        if (GetKeyValue() == 27) break;
    }


    while (true) {
        if (GetKeyValue() == 27)
            break;
    }
}
//���� ���� ��� ����
int ChoosePlaying() {

    DrawChoosePlaying();

    int result = 0;
    int x = 20 + 11;
    int y = 21;
    gotoxy(x, y);
    while (true) {
        int num = _getch();
        switch (num)
        {
            //��
        case 72: {
            if (y == 23) {
                gotoxy(x - 2, y);
                printf("  ");
                gotoxy(x - 2, y -= 2);
                printf(">>");
            }
            break;
        }
               //�Ʒ�
        case 80: {
            if (y == 21) {
                gotoxy(x - 2, y);
                printf("  ");
                gotoxy(x - 2, y += 2);
                printf(">>");
            }
            break;
        }
               //enter
        case 13:
            result = y - 21; //0 �Ǵ� 2
            return result;
            //exit
        case 27:
            ReadyGame();
            break;
        }
    }
}
//���� ����
void ShowInfo()
{
    DrawInfoScreen();
    while (true) {
        if (_getch() == 27)
            break;
    }
}
//����
int main(void)
{
    //�ּܼ���
    SetConsoleView();
    //Ŀ�� ����
    CursorView();
    int menuValue = -1;

    while (true)
    {
        menuValue = ReadyGame();    //0 : ����, 2 : ���ӽ���, 4 :��������
        if (menuValue == 0) {       //rule
            ShowInfo();
        }
        else if (menuValue == 2) {    //���� ��� ��
            int res = ChoosePlaying();
            if (res == 0) StartGameAlone(); //0 : ȥ���ϱ�, 2 : 4���� �ϱ�
            else if (res == 2) StartGameMulti();
            else exit(1);
        }
        else {
            exit(1);
        }
        system("cls");
    }
    return 0;
}