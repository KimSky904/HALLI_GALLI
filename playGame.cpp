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
//카드 좌표
#define CARDCOUNT 20*4
#define CARD1X 5
#define CARD2X 15
#define CARD3X 25
#define CARD4X 35
#define CARDY 12
//설명 좌표
#define longInfoX 8
#define longInfoY 7

//콘솔 세팅
void SetConsoleView()
{
    system("mode con cols=135 lines=45 | title Halli Galli");   //화면크기,게임이름
}
//커서이동 함수
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
//keyboard 입력값 반환함
int GetKeyValue()
{
    if (_kbhit() != 0) {
        return _getch();
    }
    return 0;
}
//색상지정
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
    //출력
    void getInfo() {
        cout << "[ " << type << " , " << num << " ]";
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
    //점수
    int score;
public:
    //점수 획득
    void plusScore() {
        score += 20;
    }
    //점수 깎임
    void minusScore() {
        score -= 20;
    }
    //점수 반환
    int getScore() {
        return score;
    }
    //소멸자
    ~Player(){};
    //탈락처리
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
        cout << "[탈락] Player " << playerNum;
    }
    //플레이 가능 여부
    bool getAvailable() {
        return available;
    }
    //출력
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
    //초반 카드 수 지정
    Player(int num) {
        playerNum = num;
        available = true;
        score = 0;
    }
    //뒤집은 카드스택의 가장 위 카드 반환
    Card getFrontTopCard() {
        if (front.empty()) return Card();
        return front.top();
    }
    //뒤집지 않은 카드스택의 가장 위 카드 반환
    Card getBackTopCard() {
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
Card cards[CARDCOUNT] = {
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



//콘솔 세팅
void SetConsoleView();
//커서이동 함수
void gotoxy(int x, int y);
//keyboard 입력값 반환함
int GetKeyValue();
//색상지정
void PrintString(HANDLE hStdOut, WORD Attribute);
//[화면 DRAW]
//인트로 화면 draw
void DrawIntro();
//게임 화면 draw
void DrawStartGame();
//설명 화면 draw
void DrawInfoScreen();
//엔딩 화면 draw
void DrawRankingScreen();


//[사용자 상태 변경 메서드]
void makeFaceSmile(Player& player);
void makeFaceAngry(Player& player);
void makeAllFaceDefault(Player& player);

//[카드 출력 메서드]
//빈 카드 출력
void emptyCardPrint(Player& player);
//전체 빈 카드 출력
void emptyCardPrint(Player& one, Player& two, Player& three, Player& four);
//테이블로 낸 카드 출력
void frontCardPrint(Card& card, Player& player);

//[카드 조작 메서드]
//사용자에게 카드 랜덤 분배
int* makeRandArr(int size);
void setInitCard(Player& p1, Player& p2, Player& p3, Player& p4);
//[Ring] 모든 front 승자의 back으로 이동
void getAllFrontCard(Player& winner, Player& looser1, Player& looser2, Player& looser3);
//[MissRing] 각 player에게 한장씩 back으로 이동
void missRinging(Player& p1, Player& p2, Player& p3, Player& p4);

//[카드 판별 메서드]
//과일 수 5개 판별
bool checkFiveCard(Player& user, Player& p1, Player& p2, Player& p3);

//[카드 정보 출력 메서드]
//보유 카드 && 테이블 카드 출력
void printPlayersCardInfo(Player& p1, Player& p2, Player& p3, Player& p4);

//[메뉴 선택]
int ReadyGame();
//[게임 진행 키]
int GameKey();
//[게임 시작]
int main();
void StartGameAlone();
void StartGameMulti();
//[게임 설명]
void ShowInfo();

//----------------------------[카드 출력 메서드]----------------------------
//빈 카드
void emptyCardPrint(Player& player) {
    //카드 출력 위치
    int x;
    int y = CARDY;
    switch (player.getPlayerNum()) {
        case 1: x = CARD1X; break;
        case 2: x = CARD2X; break;
        case 3: x = CARD3X; break;
        case 4: x = CARD4X; break;
    }
    gotoxy(x, y);
    cout << "┏━━━━━━━━━━━━━━┓";
    for (int i = 0; i < 10; ++i) {
        gotoxy(x, y + i);
        cout << "┃           ┃";
    }
    gotoxy(x, y + 7);
    cout << "┗━━━━━━━━━━━━━━┛" << endl;
}
//전체 빈 카드 출력
void emptyCardPrint(Player& one, Player& two, Player& three, Player& four) {
    //카드 출력 위치
    int x;
    int y = CARDY;
    //1
    x = CARD1X;
    gotoxy(x, y);
    cout << "┏━━━━━━━━━━━━━━┓";
    for (int i = 0; i < 11; ++i) {
        gotoxy(x, y + i + 1);
        cout << "┃              ┃";
    }
    gotoxy(x, y + 12);
    cout << "┗━━━━━━━━━━━━━━┛" << endl;
    //2
    x = CARD2X;
    gotoxy(x, y);
    cout << "┏━━━━━━━━━━━━━━┓";
    for (int i = 0; i < 11; ++i) {
        gotoxy(x, y + i + 1);
        cout << "┃              ┃";
    }
    gotoxy(x, y + 12);
    cout << "┗━━━━━━━━━━━━━━┛" << endl;
    //3
    x = CARD3X;
    gotoxy(x, y);
    cout << "┏━━━━━━━━━━━━━━┓";
    for (int i = 0; i < 11; ++i) {
        gotoxy(x, y + i + 1);
        cout << "┃              ┃";
    }
    gotoxy(x, y + 12);
    cout << "┗━━━━━━━━━━━━━━┛" << endl;
    //4
    x = CARD4X;
    gotoxy(x, y);
    cout << "┏━━━━━━━━━━━━━━┓";
    for (int i = 0; i < 11; ++i) {
        gotoxy(x, y + i + 1);
        cout << "┃              ┃";
    }
    gotoxy(x, y + 12);
    cout << "┗━━━━━━━━━━━━━━┛" << endl;
}
//앞에 있는 카드 냄
void frontCardPrint(Card card, Player player) {
    HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
    //카드 타입
    int type = card.getType();
    char fruit = 'e';
    int Color = RED;
    switch (type) {
    case 1: fruit = '@';
        //PrintString(hStdOut, RED);
        Color = RED;
        break; //사과
    case 2: fruit = '@';
        //PrintString(hStdOut, YELLOW);
        Color = YELLOW;
        break; //바나나
    case 3: fruit = '@';
        //PrintString(hStdOut, GREEN);
        Color = GREEN;
        break; //라임
    case 4: fruit = '@';
        //PrintString(hStdOut, RED);
        Color = PURPLE;
        break; //포도
    }
    //카드 출력 위치
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
        cout << "┌──────────────┐" << endl;
        gotoxy(x, y + 1);
        cout << "│              │" << endl;
        gotoxy(x, y + 2);
        cout << "│              │" << endl;
        gotoxy(x, y + 3);
        cout << "│              │" << endl;
        gotoxy(x, y + 4);
        cout << "│              │" << endl;
        gotoxy(x, y + 5);
        cout << "│              │" << endl;
        gotoxy(x, y + 6);
        PrintString(hStdOut, WHITE);
        cout << "│       ";
        PrintString(hStdOut, Color);
        cout << fruit;
        PrintString(hStdOut, WHITE);
        cout << "      │" << endl;
        gotoxy(x, y + 7);
        cout << "│              │" << endl;
        gotoxy(x, y + 8);
        cout << "│              │" << endl;
        gotoxy(x, y + 9);
        cout << "│              │" << endl;
        gotoxy(x, y + 10);
        cout << "│              │" << endl;
        gotoxy(x, y + 11);
        cout << "│              │" << endl;
        gotoxy(x, y + 12);
        cout << "└──────────────┘" << endl;
        break;
    case 2:
        gotoxy(x, y);
        cout << "┌──────────────┐" << endl;
        gotoxy(x, y + 1);
        cout << "│              │" << endl;
        gotoxy(x, y + 2);
        cout << "│              │" << endl;
        gotoxy(x, y + 3);
        PrintString(hStdOut, WHITE);
        cout << "│       ";
        PrintString(hStdOut, Color);
        cout << fruit;
        PrintString(hStdOut, WHITE);
        cout << "      │" << endl;
        gotoxy(x, y + 4);
        cout << "│              │" << endl;
        gotoxy(x, y + 5);
        cout << "│              │" << endl;
        gotoxy(x, y + 6);
        cout << "│              │" << endl;
        gotoxy(x, y + 7);
        cout << "│              │" << endl;
        gotoxy(x, y + 8);
        cout << "│              │" << endl;
        gotoxy(x, y + 9);
        PrintString(hStdOut, WHITE);
        cout << "│       ";
        PrintString(hStdOut, Color);
        cout << fruit;
        PrintString(hStdOut, WHITE);
        cout << "      │" << endl;
        gotoxy(x, y + 10);
        cout << "│              │" << endl;
        gotoxy(x, y + 11);
        cout << "│              │" << endl;
        gotoxy(x, y + 12);
        cout << "└──────────────┘" << endl;
        break;
    case 3:
        gotoxy(x, y);
        cout << "┌──────────────┐" << endl;
        gotoxy(x, y + 1);
        cout << "│              │" << endl;
        gotoxy(x, y + 2);
        cout << "│              │" << endl;
        gotoxy(x, y + 3);
        PrintString(hStdOut, WHITE);
        cout << "│    ";
        PrintString(hStdOut, Color);
        cout << fruit;
        PrintString(hStdOut, WHITE);
        cout << "         │" << endl;
        gotoxy(x, y + 4);
        cout << "│              │" << endl;
        gotoxy(x, y + 5);
        cout << "│              │" << endl;
        gotoxy(x, y + 6);
        PrintString(hStdOut, WHITE);
        cout << "│       ";
        PrintString(hStdOut, Color);
        cout << fruit;
        PrintString(hStdOut, WHITE);
        cout << "      │" << endl;
        gotoxy(x, y + 7);
        cout << "│              │" << endl;
        gotoxy(x, y + 8);
        cout << "│              │" << endl;
        gotoxy(x, y + 9);
        PrintString(hStdOut, WHITE);
        cout << "│          ";
        PrintString(hStdOut, Color);
        cout << fruit;
        PrintString(hStdOut, WHITE);
        cout << "   │" << endl;
        gotoxy(x, y + 10);
        cout << "│              │" << endl;
        gotoxy(x, y + 11);
        cout << "│              │" << endl;
        gotoxy(x, y + 12);
        cout << "└──────────────┘" << endl;
        break;
    case 4:
        gotoxy(x, y);
        cout << "┌──────────────┐" << endl;
        gotoxy(x, y + 1);
        cout << "│              │" << endl;
        gotoxy(x, y + 2);
        cout << "│              │" << endl;
        gotoxy(x, y + 3);
        PrintString(hStdOut, WHITE);
        cout << "│    ";
        PrintString(hStdOut, Color);
        cout << fruit << "     " << fruit;
        PrintString(hStdOut, WHITE);
        cout << "   │" << endl;
        gotoxy(x, y + 4);
        cout << "│              │" << endl;
        gotoxy(x, y + 5);
        cout << "│              │" << endl;
        gotoxy(x, y + 6);
        cout << "│              │" << endl;
        gotoxy(x, y + 7);
        cout << "│              │" << endl;
        gotoxy(x, y + 8);
        cout << "│              │" << endl;
        gotoxy(x, y + 9);
        PrintString(hStdOut, WHITE);
        cout << "│    ";
        PrintString(hStdOut, Color);
        cout << fruit << "     " << fruit;
        PrintString(hStdOut, WHITE);
        cout << "   │" << endl;
        gotoxy(x, y + 10);
        cout << "│              │" << endl;
        gotoxy(x, y + 11);
        cout << "│              │" << endl;
        gotoxy(x, y + 12);
        cout << "└──────────────┘" << endl;
        break;
    case 5:
        gotoxy(x, y);
        cout << "┌──────────────┐" << endl;
        gotoxy(x, y + 1);
        cout << "│              │" << endl;
        gotoxy(x, y + 2);
        cout << "│              │" << endl;
        gotoxy(x, y + 3);
        PrintString(hStdOut, WHITE);
        cout << "│    ";
        PrintString(hStdOut, Color);
        cout << fruit << "     " << fruit;
        PrintString(hStdOut, WHITE);
        cout << "   │" << endl;
        gotoxy(x, y + 4);
        cout << "│              │" << endl;
        gotoxy(x, y + 5);
        cout << "│              │" << endl;
        gotoxy(x, y + 6);
        PrintString(hStdOut, WHITE);
        cout << "│       ";
        PrintString(hStdOut, Color);
        cout << fruit;
        PrintString(hStdOut, WHITE);
        cout << "      │" << endl;
        gotoxy(x, y + 7);
        cout << "│              │" << endl;
        gotoxy(x, y + 8);
        cout << "│              │" << endl;
        gotoxy(x, y + 9);
        PrintString(hStdOut, WHITE);
        cout << "│    ";
        PrintString(hStdOut, Color);
        cout << fruit << "     " << fruit;
        PrintString(hStdOut, WHITE);
        cout << "   │" << endl;
        gotoxy(x, y + 10);
        cout << "│              │" << endl;
        gotoxy(x, y + 11);
        cout << "│              │" << endl;
        gotoxy(x, y + 12);
        cout << "└──────────────┘" << endl;
        break;
    }
}


//첫화면 draw
void DrawIntro()
{
    HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
    int x = 9;
    int y = 8;
    system("cls");
    PrintString(hStdOut, WHITE);
    gotoxy(x, y);
    cout << "##   ##    ##     ####     ####      ####               ####     ##     ####     ####      ####";
    gotoxy(x, y+1);
    cout << "##   ##   ####     ##       ##        ##               ##  ##   ####     ##       ##        ##";
    gotoxy(x, y+2);
    cout << "##   ##  ##  ##    ##       ##        ##              ##       ##  ##    ##       ##        ##";
    gotoxy(x, y+3);
    cout << "#######  ##  ##    ##       ##        ##              ##       ##  ##    ##       ##        ##";
    gotoxy(x, y+4);
    cout << "##   ##  ######    ##   #   ##   #    ##              ##  ###  ######    ##   #   ##   #    ##";
    gotoxy(x, y+5);
    cout << "##   ##  ##  ##    ##  ##   ##  ##    ##               ##  ##  ##  ##    ##  ##   ##  ##    ##";
    gotoxy(x, y+6);
    cout << "##   ##  ##  ##   #######  #######   ####               #####  ##  ##   #######  #######   ####";


    PrintString(hStdOut, WHITE);
    gotoxy(29, 30);
    cout << ">>  Game Rule";
    gotoxy(29, 32);
    cout << "    Game Start";
    gotoxy(29, 34);
    cout << "    Exit";
}
//게임화면 draw
void DrawStartGame()
{
    //120 41
    system("cls");

    //카드 1
    gotoxy(CARD1X, CARDY);
    cout << "┌──────────────┐";
    for (int i = CARDY+1; i < CARDY+12; i++) {
        gotoxy(CARD1X, i);
        cout << "│              │";
    }
    gotoxy(CARD1X, CARDY + 12);
    cout << "└──────────────┘";

    //카드 2
    gotoxy(CARD2X, CARDY);
    cout << "┌──────────────┐";
    for (int i = CARDY+1; i < CARDY+12; i++) {
        gotoxy(CARD2X, i);
        cout << "│              │";
    }
    gotoxy(CARD2X, CARDY+12);
    cout << "└──────────────┘";

    //카드 3
    gotoxy(CARD3X, CARDY);
    cout << "┌──────────────┐";
    for (int i = CARDY+1; i < CARDY+12; i++) {
        gotoxy(CARD3X, i);
        cout << "│              │";
    }
    gotoxy(CARD3X, CARDY+12);
    cout << "└──────────────┘";

    //카드 4
    gotoxy(CARD4X, CARDY);
    cout << "┌──────────────┐";
    for (int i = CARDY+1; i < CARDY+12; i++) {
        gotoxy(CARD4X, i);
        cout << "│              │";
    }
    gotoxy(CARD4X, CARDY+12);
    cout << "└──────────────┘";

    for (int i = 0; i < 45; i++) {
        gotoxy(48, i);
        cout << "│";
    }

    //사용자 상태 정보
    gotoxy(57, 4);
    cout << "Player 1";
    gotoxy(50, 3);
    cout << "┌─────────┐";
    gotoxy(50, 4);
    cout << "│  ⌒  ⌒ │";
    gotoxy(50, 5);
    cout << "│  ◐  ◑ │";
    gotoxy(50, 6);
    cout << "│         │";
    gotoxy(50, 7);
    cout << "│    ∇   │";
    gotoxy(50, 8);
    cout << "└─────────┘";


    gotoxy(57, 14);
    cout << "Player 2";
    gotoxy(50, 13);
    cout << "┌─────────┐";
    gotoxy(50, 14);
    cout << "│  ⌒  ⌒ │";
    gotoxy(50, 15);
    cout << "│  〓  〓 │";
    gotoxy(50, 16);
    cout << "│         │";
    gotoxy(50, 17);
    cout << "│    ∪   │";
    gotoxy(50, 18);
    cout << "└─────────┘";

    gotoxy(57, 24);
    cout << "Player 3";
    gotoxy(50, 23);
    cout << "┌─────────┐";
    gotoxy(50, 24);
    cout << "│  ⌒  ⌒ │";
    gotoxy(50, 25);
    cout << "│  ∧  ∧ │";
    gotoxy(50, 26);
    cout << "│         │";
    gotoxy(50, 27);
    cout << "│    ∪   │";
    gotoxy(50, 28);
    cout << "└─────────┘";

    gotoxy(57, 34);
    cout << "Player 4";
    gotoxy(50, 33);
    cout << "┌─────────┐";
    gotoxy(50, 34);
    cout << "│  ⌒  ⌒ │";
    gotoxy(50, 35);
    cout << "│  ≡  ≡ │";
    gotoxy(50, 36);
    cout << "│         │";
    gotoxy(50, 37);
    cout << "│    ∪   │";
    gotoxy(50, 38);
    cout << "└─────────┘";

}
//엔딩화면 draw
void DrawRankingScreen(int gameType) {
    //135 45
    HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
    system("cls");

    //구조체
    struct players {
        char name[20];
        int score;
        int rank;
    } pl[10];
    FILE* fp1;
   
    //Multi
    if (gameType == 0) {
        //파일에서 읽어옴
        while (true) {
            fopen_s(&fp1, "database.txt", "r");
            if (fp1 == NULL) {
                gotoxy(0, 0);
                cout << "파일이 존재하지 않습니다." << endl;
            }
            else break;
        }
    }
    //Solo
    else {
        //파일에서 읽어옴
        while (true) {
            fopen_s(&fp1, "database_solo.txt", "r");
            if (fp1 == NULL) {
                gotoxy(0, 0);
                cout << "파일이 존재하지 않습니다." << endl;
            }
            else break;
        }
    }
    
    for (int i = 0; i < 10; i++) { 
        fscanf_s(fp1, "%s", pl[i].name, 20);
        fscanf_s(fp1, "%d", &(pl[i].score));
    }
    fclose(fp1);


    //순위 저장
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
    cout << "┌──────── [  RANKING  ]────────┐ ";
    for (int i = 1; i <= 10; i++) {
        for (int j = 0; j < 10; j++) {
            if (pl[j].rank == i) {
                gotoxy(x, ++y);
                cout << "│                              │";
                gotoxy(x, ++y);
                if (pl[j].score == 0) {
                    PrintString(hStdOut, WHITE);
                    printf("│               -              │");
                }
                else {
                    switch (i) {
                    case 1:
                        PrintString(hStdOut, WHITE);
                        cout << "│  ";
                        PrintString(hStdOut, YELLOW);
                        printf("%2d     %10s    %4d", pl[j].rank, pl[j].name, pl[j].score);
                        PrintString(hStdOut, WHITE);
                        cout << "   │";
                        break;
                    case 2:
                        PrintString(hStdOut, WHITE);
                        cout << "│  ";
                        PrintString(hStdOut, 7);
                        printf("%2d     %10s    %4d", pl[j].rank, pl[j].name, pl[j].score);
                        PrintString(hStdOut, WHITE);
                        cout << "   │";
                        break;
                    case 3:
                        PrintString(hStdOut, WHITE);
                        cout << "│  ";
                        PrintString(hStdOut, 6);
                        printf("%2d     %10s    %4d", pl[j].rank, pl[j].name, pl[j].score);
                        PrintString(hStdOut, WHITE);
                        cout << "   │";
                        break;
                    default:
                        PrintString(hStdOut, WHITE);
                        printf("│  %2d     %10s    %4d   │", pl[j].rank, pl[j].name, pl[j].score);
                    }
                }
                
            }
        }
    }
    gotoxy(x, y + 1);
    cout << "│                              │";
    gotoxy(x, y + 2);
    cout << "└──────────────────────────────┘ ";


    //사용자 score 등등
    x = 32;
    y = 8;
    gotoxy(x, y);
    cout << "┌───────────── [  INFO  ]────────────┐ ";
    gotoxy(x, y + 1);
    cout << "│                                    │";
    gotoxy(x, y + 2);
    cout << "│                                    │";
    gotoxy(x, y + 3);
    cout << "│                                    │";
    gotoxy(x, y + 4);
    cout << "│                                    │";
    gotoxy(x, y + 5);
    cout << "│                                    │";
    gotoxy(x, y + 6);
    cout << "│                                    │";
    gotoxy(x, y + 7);
    cout << "│                                    │";
    gotoxy(x, y + 8);
    cout << "│                                    │";
    gotoxy(x, y + 9);
    cout << "│                                    │";
    gotoxy(x, y + 10);
    cout << "└────────────────────────────────────┘ ";

    gotoxy(x, y + 12);
    cout << "┌──────── [  DEVELOPE  INFO  ]───────┐ ";
    gotoxy(x, y + 13);
    cout << "│                                    │";
    gotoxy(x, y + 14);
    cout << "│    latest change    2021.10.30     │";
    gotoxy(x, y + 15); 
    cout << "│                                    │";
    gotoxy(x, y + 16); 
    cout << "│    name                 김하늘     │";
    gotoxy(x, y + 17);
    cout << "│                                    │";
    gotoxy(x, y + 18);
    cout << "│    sch    미림여자정보과학고등학교 │";
    gotoxy(x, y + 19);
    cout << "│                                    │";
    gotoxy(x, y + 20);
    cout << "│    eml    KimCloud52@gmail.com     │";
    gotoxy(x, y + 21);
    cout << "│                                    │";
    gotoxy(x, y + 22);
    cout << "└────────────────────────────────────┘ ";

}
//설명화면 draw
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
            cout << "≫                                                                                                    ≫";
        }
    }
    gotoxy(3, 19);
    cout << "≫≫≫≫≫≫≫≫≫≫≫≫≫≫≫≫≫≫≫≫≫≫≫≫≫≫≫≫≫≫≫≫≫≫≫≫≫≫≫≫≫≫≫≫≫≫≫≫≫≫≫≫";
    gotoxy(3, 21);
    cout << "≫  § 기본 진행방법은 보드게임 '할리갈리'와 동일합니다.                                              ≫";
    gotoxy(3, 23);
    cout << "≫  § 카드를 모두 잃으면 탈락, 끝까지 남은 사람이 승리하게 됩니다.                                   ≫";
    gotoxy(3, 25);
    cout << "≫  § 총 4명의 플레이어가 있으며, 각 플레이어에게 28장의 카드가 주어집니다.                          ≫";
    gotoxy(3, 27);
    cout << "≫  § 순서에 따라 'space'로 카드를 뒤집습니다.                                                       ≫";
    gotoxy(3, 29);
    cout << "≫  § 앞의 놓인 카드의 과일 수가 5개가 되면 'enter'로 종을 칩니다.                                   ≫";
    gotoxy(3, 31);
    cout << "≫  § 가장 빨리 종을 친 사람이 앞의 카드를 모두 가져갑니다.                                          ≫";
    gotoxy(3, 33);
    cout << "≫  § 만일 5개가 아닌 상태에서 종을 치면, 나머지 플레이어에게 카드를 1장씩 반납합니다.               ≫";
    gotoxy(3, 35);
    cout << "≫  § 또 앞에 나와 있던 카드는 다음 턴으로 넘어갑니다.                                               ≫";
    gotoxy(3, 37);
    cout << "≫  § 카드를 모두 사용한 플레이어는 즉시 탈락처리됩니다.                   § 나가기 : esc           ≫";
    gotoxy(3, 39);
    cout << "≫≫≫≫≫≫≫≫≫≫≫≫≫≫≫≫≫≫≫≫≫≫≫≫≫≫≫≫≫≫≫≫≫≫≫≫≫≫≫≫≫≫≫≫≫≫≫≫≫≫≫≫";

}



