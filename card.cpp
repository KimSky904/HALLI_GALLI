#include "card.h"
#include<iostream>
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
    //���
    void getInfo() {
        cout << "[ " << type << " , " << num << " ]";
    }
};