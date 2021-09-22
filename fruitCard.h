#ifndef Card_h
#define Card_h

/*
*	카드 숫자 : 1,2,3,4,5
*	과일 종류 : 바나나, 딸기, 라임, 포도
* 
*   
* 
*	[기본틀]
* 		system("cls");
		gotoxy(5, 4);
		cout << "┏━━━━━━━━━━━━━━┓";
		gotoxy(5, 5);
		cout << "┃　　　　　　　　　　　　　　┃";
		gotoxy(5, 6);
		cout << "┃　　　　　　　　　　　　　　┃";
		gotoxy(5, 7);
		cout << "┃　　　　　　　　　　　　　　┃";
		gotoxy(5, 8);
		cout << "┃　　　　　　　　　　　　　　┃";
		gotoxy(5, 9);
		cout << "┃　　　　　　　　　　　　　　┃";
		gotoxy(5, 10);
		cout << "┃　　　　　　　　　　　　　　┃";
		gotoxy(5, 11);
		cout << "┃　　　　　　　　　　　　　　┃";
		gotoxy(5, 12);
		cout << "┃　　　　　　　　　　　　　　┃";
		gotoxy(5, 13);
		cout << "┗━━━━━━━━━━━━━━┛";
* 
* 
*/

class Card {
public:
	void banana_1(){
		system("cls");
		gotoxy(5, 4);
		cout << "┏━━━━━━━━━━━━━━┓";
		gotoxy(5, 5);
		cout << "┃　　　　　　　　　　　　　　┃";
		gotoxy(5, 6);
		cout << "┃　　　　　　　　　　　　　　┃";
		gotoxy(5, 7);
		cout << "┃　　　　　　　　　　　　　　┃";
		gotoxy(5, 8);
		cout << "┃　　　　　　　　　　　　　　┃";
		gotoxy(5, 9);
		cout << "┃　　　　　　　　　　　　　　┃";
		gotoxy(5, 10);
		cout << "┃　　　　　　　　　　　　　　┃";
		gotoxy(5, 11);
		cout << "┃　　　　　　　　　　　　　　┃";
		gotoxy(5, 12);
		cout << "┃　　　　　　　　　　　　　　┃";
		gotoxy(5, 13);
		cout << "┗━━━━━━━━━━━━━━┛";
	}
};



#endif