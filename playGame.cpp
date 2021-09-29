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
    //³½ Ä«µå
    stack<Card> front;
    //³»Áö ¾ÊÀº Ä«µå
    stack<Card> back;
    //ÇÃ·¹ÀÌ¾î ¹øÈ£
    int playerNum;
public:
    int getPlayerNum() {
        return playerNum;
    }
    //ÃÊ¹Ý Ä«µå ¼ö ÁöÁ¤
    Player(int num) {
        playerNum = num;
    }
    //µÚÁýÀº Ä«µå½ºÅÃÀÇ °¡Àå À§ Ä«µå ¹ÝÈ¯
    Card getFrontTopCard() {
        if (front.empty()) return Card();
        return front.top();
    }
    //µÚÁýÁö ¾ÊÀº Ä«µå½ºÅÃÀÇ °¡Àå À§ Ä«µå ¹ÝÈ¯
    Card getBackTopCard() {
        if (back.empty()) return Card();
        return back.top();
    }
    //µÚÁýÀº/µÚÁýÁö ¾ÊÀº Ä«µåÀÇ ¼ýÀÚ ¹ÝÈ¯
    int getFrontCount() {
        return front.size();
    }
    int getBackCount() {
        return back.size();
    }
    //Ä«µå Ãß°¡
    void pushBack(const Card& card) {
        front.push(card);
    }
    void pushFront(const Card& card) {
        back.push(card);
    }
    //Ä«µå ÀÒÀ½¤¤
    void popBack() {
        front.pop();
    }
    void popFront() {
        back.pop();
    }
    //back -> front Ä«µå µÚÁýÀ½
    int open() {
        if (back.empty()) {
            return -1;
        }
        pushFront(getBackTopCard());
        popBack();
        return 0;
    }
};


//ºó Ä«µå
void emptyCardPrint() {
    cout << "                                               "
        << "¦®¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¯" << endl;
    for (int i = 0; i < 7; ++i)
        cout << "                                               "
        << "¦­           ¦­" << endl;

    cout << "                                               "
        << "¦±¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦°" << endl;
}

//¾Õ¿¡ ÀÖ´Â Ä«µå ³¿
void frontCardPrint(Card card) {
    //Ä«µå Å¸ÀÔ
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
            << "¦®¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¯" << endl;
        cout << "                                               "
            << "¦­           ¦­" << endl;
        cout << "                                               "
            << "¦­           ¦­" << endl;
        cout << "                                               "
            << "¦­           ¦­" << endl;
        cout << "                                               "
            << "¦­     " << fruit << "     ¦­" << endl;
        cout << "                                               "
            << "¦­           ¦­" << endl;
        cout << "                                               "
            << "¦­           ¦­" << endl;
        cout << "                                               "
            << "¦­           ¦­" << endl;
        cout << "                                               "
            << "¦±¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦°" << endl;
        break;
    case 2:
        cout << "                                               "
            << "¦®¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¯" << endl;
        cout << "                                               "
            << "¦­           ¦­" << endl;
        cout << "                                               "
            << "¦­           ¦­" << endl;
        cout << "                                               "
            << "¦­     " << fruit << "     ¦­" << endl;
        cout << "                                               "
            << "¦­           ¦­" << endl;
        cout << "                                               "
            << "¦­     " << fruit << "     ¦­" << endl;
        cout << "                                               "
            << "¦­           ¦­" << endl;
        cout << "                                               "
            << "¦­           ¦­" << endl;
        cout << "                                               "
            << "¦±¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦°" << endl;
        break;
    case 3:
        cout << "                                               "
            << "¦®¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¯" << endl;
        cout << "                                               "
            << "¦­           ¦­" << endl;
        cout << "                                               "
            << "¦­           ¦­" << endl;
        cout << "                                               "
            << "¦­     " << fruit << "     ¦­" << endl;
        cout << "                                               "
            << "¦­           ¦­" << endl;
        cout << "                                               "
            << "¦­   " << fruit << "   " << fruit << "   ¦­" << endl;
        cout << "                                               "
            << "¦­           ¦­" << endl;
        cout << "                                               "
            << "¦­           ¦­" << endl;
        cout << "                                               "
            << "¦±¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦°" << endl;
        break;
    case 4:
        cout << "                                               "
            << "¦®¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¯" << endl;
        cout << "                                               "
            << "¦­           ¦­" << endl;
        cout << "                                               "
            << "¦­   " << fruit << "   " << fruit << "   ¦­" << endl;
        cout << "                                               "
            << "¦­           ¦­" << endl;
        cout << "                                               "
            << "¦­           ¦­" << endl;
        cout << "                                               "
            << "¦­           ¦­" << endl;
        cout << "                                               "
            << "¦­   " << fruit << "   " << fruit << "   ¦­" << endl;
        cout << "                                               "
            << "¦­           ¦­" << endl;
        cout << "                                               "
            << "¦±¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦°" << endl;
        break;
    case 5:
        cout << "                                               "
            << "¦®¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¯" << endl;
        cout << "                                               "
            << "¦­           ¦­" << endl;
        cout << "                                               "
            << "¦­   " << fruit << "   " << fruit << "   ¦­" << endl;
        cout << "                                               "
            << "¦­           ¦­" << endl;
        cout << "                                               "
            << "¦­     " << fruit << "     ¦­" << endl;
        cout << "                                               "
            << "¦­           ¦­" << endl;
        cout << "                                               "
            << "¦­   " << fruit << "   " << fruit << "   ¦­" << endl;
        cout << "                                               "
            << "¦­           ¦­" << endl;
        cout << "                                               "
            << "¦±¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦°" << endl;
        break;
    default:
        emptyCardPrint();
    }
}


