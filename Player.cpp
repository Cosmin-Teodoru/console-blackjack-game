#include "Player.h"
Player::Player()
{
    cards_value = 0;
    no_of_cards = 0;
    score = 0;
    status = 0;
    as = 0;
    total_score = 0;
    dbl = 0;
    bet = 0;
    money = 50000;
    winnings = 0;
}
void Player::addCard(Card deck[210], int& n)
{
    Card card = deck[n--];
    if (status == 0)
    {
        if (card.value == 1 && cards_value + 10 <= 21)
            as = true;
        cards[++no_of_cards] = card;
        cards_value += card.value;
        if (as)
        {
            if (cards_value + 10 == 21 && no_of_cards == 2)
            {
                status = 3;
                cards_value = 21;
            }
            else if (cards_value + 10 == 21)
            {
                status = 2;
                cards_value = 21;
            }
            else if (cards_value + 10 > 21)
            {
                as = false;
            }
        }
        else
        {
            if (cards_value == 21)
            {
                status = 2;
            }
            else if (cards_value > 21)
            {
                status = -1;
            }
        }
    }
}
void Player::printTotalAndCards()
{
    cout << nick << ':';

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

    cout << " (bet: " << bet << "$)" << endl << endl;
}
int Player::getVal()
{
    return cards_value;
}
int Player::getStatus()
{
    return status;
}
void Player::endTurn()
{
    if (status == 0)
        status = 1;
    if (as)
        cards_value += 10;
}
void Player::reset()
{
    cards_value = 0;
    no_of_cards = 0;
    score = 0;
    status = 0;
    as = 0;
    if (dbl)
        bet /= 2;
    dbl = 0;
    winnings = 0;
}
void Player::setNick(string s)
{
    nick = s;
}
void Player::calcScore(Player dealer)
{
    score = 0;
    if (status == -1)
        score = 0;
    else if (status == 1 && dealer.status == -1)
        score = 2;
    else if (status == 1 && dealer.status == 1)
    {
        if (cards_value > dealer.cards_value)
            score = 2;
        else if (cards_value < dealer.cards_value)
            score = 0;
        else
            score = 1;
    }
    else if (status == 0 && (dealer.status == 2 || dealer.status == 3))
        score = 0;
    else if (status == 1 && (dealer.status == 2 || dealer.status == 3))
        score = 0;
    else if (status == 2 && (dealer.status == 1 || dealer.status == -1))
        score = 2;
    else if (status == 2 && dealer.status == 2)
        score = 1;
    else if (status == 2 && dealer.status == 3)
        score = 0;
    else if (status == 3 && dealer.status != 3)
        score = 2.5;


    money += bet * score;
    winnings += bet * score;
    score -= 1;
    if (dbl)
        score *= 2;
    total_score += score;
}
void Player::makeDouble(Card deck[210], int& n)
{
    if (money >= bet)
    {
        dbl = true;
        this->addCard(deck, n);
        this->endTurn();
        money -= bet;
        bet *= 2;
    }

}
void Player::placeBet()
{
    string command = "c";
    if (bet != 0)
    {
        if (bet * 2 <= money)
        {
            while (1)
            {
                cout << nick << "(" << money << "$ - previous bet: " << bet << "$)\nr - repeat bet\nd - double previous bet\na - all-in\nc - choose another value\n:";
                cin >> command;
                if (command == "r" || command == "d" || command == "a" || command == "c")
                    break;
                else
                    cout << "Unknown command\n";
            }
        }
        else if (bet <= money)
        {
            while (1)
            {
                cout << nick << "(" << money << "$ - previous bet: " << bet << "$)\nr - repeat bet\na - all-in\nc - choose another value\n:";
                cin >> command;
                if (command == "r" || command == "a" || command == "c")
                    break;
                else
                    cout << "Unknown command\n";
            }
        }
        else
        {
            while (1)
            {
                cout << nick << "(" << money << "$ - previous bet: " << bet << "$)\na - all-in\nc - choose another value\n:";
                cin >> command;
                if (command == "a" || command == "c")
                    break;
                else
                    cout << "Unknown command\n";
            }
        }

    }
    if (command == "a")
        bet = money;
    else if (command == "d")
        bet *= 2;
    else if (command == "c")
    {
        while (1)
        {
            cout << nick << "(" << money << "$)" << ", place your bet(min. 2$): ";
            cin >> bet;
            cin.clear();
            cin.ignore(256, '\n');
            if (bet < 2)
                cout << "Invalid value\n";
            else if (bet > money)
                cout << "Not enough money\n";
            else
                break;
        }
    }
    money -= bet;
}

int Player::getMoney()
{
    return money;
}
int Player::getBet()
{
    return bet;
}
float Player::getScore()
{
    return score;
}
float Player::getTotalScore()
{
    return total_score;
}
string Player::getNick()
{
    return nick;
}
int Player::getWinnings()
{
    return winnings;
}