//[사용자 표정 변경 메서드]
void makeFaceSmile(Player& player) {
    int x=50, y;
    switch (player.getPlayerNum()){
    case 1: y = 5; break;
    case 2: y = 15; break;
    case 3: y = 25; break;
    case 4: y = 35; break;
    }
    gotoxy(x, y);
    cout << "│   >  <  │";
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
    cout << "│  ㅜ  ㅜ │"; 
}
void makeAllFaceDefault(Player& player) {
    int x = 50, y;
    switch (player.getPlayerNum()) {
    case 1: 
        gotoxy(x,5);
        cout << "│  ◐  ◑ │";
        break;
    case 2: 
        gotoxy(x, 15);
        cout << "│  〓  〓 │";
        break;
    case 3: 
        gotoxy(x, 25);
        cout << "│  ∧  ∧ │";
        break;
    case 4: 
        gotoxy(x, 35);
        cout << "│  ≡  ≡ │";
        break;
    }
}


//[카드조작] 사용자에게 카드 분배
int* makeRandArr(int size) {
    int* arr = new int[size] { 0, };
    int* chk = new int[size] { 0, };
    int cnt = 0;

    srand((unsigned int)time(NULL));

    while (cnt < size) {
        int r = rand() % size;      // 0 ~ size 난수 생성
        if (!chk[r]) {              // 이미 뽑힌 적이 없는 숫자면
            ++chk[r], arr[cnt] = r; // 체크 후 shuffle 배열에 추가
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

//[판별] 과일 수 5개 판별
bool checkFiveCard(Player& user, Player& p1, Player& p2, Player& p3) {
    //각 과일에 대한 개수 배열
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
//[판별] 종쳤을 경우 - 모든 front를 승자의 back으로 이동
void getAllFrontCard(Player& winner, Player& looser1, Player& looser2, Player& looser3) {
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
    //테이블 카드 초기화
    emptyCardPrint(winner,looser1,looser2,looser3);
    //설명 출력
    gotoxy(longInfoX+4, longInfoY);
    cout << winner.getPlayerNum() << "번 플레이어가 종을 쳤습니다. 테이블의 모든 카드 획득!";
    Sleep(2000);
    gotoxy(longInfoX, longInfoY);
    cout << "                                                                          ";
}
//[판별] 종 잘못쳤을 경우 - 각 player에게 카드 한장씩 back에 넘김
void missRinging(Player& looser, Player& winner1, Player& winner2, Player& winner3) {
    //플레이 가능한 인원 수 세기
    int cnt = 0;
    if (looser.getAvailable()) cnt++;
    if (winner1.getAvailable()) cnt++;
    if (winner2.getAvailable()) cnt++;
    if (winner3.getAvailable()) cnt++;
    //back 카드가 없을 경우,부족한 경우 탈락
    if (looser.backIsEmpty() || looser.getBackCount() < cnt - 1) {
        looser.setNoneAvailable();
        //설명 출력
        gotoxy(longInfoX+6, longInfoY);
        cout << looser.getPlayerNum() << "번 플레이어는 카드가 부족하여 탈락되었습니다.";
        Sleep(2000);
        gotoxy(longInfoX+6, longInfoY);
        cout << "                                                      ";
        return;
    }
    //게임플레이 가능한 인원 카드 나눠주기
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
    //설명 출력
    gotoxy(longInfoX, longInfoY);
    cout << looser.getPlayerNum() << "번 플레이어가 종을 잘못쳤습니다. 각 인원에게 카드를 나누어줍니다.";
    Sleep(2000);
    gotoxy(longInfoX, longInfoY);
    cout << "                                                                          ";
    return;
}


//메뉴선택
int ReadyGame()
{
    //시작화면 그리기
    DrawIntro();
    int result = 0;
    int x = 31;
    int y = 30;
    gotoxy(x, y);
    while (true) {
        int num = _getch();
        switch (num)
        {
        //위
        case 72: {
            if (y > 30) {
                gotoxy(x - 2, y);
                printf("  ");
                gotoxy(x - 2, y -= 2);
                printf(">>");
            }
            break;
        }
        //아래
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
            result = y - 30; //0 또는 2 또는 4
            gotoxy(0, 0);
            cout << result <<"   " << endl;
            return result;
        //exit
        case 27:
            return -1;
        }
    }
    
    return 0;
}
//게임 진행 키
int GameKey()
{
    while (true) {
        //키값 받아오기 (종치기 : 1, 카드 내기 : 2, 나가기 : 0)
        int key = _getch();
        if (key == 13) {         //종치기 = 1 (enter)
            return 1;
        }
        else if (key == 32) {    //카드 내기 = 2 (space)
            return 2;
        }
        else if (key == 27) {    //exit = 0 (esc)
            return 3;
        }
    }
    return 0;
}

//보유 카드 && 테이블 카드 출력
void printPlayersCardInfo(Player &p1,Player &p2,Player &p3,Player &p4) {

    gotoxy(57, 6);
    cout << "테이블카드 수 : " << p1.getFrontCount() << "  ";
    gotoxy(57, 7);
    cout << "소유카드 수 : " << p1.getBackCount() << "  ";

    gotoxy(57, 16);
    cout << "테이블카드 수 : " << p2.getFrontCount() << "  ";
    gotoxy(57, 17);
    cout << "소유카드 수 : " << p2.getBackCount() << "  ";

    gotoxy(57, 26);
    cout << "테이블카드 수 : " << p3.getFrontCount() << "  ";
    gotoxy(57, 27);
    cout << "소유카드 수 : " << p3.getBackCount() << "  ";

    gotoxy(57, 36);
    cout << "테이블카드 수 : " << p4.getFrontCount() << "  ";
    gotoxy(57, 37);
    cout << "소유카드 수 : " << p4.getBackCount() << "  ";
}

void DrawChoosePlaying() {
    system("cls");

    int x = 20;
    int y = 17;
    gotoxy(x, y);
    cout << "┌───────────────────────────────────────────────┐";
    gotoxy(x, y + 1); 
    cout << "│                                               │";
    gotoxy(x, y + 2);
    cout << "│               게임 진행 방식 선택             │";
    gotoxy(x, y + 3);
    cout << "│                                               │";
    gotoxy(x, y + 4);
    cout << "│                 >>  1 Players                 │";
    gotoxy(x, y + 5);
    cout << "│                                               │";
    gotoxy(x, y + 6);
    cout << "│                     4 Players                 │";
    gotoxy(x, y + 7);
    cout << "│                                               │";
    gotoxy(x, y + 8);
    cout << "└───────────────────────────────────────────────┘";


}
//게임 시작 (1 vs 1 vs 1 vs 1)
void StartGameMulti()
{
    //4명이 플레이할 경우(카드 넘기기/종치기) : qw  xc  nm  op
    DrawStartGame();
    //조작법 draw
    {
        int x = 12;
        gotoxy(x, 30);
        cout << "┌───────────  조작법 ( NEXT / BELL ) ──────────┐";
        gotoxy(x, 31);
        cout << "│                                              │";
        gotoxy(x, 32);
        cout << "│           Player 1   ▷   Q  /  W            │";
        gotoxy(x, 33); 
        cout << "│                                              │";
        gotoxy(x, 34);
        cout << "│           Player 2   ▷   X  /  C            │";
        gotoxy(x, 35);
        cout << "│                                              │";
        gotoxy(x, 36);
        cout << "│           Player 3   ▷   N  /  M            │";
        gotoxy(x, 37);
        cout << "│                                              │";
        gotoxy(x, 38);
        cout << "│           Player 4   ▷   O  /  P            │";
        gotoxy(x, 39); 
        cout << "│                                              │";
        gotoxy(x, 40);
        cout << "└──────────────────────────────────────────────┘";
    }
    //사용자 생성
    Player user(1), p1(2), p2(3), p3(4);
    //카드 랜덤배치,사용자에게 카드 분배
    setInitCard(user, p1, p2, p3);
    //반복
    int input = 0;
    int turn = -1;
    while (true) {
        // (1:1:1:1) 한명의 플레이어만 남았을 경우
        if ((int)user.getAvailable() + (int)p1.getAvailable() + (int)p2.getAvailable() + (int)p3.getAvailable() == 1) { 
            string winnerName = "";
            if (user.getAvailable() == 1) winnerName = "Player 1";
            else if (p1.getAvailable() == 1) winnerName = "Player 2";
            else if (p2.getAvailable() == 1) winnerName = "Player 3";
            else if (p3.getAvailable() == 1) winnerName = "Player 4";
            //랭킹 물어보기
            {
                int x = 20;
                int y = 17;
                gotoxy(x, y);
                cout << "┌─────────────────────────────────────────┐";
                gotoxy(x, y+1);
                cout << "│                                         │";
                gotoxy(x, y + 2);
                cout << "│                GAME OVER                │";
                gotoxy(x, y + 3);
                cout << "│                                         │";
                gotoxy(x, y + 4);
                cout << "│             winner :  "<< winnerName<<"          │";
                gotoxy(x, y + 5);
                cout << "│                                         │";
                gotoxy(x, y + 6);
                cout << "│   랭킹을 작성하시겠습니까?  [ Y / N ]   │";
                gotoxy(x, y + 7);
                cout << "│                                         │";
                gotoxy(x, y + 8);
                cout << "└─────────────────────────────────────────┘";
            
                //Y 또는 N 선택
                while (true) {
                    if (_getch() == 89 || _getch() == 121) {
                        string userName = "";
                        gotoxy(x, y + 4);
                        cout << "│                                         │";
                        gotoxy(x, y + 5);
                        cout << "│    닉네임 입력 :                        │";
                        gotoxy(x, y + 6);
                        cout << "│                                         │";
                        gotoxy(x+12, y + 5);
                        cin >> userName;
                        gotoxy(0, 0);
                        cout << userName << endl;

                        //사용자 이름, 점수 파일에 저장
                        ofstream out("database.txt", ios::app);
                        //임시 점수
                        int score = 100;
                        out << userName << " " << score << "\n";
                        out.close();

                        //랭킹 화면 draw
                        DrawRankingScreen(0);
                        break;
                    }
                    else if (_getch() == 78 || _getch() == 110){
                        gotoxy(x, y);
                        cout << "┌─────────────────────────────────────────┐";
                        gotoxy(x, y + 1);
                        cout << "│                                         │";
                        gotoxy(x, y + 2);
                        cout << "│                GAME OVER                │";
                        gotoxy(x, y + 3);
                        cout << "│                                         │";
                        gotoxy(x, y + 4);
                        cout << "│     잠시후 메인화면으로 이동합니다.     │";
                        gotoxy(x, y + 5);
                        cout << "│                                         │";
                        gotoxy(x, y + 6);
                        cout << "│                                         │";
                        gotoxy(x, y + 7);
                        cout << "│                                         │";
                        gotoxy(x, y + 8);
                        cout << "└─────────────────────────────────────────┘";
                        Sleep(2000);
                        //메인으로 이동
                        break;
                    }
                }
                break;
            }
        }

        turn++;
        //1번 차례
        if (turn % 4 == 0) {
            printPlayersCardInfo(user, p1, p2, p3);
            if (!user.getAvailable()) {
                continue;
            }
            else {
                //Player 1 : 카드 내기 Q, 종치기 W (81,113 / 87,119)

                //체크
                gotoxy(0, 1);
                cout << "1번 차례";
                Sleep(500);
                gotoxy(0, 1);
                cout << "            ";

                //설명 출력
                gotoxy(longInfoX + 13, longInfoY - 2);
                cout << "                                        ";
                gotoxy(longInfoX + 13, longInfoY - 2);
                cout << "[ " << user.getPlayerNum() << "번 PLAYER ]";

                //카드 낼때까지 기다림
                int cardInput = 0;
                while (true) {
                    cardInput = _getch();
                    if (cardInput == 81 || cardInput == 113) break;
                }

                //체크
                gotoxy(0, 1);
                cout << "(1) 빠져나옴";
                Sleep(500);
                gotoxy(0, 1);
                cout << "            ";

                //카드 뒤집기
                if (cardInput == 81 || cardInput == 113) {
                    if (user.open() == -1) continue;
                    gotoxy(10, 14);
                    frontCardPrint(user.getFrontTopCard(), user);
                    input = _getch();
                    //종 치기
                    if (input == 87 || input == 119 ) { //user가 종 친 경우
                        //체크
                        gotoxy(0, 1);
                        cout << "1번이 종침";
                        Sleep(500);
                        gotoxy(0, 1);
                        cout << "            ";
                        PlaySound(TEXT("ringingBell.wav"), 0, SND_FILENAME | SND_ASYNC);
                        //과일 5개일때 쳤을 경우
                        if (checkFiveCard(user, p1, p2, p3)) {
                            //점수 계산
                            user.plusScore();
                            //(나)웃는 표정
                            makeAllFaceDefault(p1);
                            makeAllFaceDefault(p2);
                            makeAllFaceDefault(p3);
                            makeFaceSmile(user);
                            //테이블 위의 카드 모두 가져감
                            getAllFrontCard(user, p1, p2, p3);
                            printPlayersCardInfo(user, p1, p2, p3);
                        }
                        //잘못 쳤을 경우
                        else {
                            //점수 계산
                            user.minusScore();
                            //화난 표정
                            makeAllFaceDefault(p1);
                            makeAllFaceDefault(p2);
                            makeAllFaceDefault(p3);
                            makeFaceAngry(user);
                            PlaySound(TEXT("missingBell.wav"), 0, SND_FILENAME | SND_ASYNC);
                            //카드 한장씩 나누어줌
                            missRinging(user, p1, p2, p3);
                            printPlayersCardInfo(user, p1, p2, p3);
                        }
                    }
                    //종 치기
                    else if (input == 67 || input == 99) { //p1가 종 친 경우
                        //체크
                        gotoxy(0, 1);
                        cout << "2번이 종침";
                        Sleep(500);
                        gotoxy(0, 1);
                        cout << "            ";
                        PlaySound(TEXT("ringingBell.wav"), 0, SND_FILENAME | SND_ASYNC);
                        //과일 5개일때 쳤을 경우
                        if (checkFiveCard(user, p1, p2, p3)) {
                            //점수 계산
                            p1.plusScore();
                            //(나)웃는 표정
                            makeAllFaceDefault(user);
                            makeAllFaceDefault(p2);
                            makeAllFaceDefault(p3);
                            makeFaceSmile(p1);
                            //테이블 위의 카드 모두 가져감
                            getAllFrontCard(p1, user, p2, p3);
                            printPlayersCardInfo(user, p1, p2, p3);
                        }
                        //잘못 쳤을 경우
                        else {
                            //점수 계산
                            p1.minusScore();
                            //화난 표정, 나머지 기본 표정
                            makeAllFaceDefault(user);
                            makeAllFaceDefault(p2);
                            makeAllFaceDefault(p3);
                            makeFaceAngry(p1);
                            PlaySound(TEXT("missingBell.wav"), 0, SND_FILENAME | SND_ASYNC);
                            //카드 한장씩 나누어줌
                            missRinging(p1, user, p2, p3);
                            printPlayersCardInfo(user, p1, p2, p3);
                        }
                    }
                    //종 치기
                    else if (input == 77 || input == 109) { //p2가 종 친 경우
                        //체크
                        gotoxy(0, 1);
                        cout << "3번이 종침";
                        Sleep(500);
                        gotoxy(0, 1);
                        cout << "            ";
                        PlaySound(TEXT("ringingBell.wav"), 0, SND_FILENAME | SND_ASYNC);
                        //과일 5개일때 쳤을 경우
                        if (checkFiveCard(user, p1, p2, p3)) {
                            //점수 계산
                            p2.plusScore();
                            //(나)웃는 표정
                            makeAllFaceDefault(p1);
                            makeAllFaceDefault(user);
                            makeAllFaceDefault(p3);
                            makeFaceSmile(p2);
                            //테이블 위의 카드 모두 가져감
                            getAllFrontCard(p2, p1, user, p3);
                            printPlayersCardInfo(user, p1, p2, p3);
                        }
                        //잘못 쳤을 경우
                        else {
                            //점수 계산
                            p2.minusScore();
                            //화난 표정, 나머지 기본 표정
                            makeAllFaceDefault(p1);
                            makeAllFaceDefault(user);
                            makeAllFaceDefault(p3);
                            makeFaceAngry(p2);
                            PlaySound(TEXT("missingBell.wav"), 0, SND_FILENAME | SND_ASYNC);
                            missRinging(p2, p1, user, p3);
                            printPlayersCardInfo(user, p1, p2, p3);
                        }
                    }
                    //종 치기
                    else if (input == 80 || input == 112) { //p3가 종 친 경우
                        //체크
                        gotoxy(0, 1);
                        cout << "4번이 종침";
                        Sleep(500);
                        gotoxy(0, 1);
                        cout << "            ";
                        PlaySound(TEXT("ringingBell.wav"), 0, SND_FILENAME | SND_ASYNC);
                        //과일 5개일때 쳤을 경우
                        if (checkFiveCard(user, p1, p2, p3)) {
                            //점수 계산
                            p3.plusScore();
                            //(나)웃는 표정
                            makeAllFaceDefault(p1);
                            makeAllFaceDefault(p2);
                            makeAllFaceDefault(user);
                            makeFaceSmile(p3);
                            //테이블 위의 카드 모두 가져감
                            getAllFrontCard(p3, p1, p2, user);
                            printPlayersCardInfo(user, p1, p2, p3);
                        }
                        //잘못 쳤을 경우
                        else {
                            //점수 계산
                            p3.minusScore();
                            //화난 표정, 나머지 기본 표정
                            makeAllFaceDefault(p1);
                            makeAllFaceDefault(p2);
                            makeAllFaceDefault(user);
                            makeFaceAngry(p3);
                            PlaySound(TEXT("missingBell.wav"), 0, SND_FILENAME | SND_ASYNC);
                            missRinging(p3, p1, p2, user);
                            printPlayersCardInfo(user, p1, p2, p3);
                        }
                    }
                    //else if (input == 81 || input == 119) {
                    //    //종 치지 않음
                    //    continue;
                    //}
                    //이상한 키 누른 경우 (카드 넘길때)
                    else {
                        gotoxy(0, 0);
                        cout << "else!!";
                        Sleep(50);
                        gotoxy(0, 0);
                        cout << "         ";
                    }
                }
            }
            if (user.getBackCount() == 0) {
                //화난 표정
                makeAllFaceDefault(p1);
                makeAllFaceDefault(p2);
                makeAllFaceDefault(p3);
                makeFaceAngry(user);
                user.setNoneAvailable();
                printPlayersCardInfo(user, p1, p2, p3);
                gotoxy(longInfoX + 10, longInfoY);
                cout << user.getPlayerNum()<< "번 사용자가 탈락되었습니다.";
                Sleep(2000);
                gotoxy(longInfoX + 10, longInfoY);
                cout << "                              ";
            }
        }
        else if (turn % 4 == 1) {
            printPlayersCardInfo(user, p1, p2, p3);
            if (!p1.getAvailable()) {
                continue;
            }
            else {
                //Player 2 : 카드 내기 X, 종치기 C (88,120 / 67,99)
                
                //체크
                gotoxy(0, 1);
                cout << "2번 차례";
                Sleep(500);
                gotoxy(0, 1);
                cout << "            ";

                //설명 출력
                gotoxy(longInfoX + 13, longInfoY - 2);
                cout << "                                        ";
                gotoxy(longInfoX + 13, longInfoY - 2);
                cout << "[ " << p1.getPlayerNum() << "번 PLAYER ]";

                //카드 낼때까지 기다림
                int cardInput = 0;
                while (true) {
                    cardInput = _getch();
                    if (cardInput == 88 || cardInput == 120) break;
                }
                //체크
                gotoxy(0, 1);
                cout << "(2) 빠져나옴";
                Sleep(500);
                gotoxy(0, 1);
                cout << "            ";

                //카드 뒤집기
                if (cardInput == 88 || cardInput == 120) {
                    if (p1.open() == -1) continue;
                    gotoxy(10, 14);
                    frontCardPrint(p1.getFrontTopCard(), p1);
                    input = _getch();
                    //종 치기
                    if (input == 87 || input == 119) { //user가 종 친 경우
                        //체크
                        gotoxy(0, 1);
                        cout << "1번이 종침";
                        Sleep(500);
                        gotoxy(0, 1);
                        cout << "            ";
                        PlaySound(TEXT("ringingBell.wav"), 0, SND_FILENAME | SND_ASYNC);
                        //과일 5개일때 쳤을 경우
                        if (checkFiveCard(user, p1, p2, p3)) {
                            //점수 계산
                            user.plusScore();
                            //(나)웃는 표정
                            makeAllFaceDefault(p1);
                            makeAllFaceDefault(p2);
                            makeAllFaceDefault(p3);
                            makeFaceSmile(user);
                            //테이블 위의 카드 모두 가져감
                            getAllFrontCard(user, p1, p2, p3);
                            printPlayersCardInfo(user, p1, p2, p3);
                        }
                        //잘못 쳤을 경우
                        else {
                            //점수 계산
                            user.minusScore();
                            //화난 표정
                            makeAllFaceDefault(p1);
                            makeAllFaceDefault(p2);
                            makeAllFaceDefault(p3);
                            makeFaceAngry(user);
                            PlaySound(TEXT("missingBell.wav"), 0, SND_FILENAME | SND_ASYNC);
                            //카드 한장씩 나누어줌
                            missRinging(user, p1, p2, p3);
                            printPlayersCardInfo(user, p1, p2, p3);
                        }
                    }
                    //종 치기
                    else if (input == 67 || input == 99) { //p1가 종 친 경우
                        //체크
                        gotoxy(0, 1);
                        cout << "2번이 종침";
                        Sleep(500);
                        gotoxy(0, 1);
                        cout << "            ";
                        PlaySound(TEXT("ringingBell.wav"), 0, SND_FILENAME | SND_ASYNC);
                        //과일 5개일때 쳤을 경우
                        if (checkFiveCard(user, p1, p2, p3)) {
                            //점수 계산
                            p1.plusScore();
                            //(나)웃는 표정
                            makeAllFaceDefault(user);
                            makeAllFaceDefault(p2);
                            makeAllFaceDefault(p3);
                            makeFaceSmile(p1);
                            //테이블 위의 카드 모두 가져감
                            getAllFrontCard(p1, user, p2, p3);
                            printPlayersCardInfo(user, p1, p2, p3);
                        }
                        //잘못 쳤을 경우
                        else {
                            //점수 계산
                            p1.minusScore();
                            //화난 표정, 나머지 기본 표정
                            makeAllFaceDefault(user);
                            makeAllFaceDefault(p2);
                            makeAllFaceDefault(p3);
                            makeFaceAngry(p1);
                            PlaySound(TEXT("missingBell.wav"), 0, SND_FILENAME | SND_ASYNC);
                            //카드 한장씩 나누어줌
                            missRinging(p1, user, p2, p3);
                            printPlayersCardInfo(user, p1, p2, p3);
                        }
                    }
                    //종 치기
                    else if (input == 77 || input == 109) { //p2가 종 친 경우
                        //체크
                        gotoxy(0, 1);
                        cout << "3번이 종침";
                        Sleep(500);
                        gotoxy(0, 1);
                        cout << "            ";
                        PlaySound(TEXT("ringingBell.wav"), 0, SND_FILENAME | SND_ASYNC);
                        //과일 5개일때 쳤을 경우
                        if (checkFiveCard(user, p1, p2, p3)) {
                            //점수 계산
                            p2.plusScore();
                            //(나)웃는 표정
                            makeAllFaceDefault(p1);
                            makeAllFaceDefault(user);
                            makeAllFaceDefault(p3);
                            makeFaceSmile(p2);
                            //테이블 위의 카드 모두 가져감
                            getAllFrontCard(p2, p1, user, p3);
                            printPlayersCardInfo(user, p1, p2, p3);
                        }
                        //잘못 쳤을 경우
                        else {
                            //점수 계산
                            p2.minusScore();
                            //화난 표정, 나머지 기본 표정
                            makeAllFaceDefault(p1);
                            makeAllFaceDefault(user);
                            makeAllFaceDefault(p3);
                            makeFaceAngry(p2);
                            PlaySound(TEXT("missingBell.wav"), 0, SND_FILENAME | SND_ASYNC);
                            missRinging(p2, p1, user, p3);
                            printPlayersCardInfo(user, p1, p2, p3);
                        }
                    }
                    //종 치기
                    else if (input == 80 || input == 112) { //p3가 종 친 경우
                        //체크
                        gotoxy(0, 1);
                        cout << "4번이 종침";
                        Sleep(500);
                        gotoxy(0, 1);
                        cout << "            ";
                        PlaySound(TEXT("ringingBell.wav"), 0, SND_FILENAME | SND_ASYNC);
                        //과일 5개일때 쳤을 경우
                        if (checkFiveCard(user, p1, p2, p3)) {
                            //점수 계산
                            p3.plusScore();
                            //(나)웃는 표정
                            makeAllFaceDefault(p1);
                            makeAllFaceDefault(p2);
                            makeAllFaceDefault(user);
                            makeFaceSmile(p3);
                            //테이블 위의 카드 모두 가져감
                            getAllFrontCard(p3, p1, p2, user);
                            printPlayersCardInfo(user, p1, p2, p3);
                        }
                        //잘못 쳤을 경우
                        else {
                            //점수 계산
                            p3.minusScore();
                            //화난 표정, 나머지 기본 표정
                            makeAllFaceDefault(p1);
                            makeAllFaceDefault(p2);
                            makeAllFaceDefault(user);
                            makeFaceAngry(p3);
                            PlaySound(TEXT("missingBell.wav"), 0, SND_FILENAME | SND_ASYNC);
                            missRinging(p3, p1, p2, user);
                            printPlayersCardInfo(user, p1, p2, p3);
                        }
                    }
                    //else if (input == 81 || input == 119) {
                    //    //종 치지 않음
                    //    continue;
                    //}
                    //아무도 종을 치지 않을 경우
                    else {
                        gotoxy(0, 0);
                        cout << "else!!";
                        Sleep(50);
                        gotoxy(0, 0);
                        cout << "         ";
                    }
                }
            }
            if (p1.getBackCount() == 0) {
                //화난 표정
                makeAllFaceDefault(user);
                makeAllFaceDefault(p2);
                makeAllFaceDefault(p3);
                makeFaceAngry(p1);
                p1.setNoneAvailable();
                printPlayersCardInfo(user, p1, p2, p3);
                gotoxy(longInfoX + 10, longInfoY);
                cout << p1.getPlayerNum() << "번 사용자가 탈락되었습니다.";
                Sleep(2000);
                gotoxy(longInfoX + 10, longInfoY);
                cout << "                              ";
            }
        }
        else if (turn % 4 == 2) {
            printPlayersCardInfo(user, p1, p2, p3);
            if (!p2.getAvailable()) {
                continue;
            }
            else {
                //Player 3 : 카드 내기 N, 종치기 M (78,110 / 77,109)

                //체크
                gotoxy(0, 1);
                cout << "3번 차례";
                Sleep(500);
                gotoxy(0, 1);
                cout << "            ";

                //설명 출력
                gotoxy(longInfoX + 13, longInfoY - 2);
                cout << "                                        ";
                gotoxy(longInfoX + 13, longInfoY - 2);
                cout << "[ " << p2.getPlayerNum() << "번 PLAYER ]";

                //카드 낼때까지 기다림
                int cardInput = 0;
                while (true) {
                    cardInput = _getch();
                    if (cardInput == 78 || cardInput == 110) break;
                }
                //체크
                gotoxy(0, 1);
                cout << "(3) 빠져나옴";
                Sleep(500);
                gotoxy(0, 1);
                cout << "            ";

                //카드 뒤집기
                if (cardInput == 78 || cardInput == 110) {
                    if (p2.open() == -1) continue;
                    gotoxy(10, 14);
                    frontCardPrint(p2.getFrontTopCard(), p2);
                    input = _getch();
                    //종 치기
                    if (input == 87 || input == 119) { //user가 종 친 경우
                        //체크
                        gotoxy(0, 1);
                        cout << "1번이 종침";
                        Sleep(500);
                        gotoxy(0, 1);
                        cout << "            ";
                        PlaySound(TEXT("ringingBell.wav"), 0, SND_FILENAME | SND_ASYNC);
                        //과일 5개일때 쳤을 경우
                        if (checkFiveCard(user, p1, p2, p3)) {
                            //점수 계산
                            user.plusScore();
                            //(나)웃는 표정
                            makeAllFaceDefault(p1);
                            makeAllFaceDefault(p2);
                            makeAllFaceDefault(p3);
                            makeFaceSmile(user);
                            //테이블 위의 카드 모두 가져감
                            getAllFrontCard(user, p1, p2, p3);
                            printPlayersCardInfo(user, p1, p2, p3);
                        }
                        //잘못 쳤을 경우
                        else {
                            //점수 계산
                            user.minusScore();
                            //화난 표정
                            makeAllFaceDefault(p1);
                            makeAllFaceDefault(p2);
                            makeAllFaceDefault(p3);
                            makeFaceAngry(user);
                            PlaySound(TEXT("missingBell.wav"), 0, SND_FILENAME | SND_ASYNC);
                            //카드 한장씩 나누어줌
                            missRinging(user, p1, p2, p3);
                            printPlayersCardInfo(user, p1, p2, p3);
                        }
                    }
                    //종 치기
                    else if (input == 67 || input == 99) { //p1가 종 친 경우
                        //체크
                        gotoxy(0, 1);
                        cout << "2번이 종침";
                        Sleep(500);
                        gotoxy(0, 1);
                        cout << "            ";
                        PlaySound(TEXT("ringingBell.wav"), 0, SND_FILENAME | SND_ASYNC);
                        //과일 5개일때 쳤을 경우
                        if (checkFiveCard(user, p1, p2, p3)) {
                            //점수 계산
                            p1.plusScore();
                            //(나)웃는 표정
                            makeAllFaceDefault(user);
                            makeAllFaceDefault(p2);
                            makeAllFaceDefault(p3);
                            makeFaceSmile(p1);
                            //테이블 위의 카드 모두 가져감
                            getAllFrontCard(p1, user, p2, p3);
                            printPlayersCardInfo(user, p1, p2, p3);
                        }
                        //잘못 쳤을 경우
                        else {
                            //점수 계산
                            p1.minusScore();
                            //화난 표정, 나머지 기본 표정
                            makeAllFaceDefault(user);
                            makeAllFaceDefault(p2);
                            makeAllFaceDefault(p3);
                            makeFaceAngry(p1);
                            PlaySound(TEXT("missingBell.wav"), 0, SND_FILENAME | SND_ASYNC);
                            //카드 한장씩 나누어줌
                            missRinging(p1, user, p2, p3);
                            printPlayersCardInfo(user, p1, p2, p3);
                        }
                    }
                    //종 치기
                    else if (input == 77 || input == 109) { //p2가 종 친 경우
                        //체크
                        gotoxy(0, 1);
                        cout << "3번이 종침";
                        Sleep(500);
                        gotoxy(0, 1);
                        cout << "            ";
                        PlaySound(TEXT("ringingBell.wav"), 0, SND_FILENAME | SND_ASYNC);
                        //과일 5개일때 쳤을 경우
                        if (checkFiveCard(user, p1, p2, p3)) {
                            //점수 계산
                            p2.plusScore();
                            //(나)웃는 표정
                            makeAllFaceDefault(p1);
                            makeAllFaceDefault(user);
                            makeAllFaceDefault(p3);
                            makeFaceSmile(p2);
                            //테이블 위의 카드 모두 가져감
                            getAllFrontCard(p2, p1, user, p3);
                            printPlayersCardInfo(user, p1, p2, p3);
                        }
                        //잘못 쳤을 경우
                        else {
                            //점수 계산
                            p2.minusScore();
                            //화난 표정, 나머지 기본 표정
                            makeAllFaceDefault(p1);
                            makeAllFaceDefault(user);
                            makeAllFaceDefault(p3);
                            makeFaceAngry(p2);
                            PlaySound(TEXT("missingBell.wav"), 0, SND_FILENAME | SND_ASYNC);
                            missRinging(p2, p1, user, p3);
                            printPlayersCardInfo(user, p1, p2, p3);
                        }
                    }
                    //종 치기
                    else if (input == 79 || input == 111) { //p3가 종 친 경우
                        //체크
                        gotoxy(0, 1);
                        cout << "4번이 종침";
                        Sleep(500);
                        gotoxy(0, 1);
                        cout << "            ";
                        PlaySound(TEXT("ringingBell.wav"), 0, SND_FILENAME | SND_ASYNC);
                        //과일 5개일때 쳤을 경우
                        if (checkFiveCard(user, p1, p2, p3)) {
                            //점수 계산
                            p3.plusScore();
                            //(나)웃는 표정
                            makeAllFaceDefault(p1);
                            makeAllFaceDefault(p2);
                            makeAllFaceDefault(user);
                            makeFaceSmile(p3);
                            //테이블 위의 카드 모두 가져감
                            getAllFrontCard(p3, p1, p2, user);
                            printPlayersCardInfo(user, p1, p2, p3);
                        }
                        //잘못 쳤을 경우
                        else {
                            //점수 계산
                            p3.minusScore();
                            //화난 표정, 나머지 기본 표정
                            makeAllFaceDefault(p1);
                            makeAllFaceDefault(p2);
                            makeAllFaceDefault(user);
                            makeFaceAngry(p3);
                            PlaySound(TEXT("missingBell.wav"), 0, SND_FILENAME | SND_ASYNC);
                            missRinging(p3, p1, p2, user);
                            printPlayersCardInfo(user, p1, p2, p3);
                        }
                    }
                    //else if (input == 81 || input == 119) {
                    //    //종 치지 않음
                    //    continue;
                    //}
                    //아무도 종을 치지 않을 경우
                    else {
                        gotoxy(0, 0);
                        cout << "else!!";
                        Sleep(50);
                        gotoxy(0, 0);
                        cout << "         ";
                    }
                }
            }
        }
        else if (turn % 4 == 3) {
            printPlayersCardInfo(user, p1, p2, p3);
            if (!p3.getAvailable()) {
                continue;
            }
            else {
                //Player 4 : 카드 내기 O, 종치기 P (79,111 / 80,112)
                
                //체크
                gotoxy(0, 1);
                cout << "4번 차례";
                Sleep(500);
                gotoxy(0, 1);
                cout << "            ";

                //설명 출력
                gotoxy(longInfoX + 13, longInfoY - 2);
                cout << "                                        ";
                gotoxy(longInfoX + 13, longInfoY - 2);
                cout << "[ " << p3.getPlayerNum() << "번 PLAYER ]";

                //카드 낼때까지 기다림
                int cardInput = 0;
                while (true) {
                    cardInput = _getch();
                    if (cardInput == 79 || cardInput == 111) break;
                }
                //체크
                gotoxy(0, 1);
                cout << "(4) 빠져나옴";
                Sleep(500);
                gotoxy(0, 1);
                cout << "            ";

                //카드 뒤집기
                if (cardInput == 79 || cardInput == 111) {
                    if (p3.open() == -1) continue;
                    gotoxy(10, 14);
                    frontCardPrint(p3.getFrontTopCard(), p3);
                    input = _getch();
                    //종 치기
                    if (input == 87 || input == 119) { //user가 종 친 경우
                        //체크
                        gotoxy(0, 1);
                        cout << "1번이 종침";
                        Sleep(500);
                        gotoxy(0, 1);
                        cout << "            ";
                        PlaySound(TEXT("ringingBell.wav"), 0, SND_FILENAME | SND_ASYNC);
                        //과일 5개일때 쳤을 경우
                        if (checkFiveCard(user, p1, p2, p3)) {
                            //점수 계산
                            user.plusScore();
                            //(나)웃는 표정
                            makeAllFaceDefault(p1);
                            makeAllFaceDefault(p2);
                            makeAllFaceDefault(p3);
                            makeFaceSmile(user);
                            //테이블 위의 카드 모두 가져감
                            getAllFrontCard(user, p1, p2, p3);
                            printPlayersCardInfo(user, p1, p2, p3);
                        }
                        //잘못 쳤을 경우
                        else {
                            //점수 계산
                            user.minusScore();
                            //화난 표정
                            makeAllFaceDefault(p1);
                            makeAllFaceDefault(p2);
                            makeAllFaceDefault(p3);
                            makeFaceAngry(user);
                            PlaySound(TEXT("missingBell.wav"), 0, SND_FILENAME | SND_ASYNC);
                            //카드 한장씩 나누어줌
                            missRinging(user, p1, p2, p3);
                            printPlayersCardInfo(user, p1, p2, p3);
                        }
                    }
                    //종 치기
                    else if (input == 67 || input == 99) { //p1가 종 친 경우
                        //체크
                        gotoxy(0, 1);
                        cout << "2번이 종침";
                        Sleep(500);
                        gotoxy(0, 1);
                        cout << "            ";
                        PlaySound(TEXT("ringingBell.wav"), 0, SND_FILENAME | SND_ASYNC);
                        //과일 5개일때 쳤을 경우
                        if (checkFiveCard(user, p1, p2, p3)) {
                            //점수 계산
                            p1.plusScore();
                            //(나)웃는 표정
                            makeAllFaceDefault(user);
                            makeAllFaceDefault(p2);
                            makeAllFaceDefault(p3);
                            makeFaceSmile(p1);
                            //테이블 위의 카드 모두 가져감
                            getAllFrontCard(p1, user, p2, p3);
                            printPlayersCardInfo(user, p1, p2, p3);
                        }
                        //잘못 쳤을 경우
                        else {
                            //점수 계산
                            p1.minusScore();
                            //화난 표정, 나머지 기본 표정
                            makeAllFaceDefault(user);
                            makeAllFaceDefault(p2);
                            makeAllFaceDefault(p3);
                            makeFaceAngry(p1);
                            PlaySound(TEXT("missingBell.wav"), 0, SND_FILENAME | SND_ASYNC);
                            //카드 한장씩 나누어줌
                            missRinging(p1, user, p2, p3);
                            printPlayersCardInfo(user, p1, p2, p3);
                        }
                    }
                    //종 치기
                    else if (input == 77 || input == 109) { //p2가 종 친 경우
                        //체크
                        gotoxy(0, 1);
                        cout << "3번이 종침";
                        Sleep(500);
                        gotoxy(0, 1);
                        cout << "            ";
                        PlaySound(TEXT("ringingBell.wav"), 0, SND_FILENAME | SND_ASYNC);
                        //과일 5개일때 쳤을 경우
                        if (checkFiveCard(user, p1, p2, p3)) {
                            //점수 계산
                            p2.plusScore();
                            //(나)웃는 표정
                            makeAllFaceDefault(p1);
                            makeAllFaceDefault(user);
                            makeAllFaceDefault(p3);
                            makeFaceSmile(p2);
                            //테이블 위의 카드 모두 가져감
                            getAllFrontCard(p2, p1, user, p3);
                            printPlayersCardInfo(user, p1, p2, p3);
                        }
                        //잘못 쳤을 경우
                        else {
                            //점수 계산
                            p2.minusScore();
                            //화난 표정, 나머지 기본 표정
                            makeAllFaceDefault(p1);
                            makeAllFaceDefault(user);
                            makeAllFaceDefault(p3);
                            makeFaceAngry(p2);
                            PlaySound(TEXT("missingBell.wav"), 0, SND_FILENAME | SND_ASYNC);
                            missRinging(p2, p1, user, p3);
                            printPlayersCardInfo(user, p1, p2, p3);
                        }
                    }
                    //종 치기
                    else if (input == 80 || input == 112) { //p3가 종 친 경우
                        //체크
                        gotoxy(0, 1);
                        cout << "4번이 종침";
                        Sleep(500);
                        gotoxy(0, 1);
                        cout << "            ";
                        PlaySound(TEXT("ringingBell.wav"), 0, SND_FILENAME | SND_ASYNC);
                        //과일 5개일때 쳤을 경우
                        if (checkFiveCard(user, p1, p2, p3)) {
                            //점수 계산
                            p3.plusScore();
                            //(나)웃는 표정
                            makeAllFaceDefault(p1);
                            makeAllFaceDefault(p2);
                            makeAllFaceDefault(user);
                            makeFaceSmile(p3);
                            //테이블 위의 카드 모두 가져감
                            getAllFrontCard(p3, p1, p2, user);
                            printPlayersCardInfo(user, p1, p2, p3);
                        }
                        //잘못 쳤을 경우
                        else {
                            //점수 계산
                            p3.minusScore();
                            //화난 표정, 나머지 기본 표정
                            makeAllFaceDefault(p1);
                            makeAllFaceDefault(p2);
                            makeAllFaceDefault(user);
                            makeFaceAngry(p3);
                            PlaySound(TEXT("missingBell.wav"), 0, SND_FILENAME | SND_ASYNC);
                            missRinging(p3, p1, p2, user);
                            printPlayersCardInfo(user, p1, p2, p3);
                        }
                    }
                    //else if (input == 81 || input == 119) {
                    //    //종 치지 않음
                    //    continue;
                    //}
                    //아무도 종을 치지 않을 경우
                    else {
                        gotoxy(0, 0);
                        cout << "else!!";
                        Sleep(50);
                        gotoxy(0, 0);
                        cout << "         ";
                    }
                }
            }
            if (p3.getBackCount() == 0) {
                //***(나)화난 표정
                makeAllFaceDefault(user);
                makeAllFaceDefault(p1);
                makeAllFaceDefault(p2);
                makeFaceAngry(p3);

                p3.setNoneAvailable();
                printPlayersCardInfo(user, p1, p2, p3);
                gotoxy(longInfoX + 10, longInfoY);
                cout << p3.getPlayerNum() << "번 사용자가 탈락되었습니다.";
                Sleep(2000);
                gotoxy(longInfoX + 10, longInfoY);
                cout << "                              ";
            }
        }
        //게임 나가기 (강제종료)
        if (GetKeyValue() == 27) break;    
    }
    while (true) {
        if (GetKeyValue() == 27)
            break;
    }
}
//게임 시작 (1 vs com vs com vs com)
void StartGameAlone() {
    DrawStartGame();
    //조작법 draw
    {
        gotoxy(15, 30);
        cout << "┌──────────────  조작법 ──────────────┐";
        gotoxy(15, 31);
        cout << "│                                     │";
        gotoxy(15, 32);
        cout << "│      카드 넘기기 ▷  SPACE BAR      │";
        gotoxy(15, 33);
        cout << "│                                     │";
        gotoxy(15, 34);
        cout << "│        종 치기   ▷  ENTER          │";
        gotoxy(15, 35);
        cout << "│                                     │";
        gotoxy(15, 36);
        cout << "│        나가기    ▷  E key          │";
        gotoxy(15, 37);
        cout << "│                                     │";
        gotoxy(15, 38);
        cout << "└─────────────────────────────────────┘";
    }
    //사용자 생성
    Player user(1), com1(2), com2(3), com3(4);
    //카드 랜덤배치,사용자에게 카드 분배
    setInitCard(user, com1, com2, com3);

    //반복
    int input = 0;
    int turn = -1;
    while (true) {
        turn++;
        if (turn % 4 == 0) {
            printPlayersCardInfo(user, com1, com2, com3);
            if (!user.getAvailable()) {
                continue;
            }
            else {
                //설명 출력
                gotoxy(longInfoX + 13, longInfoY - 2);
                cout << "                                        ";
                gotoxy(longInfoX + 13, longInfoY - 2);
                cout << "[ " << user.getPlayerNum() << "번 PLAYER ]";

                if (user.open() == -1) continue;
                gotoxy(10, 14);
                frontCardPrint(user.getFrontTopCard(), user);
                input = GameKey();
                if (input == 1) {
                    PlaySound(TEXT("ringingBell.wav"), 0, SND_FILENAME | SND_ASYNC);
                    //과일 5개일때 쳤을 경우
                    if (checkFiveCard(user, com1, com2, com3)) {
                        //***(나)웃는 표정
                        makeAllFaceDefault(com1);
                        makeAllFaceDefault(com2);
                        makeAllFaceDefault(com3);
                        makeFaceSmile(user);
                        //테이블 위의 카드 모두 가져감
                        getAllFrontCard(user, com1, com2, com3);
                        printPlayersCardInfo(user, com1, com2, com3);
                    }
                    //잘못 쳤을 경우
                    else {
                        //***화난 표정, 나머지 기본 표정
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
                    //종 치지 않음
                }
            }
            if (user.getBackCount() == 0) {
                //***화난 표정
                makeAllFaceDefault(com1);
                makeAllFaceDefault(com2);
                makeAllFaceDefault(com3);
                makeFaceAngry(user);
                user.setNoneAvailable();
                printPlayersCardInfo(user, com1, com2, com3);
                gotoxy(longInfoX + 10, longInfoY);
                cout << user.getPlayerNum() << "번 사용자가 탈락되었습니다.";
                Sleep(2000);
                gotoxy(longInfoX + 10, longInfoY);
                cout << "                              ";

                //점수
                int score = 0;
                int x = 20;
                int y = 17;
                gotoxy(x, y);
                cout << "┌─────────────────────────────────────────┐";
                gotoxy(x, y + 1);
                cout << "│                                         │";
                gotoxy(x, y + 2);
                cout << "│                GAME OVER                │";
                gotoxy(x, y + 3);
                cout << "│                                         │";
                gotoxy(x, y + 4);
                cout << "│               score  :                  │";
                gotoxy(x + 5, y + 4);
                cout << score;
                gotoxy(x, y + 5);
                cout << "│                                         │";
                gotoxy(x, y + 6);
                cout << "│   랭킹을 작성하시겠습니까?  [ Y / N ]   │";
                gotoxy(x, y + 7);
                cout << "│                                         │";
                gotoxy(x, y + 8);
                cout << "└─────────────────────────────────────────┘";

                //Y 또는 N 선택
                while (true) {
                    if (_getch() == 89 || _getch() == 121) {
                        string userName = "";
                        gotoxy(x, y + 4);
                        cout << "│                                         │";
                        gotoxy(x, y + 5);
                        cout << "│    닉네임 입력 :                        │";
                        gotoxy(x, y + 6);
                        cout << "│                                         │";
                        gotoxy(x + 12, y + 5);
                        cin >> userName;
                        gotoxy(0, 0);
                        cout << userName << endl;

                        //사용자 이름, 점수 파일에 저장
                        ofstream out("database_solo.txt", ios::app);
                        //임시 점수
                        out << userName << " " << score << "\n";
                        out.close();

                        //랭킹 화면 draw
                        DrawRankingScreen(1);
                        break;
                    }
                    else if (_getch() == 78 || _getch() == 110) {
                        gotoxy(x, y);
                        cout << "┌─────────────────────────────────────────┐";
                        gotoxy(x, y + 1);
                        cout << "│                                         │";
                        gotoxy(x, y + 2);
                        cout << "│                GAME OVER                │";
                        gotoxy(x, y + 3);
                        cout << "│                                         │";
                        gotoxy(x, y + 4);
                        cout << "│     잠시후 메인화면으로 이동합니다.     │";
                        gotoxy(x, y + 5);
                        cout << "│                                         │";
                        gotoxy(x, y + 6);
                        cout << "│                                         │";
                        gotoxy(x, y + 7);
                        cout << "│                                         │";
                        gotoxy(x, y + 8);
                        cout << "└─────────────────────────────────────────┘";
                        Sleep(2000);
                        //메인으로 이동
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
                //설명 출력
                gotoxy(longInfoX + 13, longInfoY - 2);
                cout << "                                        ";
                gotoxy(longInfoX + 13, longInfoY - 2);
                cout << "[ " << com1.getPlayerNum() << "번 PLAYER ]";

                if (com1.open() == -1) continue;
                gotoxy(20, 14);
                frontCardPrint(com1.getFrontTopCard(), com1);
                input = GameKey();
                if (input == 1) {
                    PlaySound(TEXT("ringingBell.wav"), 0, SND_FILENAME | SND_ASYNC);
                    //과일 5개일때 쳤을 경우
                    if (checkFiveCard(com1, user, com2, com3)) {
                        //***웃는 표정
                        makeAllFaceDefault(user);
                        makeAllFaceDefault(com2);
                        makeAllFaceDefault(com3);
                        makeFaceSmile(com1);
                        //테이블 위의 카드 모두 가져감
                        getAllFrontCard(com1, user, com2, com3);
                        printPlayersCardInfo(user, com1, com2, com3);
                    }
                    //잘못 쳤을 경우
                    else {
                        //***화난 표정
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
                    //종 치지 않음
                }
            }
            if (com1.getBackCount() == 0) {
                //***화난 표정
                makeAllFaceDefault(user);
                makeAllFaceDefault(com2);
                makeAllFaceDefault(com3);
                makeFaceAngry(com1);
                com1.setNoneAvailable();
                printPlayersCardInfo(user, com1, com2, com3);
                gotoxy(longInfoX + 10, longInfoY);
                cout << com1.getPlayerNum() << "번 사용자가 탈락되었습니다.";
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
                //설명 출력
                gotoxy(longInfoX + 13, longInfoY - 2);
                cout << "                                        ";
                gotoxy(longInfoX + 13, longInfoY - 2);
                cout << "[ " << com2.getPlayerNum() << "번 PLAYER ]";

                if (com2.open() == -1) continue;
                gotoxy(30, 14);
                frontCardPrint(com2.getFrontTopCard(), com2);
                input = GameKey();
                if (input == 1) {
                    PlaySound(TEXT("ringingBell.wav"), 0, SND_FILENAME | SND_ASYNC);
                    //과일 5개일때 쳤을 경우
                    if (checkFiveCard(com2, user, com1, com3)) {
                        //***웃는 표정
                        makeAllFaceDefault(user);
                        makeAllFaceDefault(com1);
                        makeAllFaceDefault(com3);
                        makeFaceSmile(com2);
                        //테이블 위의 카드 모두 가져감
                        getAllFrontCard(com2, user, com1, com3);
                        printPlayersCardInfo(user, com1, com2, com3);
                    }
                    //잘못 쳤을 경우
                    else {
                        //***화난 표정
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
                    //종 치지 않음
                }
            }
            if (com2.getBackCount() == 0) {
                //***화난 표정
                makeAllFaceDefault(user);
                makeAllFaceDefault(com1);
                makeAllFaceDefault(com3);
                makeFaceAngry(com2);
                com2.setNoneAvailable();
                printPlayersCardInfo(user, com1, com2, com3);
                gotoxy(longInfoX + 10, longInfoY);
                cout << com2.getPlayerNum() << "번 사용자가 탈락되었습니다.";
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
                //설명 출력
                gotoxy(longInfoX + 13, longInfoY - 2);
                cout << "                                        ";
                gotoxy(longInfoX + 13, longInfoY - 2);
                cout << "[ " << com3.getPlayerNum() << "번 PLAYER ]";

                if (com3.open() == -1) continue;
                gotoxy(40, 14);
                frontCardPrint(com3.getFrontTopCard(), com3);
                input = GameKey();
                if (input == 1) {
                    PlaySound(TEXT("ringingBell.wav"), 0, SND_FILENAME | SND_ASYNC);
                    //과일 5개일때 쳤을 경우
                    if (checkFiveCard(com3, com1, com2, user)) {
                        //***(나)웃는 표정
                        makeAllFaceDefault(user);
                        makeAllFaceDefault(com1);
                        makeAllFaceDefault(com2);
                        makeFaceSmile(com3);

                        //테이블 위의 카드 모두 가져감
                        getAllFrontCard(com3, com1, com2, user);
                        printPlayersCardInfo(user, com1, com2, com3);
                    }
                    //잘못 쳤을 경우
                    else {
                        //***(나)화난 표정
                        makeAllFaceDefault(user);
                        makeAllFaceDefault(com1);
                        makeAllFaceDefault(com2);
                        makeFaceAngry(com3);
                        //각 인원에게 카드 하나씩 줌, 카드수 부족할 시 탈락
                        PlaySound(TEXT("missingBell.wav"), 0, SND_FILENAME | SND_ASYNC);
                        missRinging(com3, com1, com2, user);
                        printPlayersCardInfo(user, com1, com2, com3);
                    }
                }
                else {
                    //종 치지 않음
                }
            }
            if (com3.getBackCount() == 0) {
                //***(나)화난 표정
                makeAllFaceDefault(user);
                makeAllFaceDefault(com1);
                makeAllFaceDefault(com2);
                makeFaceAngry(com3);

                com3.setNoneAvailable();
                printPlayersCardInfo(user, com1, com2, com3);
                gotoxy(longInfoX + 10, longInfoY);
                cout << com3.getPlayerNum() << "번 사용자가 탈락되었습니다.";
                Sleep(2000);
                gotoxy(longInfoX + 10, longInfoY);
                cout << "                              ";
            }
        }
        //게임 나가기 (강제종료)
        if (GetKeyValue() == 27) break;
    }


    while (true) {
        if (GetKeyValue() == 27)
            break;
    }
}
//게임 진행 방식 선택
int ChoosePlaying() {

    DrawChoosePlaying();

    int result = 0;
    int x = 20+11;
    int y = 21;
    gotoxy(x, y);
    while (true) {
        int num = _getch();
        switch (num)
        {
        //위
        case 72: {
            if (y == 23) {
                gotoxy(x - 2, y);
                printf("  ");
                gotoxy(x - 2, y-=2);
                printf(">>");
            }
            break;
        }
        //아래
        case 80: {
            if (y == 21) {
                gotoxy(x - 2, y);
                printf("  ");
                gotoxy(x - 2, y+=2);
                printf(">>");
            }
            break;
        }
        //enter
        case 13: 
            result = y - 21; //0 또는 2
            return result;
        //exit
        case 27:
            ReadyGame();
            break;
        }
    }
}
//게임 설명
void ShowInfo()
{
    DrawInfoScreen();
    while (true) {
        if (_getch() == 27)
            break;
    }
}
//메인
int main(void)
{
    //콘솔설정
    SetConsoleView(); 
    //커서 설정
    CursorView();
    int menuValue = -1;

    while (true)
    {
        menuValue = ReadyGame();    //0 : 설명, 2 : 게임시작, 4 :게임종료
        if (menuValue == 0) {       //rule
            ShowInfo();
        }
        else if (menuValue == 2) {    //게임 방식 고름
            int res = ChoosePlaying();
            if (res == 0) StartGameAlone(); //0 : 혼자하기, 2 : 4명이 하기
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