//ÄÜ¼Ö ¼¼ÆÃ
void SetConsoleView();
//Ä¿¼­ÀÌµ¿ ÇÔ¼ö
void gotoxy(int x, int y);
//keyboard ÀÔ·Â°ª ¹ÝÈ¯ÇÔ
int GetKeyValue();
//»ö»óÁöÁ¤
void PrintString(HANDLE hStdOut, WORD Attribute);
//È­¸é·Îµù draw
void DrawLoading();
//½ÃÀÛÈ­¸é draw
void DrawIntro();
//°ÔÀÓÈ­¸é draw
void DrawStartGame();
//¼³¸íÈ­¸é draw
void DrawInfoScreen();
//[°ÔÀÓÁøÇà] Ä«µåºÐ¹è
void setInitCard(Player& p1, Player& p2, Player& p3, Player& p4);
//¸Þ´º¼±ÅÃ
int ReadyGame();
//°ÔÀÓ ÁøÇà Å°
int GameKey();
//°ÔÀÓ ½ÃÀÛ
void StartGame();
//°ÔÀÓ ¼³¸í
void ShowInfo();
//¸ÞÀÎ
int main(void);


//Ä«µå
Card cards[CARDCOUNT] = { //°úÀÏº° Ä«µå 20Àå (1:6,2:5,3:4,4:3,5:2)
    //»ç°ú
    Card(1,1),Card(1,1),Card(1,1),Card(1,1),Card(1,1),
    Card(1,1),Card(1,2),Card(1,2),Card(1,2),Card(1,2),
    Card(1,2),Card(1,3),Card(1,3),Card(1,3),Card(1,3),
    Card(1,4),Card(1,4),Card(1,4),Card(1,5),Card(1,5),
    //¹Ù³ª³ª
    Card(2,1),Card(2,1),Card(2,1),Card(2,1),Card(2,1),
    Card(2,1),Card(2,2),Card(2,2),Card(2,2),Card(2,2),
    Card(2,2),Card(2,3),Card(2,3),Card(2,3),Card(2,3),
    Card(2,4),Card(2,4),Card(2,4),Card(2,5),Card(2,5),
    //¹è
    Card(3,1),Card(3,1),Card(3,1),Card(3,1),Card(3,1),
    Card(3,1),Card(3,2),Card(3,2),Card(3,2),Card(3,2),
    Card(3,2),Card(3,3),Card(3,3),Card(3,3),Card(3,3),
    Card(3,4),Card(3,4),Card(3,4),Card(3,5),Card(3,5),
    //Ã¼¸®
    Card(4,1),Card(4,1),Card(4,1),Card(4,1),Card(4,1),
    Card(4,1),Card(4,2),Card(4,2),Card(4,2),Card(4,2),
    Card(4,2),Card(4,3),Card(4,3),Card(4,3),Card(4,3),
    Card(4,4),Card(4,4),Card(4,4),Card(4,5),Card(4,5),
};
//ÄÜ¼Ö ¼¼ÆÃ
void SetConsoleView()
{
    system("mode con cols=120 lines=41 | title Halli Galli");   //È­¸éÅ©±â,°ÔÀÓÀÌ¸§
}
//Ä¿¼­ÀÌµ¿ ÇÔ¼ö
void gotoxy(int x, int y)
{
    COORD Pos;
    Pos.X = 2 * x;
    Pos.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}
