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
public:
    //驍塊籀葬
    void setNoneAvailable() {
        available = false;
        cout << playerNum << "廓 餌辨濠陛 驍塊腎歷蝗棲棻." << endl;
    }
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
//�飛曋庰� draw
void DrawLoading();
//衛濛�飛� draw
void DrawIntro();
//啪歜�飛� draw
void DrawStartGame();
//撲貲�飛� draw
void DrawInfoScreen();
//[啪歜霞ч] 蘋萄碟寡
void setInitCard(Player& p1, Player& p2, Player& p3, Player& p4);
//詭景摹鷗
int ReadyGame();
//啪歜 霞ч 酈
int GameKey();
//啪歜 衛濛
void StartGame();
//啪歜 撲貲
void ShowInfo();
//詭檣
int main(void);

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


//�飛曋庰� draw
void DrawLoading() {

}
//羅�飛� draw
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
    cout << "     〧〧〧〧";
    gotoxy(25, 23);
    cout << "    〧〧〧〧〧";
    gotoxy(25, 24);
    cout << "   〧〧〧〧〧〧";
    gotoxy(25, 25);
    cout << "   〧〧〧〧〧〧";
    gotoxy(25, 26);
    cout << "    〧〧〧〧〧 ";
    gotoxy(25, 27);
    cout << "     〧〧〧〧 ";
                         

    PrintString(hStdOut, WHITE);
    gotoxy(28, 29);
    cout << "Ⅱ Game Rule for 'r'";
    gotoxy(28, 31);
    cout << "Ⅱ Game Start for 's'";
    gotoxy(28, 33);
    cout << "Ⅱ Exit for 'e'";
}
//啪歜�飛� draw
void DrawStartGame()
{
    //120 41
    system("cls");

    //蘋萄 1
    gotoxy(CARD1X, CARDY);
    cout << "忙式式式式式式式式式式式式式式忖";
    for (int i = CARDY+1; i < CARDY+12; i++) {
        gotoxy(CARD1X, i);
        cout << "弛              弛";
    }
    gotoxy(CARD1X, CARDY + 12);
    cout << "戌式式式式式式式式式式式式式式戎";

    //蘋萄 2
    gotoxy(CARD2X, CARDY);
    cout << "忙式式式式式式式式式式式式式式忖";
    for (int i = CARDY+1; i < CARDY+12; i++) {
        gotoxy(CARD2X, i);
        cout << "弛              弛";
    }
    gotoxy(CARD2X, CARDY+12);
    cout << "戌式式式式式式式式式式式式式式戎";

    //蘋萄 3
    gotoxy(CARD3X, CARDY);
    cout << "忙式式式式式式式式式式式式式式忖";
    for (int i = CARDY+1; i < CARDY+12; i++) {
        gotoxy(CARD3X, i);
        cout << "弛              弛";
    }
    gotoxy(CARD3X, CARDY+12);
    cout << "戌式式式式式式式式式式式式式式戎";

    //蘋萄 4
    gotoxy(CARD4X, CARDY);
    cout << "忙式式式式式式式式式式式式式式忖";
    for (int i = CARDY+1; i < CARDY+12; i++) {
        gotoxy(CARD4X, i);
        cout << "弛              弛";
    }
    gotoxy(CARD4X, CARDY+12);
    cout << "戌式式式式式式式式式式式式式式戎";

    for (int i = 0; i < 45; i++) {
        gotoxy(48, i);
        cout << "弛";
    }

    gotoxy(15,30);
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


    //餌辨濠 鼻鷓 薑爾
    gotoxy(57, 4);
    cout << "Player 1";
    gotoxy(50, 3);
    cout << "忙式式式式式式式式式忖";
    gotoxy(50, 4);
    cout << "弛  ÷  ÷ 弛";
    gotoxy(50, 5);
    cout << "弛  〢  〣 弛";
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
    cout << "弛  Ⅴ  Ⅴ 弛";
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
    cout << "弛  ∥  ∥ 弛";
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
void DrawRankingScreen() {
    //135 45
    HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
    system("cls");

    int x = 22;
    int y = 8;
    gotoxy(x, y);
    cout << "忙式式式式式式式式式式式式式式 [  RANKING  ]式式式式式式式式式式式式式式忖 ";
    gotoxy(x, y+1);
    cout << "弛                         弛";
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
    cout << "∮  ＝ 識 4貲曖 Ы溯檜橫陛 氈戲貊, 陝 Ы溯檜橫縑啪 28濰曖 蘋萄陛 輿橫餵棲棻.                          ∮";
    gotoxy(3, 27);
    cout << "∮  ＝ 牖憮縑 評塭 'space'煎 蘋萄蒂 菴餵蝗棲棻.                                                       ∮";
    gotoxy(3, 29);
    cout << "∮  ＝ 擅曖 場檣 蘋萄曖 婁橾 熱陛 5偃陛 腎賊 'enter'煎 謙擊 蘑棲棻.                                   ∮";
    gotoxy(3, 31);
    cout << "∮  ＝ 陛濰 說葬 謙擊 耀 餌塋檜 擅曖 蘋萄蒂 賅舒 陛螳骨棲棻.                                          ∮";
    gotoxy(3, 33);
    cout << "∮  ＝ 虜橾 5偃陛 嬴棋 鼻鷓縑憮 謙擊 纂賊, 釭該雖 Ы溯檜橫縑啪 蘋萄蒂 1濰噶 奩陶м棲棻.               ∮";
    gotoxy(3, 35);
    cout << "∮  ＝ 傳 擅縑 釭諦 氈湍 蘋萄朝 棻擠 欐戲煎 剩橫骨棲棻.                                               ∮";
    gotoxy(3, 37);
    cout << "∮  ＝ 蘋萄蒂 賅舒 餌辨и Ы溯檜橫朝 闊衛 驍塊籀葬腌棲棻.                   ＝ 釭陛晦 : esc           ∮";
    gotoxy(3, 39);
    cout << "∮∮∮∮∮∮∮∮∮∮∮∮∮∮∮∮∮∮∮∮∮∮∮∮∮∮∮∮∮∮∮∮∮∮∮∮∮∮∮∮∮∮∮∮∮∮∮∮∮∮∮∮";

}



//[餌辨濠 鼻鷓 滲唳 詭憮萄]
void makeFaceSmile(Player& player) {
    int x=50, y;
    switch (player.getPlayerNum()){
    case 1: y = 5; break;
    case 2: y = 15; break;
    case 3: y = 25; break;
    case 4: y = 35; break;
    }
    gotoxy(x, y);
    cout << "弛  >  < 弛";
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
    cout << "弛  \\  / 弛"; //羲蝸楚衛
}
void makeAllFaceDefault(Player& player) {
    int x = 50, y;
    switch (player.getPlayerNum()) {
    case 1: 
        gotoxy(x,5);
        cout << "弛  〢  〣 弛";
        break;
    case 2: 
        gotoxy(x, 15);
        cout << "弛  Ⅴ  Ⅴ 弛";
        break;
    case 3: 
        gotoxy(x, 25);
        cout << "弛  ∥  ∥ 弛";
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
    cout << "[ "<<winner.getPlayerNum() <<"廓 餌辨濠陛 纔檜綰 嬪曖 賅萇 蘋萄蒂 �僱磈桭炴�. ]" << endl;
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
    emptyCardPrint(winner,looser1,looser2,looser3);
}
//[っ滌] 謙 澀跤蟻擊 唳辦 - 陝 player縑啪 蘋萄 и濰噶 back縑 剩梯
void missRinging(Player& looser, Player& winner1, Player& winner2, Player& winner3) {
    //cout << "謙擊 澀跤蟻戲嘎煎 蘋萄蒂 釭援橫鄹棲棻." << endl;
    //Ы溯檜 陛棟и 檣錳 熱 撮晦
    int cnt = 0;
    if (looser.getAvailable()) cnt++;
    if (winner1.getAvailable()) cnt++;
    if (winner2.getAvailable()) cnt++;
    if (winner3.getAvailable()) cnt++;
    //back 蘋萄陛 橈擊 唳辦,睡褶и 唳辦 驍塊
    if (looser.backIsEmpty() || looser.getBackCount() < cnt - 1) {
        //cout << "鼻渠縑啪 還 蘋萄陛 睡褶ж罹 驍塊腎歷蝗棲棻." << endl;
        looser.setNoneAvailable();
        gotoxy(0,1);
        cout << "驍塊籀葬��" << endl;
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
    ////蘋萄蒂 遽 �醴� 蘋萄陛 橈擊 唳辦 驍塊
    //if (looser.backIsEmpty()) {
    //   // cout << "蘋萄蒂 輿堅 陴擎 蘋萄陛 橈橫 驍塊腎歷蝗棲棻." << endl;
    //    looser.setNoneAvailable();
    //}
    return;
}


//詭景摹鷗
int ReadyGame()
{
    //衛濛�飛� 斜葬晦
    DrawIntro();
    while (true) {
        //酈高 嫡嬴螃晦
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
void printPlayersCardInfo(Player &p1,Player &p2,Player &p3,Player &p4) {
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

//啪歜 衛濛
void StartGame()
{
    DrawStartGame();
    //餌辨濠 儅撩
    Player user(1), p1(2), p2(3), p3(4);
    //蘋萄 楠渾寡纂,餌辨濠縑啪 蘋萄 碟寡
    setInitCard(user, p1, p2, p3);
    //奩犒
    int input = 0;
    int turn = -1;
    while (true) {
        // (1:1:1:1) и貲曖 Ы溯檜橫虜 陴懊擊 唳辦
        if ((int)user.getAvailable() + (int)p1.getAvailable() + (int)p2.getAvailable() + (int)p3.getAvailable() == 1) {
            
            string winnerName = "";
            if (user.getAvailable() == 1) winnerName = "Player 1";
            else if (p1.getAvailable() == 1) winnerName = "Player 2";
            else if (p2.getAvailable() == 1) winnerName = "Player 3";
            else if (p3.getAvailable() == 1) winnerName = "Player 4";

            int x = 20;
            int y = 17;
            gotoxy(x, y);
            cout << "忙式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式忖";
            gotoxy(x, y+1);
            cout << "弛                                         弛";
            gotoxy(x, y + 2);
            cout << "弛                GAME OVER                弛";
            gotoxy(x, y + 3);
            cout << "弛                                         弛";
            gotoxy(x, y + 4);
            cout << "弛             winner :  "<< winnerName<<"          弛";
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
                    gotoxy(x+12, y + 5);
                    cin >> userName;
                    gotoxy(0, 0);
                    cout << userName << endl;
                    //楨韁 �飛� draw
                    DrawRankingScreen();
                    break;
                }
                else if (_getch() == 78 || _getch() == 110){
                    //詭檣戲煎 檜翕м棲棻 3蟾翕寰 嗥遺
                    gotoxy(0, 0);
                    cout << "詭檣戲煎 檜翕" << endl;
                    break;
                }
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
                if (user.open() == -1) continue;
                gotoxy(10, 14);
                frontCardPrint(user.getFrontTopCard(),user);
                input = GameKey();
                if (input == 1) {
                    //婁橾 5偃橾陽 蟻擊 唳辦
                    if (checkFiveCard(user, p1, p2, p3)) {
                        //纔檜綰 嬪曖 蘋萄 賅舒 陛螳馬
                        getAllFrontCard(user, p1, p2, p3);
                        printPlayersCardInfo(user, p1, p2, p3);
                    }
                    //澀跤 蟻擊 唳辦
                    else {
                        missRinging(user, p1, p2, p3);
                        printPlayersCardInfo(user, p1, p2, p3);
                    }
                }
                else if(input==2){
                    //謙 纂雖 彊擠
                }
            }
            if (user.getBackCount() == 0) {
                gotoxy(0, 1);
                cout << "驍塊" << endl;
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
                    //婁橾 5偃橾陽 蟻擊 唳辦
                    if (checkFiveCard(p1, user, p2, p3)) {
                        //纔檜綰 嬪曖 蘋萄 賅舒 陛螳馬
                        getAllFrontCard(p1, user, p2, p3);
                        printPlayersCardInfo(user, p1, p2, p3);
                    }
                    //澀跤 蟻擊 唳辦
                    else {
                        missRinging(p1, user, p2, p3);
                        printPlayersCardInfo(user, p1, p2, p3);
                    }
                }
                else {
                    //謙 纂雖 彊擠
                }
            }
            if (p1.getBackCount() == 0) {
                gotoxy(0, 1);
                cout << "驍塊" << endl;
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
                    //婁橾 5偃橾陽 蟻擊 唳辦
                    if (checkFiveCard(p2, user, p1, p3)) {
                        //纔檜綰 嬪曖 蘋萄 賅舒 陛螳馬
                        getAllFrontCard(p2, user, p1, p3);
                        printPlayersCardInfo(user, p1, p2, p3);
                    }
                    //澀跤 蟻擊 唳辦
                    else {
                        missRinging(p2, user, p1, p3);
                        printPlayersCardInfo(user, p1, p2, p3);
                    }
                }
                else {
                    //謙 纂雖 彊擠
                }
            }
            if (p2.getBackCount() == 0) {
                gotoxy(0, 1);
                cout << "驍塊" << endl;
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
                if (p3.open() == -1) continue;
                gotoxy(40, 14);
                frontCardPrint(p3.getFrontTopCard(),p3);
                input = GameKey();
                if (input == 1) {
                    //婁橾 5偃橾陽 蟻擊 唳辦
                    if (checkFiveCard(p3, p1, p2, user)) {
                        //纔檜綰 嬪曖 蘋萄 賅舒 陛螳馬
                        getAllFrontCard(p3, p1, p2, user);
                        printPlayersCardInfo(user, p1, p2, p3);
                    }
                    //澀跤 蟻擊 唳辦
                    else {
                        //陝 檣錳縑啪 蘋萄 ж釭噶 邀, 蘋萄熱 睡褶й 衛 驍塊
                        missRinging(p3, p1, p2, user);
                        printPlayersCardInfo(user, p1, p2, p3);
                    }
                }
                else {
                    //謙 纂雖 彊擠
                }
            }
            if (p3.getBackCount() == 0) {
                gotoxy(0, 1);
                cout << "驍塊" << endl;
                p3.setNoneAvailable();
                printPlayersCardInfo(user, p1, p2, p3);
            }
        }
        //  cout << "==========================================================" << endl;
        //啪歜 釭陛晦 (鬼薯謙猿)
        if (GetKeyValue() == 27) break;    
    }


    while (true) {
        if (GetKeyValue() == 27)
            break;
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
////啪歜 撲薑
//void GameSetting() {
//    DrawGameSetting();
//
//}
//void DrawGameSetting() {
//    HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
//    system("cls");
//    cout << "啪歜 Ы溯檜 撲薑 �飛�" << endl;
//}
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
        menuValue = ReadyGame();    //檣お煎, 酈 殮溘
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