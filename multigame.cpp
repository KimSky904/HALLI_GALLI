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
//蘋萄 謝ル
#define CARDCOUNT 20*4
#define CARD1X 5
#define CARD2X 15
#define CARD3X 25
#define CARD4X 35
#define CARDY 12
//撲貲 謝ル
#define longInfoX 8
#define longInfoY 7

//夔樂 撮た
void SetConsoleView()
{
    system("mode con cols=135 lines=45 | title Halli Galli");   //�飛橝店�,啪歜檜葷
}
//醴憮檜翕 л熱
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
//keyboard 殮溘高 奩�納�
int GetKeyValue()
{
    if (_kbhit() != 0) {
        return _getch();
    }
    return 0;
}
//儀鼻雖薑
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
    //轎溘
    void getInfo() {
        cout << "[ " << type << " , " << num << " ]";
    }
};

class Player {
    //魚 蘋萄
    stack<Card> front;
    //頂雖 彊擎 蘋萄
    stack<Card> back;
    //Ы溯檜橫 廓��
    int playerNum;
    //Ы溯檜 陛棟 罹睡
    bool available;
    //薄熱
    int score;
public:
    //薄熱 �僱�
    void plusScore() {
        score += 20;
    }
    //薄熱 梗歜
    void minusScore() {
        score -= 20;
    }
    //薄熱 奩��
    int getScore() {
        return score;
    }
    //模資濠
    ~Player() {};
    //驍塊籀葬
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
        cout << "[驍塊] Player " << playerNum;
    }
    //Ы溯檜 陛棟 罹睡
    bool getAvailable() {
        return available;
    }
    //轎溘
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
    //蟾奩 蘋萄 熱 雖薑
    Player(int num) {
        playerNum = num;
        available = true;
        score = 0;
    }
    //菴餵擎 蘋萄蝶鷗曖 陛濰 嬪 蘋萄 奩��
    Card getFrontTopCard() {
        if (front.empty()) return Card();
        return front.top();
    }
    //菴餵雖 彊擎 蘋萄蝶鷗曖 陛濰 嬪 蘋萄 奩��
    Card getBackTopCard() {
        return back.top();
    }
    //菴餵擎/菴餵雖 彊擎 蘋萄曖 璋濠 奩��
    int getFrontCount() {
        return front.size();
    }
    int getBackCount() {
        return back.size();
    }
    //蘋萄 蹺陛
    void pushBack(const Card& card) {
        back.push(card);
    }
    void pushFront(const Card& card) {
        front.push(card);
    }
    //蘋萄 檠擠中
    void popBack() {
        back.pop();
    }
    void popFront() {
        front.pop();
    }
    //back -> front 蘋萄 菴餵擠
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


//蘋萄
Card cards[CARDCOUNT] = {
    //餌婁
    Card(1,1),Card(1,1),Card(1,1),Card(1,1),Card(1,1),
    Card(1,1),Card(1,2),Card(1,2),Card(1,2),Card(1,2),
    Card(1,2),Card(1,3),Card(1,3),Card(1,3),Card(1,3),
    Card(1,4),Card(1,4),Card(1,4),Card(1,5),Card(1,5),
    //夥釭釭
    Card(2,1),Card(2,1),Card(2,1),Card(2,1),Card(2,1),
    Card(2,1),Card(2,2),Card(2,2),Card(2,2),Card(2,2),
    Card(2,2),Card(2,3),Card(2,3),Card(2,3),Card(2,3),
    Card(2,4),Card(2,4),Card(2,4),Card(2,5),Card(2,5),
    //寡
    Card(3,1),Card(3,1),Card(3,1),Card(3,1),Card(3,1),
    Card(3,1),Card(3,2),Card(3,2),Card(3,2),Card(3,2),
    Card(3,2),Card(3,3),Card(3,3),Card(3,3),Card(3,3),
    Card(3,4),Card(3,4),Card(3,4),Card(3,5),Card(3,5),
    //羹葬
    Card(4,1),Card(4,1),Card(4,1),Card(4,1),Card(4,1),
    Card(4,1),Card(4,2),Card(4,2),Card(4,2),Card(4,2),
    Card(4,2),Card(4,3),Card(4,3),Card(4,3),Card(4,3),
    Card(4,4),Card(4,4),Card(4,4),Card(4,5),Card(4,5),
};



//夔樂 撮た
void SetConsoleView();
//醴憮檜翕 л熱
void gotoxy(int x, int y);
//keyboard 殮溘高 奩�納�
int GetKeyValue();
//儀鼻雖薑
void PrintString(HANDLE hStdOut, WORD Attribute);
//[�飛� DRAW]
//檣お煎 �飛� draw
void DrawIntro();
//啪歜 �飛� draw
void DrawStartGame();
//撲貲 �飛� draw
void DrawInfoScreen();
//縛註 �飛� draw
void DrawRankingScreen();


//[餌辨濠 鼻鷓 滲唳 詭憮萄]
void makeFaceSmile(Player& player);
void makeFaceAngry(Player& player);
void makeAllFaceDefault(Player& player);

//[蘋萄 轎溘 詭憮萄]
//綴 蘋萄 轎溘
void emptyCardPrint(Player& player);
//瞪羹 綴 蘋萄 轎溘
void emptyCardPrint(Player& one, Player& two, Player& three, Player& four);
//纔檜綰煎 魚 蘋萄 轎溘
void frontCardPrint(Card& card, Player& player);

//[蘋萄 褻濛 詭憮萄]
//餌辨濠縑啪 蘋萄 楠渾 碟寡
int* makeRandArr(int size);
void setInitCard(Player& p1, Player& p2, Player& p3, Player& p4);
//[Ring] 賅萇 front 蝓濠曖 back戲煎 檜翕
void getAllFrontCard(Player& winner, Player& looser1, Player& looser2, Player& looser3);
//[MissRing] 陝 player縑啪 и濰噶 back戲煎 檜翕
void missRinging(Player& p1, Player& p2, Player& p3, Player& p4);

//[蘋萄 っ滌 詭憮萄]
//婁橾 熱 5偃 っ滌
bool checkFiveCard(Player& user, Player& p1, Player& p2, Player& p3);

//[蘋萄 薑爾 轎溘 詭憮萄]
//爾嶸 蘋萄 && 纔檜綰 蘋萄 轎溘
void printPlayersCardInfo(Player& p1, Player& p2, Player& p3, Player& p4);

//[詭景 摹鷗]
int ReadyGame();
//[啪歜 霞ч 酈]
int GameKey();
//[啪歜 衛濛]
int main();
void StartGameAlone();
void StartGameMulti();
//[啪歜 撲貲]
void ShowInfo();