//keyboard ÀÔ·Â°ª ¹ÝÈ¯ÇÔ
int GetKeyValue()
{
    if (_kbhit() != 0) {
        return _getch();
    }
    return 0;
}
//»ö»óÁöÁ¤
void PrintString(HANDLE hStdOut, WORD Attribute)
{
    SetConsoleTextAttribute(hStdOut, Attribute);
}
//È­¸é·Îµù draw
void DrawLoading() {

}
//½ÃÀÛÈ­¸é draw
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
    cout << "¡Ý";
    gotoxy(29, 21);
    cout << "/¡«";
    PrintString(hStdOut, RED);
    gotoxy(28, 22);
    cout << "¢É¢É¢É";
    gotoxy(27, 23);
    cout << "¢É¢É¢É¢É";
    gotoxy(27, 24);
    cout << "¢É¢É¢É¢É¢É¢É¢É";
    gotoxy(28, 25);
    cout << "¢É¢É¢É¢É";


    PrintString(hStdOut, WHITE);
    gotoxy(24, 28);
    cout << "¢º Game Rule for 'r'";
    gotoxy(24, 30);
    cout << "¢º Game Start for 's'";
    gotoxy(24, 32);
    cout << "¢º Exit for 'e'";
}
//°ÔÀÓÈ­¸é draw
void DrawStartGame()
{
    //120 41
    system("cls");

    //ÇÃ·¹ÀÌ¾î 1 (»ç¿ëÀÚ) (¿ÞÂÊ »ó´Ü)
    gotoxy(0, 0);
    cout << "¢É¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¢É";
    for (int i = 1; i < 7; i++) {
        gotoxy(0, i);
        cout << "¦­              ¦­";
    }
    gotoxy(0, 7);
    cout << "¢É¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¢É";
    gotoxy(0, 8);
    cout << "º¸À¯ Ä«µå ¼ö : " << " Àå";
    gotoxy(0, 9);
    cout << "ÆÇ¿¡ ³õÀÎ Ä«µå ¼ö : " << " Àå";

    //ÇÃ·¹ÀÌ¾î 2 (¿À¸¥ÂÊ »ó´Ü)
    gotoxy(51, 0);
    cout << "¢É¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¢É";
    for (int i = 1; i < 7; i++) {
        gotoxy(51, i);
        cout << "¦­              ¦­";
    }
    gotoxy(51, 7);
    cout << "¢É¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¢É";
    gotoxy(48, 8);
    cout << "º¸À¯ Ä«µå ¼ö : " << " Àå";
    gotoxy(48, 9);
    cout << "ÆÇ¿¡ ³õÀÎ Ä«µå ¼ö : " << " Àå";

    //ÇÃ·¹ÀÌ¾î 3 (¿ÞÂÊ ÇÏ´Ü)
    gotoxy(0, 30);
    cout << "º¸À¯ Ä«µå ¼ö : " << " Àå";
    gotoxy(0, 31);
    cout << "ÆÇ¿¡ ³õÀÎ Ä«µå ¼ö : " << " Àå";
    gotoxy(0, 32);
    cout << "¢É¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¢É";
    for (int i = 33; i < 40; i++) {
        gotoxy(0, i);
        cout << "¦­              ¦­";
    }
    gotoxy(0, 40);
    cout << "¢É¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¢É";


    //ÇÃ·¹ÀÌ¾î 4 (¿À¸¥ÂÊ ÇÏ´Ü)
    gotoxy(48, 30);
    cout << "º¸À¯ Ä«µå ¼ö : " << " Àå";
    gotoxy(48, 31);
    cout << "ÆÇ¿¡ ³õÀÎ Ä«µå ¼ö : " << " Àå";
    gotoxy(51, 32);
    cout << "¢É¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¢É";
    for (int i = 33; i < 40; i++) {
        gotoxy(51, i);
        cout << "¦­              ¦­";
    }
    gotoxy(51, 40);
    cout << "¢É¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¢É";


    //Ä«µå 1
    gotoxy(10, 14);
    cout << "¦£¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¤";
    for (int i = 15; i < 25; i++) {
        gotoxy(10, i);
        cout << "¦¢              ¦¢";
    }
    gotoxy(10, 25);
    cout << "¦¦¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¥";

    //Ä«µå 2
    gotoxy(20, 14);
    cout << "¦£¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¤";
    for (int i = 15; i < 25; i++) {
        gotoxy(20, i);
        cout << "¦¢              ¦¢";
    }
    gotoxy(20, 25);
    cout << "¦¦¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¥";

    //Ä«µå 3
    gotoxy(30, 14);
    cout << "¦£¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¤";
    for (int i = 15; i < 25; i++) {
        gotoxy(30, i);
        cout << "¦¢              ¦¢";
    }
    gotoxy(30, 25);
    cout << "¦¦¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¥";

    //Ä«µå 4
    gotoxy(40, 14);
    cout << "¦£¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¤";
    for (int i = 15; i < 25; i++) {
        gotoxy(40, i);
        cout << "¦¢              ¦¢";
    }
    gotoxy(40, 25);
    cout << "¦¦¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¥";


}
//¼³¸íÈ­¸é draw
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
            cout << "¡í                                                                                                    ¡í";
        }
    }
    gotoxy(3, 19);
    cout << "¡í¡í¡í¡í¡í¡í¡í¡í¡í¡í¡í¡í¡í¡í¡í¡í¡í¡í¡í¡í¡í¡í¡í¡í¡í¡í¡í¡í¡í¡í¡í¡í¡í¡í¡í¡í¡í¡í¡í¡í¡í¡í¡í¡í¡í¡í¡í¡í¡í¡í¡í¡í";
    gotoxy(3, 21);
    cout << "¡í  ¡× ±âº» ÁøÇà¹æ¹ýÀº º¸µå°ÔÀÓ 'ÇÒ¸®°¥¸®'¿Í µ¿ÀÏÇÕ´Ï´Ù.                                              ¡í";
    gotoxy(3, 23);
    cout << "¡í  ¡× Ä«µå¸¦ ¸ðµÎ ÀÒÀ¸¸é Å»¶ô, ³¡±îÁö ³²Àº »ç¶÷ÀÌ ½Â¸®ÇÏ°Ô µË´Ï´Ù.                                   ¡í";
    gotoxy(3, 25);
    cout << "¡í  ¡× ÃÑ 4¸íÀÇ ÇÃ·¹ÀÌ¾î°¡ ÀÖÀ¸¸ç, °¢ ÇÃ·¹ÀÌ¾î¿¡°Ô 28ÀåÀÇ Ä«µå°¡ ÁÖ¾îÁý´Ï´Ù.                          ¡í";
    gotoxy(3, 27);
    cout << "¡í  ¡× ¼ø¼­¿¡ µû¶ó 'space'·Î Ä«µå¸¦ µÚÁý½À´Ï´Ù.                                                       ¡í";
    gotoxy(3, 29);
    cout << "¡í  ¡× ¾ÕÀÇ ³õÀÎ Ä«µåÀÇ °úÀÏ ¼ö°¡ 5°³°¡ µÇ¸é 'enter'·Î Á¾À» Ä¨´Ï´Ù.                                   ¡í";
    gotoxy(3, 31);
    cout << "¡í  ¡× °¡Àå »¡¸® Á¾À» Ä£ »ç¶÷ÀÌ ¾ÕÀÇ Ä«µå¸¦ ¸ðµÎ °¡Á®°©´Ï´Ù.                                          ¡í";
    gotoxy(3, 33);
    cout << "¡í  ¡× ¸¸ÀÏ 5°³°¡ ¾Æ´Ñ »óÅÂ¿¡¼­ Á¾À» Ä¡¸é, ³ª¸ÓÁö ÇÃ·¹ÀÌ¾î¿¡°Ô Ä«µå¸¦ 1Àå¾¿ ¹Ý³³ÇÕ´Ï´Ù.               ¡í";
    gotoxy(3, 35);
    cout << "¡í  ¡× ¶Ç ¾Õ¿¡ ³ª¿Í ÀÖ´ø Ä«µå´Â ´ÙÀ½ ÅÏÀ¸·Î ³Ñ¾î°©´Ï´Ù.                                               ¡í";
    gotoxy(3, 37);
    cout << "¡í  ¡× Ä«µå¸¦ ¸ðµÎ »ç¿ëÇÑ ÇÃ·¹ÀÌ¾î´Â Áï½Ã Å»¶ôÃ³¸®µË´Ï´Ù.                   ¡× ³ª°¡±â : esc           ¡í";
    gotoxy(3, 39);
    cout << "¡í¡í¡í¡í¡í¡í¡í¡í¡í¡í¡í¡í¡í¡í¡í¡í¡í¡í¡í¡í¡í¡í¡í¡í¡í¡í¡í¡í¡í¡í¡í¡í¡í¡í¡í¡í¡í¡í¡í¡í¡í¡í¡í¡í¡í¡í¡í¡í¡í¡í¡í¡í";

}


