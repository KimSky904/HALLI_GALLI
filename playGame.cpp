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
public:
    //탈락처리
    void setNoneAvailable() {
        available = false;
        cout << playerNum << "번 사용자가 탈락되었습니다." << endl;
    }
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
    }
    //뒤집은 카드스택의 가장 위 카드 반환
    Card getFrontTopCard() {
        if (front.empty()) return Card();
        return front.top();
    }
    //뒤집지 않은 카드스택의 가장 위 카드 반환
    Card getBackTopCard() {
        //if (back.empty()) return Card();
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
        //cout << "push됨, "<< getBackCount() << endl;
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


//빈 카드
void emptyCardPrint() {
    cout << "                                               "
        << "┏━━━━━━━━━━━━━━┓" << endl;
    for (int i = 0; i < 7; ++i)
        cout << "                                               "
        << "┃           ┃" << endl;

    cout << "                                               "
        << "┗━━━━━━━━━━━━━━┛" << endl;
}

//앞에 있는 카드 냄
void frontCardPrint(Card card,Player player) {
    HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
    //카드 타입
    int type = card.getType();
    char fruit = 'e';
    switch (type) {
        case 1: fruit = '@';
            PrintString(hStdOut, RED);
            break; //사과
        case 2: fruit = '@';
            PrintString(hStdOut, YELLOW);
            break; //바나나
        case 3: fruit = '@'; 
            PrintString(hStdOut, GREEN);
            break; //라임
        case 4: fruit = '@'; 
            PrintString(hStdOut, RED);
            break; //포도
    }
    //카드 출력 위치
    int x;
    int y = 14;
    switch (player.getPlayerNum()){
        case 1: x = 10; break;
        case 2 : x = 20; break;
        case 3 : x = 30; break;
        case 4 : x = 40; break;
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
        cout << "│       "<< fruit <<"       │" << endl;
        gotoxy(x, y + 6);
        cout << "│              │" << endl;
        gotoxy(x, y + 7);
        cout << "│              │" << endl;
        gotoxy(x, y + 8);
        cout << "│              │" << endl;
        gotoxy(x, y + 9);
        cout << "│              │" << endl;
        gotoxy(x, y + 10);
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
        cout << "│       " << fruit << "      │" << endl;
        gotoxy(x, y + 4);
        cout << "│              │" << endl;
        gotoxy(x, y + 5);
        cout << "│              │" << endl;
        gotoxy(x, y + 6);
        cout << "│              │" << endl;
        gotoxy(x, y + 7);
        cout << "│       " << fruit << "      │" << endl;
        gotoxy(x, y + 8);
        cout << "│              │" << endl;
        gotoxy(x, y + 9);
        cout << "│              │" << endl;
        gotoxy(x, y + 10);
        cout << "└──────────────┘" << endl;
        break;
    case 3:
        gotoxy(x, y);
        cout << "┌──────────────┐" << endl;
        gotoxy(x, y + 1);
        cout << "│              │" << endl;
        gotoxy(x, y + 2);
        cout << "│   " << fruit << "           │" << endl;
        gotoxy(x, y + 3);
        cout << "│              │" << endl;
        gotoxy(x, y + 4);
        cout << "│              │" << endl;
        gotoxy(x, y + 5);
        cout << "│       " << fruit << "       │" << endl;
        gotoxy(x, y + 6);
        cout << "│              │" << endl;
        gotoxy(x, y + 7);
        cout << "│              │" << endl;
        gotoxy(x, y + 8);
        cout << "│           " << fruit << "  │" << endl;
        gotoxy(x, y + 9);
        cout << "│              │" << endl;
        gotoxy(x, y + 10);
        cout << "└──────────────┘" << endl;
        break;
    case 4:
        gotoxy(x, y);
        cout << "┌──────────────┐" << endl;
        gotoxy(x, y + 1);
        cout << "│              │" << endl;
        gotoxy(x, y + 2);
        cout << "│    " << fruit << "     " << fruit << "     │" << endl;
        gotoxy(x, y + 3);
        cout << "│              │" << endl;
        gotoxy(x, y + 4);
        cout << "│              │" << endl;
        gotoxy(x, y + 5);
        cout << "│              │" << endl;
        gotoxy(x, y + 6);
        cout << "│              │" << endl;
        gotoxy(x, y + 7);
        cout << "│              │" << endl;
        gotoxy(x, y + 8);
        cout << "│    " << fruit << "     " << fruit << "     │" << endl;
        gotoxy(x, y + 9);
        cout << "│              │" << endl;
        gotoxy(x, y + 10);
        cout << "└──────────────┘" << endl;
        break;
    case 5:
        gotoxy(x, y);
        cout << "┌──────────────┐" << endl;
        gotoxy(x, y + 1);
        cout << "│              │" << endl;
        gotoxy(x, y + 2);
        cout << "│    " << fruit << "     " << fruit << "     │" << endl;
        gotoxy(x, y + 3);
        cout << "│              │" << endl;
        gotoxy(x, y + 4);
        cout << "│              │" << endl;
        gotoxy(x, y + 5);
        cout << "│       " << fruit << "       │" << endl;
        gotoxy(x, y + 6);
        cout << "│              │" << endl;
        gotoxy(x, y + 7);
        cout << "│              │" << endl;
        gotoxy(x, y + 8);
        cout << "│    " << fruit << "     " << fruit << "     │" << endl;
        gotoxy(x, y + 9);
        cout << "│              │" << endl;
        gotoxy(x, y + 10);
        cout << "└──────────────┘" << endl;
        break;
    default:
        emptyCardPrint();
    }
}


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
    cout << "     ▨▨▨▨";
    gotoxy(25, 23);
    cout << "    ▨▨▨▨▨";
    gotoxy(25, 24);
    cout << "   ▨▨▨▨▨▨";
    gotoxy(25, 25);
    cout << "   ▨▨▨▨▨▨";
    gotoxy(25, 26);
    cout << "    ▨▨▨▨▨ ";
    gotoxy(25, 27);
    cout << "     ▨▨▨▨ ";
                         

    PrintString(hStdOut, WHITE);
    gotoxy(24, 29);
    cout << "▶ Game Rule for 'r'";
    gotoxy(24, 31);
    cout << "▶ Game Start for 's'";
    gotoxy(24, 33);
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
    cout << "보유 카드 수 : -";
    gotoxy(0, 9);
    cout << "판에 놓인 카드 수 : -";

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
    cout << "보유 카드 수 : -";
    gotoxy(48, 9);
    cout << "판에 놓인 카드 수 : -";

    //플레이어 3 (왼쪽 하단)
    gotoxy(0, 30);
    cout << "보유 카드 수 : -";
    gotoxy(0, 31);
    cout << "판에 놓인 카드 수 : -";
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
    cout << "보유 카드 수 : -";
    gotoxy(48, 31);
    cout << "판에 놓인 카드 수 : -";
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


//[카드분배] swap
void swap(Card* A, Card* B)
{
    Card temp;
    temp = *A;
    *A = *B;
    *B = temp;
}
//[카드분배] 카드 랜덤배치
void randomCard(Card* card) {
    for (int i = 0; i < CARDCOUNT; i++) swap(&card[i], &card[(rand() % (CARDCOUNT - i)) + i]);
}
//[카드분배] 사용자에게 카드 분배
void setInitCard(Player& p1, Player& p2, Player& p3, Player& p4) {
    randomCard(cards);
    //각 플레이어에게 카드 분배
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
    cout << "[ "<<winner.getPlayerNum() <<"번 사용자가 테이블 위의 모든 카드를 획득합니다. ]" << endl;
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
}
//[판별] 종 잘못쳤을 경우 - 각 player에게 카드 한장씩 back에 넘김
void missRinging(Player& p1, Player& p2, Player& p3, Player& p4) {
    //cout << "종을 잘못쳤으므로 카드를 나누어줍니다." << endl;
    //플레이 가능한 인원 수 세기
    int cnt = 0;
    if (p1.getAvailable()) cnt++;
    if (p2.getAvailable()) cnt++;
    if (p3.getAvailable()) cnt++;
    if (p4.getAvailable()) cnt++;
    //back 카드가 없을 경우,부족한 경우 탈락
    if (p1.backIsEmpty() || p1.getBackCount() < cnt - 1) {
        //cout << "상대에게 줄 카드가 부족하여 탈락되었습니다." << endl;
        p1.setNoneAvailable();
        return;
    }
    //게임플레이 가능한 인원 카드 나눠주기
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
    //카드를 준 후에 카드가 없을 경우 탈락
    if (p1.backIsEmpty()) {
       // cout << "카드를 주고 남은 카드가 없어 탈락되었습니다." << endl;
        p1.setNoneAvailable();
    }
    return;
}


//[출력] 테이블 위의 카드 정보
void printTableInfo(Player& user, Player& p1, Player& p2, Player& p3) {
    cout << "현재 테이블 카드 [";
    user.getFrontTopCard().getInfo(); cout << ", ";
    p1.getFrontTopCard().getInfo(); cout << ", ";
    p2.getFrontTopCard().getInfo(); cout << ", ";
    p3.getFrontTopCard().getInfo();
    cout << "]" << endl;
}
//[출력] 사용자 카드 정보
void printBackInfo(Player& user, Player& p1, Player& p2, Player& p3) {
    cout << "현재 사용자 카드 [";
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

void printPlayersCardInfo(Player &p1,Player &p2,Player &p3,Player &p4) {
    gotoxy(0, 8);
    cout << "보유 카드 수 : " << p1.getBackCount() << "  ";
    gotoxy(0, 9);
    cout << "판에 놓인 카드 수 : " << p1.getFrontCount() << "  ";

    gotoxy(48, 8);
    cout << "보유 카드 수 : " << p2.getBackCount() << "  ";
    gotoxy(48, 9);
    cout << "판에 놓인 카드 수 : " << p2.getFrontCount() << "  ";

    gotoxy(0, 30);
    cout << "보유 카드 수 : " << p3.getBackCount() << "  ";
    gotoxy(0, 31);
    cout << "판에 놓인 카드 수 : " << p3.getFrontCount() << "  ";

    gotoxy(48, 30);
    cout << "보유 카드 수 : " << p4.getBackCount() << "  ";
    gotoxy(48, 31);
    cout << "판에 놓인 카드 수 : " << p4.getFrontCount() << "  ";
}

//게임 시작
void StartGame()
{
    DrawStartGame();
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
            if (user.getAvailable()) {
                cout << "승자는 Player1 입니다." << endl;
            }
            else if (p1.getAvailable()) {
                cout << "승자는 Player2 입니다." << endl;
            }
            else if (p2.getAvailable()) {
                cout << "승자는 Player3 입니다." << endl;
            }
            else if (p3.getAvailable()) {
                cout << "승자는 Player4 입니다." << endl;
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
                gotoxy(26, 7);
                cout << "                                         ";
                gotoxy(26, 7);
                cout << "[ " << user.getPlayerNum() << "번 차례 ]";
                if (user.open() == -1) continue;
                gotoxy(10, 14);
                frontCardPrint(user.getFrontTopCard(),user);
                //printTableInfo(user, p1, p2, p3);
                //printBackInfo(user, p1, p2, p3);
                //cout << "테이블 카드 개수 : " << user.getFrontCount() << endl;
                //cout << "사용자 카드 개수 : " << user.getBackCount() << endl;
                input = GameKey();
                if (input == 1) {
                    gotoxy(24, 9);
                    cout << "                                                          ";
                    gotoxy(24, 9);
                    cout << "[ 1번 player : 종을 쳤습니다 ]";
                    //과일 5개일때 쳤을 경우
                    if (checkFiveCard(user, p1, p2, p3)) {
                        //테이블 위의 카드 모두 가져감
                        getAllFrontCard(user, p1, p2, p3);
                        printPlayersCardInfo(user, p1, p2, p3);
                    }
                    //잘못 쳤을 경우
                    else {
                        missRinging(user, p1, p2, p3);
                        printPlayersCardInfo(user, p1, p2, p3);
                    }
                }
                else if(input==2){
                    gotoxy(15, 9);
                    cout << "                                                          ";
                    gotoxy(15, 9);
                    cout << "[ 1번 player : 종을 치지 않았습니다. 다음 턴으로 넘어갑니다. ]";
                }
            }
        }
        else if (turn % 4 == 1) {
            printPlayersCardInfo(user, p1, p2, p3);
            if (!p1.getAvailable()) {
                continue;
            }
            else {
                gotoxy(26, 7);
                cout << "                                         ";
                gotoxy(26, 7);
                cout << "[ " << p1.getPlayerNum() << "번 차례 ]";
                if (p1.open() == -1) continue;
                gotoxy(20, 14);
                frontCardPrint(user.getFrontTopCard(),p1);
                //printTableInfo(user, p1, p2, p3);
                //printBackInfo(user, p1, p2, p3);
                //cout << "테이블 카드 개수 : " << p1.getFrontCount() << endl;
                //cout << "사용자 카드 개수 : " << p1.getBackCount() << endl;
                input = GameKey();
                if (input == 1) {
                    gotoxy(24, 9);
                    cout << "                                                          ";
                    gotoxy(24, 9);
                    cout << "[ 2번 player : 종을 쳤습니다 ]";
                    //과일 5개일때 쳤을 경우
                    if (checkFiveCard(p1, user, p2, p3)) {
                        //테이블 위의 카드 모두 가져감
                        getAllFrontCard(p1, user, p2, p3);
                        printPlayersCardInfo(user, p1, p2, p3);
                    }
                    //잘못 쳤을 경우
                    else {
                        missRinging(p1, user, p2, p3);
                        printPlayersCardInfo(user, p1, p2, p3);
                    }
                }
                else {
                    gotoxy(15, 9);
                    cout << "                                                          ";
                    gotoxy(15, 9);
                    cout << "[ 2번 player : 종을 치지 않았습니다. 다음 턴으로 넘어갑니다. ]";
                }
            }
        }
        else if (turn % 4 == 2) {
            printPlayersCardInfo(user, p1, p2, p3);
            if (!p2.getAvailable()) {
                continue;
            }
            else {
                gotoxy(26, 7);
                cout << "                                         ";
                gotoxy(26, 7);
                cout << "[ " << p2.getPlayerNum() << "번 차례 ]";
                if (p2.open() == -1) continue;
                gotoxy(30, 14);
                frontCardPrint(user.getFrontTopCard(),p2);
                //printTableInfo(user, p1, p2, p3);
                //printBackInfo(user, p1, p2, p3);
                //cout << "테이블 카드 개수 : " << p2.getFrontCount() << endl;
                //cout << "사용자 카드 개수 : " << p2.getBackCount() << endl;
                input = GameKey();
                if (input == 1) {
                    gotoxy(24, 9);
                    cout << "                                                          ";
                    gotoxy(24, 9);
                    cout << "[ 3번 player : 종을 쳤습니다 ]";
                    //과일 5개일때 쳤을 경우
                    if (checkFiveCard(p2, user, p1, p3)) {
                        //테이블 위의 카드 모두 가져감
                        getAllFrontCard(p2, user, p1, p3);
                        printPlayersCardInfo(user, p1, p2, p3);
                    }
                    //잘못 쳤을 경우
                    else {
                        missRinging(p2, user, p1, p3);
                        printPlayersCardInfo(user, p1, p2, p3);
                    }
                }
                else {
                    gotoxy(15, 9);
                    cout << "                                                          ";
                    gotoxy(15, 9);
                    cout << "[ 3번 player : 종을 치지 않았습니다. 다음 턴으로 넘어갑니다. ]";
                }
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
                cout << "[ " << p3.getPlayerNum() << "번 차례 ]";
                if (p3.open() == -1) continue;
                gotoxy(40, 14);
                frontCardPrint(user.getFrontTopCard(),p3);
                //printTableInfo(user, p1, p2, p3);
                //printBackInfo(user, p1, p2, p3);
                //cout << "테이블 카드 개수 : " << p3.getFrontCount() << endl;
                //cout << "사용자 카드 개수 : " << p3.getBackCount() << endl;
                input = GameKey();
                if (input == 1) {
                    gotoxy(24, 9);
                    cout << "                                                          ";
                    gotoxy(24, 9);
                    cout << "[ 4번 player : 종을 쳤습니다 ]";
                    //과일 5개일때 쳤을 경우
                    if (checkFiveCard(p3, p1, p2, user)) {
                        //테이블 위의 카드 모두 가져감
                        getAllFrontCard(p3, p1, p2, user);
                        printPlayersCardInfo(user, p1, p2, p3);
                    }
                    //잘못 쳤을 경우
                    else {
                        //각 인원에게 카드 하나씩 줌, 카드수 부족할 시 탈락
                        missRinging(p3, p1, p2, user);
                        printPlayersCardInfo(user, p1, p2, p3);
                    }
                }
                else {
                    gotoxy(15, 9);
                    cout << "                                                          ";
                    gotoxy(15, 9);
                    cout << "[ 4번 player : 종을 치지 않았습니다. 다음 턴으로 넘어갑니다. ]";
                }
            }
        }
        //  cout << "==========================================================" << endl;
        //게임 나가기 (강제종료)
        if (GetKeyValue() == 27) break;    
    }


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