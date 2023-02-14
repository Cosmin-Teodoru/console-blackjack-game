#ifndef CARDS_H
#define CARDS_H
#include "header.h"


struct Card
{
    std::string name;
    int color, value;
};
void printCard(Card c);
void shuffle_deck(Card deck[210]);
#endif // CARDS_H
