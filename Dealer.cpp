#include "Dealer.h"
HANDLE console2 = GetStdHandle(STD_OUTPUT_HANDLE);
void Dealer::printTotalAndCards()
{
    cout << "Dealer:";
    if (no_of_cards == 2)
    {
        printCard(cards[1]);
        SetConsoleTextAttribute(console2, 252);
        cout << u8"▓▓";
        SetConsoleTextAttribute(console2, 2);
    }
    else
        for (int i = 1; i <= no_of_cards; i++)
            printCard(cards[i]);
    cout << " ";
    if (no_of_cards == 2)
        cout << "()" << endl;
    else if (as && status == 0)
        cout << "(" << cards_value << '/' << cards_value + 10 << ")" << endl;
    else if (as && status == 1)
        cout << "(" << cards_value << ")" << endl;
    else if (status == 3)
        cout << "(Blackjack!)";
    else if (status == -1)
        cout << "( " << cards_value << " - Bust)" << endl;
    else
        cout << "(" << cards_value << ")" << endl;
    cout << endl;
}
void Dealer::printTotalAndCards_2()
{
    cout << "Dealer:";
    for (int i = 1; i <= no_of_cards; i++)
        printCard(cards[i]);
    cout << " ";
    if (as && status == 0)
        cout << "(" << cards_value << '/' << cards_value + 10 << ")";
    else if (as && status == 1)
        cout << "(" << cards_value << ")";
    else if (status == 3)
        cout << "(Blackjack!)";
    else if (status == -1)
        cout << "( " << cards_value << " - Bust)";
    else
        cout << "(" << cards_value << ")";

    cout << endl << endl;
}
bool Dealer::getAs()
{
    return as;
}

