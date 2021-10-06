#include<iostream>
#include<string>
#include<ctime>
#include<cstdlib>
#include<string>
#include<conio.h>
#include<Windows.h>
#include<time.h>	
#include<list>
#include "game.h"
using namespace std;
#define RED         (FOREGROUND_RED | FOREGROUND_INTENSITY)
#define BLUE        (FOREGROUND_BLUE | FOREGROUND_INTENSITY)
#define PINK        (RED | BLUE)
#define GREEN       (FOREGROUND_GREEN | FOREGROUND_INTENSITY)
#define YELLOW      (RED | GREEN)
#define WHITE       (RED | GREEN | BLUE)


//콘솔 세팅
void SetConsoleView();
//커서이동 함수
void gotoxy(int x, int y);
//keyboard 입력값 반환함
int GetKeyValue();
//색상지정
void PrintString(HANDLE hStdOut, WORD Attribute);
//화면로딩 draw
void DrawLoading();
//시작화면 draw
void DrawIntro();
//게임화면 draw
void DrawStartGame();
//설명화면 draw
void DrawInfoScreen();
//[게임진행] 카드분배
void setInitCard(Player& p1, Player& p2, Player& p3, Player& p4);
//메뉴선택
int ReadyGame();
//게임 진행 키
int GameKey();
//게임 시작
void StartGame();
//게임 설명
void ShowInfo();
//메인
int main(void);


//카드
Card cards[CARDCOUNT] = { //과일별 카드 20장 (1:6,2:5,3:4,4:3,5:2)
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
void SetConsoleView()
{
    system("mode con cols=120 lines=41 | title Halli Galli");   //화면크기,게임이름
}
//커서이동 함수
void gotoxy(int x, int y)
{
    COORD Pos;
    Pos.X = 2 * x;
    Pos.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
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

//화면로딩 draw
void DrawLoading() {

}
//시작화면 draw
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
    cout << "◎"; 
    gotoxy(29, 21);
    cout << "/∥";
    PrintString(hStdOut, RED);
    gotoxy(28, 22);
    cout << "▨▨▨";
    gotoxy(27, 23);
    cout << "▨▨▨▨";
    gotoxy(27, 24);
    cout << "▨▨▨▨▨▨▨";
    gotoxy(28, 25);
    cout << "▨▨▨▨";


    PrintString(hStdOut, WHITE);
    gotoxy(24, 28);
    cout << "▶ Game Rule for 'r'";
    gotoxy(24, 30);
    cout << "▶ Game Start for 's'";
    gotoxy(24, 32);
    cout << "▶ Exit for 'e'";
}
//게임화면 draw
void DrawStartGame()
{
    //120 41
    system("cls");

    //플레이어 1 (사용자) (왼쪽 상단)
    gotoxy(0, 0);
    cout << "▨━━━━━━━━━━━━━━▨";
    for (int i = 1; i < 7; i++) {
        gotoxy(0, i);
        cout << "┃              ┃";
    }
    gotoxy(0, 7);
    cout << "▨━━━━━━━━━━━━━━▨";
    gotoxy(0, 8);
    cout << "보유 카드 수 : "<<" 장";
    gotoxy(0, 9);
    cout << "판에 놓인 카드 수 : " << " 장";

    //플레이어 2 (오른쪽 상단)
    gotoxy(51, 0);
    cout << "▨━━━━━━━━━━━━━━▨";
    for (int i = 1; i < 7; i++) {
        gotoxy(51, i);
        cout << "┃              ┃";
    }
    gotoxy(51, 7);
    cout << "▨━━━━━━━━━━━━━━▨";
    gotoxy(48, 8);
    cout << "보유 카드 수 : " << " 장";
    gotoxy(48, 9);
    cout << "판에 놓인 카드 수 : " << " 장";

    //플레이어 3 (왼쪽 하단)
    gotoxy(0, 30);
    cout << "보유 카드 수 : " << " 장";
    gotoxy(0, 31);
    cout << "판에 놓인 카드 수 : " << " 장";
    gotoxy(0, 32);
    cout << "▨━━━━━━━━━━━━━━▨";
    for (int i = 33; i < 40; i++) {
        gotoxy(0, i);
        cout << "┃              ┃";
    }
    gotoxy(0, 40);
    cout << "▨━━━━━━━━━━━━━━▨";


    //플레이어 4 (오른쪽 하단)
    gotoxy(48, 30);
    cout << "보유 카드 수 : " << " 장";
    gotoxy(48, 31);
    cout << "판에 놓인 카드 수 : " << " 장";
    gotoxy(51, 32);
    cout << "▨━━━━━━━━━━━━━━▨";
    for (int i = 33; i < 40; i++) {
        gotoxy(51, i);
        cout << "┃              ┃";
    }
    gotoxy(51, 40);
    cout << "▨━━━━━━━━━━━━━━▨";


    //카드 1
    gotoxy(10, 14);
    cout << "┌──────────────┐";
    for (int i = 15; i < 25; i++) {
        gotoxy(10, i);
        cout << "│              │";
    }
    gotoxy(10, 25);
    cout << "└──────────────┘";

    //카드 2
    gotoxy(20, 14);
    cout << "┌──────────────┐";
    for (int i = 15; i < 25; i++) {
        gotoxy(20, i);
        cout << "│              │";
    }
    gotoxy(20, 25);
    cout << "└──────────────┘";

    //카드 3
    gotoxy(30, 14);
    cout << "┌──────────────┐";
    for (int i = 15; i < 25; i++) {
        gotoxy(30, i);
        cout << "│              │";
    }
    gotoxy(30, 25);
    cout << "└──────────────┘";

    //카드 4
    gotoxy(40, 14);
    cout << "┌──────────────┐";
    for (int i = 15; i < 25; i++) {
        gotoxy(40, i);
        cout << "│              │";
    }
    gotoxy(40, 25);
    cout << "└──────────────┘";


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


//[게임진행] 카드분배
void setInitCard(Player &p1, Player& p2, Player& p3, Player& p4) {
    srand((unsigned int)time(NULL));
    //과일별,개수별 카드 객체 생성 => 문제 : 카드 수는 28*4, 랜덤으로 분배되도록 바꿔야함(중복없이)
    int cnt = 0;
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 4; j++) {
            cards[cnt] = Card(i, j);
            cnt++;
        }
    }

    //각 플레이어에게 카드 분배
    for (int i = 0; i < CARDCOUNT/4; i++) {
        p1.pushBack(cards[i]);
    }
    for (int i = CARDCOUNT / 4; i < CARDCOUNT/2; i++) {
        p2.pushBack(cards[i]);
    }
    for (int i = CARDCOUNT / 2; i < CARDCOUNT * (3/4); i++) {
        p3.pushBack(cards[i]);
    }
    for (int i = CARDCOUNT * (3 / 4); i < CARDCOUNT; i++) {
        p4.pushBack(cards[i]);
    }
}




