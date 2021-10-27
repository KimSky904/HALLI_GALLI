#include<iostream>
#include<fstream>
using namespace std;

int main() {

    //사용자 이름, 점수 파일에 저장
    ofstream out("database.txt", ios::app);
    //임시 점수
    int score = 50;
    string userName = "하늘2";
    out << userName << " " << score << "\n";
    out.close();

	return 0;
}