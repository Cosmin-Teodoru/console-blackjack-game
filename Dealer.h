#ifndef DEALER_H
#define DEALER_H

#include "Player.h"
#include "cards.h"

class Dealer : public Player
{
public:
    void printTotalAndCards();///card face down
    void printTotalAndCards_2();///normal
    bool getAs();
};

#endif // DEALER_H
