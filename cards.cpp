#include "cards.h"
//Card deck[210];
HANDLE console1 = GetStdHandle(STD_OUTPUT_HANDLE);

void printCard(Card c)
{
    SetConsoleTextAttribute(console1, c.color);
    std::cout << c.name;
    SetConsoleTextAttribute(console1, 2);
    std::cout << " ";
}
void shuffle_deck(Card deck[210])//fisher-yates
{
    srand(time(NULL));
    for (int i = 207; i > 0; i--)
    {
        int rnd = rand() % (i + 1);
        std::swap(deck[i], deck[rnd]);
    }
}
//int n = 207;