//----------------------------[蘋萄 轎溘 詭憮萄]----------------------------
//綴 蘋萄
void emptyCardPrint(Player& player) {
    //蘋萄 轎溘 嬪纂
    int x;
    int y = CARDY;
    switch (player.getPlayerNum()) {
    case 1: x = CARD1X; break;
    case 2: x = CARD2X; break;
    case 3: x = CARD3X; break;
    case 4: x = CARD4X; break;
    }
    gotoxy(x, y);
    cout << "旨收收收收收收收收收收收收收收旬";
    for (int i = 0; i < 10; ++i) {
        gotoxy(x, y + i);
        cout << "早           早";
    }
    gotoxy(x, y + 7);
    cout << "曲收收收收收收收收收收收收收收旭" << endl;
}
//瞪羹 綴 蘋萄 轎溘
void emptyCardPrint(Player& one, Player& two, Player& three, Player& four) {
    //蘋萄 轎溘 嬪纂
    int x;
    int y = CARDY;
    //1
    x = CARD1X;
    gotoxy(x, y);
    cout << "旨收收收收收收收收收收收收收收旬";
    for (int i = 0; i < 11; ++i) {
        gotoxy(x, y + i + 1);
        cout << "早              早";
    }
    gotoxy(x, y + 12);
    cout << "曲收收收收收收收收收收收收收收旭" << endl;
    //2
    x = CARD2X;
    gotoxy(x, y);
    cout << "旨收收收收收收收收收收收收收收旬";
    for (int i = 0; i < 11; ++i) {
        gotoxy(x, y + i + 1);
        cout << "早              早";
    }
    gotoxy(x, y + 12);
    cout << "曲收收收收收收收收收收收收收收旭" << endl;
    //3
    x = CARD3X;
    gotoxy(x, y);
    cout << "旨收收收收收收收收收收收收收收旬";
    for (int i = 0; i < 11; ++i) {
        gotoxy(x, y + i + 1);
        cout << "早              早";
    }
    gotoxy(x, y + 12);
    cout << "曲收收收收收收收收收收收收收收旭" << endl;
    //4
    x = CARD4X;
    gotoxy(x, y);
    cout << "旨收收收收收收收收收收收收收收旬";
    for (int i = 0; i < 11; ++i) {
        gotoxy(x, y + i + 1);
        cout << "早              早";
    }
    gotoxy(x, y + 12);
    cout << "曲收收收收收收收收收收收收收收旭" << endl;
}
//擅縑 氈朝 蘋萄 鹵
void frontCardPrint(Card card, Player player) {
    HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
    //蘋萄 顫殮
    int type = card.getType();
    char fruit = 'e';
    int Color = RED;
    switch (type) {
    case 1: fruit = '@';
        //PrintString(hStdOut, RED);
        Color = RED;
        break; //餌婁
    case 2: fruit = '@';
        //PrintString(hStdOut, YELLOW);
        Color = YELLOW;
        break; //夥釭釭
    case 3: fruit = '@';
        //PrintString(hStdOut, GREEN);
        Color = GREEN;
        break; //塭歜
    case 4: fruit = '@';
        //PrintString(hStdOut, RED);
        Color = PURPLE;
        break; //ん紫
    }
    //蘋萄 轎溘 嬪纂
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
        cout << "忙式式式式式式式式式式式式式式忖" << endl;
        gotoxy(x, y + 1);
        cout << "弛              弛" << endl;
        gotoxy(x, y + 2);
        cout << "弛              弛" << endl;
        gotoxy(x, y + 3);
        cout << "弛              弛" << endl;
        gotoxy(x, y + 4);
        cout << "弛              弛" << endl;
        gotoxy(x, y + 5);
        cout << "弛              弛" << endl;
        gotoxy(x, y + 6);
        PrintString(hStdOut, WHITE);
        cout << "弛       ";
        PrintString(hStdOut, Color);
        cout << fruit;
        PrintString(hStdOut, WHITE);
        cout << "      弛" << endl;
        gotoxy(x, y + 7);
        cout << "弛              弛" << endl;
        gotoxy(x, y + 8);
        cout << "弛              弛" << endl;
        gotoxy(x, y + 9);
        cout << "弛              弛" << endl;
        gotoxy(x, y + 10);
        cout << "弛              弛" << endl;
        gotoxy(x, y + 11);
        cout << "弛              弛" << endl;
        gotoxy(x, y + 12);
        cout << "戌式式式式式式式式式式式式式式戎" << endl;
        break;
    case 2:
        gotoxy(x, y);
        cout << "忙式式式式式式式式式式式式式式忖" << endl;
        gotoxy(x, y + 1);
        cout << "弛              弛" << endl;
        gotoxy(x, y + 2);
        cout << "弛              弛" << endl;
        gotoxy(x, y + 3);
        PrintString(hStdOut, WHITE);
        cout << "弛       ";
        PrintString(hStdOut, Color);
        cout << fruit;
        PrintString(hStdOut, WHITE);
        cout << "      弛" << endl;
        gotoxy(x, y + 4);
        cout << "弛              弛" << endl;
        gotoxy(x, y + 5);
        cout << "弛              弛" << endl;
        gotoxy(x, y + 6);
        cout << "弛              弛" << endl;
        gotoxy(x, y + 7);
        cout << "弛              弛" << endl;
        gotoxy(x, y + 8);
        cout << "弛              弛" << endl;
        gotoxy(x, y + 9);
        PrintString(hStdOut, WHITE);
        cout << "弛       ";
        PrintString(hStdOut, Color);
        cout << fruit;
        PrintString(hStdOut, WHITE);
        cout << "      弛" << endl;
        gotoxy(x, y + 10);
        cout << "弛              弛" << endl;
        gotoxy(x, y + 11);
        cout << "弛              弛" << endl;
        gotoxy(x, y + 12);
        cout << "戌式式式式式式式式式式式式式式戎" << endl;
        break;
    case 3:
        gotoxy(x, y);
        cout << "忙式式式式式式式式式式式式式式忖" << endl;
        gotoxy(x, y + 1);
        cout << "弛              弛" << endl;
        gotoxy(x, y + 2);
        cout << "弛              弛" << endl;
        gotoxy(x, y + 3);
        PrintString(hStdOut, WHITE);
        cout << "弛    ";
        PrintString(hStdOut, Color);
        cout << fruit;
        PrintString(hStdOut, WHITE);
        cout << "         弛" << endl;
        gotoxy(x, y + 4);
        cout << "弛              弛" << endl;
        gotoxy(x, y + 5);
        cout << "弛              弛" << endl;
        gotoxy(x, y + 6);
        PrintString(hStdOut, WHITE);
        cout << "弛       ";
        PrintString(hStdOut, Color);
        cout << fruit;
        PrintString(hStdOut, WHITE);
        cout << "      弛" << endl;
        gotoxy(x, y + 7);
        cout << "弛              弛" << endl;
        gotoxy(x, y + 8);
        cout << "弛              弛" << endl;
        gotoxy(x, y + 9);
        PrintString(hStdOut, WHITE);
        cout << "弛          ";
        PrintString(hStdOut, Color);
        cout << fruit;
        PrintString(hStdOut, WHITE);
        cout << "   弛" << endl;
        gotoxy(x, y + 10);
        cout << "弛              弛" << endl;
        gotoxy(x, y + 11);
        cout << "弛              弛" << endl;
        gotoxy(x, y + 12);
        cout << "戌式式式式式式式式式式式式式式戎" << endl;
        break;
    case 4:
        gotoxy(x, y);
        cout << "忙式式式式式式式式式式式式式式忖" << endl;
        gotoxy(x, y + 1);
        cout << "弛              弛" << endl;
        gotoxy(x, y + 2);
        cout << "弛              弛" << endl;
        gotoxy(x, y + 3);
        PrintString(hStdOut, WHITE);
        cout << "弛    ";
        PrintString(hStdOut, Color);
        cout << fruit << "     " << fruit;
        PrintString(hStdOut, WHITE);
        cout << "   弛" << endl;
        gotoxy(x, y + 4);
        cout << "弛              弛" << endl;
        gotoxy(x, y + 5);
        cout << "弛              弛" << endl;
        gotoxy(x, y + 6);
        cout << "弛              弛" << endl;
        gotoxy(x, y + 7);
        cout << "弛              弛" << endl;
        gotoxy(x, y + 8);
        cout << "弛              弛" << endl;
        gotoxy(x, y + 9);
        PrintString(hStdOut, WHITE);
        cout << "弛    ";
        PrintString(hStdOut, Color);
        cout << fruit << "     " << fruit;
        PrintString(hStdOut, WHITE);
        cout << "   弛" << endl;
        gotoxy(x, y + 10);
        cout << "弛              弛" << endl;
        gotoxy(x, y + 11);
        cout << "弛              弛" << endl;
        gotoxy(x, y + 12);
        cout << "戌式式式式式式式式式式式式式式戎" << endl;
        break;
    case 5:
        gotoxy(x, y);
        cout << "忙式式式式式式式式式式式式式式忖" << endl;
        gotoxy(x, y + 1);
        cout << "弛              弛" << endl;
        gotoxy(x, y + 2);
        cout << "弛              弛" << endl;
        gotoxy(x, y + 3);
        PrintString(hStdOut, WHITE);
        cout << "弛    ";
        PrintString(hStdOut, Color);
        cout << fruit << "     " << fruit;
        PrintString(hStdOut, WHITE);
        cout << "   弛" << endl;
        gotoxy(x, y + 4);
        cout << "弛              弛" << endl;
        gotoxy(x, y + 5);
        cout << "弛              弛" << endl;
        gotoxy(x, y + 6);
        PrintString(hStdOut, WHITE);
        cout << "弛       ";
        PrintString(hStdOut, Color);
        cout << fruit;
        PrintString(hStdOut, WHITE);
        cout << "      弛" << endl;
        gotoxy(x, y + 7);
        cout << "弛              弛" << endl;
        gotoxy(x, y + 8);
        cout << "弛              弛" << endl;
        gotoxy(x, y + 9);
        PrintString(hStdOut, WHITE);
        cout << "弛    ";
        PrintString(hStdOut, Color);
        cout << fruit << "     " << fruit;
        PrintString(hStdOut, WHITE);
        cout << "   弛" << endl;
        gotoxy(x, y + 10);
        cout << "弛              弛" << endl;
        gotoxy(x, y + 11);
        cout << "弛              弛" << endl;
        gotoxy(x, y + 12);
        cout << "戌式式式式式式式式式式式式式式戎" << endl;
        break;
    }
}


