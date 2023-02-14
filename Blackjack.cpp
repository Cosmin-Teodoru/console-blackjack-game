#include "header.h"
#include "cards.h"
#include "Player.h"
#include "Dealer.h"
using namespace std;
ifstream fin("cards.txt");
HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
CONSOLE_FONT_INFOEX cfi;

Card deck[210];
int n = 207;

Player players[5];
Dealer dealer;
int no = 0, aux;
void cls(HANDLE hConsole) // source: stack overflow
{
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    SMALL_RECT scrollRect;
    COORD scrollTarget;
    CHAR_INFO fill;

    // Get the number of character cells in the current buffer.
    if (!GetConsoleScreenBufferInfo(hConsole, &csbi))
    {
        return;
    }

    // Scroll the rectangle of the entire buffer.
    scrollRect.Left = 0;
    scrollRect.Top = 0;
    scrollRect.Right = csbi.dwSize.X;
    scrollRect.Bottom = csbi.dwSize.Y;

    // Scroll it upwards off the top of the buffer with a magnitude of the entire height.
    scrollTarget.X = 0;
    scrollTarget.Y = (SHORT)(0 - csbi.dwSize.Y);

    // Fill with empty spaces with the buffer's default text attribute.
    fill.Char.UnicodeChar = TEXT(' ');
    fill.Attributes = csbi.wAttributes;

    // Do the scroll
    ScrollConsoleScreenBuffer(hConsole, &scrollRect, NULL, scrollTarget, &fill);

    // Move the cursor to the top left corner too.
    csbi.dwCursorPosition.X = 0;
    csbi.dwCursorPosition.Y = 0;

    SetConsoleCursorPosition(hConsole, csbi.dwCursorPosition);
}
//cls(console);
void print_all_highlighted_turn(int turn)
{
    for (int i = 0; i < no; i++)
    {
        if (i == turn)
            SetConsoleTextAttribute(console, 14);
        players[i].printTotalAndCards();
    }
    dealer.printTotalAndCards();
}
bool compare_players(Player p1, Player p2)
{
    if (p1.getMoney() > p2.getMoney())
        return true;
    else if (p1.getMoney() == p2.getMoney() && p1.getScore() > p2.getScore())
        return true;
    return false;
}
int main()
{
    string command = "", auxs, eliminated[10];
    char comm = ' ';
    int games = 0, m = 0;


    cfi.cbSize = sizeof(cfi);
    cfi.nFont = 0;
    cfi.dwFontSize.X = 0;                   // Width of each character in the font
    cfi.dwFontSize.Y = 21;                  // Height
    cfi.FontFamily = FF_DONTCARE;
    cfi.FontWeight = FW_NORMAL;
    wcscpy(cfi.FaceName, L"Consolas"); // Choose your font
    SetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE), FALSE, &cfi);


    SetConsoleTextAttribute(console, 2);
    SetConsoleOutputCP(65001);///enable unicode characters

    if (fin.good())
    {
        for (int i = 0; i < 208; i++)
            fin >> deck[i].name;
        for (int i = 0; i < 208; i++)
            fin >> deck[i].value;
        for (int i = 0; i < 208; i++)
            fin >> deck[i].color;
    }
    else
    {
        cout << "Could not find deck file\n";
        Sleep(200);
        cout << "Generating deck...\n";
        deck[0].name += "A";
        deck[1].name += "2";
        deck[2].name += "3";
        deck[3].name += "4";
        deck[4].name += "5";
        deck[5].name += "6";
        deck[6].name += "7";
        deck[7].name += "8";
        deck[8].name += "9";
        deck[9].name += "10";
        deck[10].name += "J";
        deck[11].name += "Q";
        deck[12].name += "K";
        for (int i = 0; i <= 8; i++)
            deck[i].value = i + 1;
        for (int i = 9; i <= 12; i++)
            deck[i].value = 10;
        for (int i = 0; i < 13; i++)
            deck[i + 13] = deck[i + 26] = deck[i + 39] = deck[i];
        for (int i = 0; i < 13; i++)
        {
            deck[i].name += u8"♠";
            deck[i].color = 244;
        }
        for (int i = 13; i < 26; i++)
        {
            deck[i].name += u8"♦";
            deck[i].color = 244;
        }
        for (int i = 26; i < 39; i++)
        {
            deck[i].name += u8"♠";
            deck[i].color = 240;
        }
        for (int i = 39; i < 52; i++)
        {
            deck[i].name += u8"♣";
            deck[i].color = 240;
        }
        for (int i = 0; i < 52; i++)
            deck[i + 52] = deck[i + 104] = deck[i + 156] = deck[i];
    }
    fin.close();
    while (no > 5 || no < 1)
    {
        cout << "Enter number of players: ";
        cin >> no;
        cin.clear();
        cin.ignore(256, '\n');
        if (no > 5)
            cout << "Too many players\n";
        else if (no < 1)
            cout << "Not enough players\n";
    }

    cout << "Do you want to choose your nicknames?(y - yes/ n - no)\n";
    comm = getch();
    while (comm != 'y' && comm != 'n')
    {
        cout << "Unknown command\n" << "Do you want to choose your nicknames?(y - yes/ n - no)\n";
        comm = getch();
    }
    if (comm == 'n')
    {
        for (int i = 0; i < 5; i++)
        {
            string ss = "Player ";
            players[i].setNick(ss + (char)(i + 1 + '0'));
        }
        //players[9].setNick("Player 10");
    }
    else
    {
        cout << "Choose your nickname:\n";
        for (int i = 0; i < no; i++)
        {
            cout << "Player " << i + 1 << ": ";
            cin >> command;
            players[i].setNick(command);
        }
    }
    dealer.setNick("Dealer");

    srand(time(0));
    int rnd = rand() % 100 + 10;
    while (rnd)
    {
        shuffle_deck(deck);
        rnd--;
    }
    cout << "Shuffling deck";
    Sleep(333);
    cout << '.';
    Sleep(333);
    cout << '.';
    Sleep(333);
    cout << '.';
    Sleep(500);
    cout << endl;
    do
    {
        for (int i = 0; i < no; i++)
            players[i].placeBet();
        for (int x = 1; x <= 2; x++)
        {

            cls(console);
            for (int i = 0; i < no; i++)
            {
                players[i].addCard(deck, n);
                for (int j = 0; j < no; j++)
                {
                    players[j].printTotalAndCards();

                }
                dealer.printTotalAndCards();
                Sleep(800);
                cls(console);
            }
            dealer.addCard(deck, n);
            for (int j = 0; j < no; j++)
            {
                players[j].printTotalAndCards();

            }
            dealer.printTotalAndCards();
            Sleep(800);
        }
        for (int i = 0; i < no && dealer.getStatus() != 3; i++)
        {

            cls(console);
            print_all_highlighted_turn(i);
            if (players[i].getStatus() == 0 && players[i].getMoney() >= players[i].getBet())
            {
                cout << players[i].getNick() << "(h - hit / s - stand / d - double): ";
                cin >> command;
                while (command != "h" && command != "s" && command != "d")
                {
                    cout << "Unknown command\n" << players[i].getNick() << "(h - hit / s - stand / d - double): ";
                    cin >> command;
                }
                if (command == "s")
                {
                    players[i].endTurn();
                }
                else if (command == "h")
                {
                    players[i].addCard(deck, n);
                }
                else
                {
                    players[i].makeDouble(deck, n);
                }
                cls(console);
                print_all_highlighted_turn(i);
            }
            while (players[i].getStatus() == 0)
            {

                cout << players[i].getNick() << "(h - hit / s - stand): ";
                cin >> command;
                while (command != "h" && command != "s")
                {
                    cout << "Unknown command\n" << players[i].getNick() << "(h - hit / s - stand): ";
                    cin >> command;
                }
                if (command == "s")
                {
                    players[i].endTurn();
                }
                else if (command == "h")
                {
                    players[i].addCard(deck, n);
                }
                cls(console);
                print_all_highlighted_turn(i);
            }
        }
        bool all_lost = 1;
        for (int x = 0; x < no; x++)
        {
            if (players[x].getStatus() != -1 && players[x].getStatus() != 3)
                all_lost = 0;
        }
        if (all_lost)
            dealer.endTurn();
        Sleep(1500);
        cls(console);
        for (int j = 0; j < no; j++)
            players[j].printTotalAndCards();
        dealer.printTotalAndCards_2();

        while (dealer.getStatus() == 0)
        {

            if (dealer.getVal() > 16 || (dealer.getAs() && (dealer.getVal() + 10 > 16)))
            {
                dealer.endTurn();

                if (dealer.getAs() == 1)
                {
                    cls(console);
                    for (int j = 0; j < no; j++)
                        players[j].printTotalAndCards();
                    dealer.printTotalAndCards_2();
                    cout << endl;
                }

            }
            else
            {
                dealer.addCard(deck, n);
                Sleep(1000);
                cls(console);
                for (int j = 0; j < no; j++)
                    players[j].printTotalAndCards();
                dealer.printTotalAndCards_2();
                cout << endl;
            }
        }
        for (int j = 0; j < no; j++)
            players[j].calcScore(dealer);
        Sleep(2000);
        cout << "Score(this game):\n";
        for (int j = 0; j < no; j++)
        {
            cout << players[j].getNick() << ":" << players[j].getScore();
            cout << "  +" << players[j].getWinnings() << '$' << endl;
        }
        cout << "\nTotal Score:\n";
        for (int j = 0; j < no; j++)
        {
            cout << players[j].getNick() << ":" << players[j].getTotalScore() << endl;
        }

        for (int j = 0; j < no; j++)
            players[j].reset();
        dealer.reset();

        if (n < 50)
        {
            rnd = rand() % 100;
            while (rnd)
            {
                shuffle_deck(deck);
                rnd--;
            }
            n = 207;
            cout << "Shuffling deck";
            Sleep(333);
            cout << '.';
            Sleep(333);
            cout << '.';
            Sleep(333);
            cout << '.';
            Sleep(500);
        }
        cout << '\n';
        SetConsoleTextAttribute(console, 4);
        for (int i = 0; i < no - 1; i++)
        {
            if (players[i].getMoney() < 2)
            {
                cout << players[i].getNick() << " lost all of his/her money and was eliminated\n";
                eliminated[m++] = players[i].getNick();
                for (int j = i; j < no - 1; j++)
                    players[j] = players[j + 1];
                no--;
                i--;
            }
        }
        if (players[no - 1].getMoney() < 2)
        {
            cout << players[no - 1].getNick() << " lost all of his/her money and was eliminated\n";
            eliminated[m++] = players[no - 1].getNick();
            no--;
        }
        if (no == 0)
        {
            cout << "All players were eliminated\n\n";
            SetConsoleTextAttribute(console, 2);
            break;
        }
        SetConsoleTextAttribute(console, 2);
        cout << "Continue game?(y - yes/ n - no)\n";
        char comm = getch();
        while (comm != 'y' && comm != 'n')
        {
            cout << "Unknown command\n" << "Continue game?(y - yes/ n - no)\n";
            comm = getch();
        }
        cout << endl;
        cls(console);
        command = "";
        command = command + comm;
        games++;
    } while (command != "n");///end of game

    cout << "Saving";
    Sleep(333);
    cout << '.';
    Sleep(333);
    cout << '.';
    Sleep(333);
    cout << '.';
    Sleep(500);
    cout << '\n';
    ofstream gout("cards.txt");
    for (int i = 0; i < 208; i++)
    {
        gout << deck[i].name << " ";
    }
    gout << endl;
    for (int i = 0; i < 208; i++)
    {
        gout << deck[i].value << " ";
    }
    gout << endl;
    for (int i = 0; i < 208; i++)
    {
        gout << deck[i].color << " ";
    }
    sort(players, players + no, compare_players);

    cout << "Results:\n";
    int place = 0;
    if (no >= 1)
    {
        SetConsoleTextAttribute(console, 6);
        cout << "1st: " << players[0].getNick() << ' ' << players[0].getMoney() << "$\n";
        place++;
        if (no >= 2)
        {
            SetConsoleTextAttribute(console, 7);
            cout << "2nd: " << players[1].getNick() << ' ' << players[1].getMoney() << "$\n";
            place++;
            if (no >= 3)
            {
                SetConsoleTextAttribute(console, 12);
                cout << "3rd: " << players[2].getNick() << ' ' << players[2].getMoney() << "$\n";
                place++;
                if (no >= 4)
                {
                    SetConsoleTextAttribute(console, 15);
                    for (int i = 3; i < no; i++)
                    {
                        cout << i + 1 << "th: " << players[i].getNick() << ' ' << players[i].getMoney() << "$\n";
                        place++;
                    }
                }
            }
        }
    }
    SetConsoleTextAttribute(console, 4);
    for (int i = m - 1; i >= 0; i--)
    {
        place++;
        switch (place)
        {
        case 1:
            cout << "1st: ";
            break;
        case 2:
            cout << "2nd: ";
            break;
        case 3:
            cout << "3rd: ";
            break;
        default:
            cout << place << "th: ";
        }
        cout << eliminated[i] << " eliminated\n";
    }
    SetConsoleTextAttribute(console, 2);
    cout << "\nPress any key to close.\n";
    getch();
    return 0;
}
