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
    }
    //菴餵擎 蘋萄蝶鷗曖 陛濰 嬪 蘋萄 奩��
    Card getFrontTopCard() {
        if (front.empty()) return Card();
        return front.top();
    }
    //菴餵雖 彊擎 蘋萄蝶鷗曖 陛濰 嬪 蘋萄 奩��
    Card getBackTopCard() {
        //if (back.empty()) return Card();
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
        //cout << "push脾, "<< getBackCount() << endl;
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


//綴 蘋萄
void emptyCardPrint() {
    cout << "                                               "
        << "旨收收收收收收收收收收收收收收旬" << endl;
    for (int i = 0; i < 7; ++i)
        cout << "                                               "
        << "早           早" << endl;

    cout << "                                               "
        << "曲收收收收收收收收收收收收收收旭" << endl;
}

//擅縑 氈朝 蘋萄 鹵
void frontCardPrint(Card card) {
    //蘋萄 顫殮
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
            << "旨收收收收收收收收收收收收收收旬" << endl;
        cout << "                                               "
            << "早           早" << endl;
        cout << "                                               "
            << "早           早" << endl;
        cout << "                                               "
            << "早           早" << endl;
        cout << "                                               "
            << "早     " << fruit << "     早" << endl;
        cout << "                                               "
            << "早           早" << endl;
        cout << "                                               "
            << "早           早" << endl;
        cout << "                                               "
            << "早           早" << endl;
        cout << "                                               "
            << "曲收收收收收收收收收收收收收收旭" << endl;
        break;
    case 2:
        cout << "                                               "
            << "旨收收收收收收收收收收收收收收旬" << endl;
        cout << "                                               "
            << "早           早" << endl;
        cout << "                                               "
            << "早           早" << endl;
        cout << "                                               "
            << "早     " << fruit << "     早" << endl;
        cout << "                                               "
            << "早           早" << endl;
        cout << "                                               "
            << "早     " << fruit << "     早" << endl;
        cout << "                                               "
            << "早           早" << endl;
        cout << "                                               "
            << "早           早" << endl;
        cout << "                                               "
            << "曲收收收收收收收收收收收收收收旭" << endl;
        break;
    case 3:
        cout << "                                               "
            << "旨收收收收收收收收收收收收收收旬" << endl;
        cout << "                                               "
            << "早           早" << endl;
        cout << "                                               "
            << "早           早" << endl;
        cout << "                                               "
            << "早     " << fruit << "     早" << endl;
        cout << "                                               "
            << "早           早" << endl;
        cout << "                                               "
            << "早   " << fruit << "   " << fruit << "   早" << endl;
        cout << "                                               "
            << "早           早" << endl;
        cout << "                                               "
            << "早           早" << endl;
        cout << "                                               "
            << "曲收收收收收收收收收收收收收收旭" << endl;
        break;
    case 4:
        cout << "                                               "
            << "旨收收收收收收收收收收收收收收旬" << endl;
        cout << "                                               "
            << "早           早" << endl;
        cout << "                                               "
            << "早   " << fruit << "   " << fruit << "   早" << endl;
        cout << "                                               "
            << "早           早" << endl;
        cout << "                                               "
            << "早           早" << endl;
        cout << "                                               "
            << "早           早" << endl;
        cout << "                                               "
            << "早   " << fruit << "   " << fruit << "   早" << endl;
        cout << "                                               "
            << "早           早" << endl;
        cout << "                                               "
            << "曲收收收收收收收收收收收收收收旭" << endl;
        break;
    case 5:
        cout << "                                               "
            << "旨收收收收收收收收收收收收收收旬" << endl;
        cout << "                                               "
            << "早           早" << endl;
        cout << "                                               "
            << "早   " << fruit << "   " << fruit << "   早" << endl;
        cout << "                                               "
            << "早           早" << endl;
        cout << "                                               "
            << "早     " << fruit << "     早" << endl;
        cout << "                                               "
            << "早           早" << endl;
        cout << "                                               "
            << "早   " << fruit << "   " << fruit << "   早" << endl;
        cout << "                                               "
            << "早           早" << endl;
        cout << "                                               "
            << "曲收收收收收收收收收收收收收收旭" << endl;
        break;
    default:
        emptyCardPrint();
    }
}


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