//羅�飛� draw
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
//啪歜�飛� draw
void DrawStartGame()
{
    //120 41
    system("cls");

    //蘋萄 1
    gotoxy(CARD1X, CARDY);
    cout << "忙式式式式式式式式式式式式式式忖";
    for (int i = CARDY + 1; i < CARDY + 12; i++) {
        gotoxy(CARD1X, i);
        cout << "弛              弛";
    }
    gotoxy(CARD1X, CARDY + 12);
    cout << "戌式式式式式式式式式式式式式式戎";

    //蘋萄 2
    gotoxy(CARD2X, CARDY);
    cout << "忙式式式式式式式式式式式式式式忖";
    for (int i = CARDY + 1; i < CARDY + 12; i++) {
        gotoxy(CARD2X, i);
        cout << "弛              弛";
    }
    gotoxy(CARD2X, CARDY + 12);
    cout << "戌式式式式式式式式式式式式式式戎";

    //蘋萄 3
    gotoxy(CARD3X, CARDY);
    cout << "忙式式式式式式式式式式式式式式忖";
    for (int i = CARDY + 1; i < CARDY + 12; i++) {
        gotoxy(CARD3X, i);
        cout << "弛              弛";
    }
    gotoxy(CARD3X, CARDY + 12);
    cout << "戌式式式式式式式式式式式式式式戎";

    //蘋萄 4
    gotoxy(CARD4X, CARDY);
    cout << "忙式式式式式式式式式式式式式式忖";
    for (int i = CARDY + 1; i < CARDY + 12; i++) {
        gotoxy(CARD4X, i);
        cout << "弛              弛";
    }
    gotoxy(CARD4X, CARDY + 12);
    cout << "戌式式式式式式式式式式式式式式戎";

    for (int i = 0; i < 45; i++) {
        gotoxy(48, i);
        cout << "弛";
    }

    //餌辨濠 鼻鷓 薑爾
    gotoxy(57, 4);
    cout << "Player 1";
    gotoxy(50, 3);
    cout << "忙式式式式式式式式式忖";
    gotoxy(50, 4);
    cout << "弛  ÷  ÷ 弛";
    gotoxy(50, 5);
    cout << "弛   =  =  弛";
    gotoxy(50, 6);
    cout << "弛         弛";
    gotoxy(50, 7);
    cout << "弛    √   弛";
    gotoxy(50, 8);
    cout << "戌式式式式式式式式式戎";


    gotoxy(57, 14);
    cout << "Player 2";
    gotoxy(50, 13);
    cout << "忙式式式式式式式式式忖";
    gotoxy(50, 14);
    cout << "弛  ÷  ÷ 弛";
    gotoxy(50, 15);
    cout << "弛  ㏑  ㏑ 弛";
    gotoxy(50, 16);
    cout << "弛         弛";
    gotoxy(50, 17);
    cout << "弛    ↙   弛";
    gotoxy(50, 18);
    cout << "戌式式式式式式式式式戎";

    gotoxy(57, 24);
    cout << "Player 3";
    gotoxy(50, 23);
    cout << "忙式式式式式式式式式忖";
    gotoxy(50, 24);
    cout << "弛  ÷  ÷ 弛";
    gotoxy(50, 25);
    cout << "弛  天  天 弛";
    gotoxy(50, 26);
    cout << "弛         弛";
    gotoxy(50, 27);
    cout << "弛    ↙   弛";
    gotoxy(50, 28);
    cout << "戌式式式式式式式式式戎";

    gotoxy(57, 34);
    cout << "Player 4";
    gotoxy(50, 33);
    cout << "忙式式式式式式式式式忖";
    gotoxy(50, 34);
    cout << "弛  ÷  ÷ 弛";
    gotoxy(50, 35);
    cout << "弛  ＜  ＜ 弛";
    gotoxy(50, 36);
    cout << "弛         弛";
    gotoxy(50, 37);
    cout << "弛    ↙   弛";
    gotoxy(50, 38);
    cout << "戌式式式式式式式式式戎";

}
//縛註�飛� draw
void DrawRankingScreen(int gameType) {
    //135 45
    HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
    system("cls");

    //掘褻羹
    struct players {
        char name[20];
        int score;
        int rank;
    } pl[10];
    FILE* fp1;

    //Multi
    if (gameType == 0) {
        //だ橾縑憮 檗橫褥
        while (true) {
            fopen_s(&fp1, "database.txt", "r");
            if (fp1 == NULL) {
                gotoxy(0, 0);
                cout << "だ橾檜 襄營ж雖 彊蝗棲棻." << endl;
            }
            else break;
        }
    }
    //Solo
    else {
        //だ橾縑憮 檗橫褥
        while (true) {
            fopen_s(&fp1, "database_solo.txt", "r");
            if (fp1 == NULL) {
                gotoxy(0, 0);
                cout << "だ橾檜 襄營ж雖 彊蝗棲棻." << endl;
            }
            else break;
        }
    }

    for (int i = 0; i < 10; i++) {
        fscanf_s(fp1, "%s", pl[i].name, 20);
        fscanf_s(fp1, "%d", &(pl[i].score));
    }
    fclose(fp1);


    //牖嬪 盪濰
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
    cout << "忙式式式式式式式式 [  RANKING  ]式式式式式式式式忖 ";
    for (int i = 1; i <= 10; i++) {
        for (int j = 0; j < 10; j++) {
            if (pl[j].rank == i) {
                gotoxy(x, ++y);
                cout << "弛                              弛";
                gotoxy(x, ++y);
                if (pl[j].score == 0) {
                    PrintString(hStdOut, WHITE);
                    printf("弛               -              弛");
                }
                else {
                    switch (i) {
                    case 1:
                        PrintString(hStdOut, WHITE);
                        cout << "弛  ";
                        PrintString(hStdOut, YELLOW);
                        printf("%2d     %10s    %4d", pl[j].rank, pl[j].name, pl[j].score);
                        PrintString(hStdOut, WHITE);
                        cout << "   弛";
                        break;
                    case 2:
                        PrintString(hStdOut, WHITE);
                        cout << "弛  ";
                        PrintString(hStdOut, 7);
                        printf("%2d     %10s    %4d", pl[j].rank, pl[j].name, pl[j].score);
                        PrintString(hStdOut, WHITE);
                        cout << "   弛";
                        break;
                    case 3:
                        PrintString(hStdOut, WHITE);
                        cout << "弛  ";
                        PrintString(hStdOut, 6);
                        printf("%2d     %10s    %4d", pl[j].rank, pl[j].name, pl[j].score);
                        PrintString(hStdOut, WHITE);
                        cout << "   弛";
                        break;
                    default:
                        PrintString(hStdOut, WHITE);
                        printf("弛  %2d     %10s    %4d   弛", pl[j].rank, pl[j].name, pl[j].score);
                    }
                }

            }
        }
    }
    gotoxy(x, y + 1);
    cout << "弛                              弛";
    gotoxy(x, y + 2);
    cout << "戌式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式戎 ";


    //餌辨濠 score 蛔蛔
    x = 32;
    y = 8;
    gotoxy(x, y);
    cout << "忙式式式式式式式式式式式式式 [  INFO  ]式式式式式式式式式式式式忖 ";
    gotoxy(x, y + 1);
    cout << "弛                                    弛";
    gotoxy(x, y + 2);
    cout << "弛                                    弛";
    gotoxy(x, y + 3);
    cout << "弛                                    弛";
    gotoxy(x, y + 4);
    cout << "弛                                    弛";
    gotoxy(x, y + 5);
    cout << "弛                                    弛";
    gotoxy(x, y + 6);
    cout << "弛                                    弛";
    gotoxy(x, y + 7);
    cout << "弛                                    弛";
    gotoxy(x, y + 8);
    cout << "弛                                    弛";
    gotoxy(x, y + 9);
    cout << "弛                                    弛";
    gotoxy(x, y + 10);
    cout << "戌式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式戎 ";

    gotoxy(x, y + 12);
    cout << "忙式式式式式式式式 [  DEVELOPE  INFO  ]式式式式式式式忖 ";
    gotoxy(x, y + 13);
    cout << "弛                                    弛";
    gotoxy(x, y + 14);
    cout << "弛    latest change    2021.10.30     弛";
    gotoxy(x, y + 15);
    cout << "弛                                    弛";
    gotoxy(x, y + 16);
    cout << "弛    name                 梯ж棺     弛";
    gotoxy(x, y + 17);
    cout << "弛                                    弛";
    gotoxy(x, y + 18);
    cout << "弛    sch    嘐葡罹濠薑爾婁з堅蛔з掖 弛";
    gotoxy(x, y + 19);
    cout << "弛                                    弛";
    gotoxy(x, y + 20);
    cout << "弛    eml    KimCloud52@gmail.com     弛";
    gotoxy(x, y + 21);
    cout << "弛                                    弛";
    gotoxy(x, y + 22);
    cout << "戌式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式戎 ";

}
//撲貲�飛� draw
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
            cout << "∮                                                                                                    ∮";
        }
    }
    gotoxy(3, 19);
    cout << "∮∮∮∮∮∮∮∮∮∮∮∮∮∮∮∮∮∮∮∮∮∮∮∮∮∮∮∮∮∮∮∮∮∮∮∮∮∮∮∮∮∮∮∮∮∮∮∮∮∮∮∮";
    gotoxy(3, 21);
    cout << "∮  ＝ 晦獄 霞ч寞徹擎 爾萄啪歜 'й葬陞葬'諦 翕橾м棲棻.                                              ∮";
    gotoxy(3, 23);
    cout << "∮  ＝ 蘋萄蒂 賅舒 檠戲賊 驍塊, 部梱雖 陴擎 餌塋檜 蝓葬ж啪 腌棲棻.                                   ∮";
    gotoxy(3, 25);
    cout << "∮  ＝ 識 4貲曖 Ы溯檜橫陛 氈戲貊, 陝 Ы溯檜橫縑啪 20濰曖 蘋萄陛 輿橫餵棲棻.                          ∮";
    gotoxy(3, 27);
    cout << "∮  ＝ 1貲 傳朝 4貲檜 Ы溯檜й 熱 氈蝗棲棻. 晦獄 翕濛擎 褻濛徹擊 鱔п 憲溥萄董棲棻.                   ∮";
    gotoxy(3, 29);
    cout << "∮  ＝ 纔檜綰縑 場檣 蘋萄曖 婁橾 熱陛 5偃陛 腎賊 '雖薑 酈'煎 謙擊 蘑棲棻.                             ∮";
    gotoxy(3, 31);
    cout << "∮  ＝ 陛濰 說葬 謙擊 耀 餌塋檜 擅曖 蘋萄蒂 賅舒 陛螳骨棲棻.                                          ∮";
    gotoxy(3, 33);
    cout << "∮  ＝ 虜橾 5偃陛 嬴棋 鼻鷓縑憮 謙擊 纂賊, 釭該雖 Ы溯檜橫縑啪 蘋萄蒂 1濰噶 釭援橫鄹棲棻.             ∮";
    gotoxy(3, 35);
    cout << "∮  ＝ 蹺陛 蕨薑                                                                                      ∮";
    gotoxy(3, 37);
    cout << "∮  ＝ 蘋萄蒂 賅舒 餌辨и Ы溯檜橫朝 闊衛 驍塊籀葬腌棲棻.                   ＝ 釭陛晦 : esc           ∮";
    gotoxy(3, 39);
    cout << "∮∮∮∮∮∮∮∮∮∮∮∮∮∮∮∮∮∮∮∮∮∮∮∮∮∮∮∮∮∮∮∮∮∮∮∮∮∮∮∮∮∮∮∮∮∮∮∮∮∮∮∮";

}



//[餌辨濠 ル薑 滲唳 詭憮萄]
void makeFaceSmile(Player& player) {
    int x = 50, y;
    switch (player.getPlayerNum()) {
    case 1: y = 5; break;
    case 2: y = 15; break;
    case 3: y = 25; break;
    case 4: y = 35; break;
    }
    gotoxy(x, y);
    cout << "弛   >  <  弛";
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
    cout << "弛  厄  厄 弛";
}
void makeAllFaceDefault(Player& player) {
    int x = 50, y;
    switch (player.getPlayerNum()) {
    case 1:
        gotoxy(x, 5);
        cout << "弛   =  =  弛";
        break;
    case 2:
        gotoxy(x, 15);
        cout << "弛  ㏑  ㏑ 弛";
        break;
    case 3:
        gotoxy(x, 25);
        cout << "弛  天  天 弛";
        break;
    case 4:
        gotoxy(x, 35);
        cout << "弛  ＜  ＜ 弛";
        break;
    }
}


