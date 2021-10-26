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
#define PURPLE      (RED | BLUE | BLUE)
#define WHITE       (RED | GREEN | BLUE)
#define CARDCOUNT 20*4
#define CARD1X 5
#define CARD2X 15
#define CARD3X 25
#define CARD4X 35
#define CARDY 12


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


//ȭ��ε� draw
void DrawLoading() {

}
//ùȭ�� draw
void DrawIntro()
{
    HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
    int x = 9;
    PrintString(hStdOut, WHITE);
    system("cls");
    gotoxy(x, 4);
    cout << "##   ##    ##     ####     ####      ####               ####     ##     ####     ####      ####";
    gotoxy(x, 5);
    cout << "##   ##   ####     ##       ##        ##               ##  ##   ####     ##       ##        ##";
    gotoxy(x, 6);
    cout << "##   ##  ##  ##    ##       ##        ##              ##       ##  ##    ##       ##        ##";
    gotoxy(x, 7);
    cout << "#######  ##  ##    ##       ##        ##              ##       ##  ##    ##       ##        ##";
    gotoxy(x, 8);
    cout << "##   ##  ######    ##   #   ##   #    ##              ##  ###  ######    ##   #   ##   #    ##";
    gotoxy(x, 9);
    cout << "##   ##  ##  ##    ##  ##   ##  ##    ##               ##  ##  ##  ##    ##  ##   ##  ##    ##";
    gotoxy(x, 10);
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
    gotoxy(28, 29);
    cout << "�� Game Rule for 'r'";
    gotoxy(28, 31);
    cout << "�� Game Start for 's'";
    gotoxy(28, 33);
    cout << "�� Exit for 'e'";
}
//����ȭ�� draw
void DrawStartGame()
{
    //120 41
    system("cls");

    //ī�� 1
    gotoxy(CARD1X, CARDY);
    cout << "��������������������������������";
    for (int i = CARDY+1; i < CARDY+12; i++) {
        gotoxy(CARD1X, i);
        cout << "��              ��";
    }
    gotoxy(CARD1X, CARDY + 12);
    cout << "��������������������������������";

    //ī�� 2
    gotoxy(CARD2X, CARDY);
    cout << "��������������������������������";
    for (int i = CARDY+1; i < CARDY+12; i++) {
        gotoxy(CARD2X, i);
        cout << "��              ��";
    }
    gotoxy(CARD2X, CARDY+12);
    cout << "��������������������������������";

    //ī�� 3
    gotoxy(CARD3X, CARDY);
    cout << "��������������������������������";
    for (int i = CARDY+1; i < CARDY+12; i++) {
        gotoxy(CARD3X, i);
        cout << "��              ��";
    }
    gotoxy(CARD3X, CARDY+12);
    cout << "��������������������������������";

    //ī�� 4
    gotoxy(CARD4X, CARDY);
    cout << "��������������������������������";
    for (int i = CARDY+1; i < CARDY+12; i++) {
        gotoxy(CARD4X, i);
        cout << "��              ��";
    }
    gotoxy(CARD4X, CARDY+12);
    cout << "��������������������������������";

    for (int i = 0; i < 45; i++) {
        gotoxy(48, i);
        cout << "��";
    }

    gotoxy(15,30);
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


    //����� ���� ����
    gotoxy(57, 4);
    cout << "Player 1";
    gotoxy(50, 3);
    cout << "����������������������";
    gotoxy(50, 4);
    cout << "��  ��  �� ��";
    gotoxy(50, 5);
    cout << "��  ��  �� ��";
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



//[����� ���� ���� �޼���]
void makeFaceSmile(Player& player) {
    int x=50, y;
    switch (player.getPlayerNum()){
    case 1: y = 5; break;
    case 2: y = 15; break;
    case 3: y = 25; break;
    case 4: y = 35; break;
    }
    gotoxy(x, y);
    cout << "��  >  < ��";
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
    cout << "��  \\  / ��"; //��������
}
void makeAllFaceDefault(Player& player) {
    int x = 50, y;
    switch (player.getPlayerNum()) {
    case 1: 
        gotoxy(x,5);
        cout << "��  ��  �� ��";
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

    for (int i = 0; i < CARDCOUNT / 4 ; ++i)
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
    //���̺� ī�� �ʱ�ȭ
    emptyCardPrint(winner,looser1,looser2,looser3);
}
//[�Ǻ�] �� �߸����� ��� - �� player���� ī�� ���徿 back�� �ѱ�
void missRinging(Player& looser, Player& winner1, Player& winner2, Player& winner3) {
    //cout << "���� �߸������Ƿ� ī�带 �������ݴϴ�." << endl;
    //�÷��� ������ �ο� �� ����
    int cnt = 0;
    if (looser.getAvailable()) cnt++;
    if (winner1.getAvailable()) cnt++;
    if (winner2.getAvailable()) cnt++;
    if (winner3.getAvailable()) cnt++;
    //back ī�尡 ���� ���,������ ��� Ż��
    if (looser.backIsEmpty() || looser.getBackCount() < cnt - 1) {
        //cout << "��뿡�� �� ī�尡 �����Ͽ� Ż���Ǿ����ϴ�." << endl;
        looser.setNoneAvailable();
        gotoxy(0,1);
        cout << "Ż��ó����" << endl;
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
    ////ī�带 �� �Ŀ� ī�尡 ���� ��� Ż��
    //if (looser.backIsEmpty()) {
    //   // cout << "ī�带 �ְ� ���� ī�尡 ���� Ż���Ǿ����ϴ�." << endl;
    //    looser.setNoneAvailable();
    //}
    return;
}


//�޴�����
int ReadyGame()
{
    //����ȭ�� �׸���
    DrawIntro();
    while (true) {
        //Ű�� �޾ƿ���
        int key = _getch();
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

//���� ī�� && ���̺� ī�� ���
void printPlayersCardInfo(Player &p1,Player &p2,Player &p3,Player &p4) {
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
        gotoxy(0, 0);
        cout << (int)user.getAvailable() + (int)p1.getAvailable() + (int)p2.getAvailable() + (int)p3.getAvailable() << endl;
        if ((int)user.getAvailable() + (int)p1.getAvailable() + (int)p2.getAvailable() + (int)p3.getAvailable() == 1) {
            //����ȭ��
            //DrawRankingScreen();
            cout << "End" << endl;
            break;
        }

        turn++;
        if (turn % 4 == 0) {
            printPlayersCardInfo(user, p1, p2, p3);
            if (!user.getAvailable()) {
                continue;
            }
            else {
                if (user.open() == -1) continue;
                gotoxy(10, 14);
                frontCardPrint(user.getFrontTopCard(),user);
                input = GameKey();
                if (input == 1) {
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
                    //�� ġ�� ����
                }
            }
            if (user.getBackCount() == 0) {
                gotoxy(0, 1);
                cout << "Ż��" << endl;
                user.setNoneAvailable();
                printPlayersCardInfo(user, p1, p2, p3);
            }
        }
        else if (turn % 4 == 1) {
            printPlayersCardInfo(user, p1, p2, p3);
            if (!p1.getAvailable()) {
                continue;
            }
            else {
                if (p1.open() == -1) continue;
                gotoxy(20, 14);
                frontCardPrint(p1.getFrontTopCard(),p1);
                input = GameKey();
                if (input == 1) {
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
                    //�� ġ�� ����
                }
            }
            if (p1.getBackCount() == 0) {
                gotoxy(0, 1);
                cout << "Ż��" << endl;
                p1.setNoneAvailable();
                printPlayersCardInfo(user, p1, p2, p3);
            }
        }
        else if (turn % 4 == 2) {
            printPlayersCardInfo(user, p1, p2, p3);
            if (!p2.getAvailable()) {
                continue;
            }
            else {
                if (p2.open() == -1) continue;
                gotoxy(30, 14);
                frontCardPrint(p2.getFrontTopCard(),p2);
                input = GameKey();
                if (input == 1) {
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
                    //�� ġ�� ����
                }
            }
            if (p2.getBackCount() == 0) {
                gotoxy(0, 1);
                cout << "Ż��" << endl;
                p2.setNoneAvailable();
                printPlayersCardInfo(user, p1, p2, p3);
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
                frontCardPrint(p3.getFrontTopCard(),p3);
                input = GameKey();
                if (input == 1) {
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
                    //�� ġ�� ����
                }
            }
            if (p3.getBackCount() == 0) {
                gotoxy(0, 1);
                cout << "Ż��" << endl;
                p3.setNoneAvailable();
                printPlayersCardInfo(user, p1, p2, p3);
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
        if (_getch() == 27)
            break;
    }
}
////���� ����
//void GameSetting() {
//    DrawGameSetting();
//
//}
//void DrawGameSetting() {
//    HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
//    system("cls");
//    cout << "���� �÷��� ���� ȭ��" << endl;
//}
//����
int main(void)
{
    //�ּܼ���
    SetConsoleView(); 
    int menuValue = -1;
    while (true)
    {
        menuValue = ReadyGame();    //��Ʈ��, Ű �Է�
        if (menuValue == 1) {       //rule
            ShowInfo();
        }
        else if (menuValue == 2) {    //start
            //GameSetting();
            StartGame();
        }
        else {
            exit(1);
        }
        system("cls");
    }
    return 0;
}