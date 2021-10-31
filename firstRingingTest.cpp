#include<iostream>
#include<time.h>
#include<conio.h>
using namespace std;
int main() {

	//clock_t start = clock();
	//
	//while (true) {
	//	clock_t end = clock();
	//	int input;
	//	input = _kbhit();
	//	cout << input << endl;
	//	//엔터 입력하면 종료
	//	if (input == 1) {
	//		int input1 = _getch();
	//		cout << "enter 입력해서 종료" << input1 <<endl;
	//		break;
	//	}
	//	//10초가 지나면 종료
	//	if ((double)(end - start) >= 10000) {
	//		cout << "10초가 지나서 종료" << endl;
	//		break;
	//	}

	//}

	//double a = 0.1;
	int a = 152;
	int b = 15;

	double c = a/b;
	cout << c << endl;
	printf("%.2f", c);

}