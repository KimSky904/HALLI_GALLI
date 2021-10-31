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
#include <random>
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
//턴 횟수 (전역변수)
int turnCount = 0;


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
    //플레이어 이름
    string name;
    //카드 획득 횟수
    int count;
    //게임시작 시간
    clock_t startGame;
    //게임끝 시간
    clock_t endGame;
public:
    //생성자
    Player(int num) {
        playerNum = num;
        available = true;
        score = 0;
        count = 0;
        startGame = clock();
    }
    //이름 지정
    void setName(string name) {
        this->name = name;
    }
    //이름 반환
    string getName() {
        return name;
    }
    //카드획득횟수 반환
    int getCount() {
        return count;
    }
    //게임 소요시간 반환
    int getTime() {
        endGame = clock();
        return (int)(endGame - startGame);
    }
    //점수 획득
    void plusScore() {
        score += 20;
        count++;
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
    //카드 잃음
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
    Card(1,1),Card(1,1),Card(1,1),Card(1,1),Card(1,1),
    Card(1,1),Card(1,2),Card(1,2),Card(1,2),Card(1,2),
    Card(1,2),Card(1,3),Card(1,3),Card(1,3),Card(1,3),
    Card(1,4),Card(1,4),Card(1,4),Card(1,5),Card(1,5),

    Card(2,1),Card(2,1),Card(2,1),Card(2,1),Card(2,1),
    Card(2,1),Card(2,2),Card(2,2),Card(2,2),Card(2,2),
    Card(2,2),Card(2,3),Card(2,3),Card(2,3),Card(2,3),
    Card(2,4),Card(2,4),Card(2,4),Card(2,5),Card(2,5),

    Card(3,1),Card(3,1),Card(3,1),Card(3,1),Card(3,1),
    Card(3,1),Card(3,2),Card(3,2),Card(3,2),Card(3,2),
    Card(3,2),Card(3,3),Card(3,3),Card(3,3),Card(3,3),
    Card(3,4),Card(3,4),Card(3,4),Card(3,5),Card(3,5),

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
void DrawRankingScreen(Player& user);


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


//빈 카드 출력
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
    cout << "│   =  =  │";
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
    cout << "│  ㅡ  ㅡ │";
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
void DrawRankingScreen(Player& user) {
    //135 45
    HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
    system("cls");

    //파일 줄 수 세기
    int line = 0;
    char c;
    FILE* lineFp = fopen("database.txt", "r");
    while ((c = fgetc(lineFp)) != EOF)
        if (c == '\n') line++;
    fclose(lineFp);

    //구조체
    struct players {
        char name[20];
        int score;
        int rank;
    };
    //라인 수 만큼 동적할당
    players* pl = new players[line];

    FILE* fp;
    //파일에서 읽어옴
    while (true) {
        fopen_s(&fp, "database.txt", "r");
        if (fp == NULL) {
            gotoxy(0, 0);
            cout << "파일이 존재하지 않습니다." << endl;
        }
        else break;
    }

    for (int i = 0; i < line; i++) {
        fscanf_s(fp, "%s", pl[i].name, 20);
        fscanf_s(fp, "%d", &(pl[i].score));
    }
    fclose(fp);


    //순위 저장
    for (int i = 0; i < line; i++) {
        pl[i].rank = 1;
        for (int j = 0; j < line; j++) {
            if (pl[i].score < pl[j].score) pl[i].rank++;
        }
    }
    int x = 14;
    int y = 8;
    gotoxy(x, y);
    int printCount = 0;
    cout << "┌──────── [  RANKING  ]────────┐ ";
    for (int i = 1; i <= 10; i++) {
        for (int j = 0; j < line; j++) {
            if (printCount == 10) break;
            if (pl[j].rank == i) {
                gotoxy(x, ++y);
                cout << "│                              │";
                gotoxy(x, ++y);
                switch (i) {
                case 1:
                    printCount++;
                    PrintString(hStdOut, WHITE);
                    cout << "│  ";
                    PrintString(hStdOut, YELLOW);
                    printf("%2d    %12s    %4d", pl[j].rank, pl[j].name, pl[j].score);
                    PrintString(hStdOut, WHITE);
                    cout << "  │";
                    break;
                case 2:
                    printCount++;
                    PrintString(hStdOut, WHITE);
                    cout << "│  ";
                    PrintString(hStdOut, 7);
                    printf("%2d    %12s    %4d", pl[j].rank, pl[j].name, pl[j].score);
                    PrintString(hStdOut, WHITE);
                    cout << "  │";
                    break;
                case 3:
                    printCount++;
                    PrintString(hStdOut, WHITE);
                    cout << "│  ";
                    PrintString(hStdOut, 6);
                    printf("%2d    %12s    %4d", pl[j].rank, pl[j].name, pl[j].score);
                    PrintString(hStdOut, WHITE);
                    cout << "  │";
                    break;
                default:
                    printCount++;
                    PrintString(hStdOut, WHITE);
                    printf("│  %2d    %12s    %4d  │", pl[j].rank, pl[j].name, pl[j].score);
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
    printf("│     획득한 score    :      %4d    │", user.getScore());
    gotoxy(x, y + 3);
    cout << "│                                    │";
    gotoxy(x, y + 4);
    printf("│     카드 획득 횟수  :      %4d    │", user.getCount());
    gotoxy(x, y + 5);
    cout << "│                                    │";
    gotoxy(x, y + 6);
    printf("│     종친 횟수       :      %4d    │", turnCount);
    gotoxy(x, y + 7);
    cout << "│                                    │";
    gotoxy(x, y + 8);
    printf("│     플레이 시간     :     %4d초   │", user.getTime() / 1000);
    gotoxy(x, y + 9);
    cout << "│                                    │";
    gotoxy(x, y + 10);
    cout << "└────────────────────────────────────┘ ";

    gotoxy(x, y + 12);
    cout << "┌──────── [  DEVELOPER INFO  ]───────┐ ";
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

    while (true) {
        if (_kbhit()) {
            if (_getch() == 27) return;
        }
    }
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
    cout << "≫  § 총 4명의 플레이어가 있으며, 각 플레이어에게 20장의 카드가 주어집니다.                          ≫";
    gotoxy(3, 27);
    cout << "≫  § 테이블에 놓인 카드의 과일 수가 5개가 되면 '지정 키'로 종을 칩니다.                             ≫";
    gotoxy(3, 29);
    cout << "≫  § 1명 또는 4명이 플레이할 수 있습니다. 기본 동작은 조작법을 통해 알려드립니다.                   ≫";
    gotoxy(3, 31);
    cout << "≫  § 동시에 종을 쳤을 경우, 더 빨리 종을 친 사람이 테이블의 카드를 모두 가져갑니다.                 ≫";
    gotoxy(3, 33);
    cout << "≫  § 만일 5개가 아닌 상태에서 종을 치면, 나머지 플레이어에게 카드를 1장씩 나누어줍니다.             ≫";
    gotoxy(3, 35);
    cout << "≫  § 1명이 플레이할 경우 로봇과 경쟁할 수 있으며, 랭킹등록이 가능합니다.                            ≫";
    gotoxy(3, 37);
    cout << "≫  § 4명이 플레이할 경우 랭킹등록은 불가합니다.                           § 나가기 : esc           ≫";
    gotoxy(3, 39);
    cout << "≫≫≫≫≫≫≫≫≫≫≫≫≫≫≫≫≫≫≫≫≫≫≫≫≫≫≫≫≫≫≫≫≫≫≫≫≫≫≫≫≫≫≫≫≫≫≫≫≫≫≫≫";

}
//게임진행 선택 화면 draw
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
    cout << "│                 >>  1 Player                  │";
    gotoxy(x, y + 5);
    cout << "│                                               │";
    gotoxy(x, y + 6);
    cout << "│                     4 Players                 │";
    gotoxy(x, y + 7);
    cout << "│                                               │";
    gotoxy(x, y + 8);
    cout << "└───────────────────────────────────────────────┘";


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
        cout << "│   =  =  │";
        break;
    case 2: 
        gotoxy(x, 15);
        cout << "│  〓  〓 │";
        break;
    case 3: 
        gotoxy(x, 25);
        cout << "│  ㅡ  ㅡ │";
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

//1 vs com 게임 종료    
void checkUserAvailable(Player& user,Player& com1, Player& com2,Player& com3) {
    //사용자가 탈락했을 경우
    if (!user.getAvailable()) {
        gotoxy(longInfoX + 10, longInfoY);
        cout << user.getPlayerNum() << "번 사용자가 탈락되었습니다.";
        Sleep(2000);
        gotoxy(longInfoX + 10, longInfoY);
        cout << "                              ";

    }
    //화난 표정
    makeAllFaceDefault(com1);
    makeAllFaceDefault(com2);
    makeAllFaceDefault(com3);
    makeFaceAngry(user);
    user.setNoneAvailable();
    printPlayersCardInfo(user, com1, com2, com3);

    //점수
    int score = user.getScore();
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
    gotoxy(x + 15, y + 4);
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
        int in = _getch();
        if (in  == 89 || in == 121) {
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

            //사용자 이름 객체에 저장
            user.setName(userName);
            //사용자 이름, 점수 파일에 저장
            ofstream out("database.txt", ios::app);
            //점수 저장
            out << userName << " " << score << "\n";
            out.close();
            
            //랭킹 화면 draw
            DrawRankingScreen(user);
            break;
        }
        else if (in == 78 || in == 110) {
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
}

//탈락인지 확인
void checkPlayerNoneAble(Player& user,Player& p1,Player& p2,Player& p3){
    if (user.getBackCount() == 0) {
        //화난 표정
        makeAllFaceDefault(p1);
        makeAllFaceDefault(p2);
        makeAllFaceDefault(p3);
        makeFaceAngry(user);
        user.setNoneAvailable();
        printPlayersCardInfo(user, p1, p2, p3);
        gotoxy(longInfoX + 10, longInfoY);
        cout << user.getPlayerNum() << "번 사용자가 탈락되었습니다.";
        Sleep(2000);
        gotoxy(longInfoX + 10, longInfoY);
        cout << "                              ";
    }
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
    //전 단계에서 종쳤는지, 카드넘겼는지 확인
    boolean pushOk = false;
    while (true) {
        // (1:1:1:1) 한명의 플레이어만 남았을 경우
        if ((int)user.getAvailable() + (int)p1.getAvailable() + (int)p2.getAvailable() + (int)p3.getAvailable() == 1) {
            string winnerName = "";
            if (user.getAvailable() == 1) winnerName = "Player 1";
            else if (p1.getAvailable() == 1) winnerName = "Player 2";
            else if (p2.getAvailable() == 1) winnerName = "Player 3";
            else if (p3.getAvailable() == 1) winnerName = "Player 4";
            //결과화면
            {
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
                cout << "│             winner :  " << winnerName << "          │";
                gotoxy(x, y + 5);
                cout << "│                                         │";
                gotoxy(x, y + 6);
                cout << "│     잠시후 메인화면으로 이동합니다.     │";
                gotoxy(x, y + 7);
                cout << "│                                         │";
                gotoxy(x, y + 8);
                cout << "└─────────────────────────────────────────┘";

                Sleep(5000);
                main();
                break;
            }
        }
        turn++;
        //1번 차례
        if (turn % 4 == 0) {
            //다음 턴으로 넘어가는 키 지정
            int nextKey1 = 88, nextKey2 = 120;
            printPlayersCardInfo(user, p1, p2, p3);
            if (!user.getAvailable()) {
                continue;
            }
            else {
                //Player 1 : 카드 내기 Q, 종치기 W (81,113 / 87,119)
                
                //설명 출력
                gotoxy(longInfoX + 13, longInfoY - 2);
                cout << "                                        ";
                gotoxy(longInfoX + 13, longInfoY - 2);
                cout << "[ " << user.getPlayerNum() << "번 PLAYER ]";


                //전 턴에서 카드내기가 이미 눌렸는지 확인
                if (pushOk == false) {
                    while (true) {
                        int value = _getch();
                        if (value == 81 || value == 113) break;
                    }
                }

                //카드 뒤집기
                if (user.open() == -1) continue;
                PlaySound(TEXT("openCard.wav"), 0, SND_FILENAME | SND_ASYNC);
                frontCardPrint(user.getFrontTopCard(), user);
                printPlayersCardInfo(user, p1, p2, p3);

                //다음턴 출력
                gotoxy(longInfoX + 13, longInfoY - 2);
                cout << "                                        ";
                gotoxy(longInfoX + 13, longInfoY - 2);
                cout << "[ " << p1.getPlayerNum() << "번 PLAYER ]";

                //다음 턴 선수의 키값 구하기 (탈락자 때문)
                if (!p1.getAvailable()) {
                    nextKey1 = 78, nextKey2 = 110;
                    gotoxy(longInfoX + 13, longInfoY - 2);
                    cout << "                                        ";
                    gotoxy(longInfoX + 13, longInfoY - 2);
                    cout << "[ " << p2.getPlayerNum() << "번 PLAYER ]";
                    if (!p2.getAvailable()) {
                        nextKey1 = 79, nextKey2 = 111;
                        gotoxy(longInfoX + 13, longInfoY - 2);
                        cout << "                                        ";
                        gotoxy(longInfoX + 13, longInfoY - 2);
                        cout << "[ " << p3.getPlayerNum() << "번 PLAYER ]";
                        if (!p3.getAvailable()) {
                            nextKey1 = 81, nextKey2 = 113;
                            gotoxy(longInfoX + 13, longInfoY - 2);
                            cout << "                                        ";
                            gotoxy(longInfoX + 13, longInfoY - 2);
                            cout << "[ " << user.getPlayerNum() << "번 PLAYER ]";
                        }
                    }
                }

                //종치거나 다음 차례가 카드넘김
                while (true) {
                    input = _getch();
                    if (input == 87 || input == 119 ||
                        input == 67 || input == 99 ||
                        input == 77 || input == 109 ||
                        input == 80 || input == 112 ||
                        input == nextKey1 || input == nextKey2) break;
                }

                //다음턴이 카드를 넘긴 경우
                if (input == nextKey1 || input == nextKey2) {
                    pushOk = true;
                    checkPlayerNoneAble(user, p1, p2, p3);
                    continue;
                }
                else {
                    pushOk = false;
                    //1번이 종쳤을 경우
                    if (input == 87 || input == 119) { //user가 종 친 경우
                        if (user.getAvailable()) {
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
                    }
                    //2번이 종쳤을 경우
                    else if (input == 67 || input == 99) { //p1가 종 친 경우
                        if (p1.getAvailable()) {
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
                    }
                    //3번이 종쳤을 경우
                    else if (input == 77 || input == 109) { //p2가 종 친 경우
                        if (p2.getAvailable()) {
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
                    }
                    //4번이 종쳤을 경우
                    else if (input == 80 || input == 112) { //p3가 종 친 경우
                        if (p3.getAvailable()) {
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
                    }
                }

                //1번 탈락 처리
                if (user.getBackCount() == 0) {
                    //화난 표정
                    makeAllFaceDefault(p1);
                    makeAllFaceDefault(p2);
                    makeAllFaceDefault(p3);
                    makeFaceAngry(user);
                    user.setNoneAvailable();
                    printPlayersCardInfo(user, p1, p2, p3);
                    gotoxy(longInfoX + 10, longInfoY);
                    cout << user.getPlayerNum() << "번 사용자가 탈락되었습니다.";
                    Sleep(2000);
                    gotoxy(longInfoX + 10, longInfoY);
                    cout << "                              ";
                }
                continue;
            }
        }
        //2번 차례
        if (turn % 4 == 1) {
            //다음 턴으로 넘어가는 키 지정
            int nextKey1 = 78, nextKey2 = 110;
            printPlayersCardInfo(user, p1, p2, p3);
            if (!p1.getAvailable()) {
                continue;
            }
            else {
                //Player 2 : 카드 내기 X, 종치기 C (88,120 / 67,99)

                //설명 출력
                gotoxy(longInfoX + 13, longInfoY - 2);
                cout << "                                        ";
                gotoxy(longInfoX + 13, longInfoY - 2);
                cout << "[ " << p1.getPlayerNum() << "번 PLAYER ]";

                //전 턴에서 카드내기가 이미 눌렸는지 확인
                if (pushOk == false) {
                    while (true) {
                        int value = _getch();
                        if (value == 88 || value == 120) break;
                    }
                }

                //카드 뒤집기
                if (p1.open() == -1) continue;
                PlaySound(TEXT("openCard.wav"), 0, SND_FILENAME | SND_ASYNC);
                frontCardPrint(p1.getFrontTopCard(), p1);
                printPlayersCardInfo(user, p1, p2, p3);

                //다음턴 출력
                gotoxy(longInfoX + 13, longInfoY - 2);
                cout << "                                        ";
                gotoxy(longInfoX + 13, longInfoY - 2);
                cout << "[ " << p2.getPlayerNum() << "번 PLAYER ]";

                //다음 턴 선수의 키값 구하기 (탈락자 때문)
                if (!p2.getAvailable()) {
                    nextKey1 = 79, nextKey2 = 111;
                    gotoxy(longInfoX + 13, longInfoY - 2);
                    cout << "                                        ";
                    gotoxy(longInfoX + 13, longInfoY - 2);
                    cout << "[ " << p3.getPlayerNum() << "번 PLAYER ]";
                    if (!p3.getAvailable()) {
                        nextKey1 = 81, nextKey2 = 113;
                        gotoxy(longInfoX + 13, longInfoY - 2);
                        cout << "                                        ";
                        gotoxy(longInfoX + 13, longInfoY - 2);
                        cout << "[ " << user.getPlayerNum() << "번 PLAYER ]";
                        if (!user.getAvailable()) {
                            if (!user.getAvailable()) nextKey1 = 88, nextKey2 = 120;
                            gotoxy(longInfoX + 13, longInfoY - 2);
                            cout << "                                        ";
                            gotoxy(longInfoX + 13, longInfoY - 2);
                            cout << "[ " << p1.getPlayerNum() << "번 PLAYER ]";
                        }
                    }
                }

                //종치거나 다음 차례가 카드넘김
                while (true) {
                    input = _getch();
                    if (input == 87 || input == 119 ||
                        input == 67 || input == 99 ||
                        input == 77 || input == 109 ||
                        input == 80 || input == 112 ||
                        input == nextKey1 || input == nextKey2) break;
                }

                //다음턴이 카드를 넘긴 경우
                if (input == nextKey1 || input == nextKey2) {
                    pushOk = true;
                    checkPlayerNoneAble(p1, user, p2, p3);
                    continue;
                }
                //누군가 종친 경우
                else {
                    pushOk = false;
                    //1번이 종쳤을 경우
                    if (input == 87 || input == 119) { //user가 종 친 경우
                        if (user.getAvailable()) {
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
                    }
                    //2번이 종쳤을 경우
                    else if (input == 67 || input == 99) { //p1가 종 친 경우
                        if (p1.getAvailable()) {
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
                    }
                    //3번이 종쳤을 경우
                    else if (input == 77 || input == 109) { //p2가 종 친 경우
                        if (p2.getAvailable()) {
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
                    }
                    //4번이 종쳤을 경우
                    else if (input == 80 || input == 112) { //p3가 종 친 경우
                        if (p3.getAvailable()) {
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
                    }
                }

                //2번 탈락 처리
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
                continue;
                
            }
        }
        //3번 차례
        if (turn % 4 == 2) {
            //다음 턴으로 넘어가는 키 지정
            int nextKey1 = 79, nextKey2 = 111;
            printPlayersCardInfo(user, p1, p2, p3);
            if (!p2.getAvailable()) {
                continue;
            }
            else {
                //Player 3 : 카드 내기 N, 종치기 M (78,110 / 77,109)

                //설명 출력
                gotoxy(longInfoX + 13, longInfoY - 2);
                cout << "                                        ";
                gotoxy(longInfoX + 13, longInfoY - 2);
                cout << "[ " << p2.getPlayerNum() << "번 PLAYER ]";

                //전 턴에서 카드내기가 이미 눌렸는지 확인
                if (pushOk == false) {
                    while (true) {
                        int value = _getch();
                        if (value == 78 || value == 110) break;
                    }
                }

                //카드 뒤집기
                if (p2.open() == -1) continue;
                PlaySound(TEXT("openCard.wav"), 0, SND_FILENAME | SND_ASYNC);
                frontCardPrint(p2.getFrontTopCard(), p2);
                printPlayersCardInfo(user, p1, p2, p3);

                //다음턴 출력
                gotoxy(longInfoX + 13, longInfoY - 2);
                cout << "                                        ";
                gotoxy(longInfoX + 13, longInfoY - 2);
                cout << "[ " << p3.getPlayerNum() << "번 PLAYER ]";
 
                //다음 턴 선수의 키값 구하기 (탈락자 때문)
                if (!p3.getAvailable()) {
                    nextKey1 = 81, nextKey2 = 113;
                    gotoxy(longInfoX + 13, longInfoY - 2);
                    cout << "                                        ";
                    gotoxy(longInfoX + 13, longInfoY - 2);
                    cout << "[ " << user.getPlayerNum() << "번 PLAYER ]";
                    if (!user.getAvailable()) {
                        nextKey1 = 88, nextKey2 = 120;
                        gotoxy(longInfoX + 13, longInfoY - 2);
                        cout << "                                        ";
                        gotoxy(longInfoX + 13, longInfoY - 2);
                        cout << "[ " << p1.getPlayerNum() << "번 PLAYER ]";
                        if (!p1.getAvailable()) {
                            nextKey1 = 78, nextKey2 = 110;
                            gotoxy(longInfoX + 13, longInfoY - 2);
                            cout << "                                        ";
                            gotoxy(longInfoX + 13, longInfoY - 2);
                            cout << "[ " << p2.getPlayerNum() << "번 PLAYER ]";
                        }
                    }
                }

                //종치거나 다음 차례가 카드넘김
                while (true) {
                    input = _getch();
                    if (input == 87 || input == 119 ||
                        input == 67 || input == 99 ||
                        input == 77 || input == 109 ||
                        input == 80 || input == 112 ||
                        input == nextKey1 || input == nextKey2) break;
                }

                //다음턴이 카드를 넘긴 경우
                if (input == nextKey1 || input == nextKey2) {
                    pushOk = true;
                    checkPlayerNoneAble(p2, p1, user, p3);
                    continue;
                }
                else {
                    pushOk = false;
                    //1번이 종쳤을 경우
                    if (input == 87 || input == 119) { //user가 종 친 경우
                        //탈락된 사용자일 경우 continue
                        if (user.getAvailable()) {
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
                    }
                    //2번이 종쳤을 경우
                    else if (input == 67 || input == 99) { //p1가 종 친 경우
                        //탈락된 사용자일 경우 continue
                        if (p1.getAvailable()) {

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
                    }
                    //3번이 종쳤을 경우
                    else if (input == 77 || input == 109) { //p2가 종 친 경우
                        //탈락된 사용자일 경우 종 칠 수 없음
                        if (p2.getAvailable()) {
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
                    }
                    //4번이 종쳤을 경우
                    else if (input == 80 || input == 112) { //p3가 종 친 경우
                        //탈락된 사용자일 경우 continue
                        if (p3.getAvailable()) {

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
                    }
                }

                //3번 탈락 처리
                if (p2.getBackCount() == 0) {
                    //화난 표정
                    makeAllFaceDefault(user);
                    makeAllFaceDefault(p1);
                    makeAllFaceDefault(p3);
                    makeFaceAngry(p2);
                    p2.setNoneAvailable();
                    printPlayersCardInfo(user, p1, p2, p3);
                    gotoxy(longInfoX + 10, longInfoY);
                    cout << p2.getPlayerNum() << "번 사용자가 탈락되었습니다.";
                    Sleep(2000);
                    gotoxy(longInfoX + 10, longInfoY);
                    cout << "                              ";
                }
                continue;
            }
        }
        //4번 차례
        if (turn % 4 == 3) {
            //다음 턴으로 넘어가는 키 지정
            int nextKey1 = 81, nextKey2 = 113;
            printPlayersCardInfo(user, p1, p2, p3);
            if (!p3.getAvailable()) {
                continue;
            }
            else {
                //Player 4 : 카드 내기 O, 종치기 P (79,111 / 80,112)

                //설명 출력
                gotoxy(longInfoX + 13, longInfoY - 2);
                cout << "                                        ";
                gotoxy(longInfoX + 13, longInfoY - 2);
                cout << "[ " << p3.getPlayerNum() << "번 PLAYER ]";


                //전 턴에서 카드내기가 이미 눌렸는지 확인
                if (pushOk == false) {
                    while (true) {
                        int value = _getch();
                        if (value == 79 || value == 111) break;
                    }
                }

                //카드 뒤집기
                if (p3.open() == -1) continue;
                PlaySound(TEXT("openCard.wav"), 0, SND_FILENAME | SND_ASYNC);
                frontCardPrint(p3.getFrontTopCard(), p3);
                printPlayersCardInfo(user, p1, p2, p3);

                //다음턴 출력
                gotoxy(longInfoX + 13, longInfoY - 2);
                cout << "                                        ";
                gotoxy(longInfoX + 13, longInfoY - 2);
                cout << "[ " << user.getPlayerNum() << "번 PLAYER ]";

                //다음 턴 선수의 키값 구하기 (탈락자 때문)
                if (!user.getAvailable()) {
                    nextKey1 = 88, nextKey2 = 120;
                    gotoxy(longInfoX + 13, longInfoY - 2);
                    cout << "                                        ";
                    gotoxy(longInfoX + 13, longInfoY - 2);
                    cout << "[ " << p1.getPlayerNum() << "번 PLAYER ]";
                    if (!p1.getAvailable()) {
                        nextKey1 = 78, nextKey2 = 110;
                        gotoxy(longInfoX + 13, longInfoY - 2);
                        cout << "                                        ";
                        gotoxy(longInfoX + 13, longInfoY - 2);
                        cout << "[ " << p2.getPlayerNum() << "번 PLAYER ]";
                        if (!p2.getAvailable()) {
                            nextKey1 = 79, nextKey2 = 111;
                            gotoxy(longInfoX + 13, longInfoY - 2);
                            cout << "                                        ";
                            gotoxy(longInfoX + 13, longInfoY - 2);
                            cout << "[ " << p3.getPlayerNum() << "번 PLAYER ]";
                        }
                    }
                }

                //종치거나 다음 차례가 카드넘김
                while (true) {
                    input = _getch();
                    if (input == 87 || input == 119 ||
                        input == 67 || input == 99 ||
                        input == 77 || input == 109 ||
                        input == 80 || input == 112 ||
                        input == nextKey1 || input == nextKey2) break;
                }

                //다음턴이 카드를 넘긴 경우
                if (input == nextKey1 || input == nextKey2) {
                    pushOk = true;
                    checkPlayerNoneAble(p3, p1, p2, user);
                    continue;
                }
                else {
                    pushOk = false;
                    //1번이 종친 경우
                    if (input == 87 || input == 119) { //user가 종 친 경우
                        if (user.getAvailable()) {
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
                    }
                    //2번이 종친 경우
                    else if (input == 67 || input == 99) { //p1가 종 친 경우
                        if (p1.getAvailable()) {
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
                    }
                    //3번이 종친 경우
                    else if (input == 77 || input == 109) { //p2가 종 친 경우
                        if (p2.getAvailable()) {
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
                    }
                    //4번이 종친 경우
                    else if (input == 80 || input == 112) { //p3가 종 친 경우
                        if (p3.getAvailable()) {
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
                    }
                }


                //4번 탈락 처리
                if (p3.getBackCount() == 0) {
                    //(나)화난 표정
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
                continue;
            }
        }
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
        cout << "│                                     │";
        gotoxy(15, 33);
        cout << "│      카드 넘기기 ▷  SPACE BAR      │";
        gotoxy(15, 34);
        cout << "│                                     │";
        gotoxy(15, 35);
        cout << "│        종 치기   ▷  ENTER          │";
        gotoxy(15, 36);
        cout << "│                                     │";
        gotoxy(15, 37);
        cout << "│                                     │";
        gotoxy(15, 38);
        cout << "└─────────────────────────────────────┘";
    }
    //사용자 생성
    Player user(1), com1(2), com2(3), com3(4);
    //카드 랜덤배치,사용자에게 카드 분배
    setInitCard(user, com1, com2, com3);
    //시드값을 얻기 위한 random_device
    random_device rd;
    //난수 생성 엔진 초기화
    mt19937 gen(rd());
    //0.5초 ~ 1.3초 균등한 난수 정의 (난이도 역할)
    uniform_int_distribution<int> sec(500, 1300);
    //com1 ~ com3 균등 난수
    uniform_int_distribution<int> com(1, 3);

    //반복
    int input = 0;
    int turn = -1;
    while (true) {
        turn++;
        if (turn % 4 == 0) {
            printPlayersCardInfo(user, com1, com2, com3);
            if ((int)com1.getAvailable() + (int)com2.getAvailable() + (int)com3.getAvailable() == 0){
                checkUserAvailable(user, com1, com2, com3);
                break;
            }
            if (!user.getAvailable()) {
                checkUserAvailable(user, com1, com2, com3);
                break;
            }
            else {
                //설명 출력
                gotoxy(longInfoX + 13, longInfoY - 2);
                cout << "                                        ";
                gotoxy(longInfoX + 13, longInfoY - 2);
                cout << "[ " << user.getPlayerNum() << "번 PLAYER ]";

                //카드 낼때까지 대기
                while (true) {
                    int input = _getch();
                    if (input == 32) break;
                }

                //카드 뒤집기
                if (user.open() == -1) continue;
                PlaySound(TEXT("openCard.wav"), 0, SND_FILENAME | SND_ASYNC);
                gotoxy(10, 14);
                frontCardPrint(user.getFrontTopCard(), user);

                //5개인지 확인
                if (checkFiveCard(user, com1, com2, com3)) {
                    turnCount++;
                    //로봇중에서 랜덤으로 종침
                    //랜덤 기다리는 시간
                    int msec = sec(gen);
                    //사용자 종침 여부
                    boolean userRinging = false;
                    clock_t start = clock();
                    //사용자가 로봇보다 빨리 칠 경우 true
                    while (true) {
                        clock_t end = clock();
                        if (_kbhit()) { 
                            int userRingingKey = _getch();
                            if (userRingingKey == 13) {
                                userRinging = true;
                                break;
                            }
                        }
                        if ((double)(end - start) >= msec) {
                            userRinging = false;
                            break;
                        }
                        else userRinging = false;
                    }
                    //사용자가 빠른경우
                    if (userRinging) {
                        PlaySound(TEXT("ringingBell.wav"), 0, SND_FILENAME | SND_ASYNC);
                        //점수 계산
                        user.plusScore();
                        //(나)웃는 표정
                        makeAllFaceDefault(com1);
                        makeAllFaceDefault(com2);
                        makeAllFaceDefault(com3);
                        makeFaceSmile(user);
                        //테이블 위의 카드 모두 가져감
                        getAllFrontCard(user, com1, com2, com3);
                        printPlayersCardInfo(user, com1, com2, com3);
                    }
                    //로봇이 빠른경우
                    else {
                        PlaySound(TEXT("ringingBell.wav"), 0, SND_FILENAME | SND_ASYNC);
                        int randomRobot = com(gen);
                        //남은 로봇 1대일 경우
                        if (com1.getAvailable() + com2.getAvailable() + com3.getAvailable() == 1) {
                            if (com1.getAvailable()) randomRobot = 1;
                            else if(com2.getAvailable()) randomRobot = 2;
                            else randomRobot = 3;
                        }
                        //남은 로봇 2대 이상일 경우
                        else {
                            //com1이 탈락인 경우
                            if (randomRobot == 1 && !com1.getAvailable()) randomRobot = 2;
                            //com2이 탈락인 경우
                            if (randomRobot == 2 && !com2.getAvailable()) randomRobot = 3;
                            //com3이 탈락인 경우
                            if (randomRobot == 3 && !com3.getAvailable()) randomRobot = 1;
                        }
                        switch (randomRobot) {
                        case 1:
                            //점수 계산 
                            com1.plusScore();
                            //(나)웃는 표정
                            makeAllFaceDefault(user);
                            makeAllFaceDefault(com2);
                            makeAllFaceDefault(com3);
                            makeFaceSmile(com1);
                            //테이블 위의 카드 모두 가져감
                            getAllFrontCard(com1, user, com2, com3);
                            printPlayersCardInfo(user, com1, com2, com3);
                            break;
                        case 2:
                            //점수 계산
                            com2.plusScore();
                            //(나)웃는 표정
                            makeAllFaceDefault(com1);
                            makeAllFaceDefault(com3);
                            makeAllFaceDefault(user);
                            makeFaceSmile(com2);
                            //테이블 위의 카드 모두 가져감
                            getAllFrontCard(com2, user, com1, com3);
                            printPlayersCardInfo(user, com1, com2, com3);
                            break;
                        case 3:
                            //점수 계산
                            com3.plusScore();
                            //(나)웃는 표정
                            makeAllFaceDefault(user);
                            makeAllFaceDefault(com1);
                            makeAllFaceDefault(com2);
                            makeFaceSmile(com3);
                            //테이블 위의 카드 모두 가져감
                            getAllFrontCard(com3, user, com1, com2);
                            printPlayersCardInfo(user, com1, com2, com3);
                            break;
                        }
                    }
                }
                //5개가 아니었을 때 종쳤을 경우
                else {
                    //사용자 종침 여부
                    boolean userRinging = false;
                    clock_t start = clock();
                    int userRingingKey;
                    //사용자가 1.5초안에 종을 쳤을 경우
                    while (true) {
                        clock_t end = clock();
                        double time = end - start;
                        if (_kbhit()) { //1.5초안에 종치면 true
                            userRingingKey = _getch();
                            if (userRingingKey == 13) {
                                userRinging = true;
                                break;
                            }
                        }
                        else { //1.5초 안에 예외키 누르거나 안누르면 false
                            userRinging = false;
                        }
                        if (time >= 1500) { //1.5초 기다려줌
                            userRinging = false;
                            break;
                        }
                    }
                    if (userRinging) {
                        //점수 계산
                        user.minusScore();
                        //화난 표정
                        makeAllFaceDefault(com1);
                        makeAllFaceDefault(com2);
                        makeAllFaceDefault(com3);
                        makeFaceAngry(user);
                        PlaySound(TEXT("missingBell.wav"), 0, SND_FILENAME | SND_ASYNC);
                        //카드 한장씩 나누어줌
                        missRinging(user, com1, com2, com3);
                        printPlayersCardInfo(user, com1, com2, com3);
                    }
                }
            }
            //사용자가 탈락하거나 com123이 모두 탈락한 경우
            if (user.getBackCount() == 0 || !user.getAvailable() || ((int)com1.getAvailable() + (int)com2.getAvailable() + (int)com3.getAvailable() == 0)) {
                checkUserAvailable(user, com1, com2, com3);
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

                //모든 로봇은 0.2+a 초간격으로 카드를 낸다.
                clock_t start = clock();
                while (true) {
                    clock_t end = clock();
                    if ((double)(end - start) >= 20) break;
                }

                //카드 뒤집기
                if (com1.open() == -1) continue;
                PlaySound(TEXT("openCard.wav"), 0, SND_FILENAME | SND_ASYNC);
                gotoxy(20, 14);
                frontCardPrint(com1.getFrontTopCard(), com1);
                
                //5개인지 확인
                if (checkFiveCard(user, com1, com2, com3)) {
                    turnCount++;
                    //로봇중에서 랜덤으로 종침
                    //기다리는 시간
                    int msec = sec(gen);
                    //사용자 종침 여부
                    boolean userRinging = false;
                    clock_t start = clock();
                    //사용자가 로봇보다 빨리 칠 경우 true
                    while (true) {
                        clock_t end = clock();
                        if (_kbhit()) {
                            int userRingingKey = _getch();
                            if (userRingingKey == 13) {
                                userRinging = true;
                                break;
                            }
                        }
                        if ((double)(end - start) >= msec) {
                            userRinging = false;
                            break;
                        }
                        else userRinging = false;
                    }
                    //사용자가 빠른경우
                    if (userRinging) {
                        PlaySound(TEXT("ringingBell.wav"), 0, SND_FILENAME | SND_ASYNC);
                        //점수 계산
                        user.plusScore();
                        //(나)웃는 표정
                        makeAllFaceDefault(com1);
                        makeAllFaceDefault(com2);
                        makeAllFaceDefault(com3);
                        makeFaceSmile(user);
                        //테이블 위의 카드 모두 가져감
                        getAllFrontCard(user, com1, com2, com3);
                        printPlayersCardInfo(user, com1, com2, com3);
                    }
                    //로봇이 빠른경우
                    else {
                        PlaySound(TEXT("ringingBell.wav"), 0, SND_FILENAME | SND_ASYNC);
                        int randomRobot = com(gen);
                        //남은 로봇 1대일 경우
                        if (com1.getAvailable() + com2.getAvailable() + com3.getAvailable() == 1) {
                            if (com1.getAvailable()) randomRobot = 1;
                            else if (com2.getAvailable()) randomRobot = 2;
                            else randomRobot = 3;
                        }
                        //남은 로봇 2대 이상일 경우
                        else {
                            //com1이 탈락인 경우
                            if (randomRobot == 1 && !com1.getAvailable()) randomRobot = 2;
                            //com2이 탈락인 경우
                            if (randomRobot == 2 && !com2.getAvailable()) randomRobot = 3;
                            //com3이 탈락인 경우
                            if (randomRobot == 3 && !com3.getAvailable()) randomRobot = 1;
                        }
                        switch (randomRobot) {
                        case 1:
                            //점수 계산
                            com1.plusScore();
                            //(나)웃는 표정
                            makeAllFaceDefault(user);
                            makeAllFaceDefault(com2);
                            makeAllFaceDefault(com3);
                            makeFaceSmile(com1);
                            //테이블 위의 카드 모두 가져감
                            getAllFrontCard(com1, user, com2, com3);
                            printPlayersCardInfo(user, com1, com2, com3);
                            break;
                        case 2:
                            //점수 계산
                            com2.plusScore();
                            //(나)웃는 표정
                            makeAllFaceDefault(com1);
                            makeAllFaceDefault(com3);
                            makeAllFaceDefault(user);
                            makeFaceSmile(com2);
                            //테이블 위의 카드 모두 가져감
                            getAllFrontCard(com2, user, com1, com3);
                            printPlayersCardInfo(user, com1, com2, com3);
                            break;
                        case 3:
                            //점수 계산
                            com3.plusScore();
                            //(나)웃는 표정
                            makeAllFaceDefault(user);
                            makeAllFaceDefault(com1);
                            makeAllFaceDefault(com2);
                            makeFaceSmile(com3);
                            //테이블 위의 카드 모두 가져감
                            getAllFrontCard(com3, user, com1, com2);
                            printPlayersCardInfo(user, com1, com2, com3);
                            break;
                        }
                    }
                }
                //5개가 아니었을 때 종쳤을 경우
                else {
                    //사용자 종침 여부
                    boolean userRinging = false;
                    clock_t start = clock();
                    int userRingingKey;
                    //사용자가 1.5초안에 종을 쳤을 경우
                    while (true) {
                        clock_t end = clock();
                        double time = end - start;
                        if (_kbhit()) { //1.5초안에 종치면 true
                            userRingingKey = _getch();
                            if (userRingingKey == 13) {
                                userRinging = true;
                                break;
                            }
                        }
                        else { //1.5초 안에 예외키 누르거나 안누르면 false
                            userRinging = false;
                        }
                        if (time >= 1500) { //1.5초 기다려줌
                            userRinging = false;
                            break;
                        }
                    }
                    if (userRinging) {
                        //점수 계산
                        user.minusScore();
                        //화난 표정
                        makeAllFaceDefault(com1);
                        makeAllFaceDefault(com2);
                        makeAllFaceDefault(com3);
                        makeFaceAngry(user);
                        PlaySound(TEXT("missingBell.wav"), 0, SND_FILENAME | SND_ASYNC);
                        //카드 한장씩 나누어줌
                        missRinging(user, com1, com2, com3);
                        printPlayersCardInfo(user, com1, com2, com3);
                    }
                }
            }
            if (com1.getBackCount() == 0) {
                //화난 표정
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
            if (user.getBackCount() == 0 || !user.getAvailable()) {
                checkUserAvailable(user, com1, com2, com3);
                break;
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

                //모든 로봇은 0.2+a 초간격으로 카드를 낸다.
                clock_t start = clock();
                while (true) {
                    clock_t end = clock();
                    if ((double)(end - start) >= 20) break;
                }

                //카드 뒤집기
                if (com2.open() == -1) continue;
                PlaySound(TEXT("openCard.wav"), 0, SND_FILENAME | SND_ASYNC);
                gotoxy(30, 14);
                frontCardPrint(com2.getFrontTopCard(), com2);

                //5개인지 확인
                if (checkFiveCard(user, com1, com2, com3)) {
                    turnCount++;
                    //로봇중에서 랜덤으로 종침
                    //기다리는 시간
                    int msec = sec(gen);
                    //사용자 종침 여부
                    boolean userRinging = false;
                    clock_t start = clock();
                    //사용자가 로봇보다 빨리 칠 경우 true
                    while (true) {
                        clock_t end = clock();
                        if (_kbhit()) {
                            int userRingingKey = _getch();
                            if (userRingingKey == 13) {
                                userRinging = true;
                                break;
                            }
                        }
                        if ((double)(end - start) >= msec) {
                            userRinging = false;
                            break;
                        }
                        else userRinging = false;
                    }
                    //사용자가 빠른경우
                    if (userRinging) {
                        PlaySound(TEXT("ringingBell.wav"), 0, SND_FILENAME | SND_ASYNC);
                        //점수 계산
                        user.plusScore();
                        //(나)웃는 표정
                        makeAllFaceDefault(com1);
                        makeAllFaceDefault(com2);
                        makeAllFaceDefault(com3);
                        makeFaceSmile(user);
                        //테이블 위의 카드 모두 가져감
                        getAllFrontCard(user, com1, com2, com3);
                        printPlayersCardInfo(user, com1, com2, com3);
                    }
                    //로봇이 빠른경우
                    else {
                        PlaySound(TEXT("ringingBell.wav"), 0, SND_FILENAME | SND_ASYNC);
                        int randomRobot = com(gen);
                        //남은 로봇 1대일 경우
                        if (com1.getAvailable() + com2.getAvailable() + com3.getAvailable() == 1) {
                            if (com1.getAvailable()) randomRobot = 1;
                            else if (com2.getAvailable()) randomRobot = 2;
                            else randomRobot = 3;
                        }
                        //남은 로봇 2대 이상일 경우
                        else {
                            //com1이 탈락인 경우
                            if (randomRobot == 1 && !com1.getAvailable()) randomRobot = 2;
                            //com2이 탈락인 경우
                            if (randomRobot == 2 && !com2.getAvailable()) randomRobot = 3;
                            //com3이 탈락인 경우
                            if (randomRobot == 3 && !com3.getAvailable()) randomRobot = 1;
                        }
                        switch (randomRobot) {
                        case 1:
                            //점수 계산
                            com1.plusScore();
                            //(나)웃는 표정
                            makeAllFaceDefault(user);
                            makeAllFaceDefault(com2);
                            makeAllFaceDefault(com3);
                            makeFaceSmile(com1);
                            //테이블 위의 카드 모두 가져감
                            getAllFrontCard(com1, user, com2, com3);
                            printPlayersCardInfo(user, com1, com2, com3);
                            break;
                        case 2:
                            //점수 계산
                            com2.plusScore();
                            //(나)웃는 표정
                            makeAllFaceDefault(com1);
                            makeAllFaceDefault(com3);
                            makeAllFaceDefault(user);
                            makeFaceSmile(com2);
                            //테이블 위의 카드 모두 가져감
                            getAllFrontCard(com2, user, com1, com3);
                            printPlayersCardInfo(user, com1, com2, com3);
                            break;
                        case 3:
                            //점수 계산
                            com3.plusScore();
                            //(나)웃는 표정
                            makeAllFaceDefault(user);
                            makeAllFaceDefault(com1);
                            makeAllFaceDefault(com2);
                            makeFaceSmile(com3);
                            //테이블 위의 카드 모두 가져감
                            getAllFrontCard(com3, user, com1, com2);
                            printPlayersCardInfo(user, com1, com2, com3);
                            break;
                        }
                    }
                }
                //5개가 아니었을 때 종쳤을 경우
                else {
                    //사용자 종침 여부
                    boolean userRinging = false;
                    clock_t start = clock();
                    int userRingingKey;
                    //사용자가 1.5초안에 종을 쳤을 경우
                    while (true) {
                        clock_t end = clock();
                        double time = end - start;
                        if (_kbhit()) { //1.5초안에 종치면 true
                            userRingingKey = _getch();
                            if (userRingingKey == 13) {
                                userRinging = true;
                                break;
                            }
                        }
                        else { //1.5초 안에 예외키 누르거나 안누르면 false
                            userRinging = false;
                        }
                        if (time >= 1500) { //1.5초 기다려줌
                            userRinging = false;
                            break;
                        }
                    }
                    if (userRinging) {
                        //점수 계산
                        user.minusScore();
                        //화난 표정
                        makeAllFaceDefault(com1);
                        makeAllFaceDefault(com2);
                        makeAllFaceDefault(com3);
                        makeFaceAngry(user);
                        PlaySound(TEXT("missingBell.wav"), 0, SND_FILENAME | SND_ASYNC);
                        //카드 한장씩 나누어줌
                        missRinging(user, com1, com2, com3);
                        printPlayersCardInfo(user, com1, com2, com3);
                    }
                }
            }
            if (com2.getBackCount() == 0) {
                //화난 표정
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
            if (user.getBackCount() == 0 || !user.getAvailable()) {
                checkUserAvailable(user, com1, com2, com3);
                break;
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

                //모든 로봇은 0.2+a 초간격으로 카드를 낸다.
                clock_t start = clock();
                while (true) {
                    clock_t end = clock();
                    if ((double)(end - start) >= 20) break;
                }

                //카드 뒤집기
                if (com3.open() == -1) continue;
                PlaySound(TEXT("openCard.wav"), 0, SND_FILENAME | SND_ASYNC);
                gotoxy(40, 14);
                frontCardPrint(com3.getFrontTopCard(), com3);

                //5개인지 확인
                if (checkFiveCard(user, com1, com2, com3)) {
                    turnCount++;
                    //로봇중에서 랜덤으로 종침
                    //기다리는 시간
                    int msec = sec(gen);
                    //사용자 종침 여부
                    boolean userRinging = false;
                    clock_t start = clock();
                    //사용자가 로봇보다 빨리 칠 경우 true
                    while (true) {
                        clock_t end = clock();
                        if (_kbhit()) {
                            int userRingingKey = _getch();
                            if (userRingingKey == 13) {
                                userRinging = true;
                                break;
                            }
                        }
                        if ((double)(end - start) >= msec) {
                            userRinging = false;
                            break;
                        }
                        else userRinging = false;
                    }
                    //사용자가 빠른경우
                    if (userRinging) {
                        PlaySound(TEXT("ringingBell.wav"), 0, SND_FILENAME | SND_ASYNC);
                        //점수 계산
                        user.plusScore();
                        //(나)웃는 표정
                        makeAllFaceDefault(com1);
                        makeAllFaceDefault(com2);
                        makeAllFaceDefault(com3);
                        makeFaceSmile(user);
                        //테이블 위의 카드 모두 가져감
                        getAllFrontCard(user, com1, com2, com3);
                        printPlayersCardInfo(user, com1, com2, com3);
                    }
                    //로봇이 빠른경우
                    else {
                        PlaySound(TEXT("ringingBell.wav"), 0, SND_FILENAME | SND_ASYNC);
                        int randomRobot = com(gen);
                        //남은 로봇 1대일 경우
                        if (com1.getAvailable() + com2.getAvailable() + com3.getAvailable() == 1) {
                            if (com1.getAvailable()) randomRobot = 1;
                            else if (com2.getAvailable()) randomRobot = 2;
                            else randomRobot = 3;
                        }
                        //남은 로봇 2대 이상일 경우
                        else {
                            //com1이 탈락인 경우
                            if (randomRobot == 1 && !com1.getAvailable()) randomRobot = 2;
                            //com2이 탈락인 경우
                            if (randomRobot == 2 && !com2.getAvailable()) randomRobot = 3;
                            //com3이 탈락인 경우
                            if (randomRobot == 3 && !com3.getAvailable()) randomRobot = 1;
                        }
                        switch (randomRobot) {
                        case 1:
                            //점수 계산
                            com1.plusScore();
                            //(나)웃는 표정
                            makeAllFaceDefault(user);
                            makeAllFaceDefault(com2);
                            makeAllFaceDefault(com3);
                            makeFaceSmile(com1);
                            //테이블 위의 카드 모두 가져감
                            getAllFrontCard(com1, user, com2, com3);
                            printPlayersCardInfo(user, com1, com2, com3);
                            break;
                        case 2:
                            //점수 계산
                            com2.plusScore();
                            //(나)웃는 표정
                            makeAllFaceDefault(com1);
                            makeAllFaceDefault(com3);
                            makeAllFaceDefault(user);
                            makeFaceSmile(com2);
                            //테이블 위의 카드 모두 가져감
                            getAllFrontCard(com2, user, com1, com3);
                            printPlayersCardInfo(user, com1, com2, com3);
                            break;
                        case 3:
                            //점수 계산
                            com3.plusScore();
                            //(나)웃는 표정
                            makeAllFaceDefault(user);
                            makeAllFaceDefault(com1);
                            makeAllFaceDefault(com2);
                            makeFaceSmile(com3);
                            //테이블 위의 카드 모두 가져감
                            getAllFrontCard(com3, user, com1, com2);
                            printPlayersCardInfo(user, com1, com2, com3);
                            break;
                        }
                    }
                }
                //5개가 아니었을 때 종쳤을 경우
                else {
                    //사용자 종침 여부
                    boolean userRinging = false;
                    clock_t start = clock();
                    int userRingingKey;
                    //사용자가 1.5초안에 종을 쳤을 경우
                    while (true) {
                        clock_t end = clock();
                        double time = end - start;
                        if (_kbhit()) { //1.5초안에 종치면 true
                            userRingingKey = _getch();
                            if (userRingingKey == 13) {
                                userRinging = true;
                                break;
                            }
                        }
                        else { //1.5초 안에 예외키 누르거나 안누르면 false
                            userRinging = false;
                        }
                        if (time >= 1500) { //1.5초 기다려줌
                            userRinging = false;
                            break;
                        }
                    }
                    if (userRinging) {
                        //점수 계산
                        user.minusScore();
                        //화난 표정
                        makeAllFaceDefault(com1);
                        makeAllFaceDefault(com2);
                        makeAllFaceDefault(com3);
                        makeFaceAngry(user);
                        PlaySound(TEXT("missingBell.wav"), 0, SND_FILENAME | SND_ASYNC);
                        //카드 한장씩 나누어줌
                        missRinging(user, com1, com2, com3);
                        printPlayersCardInfo(user, com1, com2, com3);
                    }
                }
            }
            if (com3.getBackCount() == 0) {
                //(나)화난 표정
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
            if (user.getBackCount() == 0 || !user.getAvailable()) {
                checkUserAvailable(user, com1, com2, com3);
                break;
            }
        }
        //게임 나가기 (강제종료)
        if (GetKeyValue() == 27) break;
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