//[蘋萄褻濛] 餌辨濠縑啪 蘋萄 碟寡
int* makeRandArr(int size) {
    int* arr = new int[size] { 0, };
    int* chk = new int[size] { 0, };
    int cnt = 0;

    srand((unsigned int)time(NULL));

    while (cnt < size) {
        int r = rand() % size;      // 0 ~ size 陪熱 儅撩
        if (!chk[r]) {              // 檜嘐 鉻�� 瞳檜 橈朝 璋濠賊
            ++chk[r], arr[cnt] = r; // 羹觼 �� shuffle 寡翮縑 蹺陛
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

//[っ滌] 婁橾 熱 5偃 っ滌
bool checkFiveCard(Player& user, Player& p1, Player& p2, Player& p3) {
    //陝 婁橾縑 渠и 偃熱 寡翮
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
//[っ滌] 謙蟻擊 唳辦 - 賅萇 front蒂 蝓濠曖 back戲煎 檜翕
void getAllFrontCard(Player& winner, Player& looser1, Player& looser2, Player& looser3) {
    //濠褐檜 魚 蘋萄 �蜈�
    int cnt1 = winner.getFrontCount();
    for (int i = 0; i < cnt1; i++) {
        winner.pushBack(winner.getFrontTopCard());
        winner.popFront();
    }
    //釭該雖 餌辨濠 蘋萄 �蜈�
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
    //纔檜綰 蘋萄 蟾晦��
    emptyCardPrint(winner, looser1, looser2, looser3);
    //撲貲 轎溘
    gotoxy(longInfoX + 4, longInfoY);
    cout << winner.getPlayerNum() << "廓 Ы溯檜橫陛 謙擊 蟻蝗棲棻. 纔檜綰曖 賅萇 蘋萄 �僱�!";
    Sleep(2000);
    gotoxy(longInfoX, longInfoY);
    cout << "                                                                          ";
}
//[っ滌] 謙 澀跤蟻擊 唳辦 - 陝 player縑啪 蘋萄 и濰噶 back縑 剩梯
void missRinging(Player& looser, Player& winner1, Player& winner2, Player& winner3) {
    //Ы溯檜 陛棟и 檣錳 熱 撮晦
    int cnt = 0;
    if (looser.getAvailable()) cnt++;
    if (winner1.getAvailable()) cnt++;
    if (winner2.getAvailable()) cnt++;
    if (winner3.getAvailable()) cnt++;
    //back 蘋萄陛 橈擊 唳辦,睡褶и 唳辦 驍塊
    if (looser.backIsEmpty() || looser.getBackCount() < cnt - 1) {
        looser.setNoneAvailable();
        //撲貲 轎溘
        gotoxy(longInfoX + 6, longInfoY);
        cout << looser.getPlayerNum() << "廓 Ы溯檜橫朝 蘋萄陛 睡褶ж罹 驍塊腎歷蝗棲棻.";
        Sleep(2000);
        gotoxy(longInfoX + 6, longInfoY);
        cout << "                                                      ";
        return;
    }
    //啪歜Ы溯檜 陛棟и 檣錳 蘋萄 釭散輿晦
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
    //撲貲 轎溘
    gotoxy(longInfoX, longInfoY);
    cout << looser.getPlayerNum() << "廓 Ы溯檜橫陛 謙擊 澀跤蟻蝗棲棻. 陝 檣錳縑啪 蘋萄蒂 釭援橫鄹棲棻.";
    Sleep(2000);
    gotoxy(longInfoX, longInfoY);
    cout << "                                                                          ";
    return;
}


//詭景摹鷗
int ReadyGame()
{
    //衛濛�飛� 斜葬晦
    DrawIntro();
    int result = 0;
    int x = 31;
    int y = 30;
    gotoxy(x, y);
    while (true) {
        int num = _getch();
        switch (num)
        {
            //嬪
        case 72: {
            if (y > 30) {
                gotoxy(x - 2, y);
                printf("  ");
                gotoxy(x - 2, y -= 2);
                printf(">>");
            }
            break;
        }
               //嬴楚
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
            result = y - 30; //0 傳朝 2 傳朝 4
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
//啪歜 霞ч 酈
int GameKey()
{
    while (true) {
        //酈高 嫡嬴螃晦 (謙纂晦 : 1, 蘋萄 頂晦 : 2, 釭陛晦 : 0)
        int key = _getch();
        if (key == 13) {         //謙纂晦 = 1 (enter)
            return 1;
        }
        else if (key == 32) {    //蘋萄 頂晦 = 2 (space)
            return 2;
        }
        else if (key == 27) {    //exit = 0 (esc)
            return 3;
        }
    }
    return 0;
}

//爾嶸 蘋萄 && 纔檜綰 蘋萄 轎溘
void printPlayersCardInfo(Player& p1, Player& p2, Player& p3, Player& p4) {

    gotoxy(57, 6);
    cout << "纔檜綰蘋萄 熱 : " << p1.getFrontCount() << "  ";
    gotoxy(57, 7);
    cout << "模嶸蘋萄 熱 : " << p1.getBackCount() << "  ";

    gotoxy(57, 16);
    cout << "纔檜綰蘋萄 熱 : " << p2.getFrontCount() << "  ";
    gotoxy(57, 17);
    cout << "模嶸蘋萄 熱 : " << p2.getBackCount() << "  ";

    gotoxy(57, 26);
    cout << "纔檜綰蘋萄 熱 : " << p3.getFrontCount() << "  ";
    gotoxy(57, 27);
    cout << "模嶸蘋萄 熱 : " << p3.getBackCount() << "  ";

    gotoxy(57, 36);
    cout << "纔檜綰蘋萄 熱 : " << p4.getFrontCount() << "  ";
    gotoxy(57, 37);
    cout << "模嶸蘋萄 熱 : " << p4.getBackCount() << "  ";
}

void DrawChoosePlaying() {
    system("cls");

    int x = 20;
    int y = 17;
    gotoxy(x, y);
    cout << "忙式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式忖";
    gotoxy(x, y + 1);
    cout << "弛                                               弛";
    gotoxy(x, y + 2);
    cout << "弛               啪歜 霞ч 寞衝 摹鷗             弛";
    gotoxy(x, y + 3);
    cout << "弛                                               弛";
    gotoxy(x, y + 4);
    cout << "弛                 >>  1 Players                 弛";
    gotoxy(x, y + 5);
    cout << "弛                                               弛";
    gotoxy(x, y + 6);
    cout << "弛                     4 Players                 弛";
    gotoxy(x, y + 7);
    cout << "弛                                               弛";
    gotoxy(x, y + 8);
    cout << "戌式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式戎";


}
//驍塊檣雖 �挫�
void checkPlayerNoneAble(Player& user, Player& p1, Player& p2, Player& p3) {
    if (user.getBackCount() == 0) {
        //�韋� ル薑
        makeAllFaceDefault(p1);
        makeAllFaceDefault(p2);
        makeAllFaceDefault(p3);
        makeFaceAngry(user);
        user.setNoneAvailable();
        printPlayersCardInfo(user, p1, p2, p3);
        gotoxy(longInfoX + 10, longInfoY);
        cout << user.getPlayerNum() << "廓 餌辨濠陛 驍塊腎歷蝗棲棻.";
        Sleep(2000);
        gotoxy(longInfoX + 10, longInfoY);
        cout << "                              ";
    }
}

//啪歜 衛濛 (1 vs 1 vs 1 vs 1)
void StartGameMulti()
{
    //4貲檜 Ы溯檜й 唳辦(蘋萄 剩晦晦/謙纂晦) : qw  xc  nm  op
    DrawStartGame();
    //褻濛徹 draw
    {
        int x = 12;
        gotoxy(x, 30);
        cout << "忙式式式式式式式式式式式  褻濛徹 ( NEXT / BELL ) 式式式式式式式式式式忖";
        gotoxy(x, 31);
        cout << "弛                                              弛";
        gotoxy(x, 32);
        cout << "弛           Player 1   Ⅰ   Q  /  W            弛";
        gotoxy(x, 33);
        cout << "弛                                              弛";
        gotoxy(x, 34);
        cout << "弛           Player 2   Ⅰ   X  /  C            弛";
        gotoxy(x, 35);
        cout << "弛                                              弛";
        gotoxy(x, 36);
        cout << "弛           Player 3   Ⅰ   N  /  M            弛";
        gotoxy(x, 37);
        cout << "弛                                              弛";
        gotoxy(x, 38);
        cout << "弛           Player 4   Ⅰ   O  /  P            弛";
        gotoxy(x, 39);
        cout << "弛                                              弛";
        gotoxy(x, 40);
        cout << "戌式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式戎";
    }
    //餌辨濠 儅撩
    Player user(1), p1(2), p2(3), p3(4);
    //蘋萄 楠渾寡纂,餌辨濠縑啪 蘋萄 碟寡
    setInitCard(user, p1, p2, p3);
    //奩犒
    int input = 0;
    int turn = -1;
    //瞪 欽啗縑憮 謙蟻朝雖, 蘋萄剩啣朝雖 �挫�
    boolean pushOk = false;
    while (true) {
        // (1:1:1:1) и貲曖 Ы溯檜橫虜 陴懊擊 唳辦
        if ((int)user.getAvailable() + (int)p1.getAvailable() + (int)p2.getAvailable() + (int)p3.getAvailable() == 1) {
            string winnerName = "";
            if (user.getAvailable() == 1) winnerName = "Player 1";
            else if (p1.getAvailable() == 1) winnerName = "Player 2";
            else if (p2.getAvailable() == 1) winnerName = "Player 3";
            else if (p3.getAvailable() == 1) winnerName = "Player 4";
            //唸婁�飛�
            {
                int x = 20;
                int y = 17;
                gotoxy(x, y);
                cout << "忙式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式忖";
                gotoxy(x, y + 1);
                cout << "弛                                         弛";
                gotoxy(x, y + 2);
                cout << "弛                GAME OVER                弛";
                gotoxy(x, y + 3);
                cout << "弛                                         弛";
                gotoxy(x, y + 4);
                cout << "弛             winner :  " << winnerName << "          弛";
                gotoxy(x, y + 5);
                cout << "弛                                         弛";
                gotoxy(x, y + 6);
                cout << "弛     濡衛�� 詭檣�飛橉虞� 檜翕м棲棻.     弛";
                gotoxy(x, y + 7);
                cout << "弛                                         弛";
                gotoxy(x, y + 8);
                cout << "戌式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式戎";

                Sleep(5000);
                main();
                break;
            }
        }
        turn++;
        //1廓 離滔
        if (turn % 4 == 0) {
            //棻擠 欐戲煎 剩橫陛朝 酈 雖薑
            int nextKey1 = 88, nextKey2 = 120;
            printPlayersCardInfo(user, p1, p2, p3);
            if (!user.getAvailable()) {
                continue;
            }
            else {
                //Player 1 : 蘋萄 頂晦 Q, 謙纂晦 W (81,113 / 87,119)
                //羹觼
                gotoxy(0, 0);
                cout << "1廓 離滔";
                //撲貲 轎溘
                gotoxy(longInfoX + 13, longInfoY - 2);
                cout << "                                        ";
                gotoxy(longInfoX + 13, longInfoY - 2);
                cout << "[ " << user.getPlayerNum() << "廓 PLAYER ]";


                //瞪 欐縑憮 蘋萄頂晦陛 檜嘐 揚溜朝雖 �挫�
                if (pushOk == false) {
                    while (true) {
                        int value = _getch();
                        if (value == 81 || value == 113) break;
                    }
                }

                //蘋萄 菴餵晦
                if (user.open() == -1) continue;
                frontCardPrint(user.getFrontTopCard(), user);
                printPlayersCardInfo(user, p1, p2, p3);

                //棻擠欐 轎溘
                gotoxy(longInfoX + 13, longInfoY - 2);
                cout << "                                        ";
                gotoxy(longInfoX + 13, longInfoY - 2);
                cout << "[ " << p1.getPlayerNum() << "廓 PLAYER ]";

                //棻擠 欐 摹熱曖 酈高 掘ж晦 (驍塊濠 陽僥)
                if (!p1.getAvailable()) {
                    nextKey1 = 78, nextKey2 = 110;
                    gotoxy(longInfoX + 13, longInfoY - 2);
                    cout << "                                        ";
                    gotoxy(longInfoX + 13, longInfoY - 2);
                    cout << "[ " << p2.getPlayerNum() << "廓 PLAYER ]";
                    if (!p2.getAvailable()) {
                        nextKey1 = 79, nextKey2 = 111;
                        gotoxy(longInfoX + 13, longInfoY - 2);
                        cout << "                                        ";
                        gotoxy(longInfoX + 13, longInfoY - 2);
                        cout << "[ " << p3.getPlayerNum() << "廓 PLAYER ]";
                        if (!p3.getAvailable()) {
                            nextKey1 = 81, nextKey2 = 113;
                            gotoxy(longInfoX + 13, longInfoY - 2);
                            cout << "                                        ";
                            gotoxy(longInfoX + 13, longInfoY - 2);
                            cout << "[ " << user.getPlayerNum() << "廓 PLAYER ]";
                        }
                    }
                }

                //謙纂剪釭 棻擠 離滔陛 蘋萄剩梯
                while (true) {
                    input = _getch();
                    if (input == 87 || input == 119 ||
                        input == 67 || input == 99 ||
                        input == 77 || input == 109 ||
                        input == 80 || input == 112 ||
                        input == nextKey1 || input == nextKey2) break;
                }

                //棻擠欐檜 蘋萄蒂 剩曹 唳辦
                if (input == nextKey1 || input == nextKey2) {
                    pushOk = true;
                    checkPlayerNoneAble(user, p1, p2, p3);
                    continue;
                }
                else {
                    pushOk = false;
                    //1廓檜 謙蟻擊 唳辦
                    if (input == 87 || input == 119) { //user陛 謙 耀 唳辦
                        if (user.getAvailable()) {
                            PlaySound(TEXT("ringingBell.wav"), 0, SND_FILENAME | SND_ASYNC);
                            //婁橾 5偃橾陽 蟻擊 唳辦
                            if (checkFiveCard(user, p1, p2, p3)) {
                                //薄熱 啗骯
                                user.plusScore();
                                //(釭)醒朝 ル薑
                                makeAllFaceDefault(p1);
                                makeAllFaceDefault(p2);
                                makeAllFaceDefault(p3);
                                makeFaceSmile(user);
                                //纔檜綰 嬪曖 蘋萄 賅舒 陛螳馬
                                getAllFrontCard(user, p1, p2, p3);
                                printPlayersCardInfo(user, p1, p2, p3);
                            }
                            //澀跤 蟻擊 唳辦
                            else {
                                //薄熱 啗骯
                                user.minusScore();
                                //�韋� ル薑
                                makeAllFaceDefault(p1);
                                makeAllFaceDefault(p2);
                                makeAllFaceDefault(p3);
                                makeFaceAngry(user);
                                PlaySound(TEXT("missingBell.wav"), 0, SND_FILENAME | SND_ASYNC);
                                //蘋萄 и濰噶 釭援橫邀
                                missRinging(user, p1, p2, p3);
                                printPlayersCardInfo(user, p1, p2, p3);
                            }
                        }
                    }
                    //2廓檜 謙蟻擊 唳辦
                    else if (input == 67 || input == 99) { //p1陛 謙 耀 唳辦
                        if (p1.getAvailable()) {
                            PlaySound(TEXT("ringingBell.wav"), 0, SND_FILENAME | SND_ASYNC);
                            //婁橾 5偃橾陽 蟻擊 唳辦
                            if (checkFiveCard(user, p1, p2, p3)) {
                                //薄熱 啗骯
                                p1.plusScore();
                                //(釭)醒朝 ル薑
                                makeAllFaceDefault(user);
                                makeAllFaceDefault(p2);
                                makeAllFaceDefault(p3);
                                makeFaceSmile(p1);
                                //纔檜綰 嬪曖 蘋萄 賅舒 陛螳馬
                                getAllFrontCard(p1, user, p2, p3);
                                printPlayersCardInfo(user, p1, p2, p3);
                            }
                            //澀跤 蟻擊 唳辦
                            else {
                                //薄熱 啗骯
                                p1.minusScore();
                                //�韋� ル薑, 釭該雖 晦獄 ル薑
                                makeAllFaceDefault(user);
                                makeAllFaceDefault(p2);
                                makeAllFaceDefault(p3);
                                makeFaceAngry(p1);
                                PlaySound(TEXT("missingBell.wav"), 0, SND_FILENAME | SND_ASYNC);
                                //蘋萄 и濰噶 釭援橫邀
                                missRinging(p1, user, p2, p3);
                                printPlayersCardInfo(user, p1, p2, p3);
                            }
                        }
                    }
                    //3廓檜 謙蟻擊 唳辦
                    else if (input == 77 || input == 109) { //p2陛 謙 耀 唳辦
                        if (p2.getAvailable()) {
                            PlaySound(TEXT("ringingBell.wav"), 0, SND_FILENAME | SND_ASYNC);
                            //婁橾 5偃橾陽 蟻擊 唳辦
                            if (checkFiveCard(user, p1, p2, p3)) {
                                //薄熱 啗骯
                                p2.plusScore();
                                //(釭)醒朝 ル薑
                                makeAllFaceDefault(p1);
                                makeAllFaceDefault(user);
                                makeAllFaceDefault(p3);
                                makeFaceSmile(p2);
                                //纔檜綰 嬪曖 蘋萄 賅舒 陛螳馬
                                getAllFrontCard(p2, p1, user, p3);
                                printPlayersCardInfo(user, p1, p2, p3);
                            }
                            //澀跤 蟻擊 唳辦
                            else {
                                //薄熱 啗骯
                                p2.minusScore();
                                //�韋� ル薑, 釭該雖 晦獄 ル薑
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
                    //4廓檜 謙蟻擊 唳辦
                    else if (input == 80 || input == 112) { //p3陛 謙 耀 唳辦
                        if (p3.getAvailable()) {
                            PlaySound(TEXT("ringingBell.wav"), 0, SND_FILENAME | SND_ASYNC);
                            //婁橾 5偃橾陽 蟻擊 唳辦
                            if (checkFiveCard(user, p1, p2, p3)) {
                                //薄熱 啗骯
                                p3.plusScore();
                                //(釭)醒朝 ル薑
                                makeAllFaceDefault(p1);
                                makeAllFaceDefault(p2);
                                makeAllFaceDefault(user);
                                makeFaceSmile(p3);
                                //纔檜綰 嬪曖 蘋萄 賅舒 陛螳馬
                                getAllFrontCard(p3, p1, p2, user);
                                printPlayersCardInfo(user, p1, p2, p3);
                            }
                            //澀跤 蟻擊 唳辦
                            else {
                                //薄熱 啗骯
                                p3.minusScore();
                                //�韋� ル薑, 釭該雖 晦獄 ル薑
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

                //1廓 驍塊 籀葬
                if (user.getBackCount() == 0) {
                    //�韋� ル薑
                    makeAllFaceDefault(p1);
                    makeAllFaceDefault(p2);
                    makeAllFaceDefault(p3);
                    makeFaceAngry(user);
                    user.setNoneAvailable();
                    printPlayersCardInfo(user, p1, p2, p3);
                    gotoxy(longInfoX + 10, longInfoY);
                    cout << user.getPlayerNum() << "廓 餌辨濠陛 驍塊腎歷蝗棲棻.";
                    Sleep(2000);
                    gotoxy(longInfoX + 10, longInfoY);
                    cout << "                              ";
                }
                continue;
            }
        }
        //2廓 離滔
        if (turn % 4 == 1) {
            //棻擠 欐戲煎 剩橫陛朝 酈 雖薑
            int nextKey1 = 78, nextKey2 = 110;
            printPlayersCardInfo(user, p1, p2, p3);
            if (!p1.getAvailable()) {
                continue;
            }
            else {
                //Player 2 : 蘋萄 頂晦 X, 謙纂晦 C (88,120 / 67,99)
                //羹觼
                gotoxy(0, 0);
                cout << "2廓 離滔";
                //撲貲 轎溘
                gotoxy(longInfoX + 13, longInfoY - 2);
                cout << "                                        ";
                gotoxy(longInfoX + 13, longInfoY - 2);
                cout << "[ " << p1.getPlayerNum() << "廓 PLAYER ]";

                //瞪 欐縑憮 蘋萄頂晦陛 檜嘐 揚溜朝雖 �挫�
                if (pushOk == false) {
                    while (true) {
                        int value = _getch();
                        if (value == 88 || value == 120) break;
                    }
                }

                //蘋萄 菴餵晦
                if (p1.open() == -1) continue;
                frontCardPrint(p1.getFrontTopCard(), p1);
                printPlayersCardInfo(user, p1, p2, p3);

                //棻擠欐 轎溘
                gotoxy(longInfoX + 13, longInfoY - 2);
                cout << "                                        ";
                gotoxy(longInfoX + 13, longInfoY - 2);
                cout << "[ " << p2.getPlayerNum() << "廓 PLAYER ]";

                //棻擠 欐 摹熱曖 酈高 掘ж晦 (驍塊濠 陽僥)
                if (!p2.getAvailable()) {
                    nextKey1 = 79, nextKey2 = 111;
                    gotoxy(longInfoX + 13, longInfoY - 2);
                    cout << "                                        ";
                    gotoxy(longInfoX + 13, longInfoY - 2);
                    cout << "[ " << p3.getPlayerNum() << "廓 PLAYER ]";
                    if (!p3.getAvailable()) {
                        nextKey1 = 81, nextKey2 = 113;
                        gotoxy(longInfoX + 13, longInfoY - 2);
                        cout << "                                        ";
                        gotoxy(longInfoX + 13, longInfoY - 2);
                        cout << "[ " << user.getPlayerNum() << "廓 PLAYER ]";
                        if (!user.getAvailable()) {
                            if (!user.getAvailable()) nextKey1 = 88, nextKey2 = 120;
                            gotoxy(longInfoX + 13, longInfoY - 2);
                            cout << "                                        ";
                            gotoxy(longInfoX + 13, longInfoY - 2);
                            cout << "[ " << p1.getPlayerNum() << "廓 PLAYER ]";
                        }
                    }
                }

                //謙纂剪釭 棻擠 離滔陛 蘋萄剩梯
                while (true) {
                    input = _getch();
                    if (input == 87 || input == 119 ||
                        input == 67 || input == 99 ||
                        input == 77 || input == 109 ||
                        input == 80 || input == 112 ||
                        input == nextKey1 || input == nextKey2) break;
                }

                //棻擠欐檜 蘋萄蒂 剩曹 唳辦
                if (input == nextKey1 || input == nextKey2) {
                    pushOk = true;
                    checkPlayerNoneAble(p1, user, p2, p3);
                    continue;
                }
                //援捱陛 謙耀 唳辦
                else {
                    pushOk = false;
                    //1廓檜 謙蟻擊 唳辦
                    if (input == 87 || input == 119) { //user陛 謙 耀 唳辦
                        if (user.getAvailable()) {
                            PlaySound(TEXT("ringingBell.wav"), 0, SND_FILENAME | SND_ASYNC);
                            //婁橾 5偃橾陽 蟻擊 唳辦
                            if (checkFiveCard(user, p1, p2, p3)) {
                                //薄熱 啗骯
                                user.plusScore();
                                //(釭)醒朝 ル薑
                                makeAllFaceDefault(p1);
                                makeAllFaceDefault(p2);
                                makeAllFaceDefault(p3);
                                makeFaceSmile(user);
                                //纔檜綰 嬪曖 蘋萄 賅舒 陛螳馬
                                getAllFrontCard(user, p1, p2, p3);
                                printPlayersCardInfo(user, p1, p2, p3);
                            }
                            //澀跤 蟻擊 唳辦
                            else {
                                //薄熱 啗骯
                                user.minusScore();
                                //�韋� ル薑
                                makeAllFaceDefault(p1);
                                makeAllFaceDefault(p2);
                                makeAllFaceDefault(p3);
                                makeFaceAngry(user);
                                PlaySound(TEXT("missingBell.wav"), 0, SND_FILENAME | SND_ASYNC);
                                //蘋萄 и濰噶 釭援橫邀
                                missRinging(user, p1, p2, p3);
                                printPlayersCardInfo(user, p1, p2, p3);
                            }
                        }
                    }
                    //2廓檜 謙蟻擊 唳辦
                    else if (input == 67 || input == 99) { //p1陛 謙 耀 唳辦
                        if (p1.getAvailable()) {
                            PlaySound(TEXT("ringingBell.wav"), 0, SND_FILENAME | SND_ASYNC);
                            //婁橾 5偃橾陽 蟻擊 唳辦
                            if (checkFiveCard(user, p1, p2, p3)) {
                                //薄熱 啗骯
                                p1.plusScore();
                                //(釭)醒朝 ル薑
                                makeAllFaceDefault(user);
                                makeAllFaceDefault(p2);
                                makeAllFaceDefault(p3);
                                makeFaceSmile(p1);
                                //纔檜綰 嬪曖 蘋萄 賅舒 陛螳馬
                                getAllFrontCard(p1, user, p2, p3);
                                printPlayersCardInfo(user, p1, p2, p3);
                            }
                            //澀跤 蟻擊 唳辦
                            else {
                                //薄熱 啗骯
                                p1.minusScore();
                                //�韋� ル薑, 釭該雖 晦獄 ル薑
                                makeAllFaceDefault(user);
                                makeAllFaceDefault(p2);
                                makeAllFaceDefault(p3);
                                makeFaceAngry(p1);
                                PlaySound(TEXT("missingBell.wav"), 0, SND_FILENAME | SND_ASYNC);
                                //蘋萄 и濰噶 釭援橫邀
                                missRinging(p1, user, p2, p3);
                                printPlayersCardInfo(user, p1, p2, p3);
                            }
                        }
                    }
                    //3廓檜 謙蟻擊 唳辦
                    else if (input == 77 || input == 109) { //p2陛 謙 耀 唳辦
                        if (p2.getAvailable()) {
                            PlaySound(TEXT("ringingBell.wav"), 0, SND_FILENAME | SND_ASYNC);
                            //婁橾 5偃橾陽 蟻擊 唳辦
                            if (checkFiveCard(user, p1, p2, p3)) {
                                //薄熱 啗骯
                                p2.plusScore();
                                //(釭)醒朝 ル薑
                                makeAllFaceDefault(p1);
                                makeAllFaceDefault(user);
                                makeAllFaceDefault(p3);
                                makeFaceSmile(p2);
                                //纔檜綰 嬪曖 蘋萄 賅舒 陛螳馬
                                getAllFrontCard(p2, p1, user, p3);
                                printPlayersCardInfo(user, p1, p2, p3);
                            }
                            //澀跤 蟻擊 唳辦
                            else {
                                //薄熱 啗骯
                                p2.minusScore();
                                //�韋� ル薑, 釭該雖 晦獄 ル薑
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
                    //4廓檜 謙蟻擊 唳辦
                    else if (input == 80 || input == 112) { //p3陛 謙 耀 唳辦
                        if (p3.getAvailable()) {
                            PlaySound(TEXT("ringingBell.wav"), 0, SND_FILENAME | SND_ASYNC);
                            //婁橾 5偃橾陽 蟻擊 唳辦
                            if (checkFiveCard(user, p1, p2, p3)) {
                                //薄熱 啗骯
                                p3.plusScore();
                                //(釭)醒朝 ル薑
                                makeAllFaceDefault(p1);
                                makeAllFaceDefault(p2);
                                makeAllFaceDefault(user);
                                makeFaceSmile(p3);
                                //纔檜綰 嬪曖 蘋萄 賅舒 陛螳馬
                                getAllFrontCard(p3, p1, p2, user);
                                printPlayersCardInfo(user, p1, p2, p3);
                            }
                            //澀跤 蟻擊 唳辦
                            else {
                                //薄熱 啗骯
                                p3.minusScore();
                                //�韋� ル薑, 釭該雖 晦獄 ル薑
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

                //2廓 驍塊 籀葬
                if (p1.getBackCount() == 0) {
                    //�韋� ル薑
                    makeAllFaceDefault(user);
                    makeAllFaceDefault(p2);
                    makeAllFaceDefault(p3);
                    makeFaceAngry(p1);
                    p1.setNoneAvailable();
                    printPlayersCardInfo(user, p1, p2, p3);
                    gotoxy(longInfoX + 10, longInfoY);
                    cout << p1.getPlayerNum() << "廓 餌辨濠陛 驍塊腎歷蝗棲棻.";
                    Sleep(2000);
                    gotoxy(longInfoX + 10, longInfoY);
                    cout << "                              ";
                }
                continue;

            }
        }
        //3廓 離滔
        if (turn % 4 == 2) {
            //棻擠 欐戲煎 剩橫陛朝 酈 雖薑
            int nextKey1 = 79, nextKey2 = 111;
            printPlayersCardInfo(user, p1, p2, p3);
            if (!p2.getAvailable()) {
                continue;
            }
            else {
                //Player 3 : 蘋萄 頂晦 N, 謙纂晦 M (78,110 / 77,109)
               //羹觼
                gotoxy(0, 0);
                cout << "3廓 離滔";

                //撲貲 轎溘
                gotoxy(longInfoX + 13, longInfoY - 2);
                cout << "                                        ";
                gotoxy(longInfoX + 13, longInfoY - 2);
                cout << "[ " << p2.getPlayerNum() << "廓 PLAYER ]";

                //瞪 欐縑憮 蘋萄頂晦陛 檜嘐 揚溜朝雖 �挫�
                if (pushOk == false) {
                    while (true) {
                        int value = _getch();
                        if (value == 78 || value == 110) break;
                    }
                }

                //蘋萄 菴餵晦
                if (p2.open() == -1) continue;
                frontCardPrint(p2.getFrontTopCard(), p2);
                printPlayersCardInfo(user, p1, p2, p3);

                //棻擠欐 轎溘
                gotoxy(longInfoX + 13, longInfoY - 2);
                cout << "                                        ";
                gotoxy(longInfoX + 13, longInfoY - 2);
                cout << "[ " << p3.getPlayerNum() << "廓 PLAYER ]";

                //棻擠 欐 摹熱曖 酈高 掘ж晦 (驍塊濠 陽僥)
                if (!p3.getAvailable()) {
                    nextKey1 = 81, nextKey2 = 113;
                    gotoxy(longInfoX + 13, longInfoY - 2);
                    cout << "                                        ";
                    gotoxy(longInfoX + 13, longInfoY - 2);
                    cout << "[ " << user.getPlayerNum() << "廓 PLAYER ]";
                    if (!user.getAvailable()) {
                        nextKey1 = 88, nextKey2 = 120;
                        gotoxy(longInfoX + 13, longInfoY - 2);
                        cout << "                                        ";
                        gotoxy(longInfoX + 13, longInfoY - 2);
                        cout << "[ " << p1.getPlayerNum() << "廓 PLAYER ]";
                        if (!p1.getAvailable()) {
                            nextKey1 = 78, nextKey2 = 110;
                            gotoxy(longInfoX + 13, longInfoY - 2);
                            cout << "                                        ";
                            gotoxy(longInfoX + 13, longInfoY - 2);
                            cout << "[ " << p2.getPlayerNum() << "廓 PLAYER ]";
                        }
                    }
                }

                //謙纂剪釭 棻擠 離滔陛 蘋萄剩梯
                while (true) {
                    input = _getch();
                    if (input == 87 || input == 119 ||
                        input == 67 || input == 99 ||
                        input == 77 || input == 109 ||
                        input == 80 || input == 112 ||
                        input == nextKey1 || input == nextKey2) break;
                }

                //棻擠欐檜 蘋萄蒂 剩曹 唳辦
                if (input == nextKey1 || input == nextKey2) {
                    pushOk = true;
                    checkPlayerNoneAble(p2, p1, user, p3);
                    continue;
                }
                else {
                    pushOk = false;
                    //1廓檜 謙蟻擊 唳辦
                    if (input == 87 || input == 119) { //user陛 謙 耀 唳辦
                        //驍塊脹 餌辨濠橾 唳辦 continue
                        if (user.getAvailable()) {
                            PlaySound(TEXT("ringingBell.wav"), 0, SND_FILENAME | SND_ASYNC);
                            //婁橾 5偃橾陽 蟻擊 唳辦
                            if (checkFiveCard(user, p1, p2, p3)) {
                                //薄熱 啗骯
                                user.plusScore();
                                //(釭)醒朝 ル薑
                                makeAllFaceDefault(p1);
                                makeAllFaceDefault(p2);
                                makeAllFaceDefault(p3);
                                makeFaceSmile(user);
                                //纔檜綰 嬪曖 蘋萄 賅舒 陛螳馬
                                getAllFrontCard(user, p1, p2, p3);
                                printPlayersCardInfo(user, p1, p2, p3);
                            }
                            //澀跤 蟻擊 唳辦
                            else {
                                //薄熱 啗骯
                                user.minusScore();
                                //�韋� ル薑
                                makeAllFaceDefault(p1);
                                makeAllFaceDefault(p2);
                                makeAllFaceDefault(p3);
                                makeFaceAngry(user);
                                PlaySound(TEXT("missingBell.wav"), 0, SND_FILENAME | SND_ASYNC);
                                //蘋萄 и濰噶 釭援橫邀
                                missRinging(user, p1, p2, p3);
                                printPlayersCardInfo(user, p1, p2, p3);
                            }
                        }
                    }
                    //2廓檜 謙蟻擊 唳辦
                    else if (input == 67 || input == 99) { //p1陛 謙 耀 唳辦
                        //驍塊脹 餌辨濠橾 唳辦 continue
                        if (p1.getAvailable()) {

                            PlaySound(TEXT("ringingBell.wav"), 0, SND_FILENAME | SND_ASYNC);
                            //婁橾 5偃橾陽 蟻擊 唳辦
                            if (checkFiveCard(user, p1, p2, p3)) {
                                //薄熱 啗骯
                                p1.plusScore();
                                //(釭)醒朝 ル薑
                                makeAllFaceDefault(user);
                                makeAllFaceDefault(p2);
                                makeAllFaceDefault(p3);
                                makeFaceSmile(p1);
                                //纔檜綰 嬪曖 蘋萄 賅舒 陛螳馬
                                getAllFrontCard(p1, user, p2, p3);
                                printPlayersCardInfo(user, p1, p2, p3);
                            }
                            //澀跤 蟻擊 唳辦
                            else {
                                //薄熱 啗骯
                                p1.minusScore();
                                //�韋� ル薑, 釭該雖 晦獄 ル薑
                                makeAllFaceDefault(user);
                                makeAllFaceDefault(p2);
                                makeAllFaceDefault(p3);
                                makeFaceAngry(p1);
                                PlaySound(TEXT("missingBell.wav"), 0, SND_FILENAME | SND_ASYNC);
                                //蘋萄 и濰噶 釭援橫邀
                                missRinging(p1, user, p2, p3);
                                printPlayersCardInfo(user, p1, p2, p3);
                            }
                        }
                    }
                    //3廓檜 謙蟻擊 唳辦
                    else if (input == 77 || input == 109) { //p2陛 謙 耀 唳辦
                        //驍塊脹 餌辨濠橾 唳辦 謙 艦 熱 橈擠
                        if (p2.getAvailable()) {
                            PlaySound(TEXT("ringingBell.wav"), 0, SND_FILENAME | SND_ASYNC);
                            //婁橾 5偃橾陽 蟻擊 唳辦
                            if (checkFiveCard(user, p1, p2, p3)) {
                                //薄熱 啗骯
                                p2.plusScore();
                                //(釭)醒朝 ル薑
                                makeAllFaceDefault(p1);
                                makeAllFaceDefault(user);
                                makeAllFaceDefault(p3);
                                makeFaceSmile(p2);
                                //纔檜綰 嬪曖 蘋萄 賅舒 陛螳馬
                                getAllFrontCard(p2, p1, user, p3);
                                printPlayersCardInfo(user, p1, p2, p3);
                            }
                            //澀跤 蟻擊 唳辦
                            else {
                                //薄熱 啗骯
                                p2.minusScore();
                                //�韋� ル薑, 釭該雖 晦獄 ル薑
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
                    //4廓檜 謙蟻擊 唳辦
                    else if (input == 80 || input == 112) { //p3陛 謙 耀 唳辦
                        //驍塊脹 餌辨濠橾 唳辦 continue
                        if (p3.getAvailable()) {

                            PlaySound(TEXT("ringingBell.wav"), 0, SND_FILENAME | SND_ASYNC);
                            //婁橾 5偃橾陽 蟻擊 唳辦
                            if (checkFiveCard(user, p1, p2, p3)) {
                                //薄熱 啗骯
                                p3.plusScore();
                                //(釭)醒朝 ル薑
                                makeAllFaceDefault(p1);
                                makeAllFaceDefault(p2);
                                makeAllFaceDefault(user);
                                makeFaceSmile(p3);
                                //纔檜綰 嬪曖 蘋萄 賅舒 陛螳馬
                                getAllFrontCard(p3, p1, p2, user);
                                printPlayersCardInfo(user, p1, p2, p3);
                            }
                            //澀跤 蟻擊 唳辦
                            else {
                                //薄熱 啗骯
                                p3.minusScore();
                                //�韋� ル薑, 釭該雖 晦獄 ル薑
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

                //3廓 驍塊 籀葬
                if (p2.getBackCount() == 0) {
                    //�韋� ル薑
                    makeAllFaceDefault(user);
                    makeAllFaceDefault(p1);
                    makeAllFaceDefault(p3);
                    makeFaceAngry(p2);
                    p2.setNoneAvailable();
                    printPlayersCardInfo(user, p1, p2, p3);
                    gotoxy(longInfoX + 10, longInfoY);
                    cout << p2.getPlayerNum() << "廓 餌辨濠陛 驍塊腎歷蝗棲棻.";
                    Sleep(2000);
                    gotoxy(longInfoX + 10, longInfoY);
                    cout << "                              ";
                }
                continue;
            }
        }
        //4廓 離滔
        if (turn % 4 == 3) {
            //棻擠 欐戲煎 剩橫陛朝 酈 雖薑
            int nextKey1 = 81, nextKey2 = 113;
            printPlayersCardInfo(user, p1, p2, p3);
            if (!p3.getAvailable()) {
                continue;
            }
            else {
                //Player 4 : 蘋萄 頂晦 O, 謙纂晦 P (79,111 / 80,112)
                //羹觼
                gotoxy(0, 0);
                cout << "4廓 離滔";
                //撲貲 轎溘
                gotoxy(longInfoX + 13, longInfoY - 2);
                cout << "                                        ";
                gotoxy(longInfoX + 13, longInfoY - 2);
                cout << "[ " << p3.getPlayerNum() << "廓 PLAYER ]";


                //瞪 欐縑憮 蘋萄頂晦陛 檜嘐 揚溜朝雖 �挫�
                if (pushOk == false) {
                    while (true) {
                        int value = _getch();
                        if (value == 79 || value == 111) break;
                    }
                }

                //蘋萄 菴餵晦
                if (p3.open() == -1) continue;
                frontCardPrint(p3.getFrontTopCard(), p3);
                printPlayersCardInfo(user, p1, p2, p3);

                //棻擠欐 轎溘
                gotoxy(longInfoX + 13, longInfoY - 2);
                cout << "                                        ";
                gotoxy(longInfoX + 13, longInfoY - 2);
                cout << "[ " << user.getPlayerNum() << "廓 PLAYER ]";

                //棻擠 欐 摹熱曖 酈高 掘ж晦 (驍塊濠 陽僥)
                if (!user.getAvailable()) {
                    nextKey1 = 88, nextKey2 = 120;
                    gotoxy(longInfoX + 13, longInfoY - 2);
                    cout << "                                        ";
                    gotoxy(longInfoX + 13, longInfoY - 2);
                    cout << "[ " << p1.getPlayerNum() << "廓 PLAYER ]";
                    if (!p1.getAvailable()) {
                        nextKey1 = 78, nextKey2 = 110;
                        gotoxy(longInfoX + 13, longInfoY - 2);
                        cout << "                                        ";
                        gotoxy(longInfoX + 13, longInfoY - 2);
                        cout << "[ " << p2.getPlayerNum() << "廓 PLAYER ]";
                        if (!p2.getAvailable()) {
                            nextKey1 = 79, nextKey2 = 111;
                            gotoxy(longInfoX + 13, longInfoY - 2);
                            cout << "                                        ";
                            gotoxy(longInfoX + 13, longInfoY - 2);
                            cout << "[ " << p3.getPlayerNum() << "廓 PLAYER ]";
                        }
                    }
                }

                //謙纂剪釭 棻擠 離滔陛 蘋萄剩梯
                while (true) {
                    input = _getch();
                    if (input == 87 || input == 119 ||
                        input == 67 || input == 99 ||
                        input == 77 || input == 109 ||
                        input == 80 || input == 112 ||
                        input == nextKey1 || input == nextKey2) break;
                }

                //棻擠欐檜 蘋萄蒂 剩曹 唳辦
                if (input == nextKey1 || input == nextKey2) {
                    pushOk = true;
                    checkPlayerNoneAble(p3, p1, p2, user);
                    continue;
                }
                else {
                    pushOk = false;
                    //1廓檜 謙耀 唳辦
                    if (input == 87 || input == 119) { //user陛 謙 耀 唳辦
                        if (user.getAvailable()) {
                            PlaySound(TEXT("ringingBell.wav"), 0, SND_FILENAME | SND_ASYNC);
                            //婁橾 5偃橾陽 蟻擊 唳辦
                            if (checkFiveCard(user, p1, p2, p3)) {
                                //薄熱 啗骯
                                user.plusScore();
                                //(釭)醒朝 ル薑
                                makeAllFaceDefault(p1);
                                makeAllFaceDefault(p2);
                                makeAllFaceDefault(p3);
                                makeFaceSmile(user);
                                //纔檜綰 嬪曖 蘋萄 賅舒 陛螳馬
                                getAllFrontCard(user, p1, p2, p3);
                                printPlayersCardInfo(user, p1, p2, p3);
                            }
                            //澀跤 蟻擊 唳辦
                            else {
                                //薄熱 啗骯
                                user.minusScore();
                                //�韋� ル薑
                                makeAllFaceDefault(p1);
                                makeAllFaceDefault(p2);
                                makeAllFaceDefault(p3);
                                makeFaceAngry(user);
                                PlaySound(TEXT("missingBell.wav"), 0, SND_FILENAME | SND_ASYNC);
                                //蘋萄 и濰噶 釭援橫邀
                                missRinging(user, p1, p2, p3);
                                printPlayersCardInfo(user, p1, p2, p3);
                            }
                        }
                    }
                    //2廓檜 謙耀 唳辦
                    else if (input == 67 || input == 99) { //p1陛 謙 耀 唳辦
                        if (p1.getAvailable()) {
                            PlaySound(TEXT("ringingBell.wav"), 0, SND_FILENAME | SND_ASYNC);
                            //婁橾 5偃橾陽 蟻擊 唳辦
                            if (checkFiveCard(user, p1, p2, p3)) {
                                //薄熱 啗骯
                                p1.plusScore();
                                //(釭)醒朝 ル薑
                                makeAllFaceDefault(user);
                                makeAllFaceDefault(p2);
                                makeAllFaceDefault(p3);
                                makeFaceSmile(p1);
                                //纔檜綰 嬪曖 蘋萄 賅舒 陛螳馬
                                getAllFrontCard(p1, user, p2, p3);
                                printPlayersCardInfo(user, p1, p2, p3);
                            }
                            //澀跤 蟻擊 唳辦
                            else {
                                //薄熱 啗骯
                                p1.minusScore();
                                //�韋� ル薑, 釭該雖 晦獄 ル薑
                                makeAllFaceDefault(user);
                                makeAllFaceDefault(p2);
                                makeAllFaceDefault(p3);
                                makeFaceAngry(p1);
                                PlaySound(TEXT("missingBell.wav"), 0, SND_FILENAME | SND_ASYNC);
                                //蘋萄 и濰噶 釭援橫邀
                                missRinging(p1, user, p2, p3);
                                printPlayersCardInfo(user, p1, p2, p3);
                            }
                        }
                    }
                    //3廓檜 謙耀 唳辦
                    else if (input == 77 || input == 109) { //p2陛 謙 耀 唳辦
                        if (p2.getAvailable()) {
                            PlaySound(TEXT("ringingBell.wav"), 0, SND_FILENAME | SND_ASYNC);
                            //婁橾 5偃橾陽 蟻擊 唳辦
                            if (checkFiveCard(user, p1, p2, p3)) {
                                //薄熱 啗骯
                                p2.plusScore();
                                //(釭)醒朝 ル薑
                                makeAllFaceDefault(p1);
                                makeAllFaceDefault(user);
                                makeAllFaceDefault(p3);
                                makeFaceSmile(p2);
                                //纔檜綰 嬪曖 蘋萄 賅舒 陛螳馬
                                getAllFrontCard(p2, p1, user, p3);
                                printPlayersCardInfo(user, p1, p2, p3);
                            }
                            //澀跤 蟻擊 唳辦
                            else {
                                //薄熱 啗骯
                                p2.minusScore();
                                //�韋� ル薑, 釭該雖 晦獄 ル薑
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
                    //4廓檜 謙耀 唳辦
                    else if (input == 80 || input == 112) { //p3陛 謙 耀 唳辦
                        if (p3.getAvailable()) {
                            PlaySound(TEXT("ringingBell.wav"), 0, SND_FILENAME | SND_ASYNC);
                            //婁橾 5偃橾陽 蟻擊 唳辦
                            if (checkFiveCard(user, p1, p2, p3)) {
                                //薄熱 啗骯
                                p3.plusScore();
                                //(釭)醒朝 ル薑
                                makeAllFaceDefault(p1);
                                makeAllFaceDefault(p2);
                                makeAllFaceDefault(user);
                                makeFaceSmile(p3);
                                //纔檜綰 嬪曖 蘋萄 賅舒 陛螳馬
                                getAllFrontCard(p3, p1, p2, user);
                                printPlayersCardInfo(user, p1, p2, p3);
                            }
                            //澀跤 蟻擊 唳辦
                            else {
                                //薄熱 啗骯
                                p3.minusScore();
                                //�韋� ル薑, 釭該雖 晦獄 ル薑
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


                //4廓 驍塊 籀葬
                if (p3.getBackCount() == 0) {
                    //(釭)�韋� ル薑
                    makeAllFaceDefault(user);
                    makeAllFaceDefault(p1);
                    makeAllFaceDefault(p2);
                    makeFaceAngry(p3);

                    p3.setNoneAvailable();
                    printPlayersCardInfo(user, p1, p2, p3);
                    gotoxy(longInfoX + 10, longInfoY);
                    cout << p3.getPlayerNum() << "廓 餌辨濠陛 驍塊腎歷蝗棲棻.";
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
//啪歜 衛濛 (1 vs com vs com vs com)
void StartGameAlone() {
    DrawStartGame();
    //褻濛徹 draw
    {
        gotoxy(15, 30);
        cout << "忙式式式式式式式式式式式式式式  褻濛徹 式式式式式式式式式式式式式式忖";
        gotoxy(15, 31);
        cout << "弛                                     弛";
        gotoxy(15, 32);
        cout << "弛      蘋萄 剩晦晦 Ⅰ  SPACE BAR      弛";
        gotoxy(15, 33);
        cout << "弛                                     弛";
        gotoxy(15, 34);
        cout << "弛        謙 纂晦   Ⅰ  ENTER          弛";
        gotoxy(15, 35);
        cout << "弛                                     弛";
        gotoxy(15, 36);
        cout << "弛        釭陛晦    Ⅰ  E key          弛";
        gotoxy(15, 37);
        cout << "弛                                     弛";
        gotoxy(15, 38);
        cout << "戌式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式戎";
    }
    //餌辨濠 儅撩
    Player user(1), com1(2), com2(3), com3(4);
    //蘋萄 楠渾寡纂,餌辨濠縑啪 蘋萄 碟寡
    setInitCard(user, com1, com2, com3);

    //奩犒
    int input = 0;
    int turn = -1;
    while (true) {
        turn++;
        if (turn % 4 == 0) {
            printPlayersCardInfo(user, com1, com2, com3);
            if (!user.getAvailable()) {
                //羹觼
                gotoxy(0, 0);
                cout << "餌辨濠 驍塊";
                Sleep(1000);
                gotoxy(0, 0);
                cout << "                          ";
                break;
            }
            else {
                //撲貲 轎溘
                gotoxy(longInfoX + 13, longInfoY - 2);
                cout << "                                        ";
                gotoxy(longInfoX + 13, longInfoY - 2);
                cout << "[ " << user.getPlayerNum() << "廓 PLAYER ]";

                //蘋萄 鳥陽梱雖 渠晦
                while (true) {
                    int input = _getch();
                    if (input == 32) break;
                }

                //蘋萄 菴餵晦
                if (user.open() == -1) continue;
                gotoxy(10, 14);
                frontCardPrint(user.getFrontTopCard(), user);

                //5偃檣雖 �挫�
                if (checkFiveCard(user, com1, com2, com3)) {
                    //煎瑪醞縑憮 楠渾戲煎 謙藹
                }



                input = GameKey();
                if (input == 1) {
                    PlaySound(TEXT("ringingBell.wav"), 0, SND_FILENAME | SND_ASYNC);
                    //婁橾 5偃橾陽 蟻擊 唳辦
                    if (checkFiveCard(user, com1, com2, com3)) {
                        //***(釭)醒朝 ル薑
                        makeAllFaceDefault(com1);
                        makeAllFaceDefault(com2);
                        makeAllFaceDefault(com3);
                        makeFaceSmile(user);
                        //纔檜綰 嬪曖 蘋萄 賅舒 陛螳馬
                        getAllFrontCard(user, com1, com2, com3);
                        printPlayersCardInfo(user, com1, com2, com3);
                    }
                    //澀跤 蟻擊 唳辦
                    else {
                        //***�韋� ル薑, 釭該雖 晦獄 ル薑
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
                    //謙 纂雖 彊擠
                }
            }
            if (user.getBackCount() == 0) {
                //***�韋� ル薑
                makeAllFaceDefault(com1);
                makeAllFaceDefault(com2);
                makeAllFaceDefault(com3);
                makeFaceAngry(user);
                user.setNoneAvailable();
                printPlayersCardInfo(user, com1, com2, com3);
                gotoxy(longInfoX + 10, longInfoY);
                cout << user.getPlayerNum() << "廓 餌辨濠陛 驍塊腎歷蝗棲棻.";
                Sleep(2000);
                gotoxy(longInfoX + 10, longInfoY);
                cout << "                              ";

                //薄熱
                int score = 0;
                int x = 20;
                int y = 17;
                gotoxy(x, y);
                cout << "忙式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式忖";
                gotoxy(x, y + 1);
                cout << "弛                                         弛";
                gotoxy(x, y + 2);
                cout << "弛                GAME OVER                弛";
                gotoxy(x, y + 3);
                cout << "弛                                         弛";
                gotoxy(x, y + 4);
                cout << "弛               score  :                  弛";
                gotoxy(x + 5, y + 4);
                cout << score;
                gotoxy(x, y + 5);
                cout << "弛                                         弛";
                gotoxy(x, y + 6);
                cout << "弛   楨韁擊 濛撩ж衛啊蝗棲梱?  [ Y / N ]   弛";
                gotoxy(x, y + 7);
                cout << "弛                                         弛";
                gotoxy(x, y + 8);
                cout << "戌式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式戎";

                //Y 傳朝 N 摹鷗
                while (true) {
                    if (_getch() == 89 || _getch() == 121) {
                        string userName = "";
                        gotoxy(x, y + 4);
                        cout << "弛                                         弛";
                        gotoxy(x, y + 5);
                        cout << "弛    棣啻歜 殮溘 :                        弛";
                        gotoxy(x, y + 6);
                        cout << "弛                                         弛";
                        gotoxy(x + 12, y + 5);
                        cin >> userName;
                        gotoxy(0, 0);
                        cout << userName << endl;

                        //餌辨濠 檜葷, 薄熱 だ橾縑 盪濰
                        ofstream out("database_solo.txt", ios::app);
                        //歜衛 薄熱
                        out << userName << " " << score << "\n";
                        out.close();

                        //楨韁 �飛� draw
                        DrawRankingScreen(1);
                        break;
                    }
                    else if (_getch() == 78 || _getch() == 110) {
                        gotoxy(x, y);
                        cout << "忙式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式忖";
                        gotoxy(x, y + 1);
                        cout << "弛                                         弛";
                        gotoxy(x, y + 2);
                        cout << "弛                GAME OVER                弛";
                        gotoxy(x, y + 3);
                        cout << "弛                                         弛";
                        gotoxy(x, y + 4);
                        cout << "弛     濡衛�� 詭檣�飛橉虞� 檜翕м棲棻.     弛";
                        gotoxy(x, y + 5);
                        cout << "弛                                         弛";
                        gotoxy(x, y + 6);
                        cout << "弛                                         弛";
                        gotoxy(x, y + 7);
                        cout << "弛                                         弛";
                        gotoxy(x, y + 8);
                        cout << "戌式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式戎";
                        Sleep(2000);
                        //詭檣戲煎 檜翕
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
                //撲貲 轎溘
                gotoxy(longInfoX + 13, longInfoY - 2);
                cout << "                                        ";
                gotoxy(longInfoX + 13, longInfoY - 2);
                cout << "[ " << com1.getPlayerNum() << "廓 PLAYER ]";

                if (com1.open() == -1) continue;
                gotoxy(20, 14);
                frontCardPrint(com1.getFrontTopCard(), com1);
                input = GameKey();
                if (input == 1) {
                    PlaySound(TEXT("ringingBell.wav"), 0, SND_FILENAME | SND_ASYNC);
                    //婁橾 5偃橾陽 蟻擊 唳辦
                    if (checkFiveCard(com1, user, com2, com3)) {
                        //***醒朝 ル薑
                        makeAllFaceDefault(user);
                        makeAllFaceDefault(com2);
                        makeAllFaceDefault(com3);
                        makeFaceSmile(com1);
                        //纔檜綰 嬪曖 蘋萄 賅舒 陛螳馬
                        getAllFrontCard(com1, user, com2, com3);
                        printPlayersCardInfo(user, com1, com2, com3);
                    }
                    //澀跤 蟻擊 唳辦
                    else {
                        //***�韋� ル薑
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
                    //謙 纂雖 彊擠
                }
            }
            if (com1.getBackCount() == 0) {
                //�韋� ル薑
                makeAllFaceDefault(user);
                makeAllFaceDefault(com2);
                makeAllFaceDefault(com3);
                makeFaceAngry(com1);
                com1.setNoneAvailable();
                printPlayersCardInfo(user, com1, com2, com3);
                gotoxy(longInfoX + 10, longInfoY);
                cout << com1.getPlayerNum() << "廓 餌辨濠陛 驍塊腎歷蝗棲棻.";
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
                //撲貲 轎溘
                gotoxy(longInfoX + 13, longInfoY - 2);
                cout << "                                        ";
                gotoxy(longInfoX + 13, longInfoY - 2);
                cout << "[ " << com2.getPlayerNum() << "廓 PLAYER ]";

                if (com2.open() == -1) continue;
                gotoxy(30, 14);
                frontCardPrint(com2.getFrontTopCard(), com2);
                input = GameKey();
                if (input == 1) {
                    PlaySound(TEXT("ringingBell.wav"), 0, SND_FILENAME | SND_ASYNC);
                    //婁橾 5偃橾陽 蟻擊 唳辦
                    if (checkFiveCard(com2, user, com1, com3)) {
                        //***醒朝 ル薑
                        makeAllFaceDefault(user);
                        makeAllFaceDefault(com1);
                        makeAllFaceDefault(com3);
                        makeFaceSmile(com2);
                        //纔檜綰 嬪曖 蘋萄 賅舒 陛螳馬
                        getAllFrontCard(com2, user, com1, com3);
                        printPlayersCardInfo(user, com1, com2, com3);
                    }
                    //澀跤 蟻擊 唳辦
                    else {
                        //�韋� ル薑
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
                    //謙 纂雖 彊擠
                }
            }
            if (com2.getBackCount() == 0) {
                //***�韋� ル薑
                makeAllFaceDefault(user);
                makeAllFaceDefault(com1);
                makeAllFaceDefault(com3);
                makeFaceAngry(com2);
                com2.setNoneAvailable();
                printPlayersCardInfo(user, com1, com2, com3);
                gotoxy(longInfoX + 10, longInfoY);
                cout << com2.getPlayerNum() << "廓 餌辨濠陛 驍塊腎歷蝗棲棻.";
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
                //撲貲 轎溘
                gotoxy(longInfoX + 13, longInfoY - 2);
                cout << "                                        ";
                gotoxy(longInfoX + 13, longInfoY - 2);
                cout << "[ " << com3.getPlayerNum() << "廓 PLAYER ]";

                if (com3.open() == -1) continue;
                gotoxy(40, 14);
                frontCardPrint(com3.getFrontTopCard(), com3);
                input = GameKey();
                if (input == 1) {
                    PlaySound(TEXT("ringingBell.wav"), 0, SND_FILENAME | SND_ASYNC);
                    //婁橾 5偃橾陽 蟻擊 唳辦
                    if (checkFiveCard(com3, com1, com2, user)) {
                        //***(釭)醒朝 ル薑
                        makeAllFaceDefault(user);
                        makeAllFaceDefault(com1);
                        makeAllFaceDefault(com2);
                        makeFaceSmile(com3);

                        //纔檜綰 嬪曖 蘋萄 賅舒 陛螳馬
                        getAllFrontCard(com3, com1, com2, user);
                        printPlayersCardInfo(user, com1, com2, com3);
                    }
                    //澀跤 蟻擊 唳辦
                    else {
                        //***(釭)�韋� ル薑
                        makeAllFaceDefault(user);
                        makeAllFaceDefault(com1);
                        makeAllFaceDefault(com2);
                        makeFaceAngry(com3);
                        //陝 檣錳縑啪 蘋萄 ж釭噶 邀, 蘋萄熱 睡褶й 衛 驍塊
                        PlaySound(TEXT("missingBell.wav"), 0, SND_FILENAME | SND_ASYNC);
                        missRinging(com3, com1, com2, user);
                        printPlayersCardInfo(user, com1, com2, com3);
                    }
                }
                else {
                    //謙 纂雖 彊擠
                }
            }
            if (com3.getBackCount() == 0) {
                //***(釭)�韋� ル薑
                makeAllFaceDefault(user);
                makeAllFaceDefault(com1);
                makeAllFaceDefault(com2);
                makeFaceAngry(com3);

                com3.setNoneAvailable();
                printPlayersCardInfo(user, com1, com2, com3);
                gotoxy(longInfoX + 10, longInfoY);
                cout << com3.getPlayerNum() << "廓 餌辨濠陛 驍塊腎歷蝗棲棻.";
                Sleep(2000);
                gotoxy(longInfoX + 10, longInfoY);
                cout << "                              ";
            }
        }
        //啪歜 釭陛晦 (鬼薯謙猿)
        if (GetKeyValue() == 27) break;
    }


    while (true) {
        if (GetKeyValue() == 27)
            break;
    }
}
//啪歜 霞ч 寞衝 摹鷗
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
            //嬪
        case 72: {
            if (y == 23) {
                gotoxy(x - 2, y);
                printf("  ");
                gotoxy(x - 2, y -= 2);
                printf(">>");
            }
            break;
        }
               //嬴楚
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
            result = y - 21; //0 傳朝 2
            return result;
            //exit
        case 27:
            ReadyGame();
            break;
        }
    }
}
//啪歜 撲貲
void ShowInfo()
{
    DrawInfoScreen();
    while (true) {
        if (_getch() == 27)
            break;
    }
}
//詭檣
int main(void)
{
    //夔樂撲薑
    SetConsoleView();
    //醴憮 撲薑
    CursorView();
    int menuValue = -1;

    while (true)
    {
        menuValue = ReadyGame();    //0 : 撲貲, 2 : 啪歜衛濛, 4 :啪歜謙猿
        if (menuValue == 0) {       //rule
            ShowInfo();
        }
        else if (menuValue == 2) {    //啪歜 寞衝 堅葷
            int res = ChoosePlaying();
            if (res == 0) StartGameAlone(); //0 : �母硥炱�, 2 : 4貲檜 ж晦
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