//[°ÔÀÓÁøÇà] Ä«µåºÐ¹è
void setInitCard(Player& p1, Player& p2, Player& p3, Player& p4) {
    srand((unsigned int)time(NULL));
    
 
    
    
    //°¢ ÇÃ·¹ÀÌ¾î¿¡°Ô Ä«µå ºÐ¹è
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




//¸Þ´º¼±ÅÃ
int ReadyGame()
{
    //½ÃÀÛÈ­¸é ±×¸®±â
    DrawIntro();
    while (true) {
        //Å°°ª ¹Þ¾Æ¿À±â
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
//°ÔÀÓ ÁøÇà Å°
int GameKey()
{
    while (true) {
        //Å°°ª ¹Þ¾Æ¿À±â (Á¾Ä¡±â : 1, Ä«µå ³»±â : 2, ³ª°¡±â : 0)
        int key = GetKeyValue();
        if (key == '\n') {         //Á¾Ä¡±â = 1 (enter)
            return 1;
        }
        else if (key == ' ') {    //Ä«µå ³»±â = 2 (space)
            return 2;
        }
        else if (key == 'e' || key == 'E') {    //exit = 0 (esc)
            break;
        }
    }
    return 0;
}
//°ÔÀÓ ½ÃÀÛ
void StartGame()
{
    DrawStartGame();
    int keyValue = GameKey();

    //°¢ »ç¿ëÀÚ °´Ã¼ »ý¼º
    Player user(1);
    Player com1(2), com2(3), com3(4);
    //°¢ »ç¿ëÀÚ Ä«µå ºÐ¹è
    setInitCard(user, com1, com2, com3);
    int turn = 1;


    /* while (true) {






         turn++;
     }*/

     //switch (keyValue) {
     //    //Á¾Ä¡±â
     //case 1:
     //    break;
     //    //Ä«µå ³»±â
     //case 2:
     //    break;
     //    //°ÔÀÓ Á¾·á
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
//°ÔÀÓ ¼³¸í
void ShowInfo()
{
    DrawInfoScreen();
    while (true) {
        if (GetKeyValue() == 27)
            break;
    }
}
//¸ÞÀÎ
int main(void)
{
    SetConsoleView(); //ÄÜ¼Ö¼³Á¤
    int menuValue = -1;
    while (true)
    {
        menuValue = ReadyGame();    //ÀÎÆ®·Î, Å° ÀÔ·Â
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