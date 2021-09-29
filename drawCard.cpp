#include "drawCard.h"
#include <iostream>

using namespace std;
void emptyCardPrint() {
    cout << "                                               "
        << "┏━━━━━━━━━━━━━━┓" << endl;
    for (int i = 0; i < 7; ++i)
        cout << "                                               "
        << "┃           ┃" << endl;

    cout << "                                               "
        << "┗━━━━━━━━━━━━━━┛" << endl;
}
void frontCardPrint(Card card) {
    //카드 타입
    int type = card.getType();
    char fruit = 'e';
    switch (type) {
        case 1: fruit = '!'; break; 
        case 2: fruit = '@'; break; 
        case 3: fruit = '#'; break;     
        case 4: fruit = '$'; break; 
    }

    switch (card.getNumber()) {
        case 1:
            cout << "                                               "
                << "┏━━━━━━━━━━━━━━┓" << endl;
            cout << "                                               "
                << "┃           ┃" << endl;
            cout << "                                               "
                << "┃           ┃" << endl;
            cout << "                                               "
                << "┃           ┃" << endl;
            cout << "                                               "
                << "┃     " << fruit << "     ┃" << endl;
            cout << "                                               "
                << "┃           ┃" << endl;
            cout << "                                               "
                << "┃           ┃" << endl;
            cout << "                                               "
                << "┃           ┃" << endl;
            cout << "                                               "
                << "┗━━━━━━━━━━━━━━┛" << endl;
            break;
        case 2:
            cout << "                                               "
                << "┏━━━━━━━━━━━━━━┓" << endl;
            cout << "                                               "
                << "┃           ┃" << endl;
            cout << "                                               "
                << "┃           ┃" << endl;
            cout << "                                               "
                << "┃     " << fruit << "     ┃" << endl;
            cout << "                                               "
                << "┃           ┃" << endl;
            cout << "                                               "
                << "┃     " << fruit << "     ┃" << endl;
            cout << "                                               "
                << "┃           ┃" << endl;
            cout << "                                               "
                << "┃           ┃" << endl;
            cout << "                                               "
                << "┗━━━━━━━━━━━━━━┛" << endl;
            break;
        case 3:
            cout << "                                               "
                << "┏━━━━━━━━━━━━━━┓" << endl;
            cout << "                                               "
                << "┃           ┃" << endl;
            cout << "                                               "
                << "┃           ┃" << endl;
            cout << "                                               "
                << "┃     " << fruit << "     ┃" << endl;
            cout << "                                               "
                << "┃           ┃" << endl;
            cout << "                                               "
                << "┃   " << fruit << "   " << fruit << "   ┃" << endl;
            cout << "                                               "
                << "┃           ┃" << endl;
            cout << "                                               "
                << "┃           ┃" << endl;
            cout << "                                               "
                << "┗━━━━━━━━━━━━━━┛" << endl;
            break;
        case 4:
            cout << "                                               "
                << "┏━━━━━━━━━━━━━━┓" << endl;
            cout << "                                               "
                << "┃           ┃" << endl;
            cout << "                                               "
                << "┃   " << fruit << "   " << fruit << "   ┃" << endl;
            cout << "                                               "
                << "┃           ┃" << endl;
            cout << "                                               "
                << "┃           ┃" << endl;
            cout << "                                               "
                << "┃           ┃" << endl;
            cout << "                                               "
                << "┃   " << fruit << "   " << fruit << "   ┃" << endl;
            cout << "                                               "
                << "┃           ┃" << endl;
            cout << "                                               "
                << "┗━━━━━━━━━━━━━━┛" << endl;
            break;
        case 5:
            cout << "                                               "
                << "┏━━━━━━━━━━━━━━┓" << endl;
            cout << "                                               "
                << "┃           ┃" << endl;
            cout << "                                               "
                << "┃   " << fruit << "   " << fruit << "   ┃" << endl;
            cout << "                                               "
                << "┃           ┃" << endl;
            cout << "                                               "
                << "┃     " << fruit << "     ┃" << endl;
            cout << "                                               "
                << "┃           ┃" << endl;
            cout << "                                               "
                << "┃   " << fruit << "   " << fruit << "   ┃" << endl;
            cout << "                                               "
                << "┃           ┃" << endl;
            cout << "                                               "
                << "┗━━━━━━━━━━━━━━┛" << endl;
            break;
        default:
            emptyCardPrint();
    }
}

