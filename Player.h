#ifndef PLAYER_H
#define PLAYER_H
#include "cards.h"
using namespace std;
class Player
{
protected:
    int cards_value, no_of_cards, money, bet, winnings;
    float score, total_score;
    int status;///0 for continuing, 1 for stopping(< 21), 2 for stopping at 21, -1 for losing, 3 for blackjack
    bool as, dbl;
    string nick;
    Card cards[15];

public:
    Player();
    void addCard(Card deck[210], int& n);
    void printTotalAndCards();
    void reset();
    void endTurn();
    void setNick(string n);
    void calcScore(Player dealer);
    void makeDouble(Card deck[210], int& n);
    void placeBet();
    bool getBlj();
    int getVal();
    int getStatus();
    int getWinnings();
    int getMoney();
    int getBet();
    float getScore();
    float getTotalScore();
    string getNick();
};
#endif // PLAYER_H
