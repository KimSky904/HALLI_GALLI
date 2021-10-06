#pragma once
using namespace std;
class Card{
	int type;
	int num;
public:
	Card();
	Card(int type, int num);
	int getType();
	int getNumber();
	void getInfo();
};