//蘋萄
Card cards[CARDCOUNT] = { //婁橾滌 蘋萄 20濰 (1:6,2:5,3:4,4:3,5:2)
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
void SetConsoleView()
{
    system("mode con cols=120 lines=41 | title Halli Galli");   //�飛橝店�,啪歜檜葷
}
//醴憮檜翕 л熱
void gotoxy(int x, int y)
{
    COORD Pos;
    Pos.X = 2 * x;
    Pos.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
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
//�飛曋庰� draw
void DrawLoading() {

}
//衛濛�飛� draw
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
    cout << "≡";
    gotoxy(29, 21);
    cout << "/‵";
    PrintString(hStdOut, RED);
    gotoxy(28, 22);
    cout << "〧〧〧";
    gotoxy(27, 23);
    cout << "〧〧〧〧";
    gotoxy(27, 24);
    cout << "〧〧〧〧〧〧〧";
    gotoxy(28, 25);
    cout << "〧〧〧〧";


    PrintString(hStdOut, WHITE);
    gotoxy(24, 28);
    cout << "Ⅱ Game Rule for 'r'";
    gotoxy(24, 30);
    cout << "Ⅱ Game Start for 's'";
    gotoxy(24, 32);
    cout << "Ⅱ Exit for 'e'";
}
//啪歜�飛� draw
void DrawStartGame()
{
    //120 41
    system("cls");

    //Ы溯檜橫 1 (餌辨濠) (豭薹 鼻欽)
    gotoxy(0, 0);
    cout << "〧收收收收收收收收收收收收收收〧";
    for (int i = 1; i < 7; i++) {
        gotoxy(0, i);
        cout << "早              早";
    }
    gotoxy(0, 7);
    cout << "〧收收收收收收收收收收收收收收〧";
    gotoxy(0, 8);
    cout << "爾嶸 蘋萄 熱 : " << " 濰";
    gotoxy(0, 9);
    cout << "っ縑 場檣 蘋萄 熱 : " << " 濰";

    //Ы溯檜橫 2 (螃艇薹 鼻欽)
    gotoxy(51, 0);
    cout << "〧收收收收收收收收收收收收收收〧";
    for (int i = 1; i < 7; i++) {
        gotoxy(51, i);
        cout << "早              早";
    }
    gotoxy(51, 7);
    cout << "〧收收收收收收收收收收收收收收〧";
    gotoxy(48, 8);
    cout << "爾嶸 蘋萄 熱 : " << " 濰";
    gotoxy(48, 9);
    cout << "っ縑 場檣 蘋萄 熱 : " << " 濰";

    //Ы溯檜橫 3 (豭薹 ж欽)
    gotoxy(0, 30);
    cout << "爾嶸 蘋萄 熱 : " << " 濰";
    gotoxy(0, 31);
    cout << "っ縑 場檣 蘋萄 熱 : " << " 濰";
    gotoxy(0, 32);
    cout << "〧收收收收收收收收收收收收收收〧";
    for (int i = 33; i < 40; i++) {
        gotoxy(0, i);
        cout << "早              早";
    }
    gotoxy(0, 40);
    cout << "〧收收收收收收收收收收收收收收〧";


    //Ы溯檜橫 4 (螃艇薹 ж欽)
    gotoxy(48, 30);
    cout << "爾嶸 蘋萄 熱 : " << " 濰";
    gotoxy(48, 31);
    cout << "っ縑 場檣 蘋萄 熱 : " << " 濰";
    gotoxy(51, 32);
    cout << "〧收收收收收收收收收收收收收收〧";
    for (int i = 33; i < 40; i++) {
        gotoxy(51, i);
        cout << "早              早";
    }
    gotoxy(51, 40);
    cout << "〧收收收收收收收收收收收收收收〧";


    //蘋萄 1
    gotoxy(10, 14);
    cout << "忙式式式式式式式式式式式式式式忖";
    for (int i = 15; i < 25; i++) {
        gotoxy(10, i);
        cout << "弛              弛";
    }
    gotoxy(10, 25);
    cout << "戌式式式式式式式式式式式式式式戎";

    //蘋萄 2
    gotoxy(20, 14);
    cout << "忙式式式式式式式式式式式式式式忖";
    for (int i = 15; i < 25; i++) {
        gotoxy(20, i);
        cout << "弛              弛";
    }
    gotoxy(20, 25);
    cout << "戌式式式式式式式式式式式式式式戎";

    //蘋萄 3
    gotoxy(30, 14);
    cout << "忙式式式式式式式式式式式式式式忖";
    for (int i = 15; i < 25; i++) {
        gotoxy(30, i);
        cout << "弛              弛";
    }
    gotoxy(30, 25);
    cout << "戌式式式式式式式式式式式式式式戎";

    //蘋萄 4
    gotoxy(40, 14);
    cout << "忙式式式式式式式式式式式式式式忖";
    for (int i = 15; i < 25; i++) {
        gotoxy(40, i);
        cout << "弛              弛";
    }
    gotoxy(40, 25);
    cout << "戌式式式式式式式式式式式式式式戎";


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


//[蘋萄碟寡] swap
void swap(Card* A, Card* B)
{
    Card temp;
    temp = *A;
    *A = *B;
    *B = temp;
}
//[蘋萄碟寡] 蘋萄 楠渾寡纂
void randomCard(Card* card) {
    for (int i = 0; i < CARDCOUNT; i++) swap(&card[i], &card[(rand() % (CARDCOUNT - i)) + i]);
}
//[蘋萄碟寡] 餌辨濠縑啪 蘋萄 碟寡
void setInitCard(Player& p1, Player& p2, Player& p3, Player& p4) {
    randomCard(cards);
    //陝 Ы溯檜橫縑啪 蘋萄 碟寡
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
    cout << "謙擊 蟻蝗棲棻. 纔檜綰曖 蘋萄蒂 橢蝗棲棻." << endl;
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
}
//[っ滌] 謙 澀跤蟻擊 唳辦 - 陝 player縑啪 蘋萄 и濰噶 back縑 剩梯
void missRinging(Player& p1, Player& p2, Player& p3, Player& p4) {
    cout << "謙擊 澀跤蟻戲嘎煎 蘋萄蒂 釭援橫鄹棲棻." << endl;
    //Ы溯檜 陛棟и 檣錳 熱 撮晦
    int cnt = 0;
    if (p1.getAvailable()) cnt++;
    if (p2.getAvailable()) cnt++;
    if (p3.getAvailable()) cnt++;
    if (p4.getAvailable()) cnt++;
    //back 蘋萄陛 橈擊 唳辦,睡褶и 唳辦 驍塊
    if (p1.backIsEmpty() || p1.getBackCount() < cnt - 1) {
        cout << "鼻渠縑啪 還 蘋萄陛 睡褶ж罹 驍塊腎歷蝗棲棻." << endl;
        p1.setNoneAvailable();
        return;
    }
    //啪歜Ы溯檜 陛棟и 檣錳 蘋萄 釭散輿晦
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
    //蘋萄蒂 遽 �醴� 蘋萄陛 橈擊 唳辦 驍塊
    if (p1.backIsEmpty()) {
        cout << "蘋萄蒂 輿堅 陴擎 蘋萄陛 橈橫 驍塊腎歷蝗棲棻." << endl;
        p1.setNoneAvailable();
    }
    return;
}


//[轎溘] 纔檜綰 嬪曖 蘋萄 薑爾
void printTableInfo(Player& user, Player& p1, Player& p2, Player& p3) {
    cout << "⑷營 纔檜綰 蘋萄 [";
    user.getFrontTopCard().getInfo(); cout << ", ";
    p1.getFrontTopCard().getInfo(); cout << ", ";
    p2.getFrontTopCard().getInfo(); cout << ", ";
    p3.getFrontTopCard().getInfo();
    cout << "]" << endl;
}
//[轎溘] 餌辨濠 蘋萄 薑爾
void printBackInfo(Player& user, Player& p1, Player& p2, Player& p3) {
    cout << "⑷營 餌辨濠 蘋萄 [";
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

//詭景摹鷗
int ReadyGame()
{
    //衛濛�飛� 斜葬晦
    DrawIntro();
    while (true) {
        //酈高 嫡嬴螃晦
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
//啪歜 霞ч 酈
int GameKey()
{
    while (true) {
        //酈高 嫡嬴螃晦 (謙纂晦 : 1, 蘋萄 頂晦 : 2, 釭陛晦 : 0)
        int key = GetKeyValue();
        if (key == '\n') {         //謙纂晦 = 1 (enter)
            return 1;
        }
        else if (key == ' ') {    //蘋萄 頂晦 = 2 (space)
            return 2;
        }
        else if (key == 'e' || key == 'E') {    //exit = 0 (esc)
            break;
        }
    }
    return 0;
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
            if (user.getAvailable()) {
                cout << "蝓濠朝 Player1 殮棲棻." << endl;
            }
            else if (p1.getAvailable()) {
                cout << "蝓濠朝 Player2 殮棲棻." << endl;
            }
            else if (p2.getAvailable()) {
                cout << "蝓濠朝 Player3 殮棲棻." << endl;
            }
            else if (p3.getAvailable()) {
                cout << "蝓濠朝 Player4 殮棲棻." << endl;
            }

            break;
        }

        turn++;
        if (turn % 4 == 0) {
            if (!user.getAvailable()) {
                cout << "[ 1廓擎 驍塊腎橫 skip腎歷蝗棲棻. ]" << endl;
                continue;
            }
            else {
                cout << "[ " << user.getPlayerNum() << "廓 離滔 ]" << endl;
                if (user.open() == -1) continue;
                printTableInfo(user, p1, p2, p3);
                printBackInfo(user, p1, p2, p3);
                cout << "纔檜綰 蘋萄 偃熱 : " << user.getFrontCount() << endl;
                cout << "餌辨濠 蘋萄 偃熱 : " << user.getBackCount() << endl;
                cin >> input;
                if (input == 1) {
                    cout << "謙擊 蟻蝗棲棻." << endl;
                    //婁橾 5偃橾陽 蟻擊 唳辦
                    if (checkFiveCard(user, p1, p2, p3)) {
                        //纔檜綰 嬪曖 蘋萄 賅舒 陛螳馬
                        getAllFrontCard(user, p1, p2, p3);
                    }
                    //澀跤 蟻擊 唳辦
                    else {
                        missRinging(user, p1, p2, p3);
                    }
                }
                else {
                    cout << "謙擊 纂雖 彊懊蝗棲棻. 棻擠 欐戲煎 剩橫骨棲棻." << endl;
                }
            }
        }
        else if (turn % 4 == 1) {
            if (!p1.getAvailable()) {
                cout << "[ 2廓擎 驍塊腎橫 skip腎歷蝗棲棻. ]" << endl;
                continue;
            }
            else {
                cout << "[ " << p1.getPlayerNum() << "廓 離滔 ]" << endl;
                if (p1.open() == -1) continue;
                printTableInfo(user, p1, p2, p3);
                printBackInfo(user, p1, p2, p3);
                cout << "纔檜綰 蘋萄 偃熱 : " << p1.getFrontCount() << endl;
                cout << "餌辨濠 蘋萄 偃熱 : " << p1.getBackCount() << endl;
                cin >> input;
                if (input == 1) {
                    cout << "謙擊 蟻蝗棲棻." << endl;
                    //婁橾 5偃橾陽 蟻擊 唳辦
                    if (checkFiveCard(p1, user, p2, p3)) {
                        //纔檜綰 嬪曖 蘋萄 賅舒 陛螳馬
                        getAllFrontCard(p1, user, p2, p3);
                    }
                    //澀跤 蟻擊 唳辦
                    else {
                        missRinging(p1, user, p2, p3);
                    }
                }
                else {
                    cout << "謙擊 纂雖 彊懊蝗棲棻. 棻擠 欐戲煎 剩橫骨棲棻." << endl;
                }
            }
        }
        else if (turn % 4 == 2) {
            if (!p2.getAvailable()) {
                cout << "[ 3廓擎 驍塊腎橫 skip腎歷蝗棲棻. ]" << endl;
                continue;
            }
            else {
                cout << "[ " << p2.getPlayerNum() << "廓 離滔 ]" << endl;
                if (p2.open() == -1) continue;
                printTableInfo(user, p1, p2, p3);
                printBackInfo(user, p1, p2, p3);
                cout << "纔檜綰 蘋萄 偃熱 : " << p2.getFrontCount() << endl;
                cout << "餌辨濠 蘋萄 偃熱 : " << p2.getBackCount() << endl;
                cin >> input;
                if (input == 1) {
                    cout << "謙擊 蟻蝗棲棻." << endl;
                    //婁橾 5偃橾陽 蟻擊 唳辦
                    if (checkFiveCard(p2, user, p1, p3)) {
                        //纔檜綰 嬪曖 蘋萄 賅舒 陛螳馬
                        getAllFrontCard(p2, user, p1, p3);
                    }
                    //澀跤 蟻擊 唳辦
                    else {
                        missRinging(p2, user, p1, p3);
                    }
                }
                else {
                    cout << "謙擊 纂雖 彊懊蝗棲棻. 棻擠 欐戲煎 剩橫骨棲棻." << endl;
                }
            }
        }
        else if (turn % 4 == 3) {
            if (!p3.getAvailable()) {
                cout << "[ 4廓擎 驍塊腎橫 skip腎歷蝗棲棻. ]" << endl;
                continue;
            }
            else {
                cout << "[ " << p3.getPlayerNum() << "廓 離滔 ]" << endl;
                if (p3.open() == -1) continue;
                printTableInfo(user, p1, p2, p3);
                printBackInfo(user, p1, p2, p3);
                cout << "纔檜綰 蘋萄 偃熱 : " << p3.getFrontCount() << endl;
                cout << "餌辨濠 蘋萄 偃熱 : " << p3.getBackCount() << endl;
                cin >> input;
                if (input == 1) {

                    cout << "謙擊 蟻蝗棲棻." << endl;
                    //婁橾 5偃橾陽 蟻擊 唳辦
                    if (checkFiveCard(p3, p1, p2, user)) {
                        //纔檜綰 嬪曖 蘋萄 賅舒 陛螳馬
                        getAllFrontCard(p3, p1, p2, user);
                    }
                    //澀跤 蟻擊 唳辦
                    else {
                        //陝 檣錳縑啪 蘋萄 ж釭噶 邀, 蘋萄熱 睡褶й 衛 驍塊
                        missRinging(p3, p1, p2, user);
                    }
                }
                else {
                    cout << "謙擊 纂雖 彊懊蝗棲棻. 棻擠 欐戲煎 剩橫骨棲棻." << endl;
                }
            }
        }
        cout << "==========================================================" << endl;
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
        if (GetKeyValue() == 27)
            break;
    }
}
//詭檣
int main(void)
{
    SetConsoleView(); //夔樂撲薑
    int menuValue = -1;
    while (true)
    {
        menuValue = ReadyGame();    //檣お煎, 酈 殮溘
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