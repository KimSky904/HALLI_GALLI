#include<iostream>
#include<fstream>
using namespace std;

int main() {

    //����� �̸�, ���� ���Ͽ� ����
    ofstream out("database.txt", ios::app);
    //�ӽ� ����
    int score = 50;
    string userName = "�ϴ�2";
    out << userName << " " << score << "\n";
    out.close();

	return 0;
}