//메뉴선택
int ReadyGame()
{
    //시작화면 그리기
    DrawIntro();    
    while (true) {
        //키값 받아오기
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
//게임 진행 키
int GameKey()
{
    while (true) {
        //키값 받아오기 (종치기 : 1, 카드 내기 : 2, 나가기 : 0)
        int key = GetKeyValue();
        if (key == '\n') {         //종치기 = 1 (enter)
            return 1;
        }
        else if (key == ' ') {    //카드 내기 = 2 (space)
            return 2;
        }
        else if (key == 'e' || key == 'E') {    //exit = 0 (esc)
            break;
        }
    }
    return 0;
}
//게임 시작
void StartGame()
{
    DrawStartGame();
    int keyValue = GameKey();

    //각 사용자 객체 생성
    Player user(1);
    Player com1(2), com2(3), com3(4);
    //각 사용자 카드 분배
    setInitCard(user, com1, com2, com3);
    int turn = 1;
    

   /* while (true) {
        





        turn++;
    }*/

    //switch (keyValue) {
    //    //종치기
    //case 1:
    //    break;
    //    //카드 내기
    //case 2:
    //    break;
    //    //게임 종료
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
//게임 설명
void ShowInfo()
{
    DrawInfoScreen();
    while (true) {
        if (GetKeyValue() == 27)
            break;
    }
}
//메인
int main(void)
{
    SetConsoleView(); //콘솔설정
    int menuValue = -1;
    while (true)
    {
        menuValue = ReadyGame();    //인트로, 키 입력
        if (menuValue == 1) {       //rule
            ShowInfo();
        }
        else if (menuValue==2) {    //start
            StartGame();      
        }
        else {
            exit(1);
        }
        system("cls");
    }
    return 0;
}