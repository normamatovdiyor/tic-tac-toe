#include <iostream>
#include <windows.h>
#include <conio.h>
#include <iomanip>

using namespace std;

bool gmov = false, validInput = false, win = false, second_player_bot = false;
string name;

char sign[3][3] = { {' ',' ',' '},{' ',' ',' '},{' ',' ',' '} };
int a, turn = 1;
char xo;

enum position { p1, p2, p3, p4, p5, p6, p7, p8, p9 };
position pl;

void table();
void logic();
void welcome();
void startGame();
void instro();
void input();
void winpage(int);
int minimax(char sign[3][3], int depth, bool isMaximizer);
int evaluate(char sign[3][3]);
position findBestMove(char sign[3][3]);

void welcome()
{
    char choise;
    system("cls");

    cout << endl << endl << endl << endl << endl << endl;
    cout << setw(20) << "Welcome!" << endl;
    cout << setw(30) << "1. To start game press 1" << endl;
    cout << setw(36) << "2. to read instruction press 2" << endl;
    cout << setw(39) << "3. for game with computer press 3" << endl;
    cout << setw(24) << "4. to exit press 4" << endl;
    cin >> choise;

    switch (choise)
    {
    case '1':
        system("cls");
        startGame();
        break;

    case '2':
        instro();
        break;

    case '3':
        system("cls");
        second_player_bot = true;
        startGame(); 
        break;

    case '4':
        system("cls");
        exit(0);

    default:
        break;
    }
    choise = 0;

    gmov = false;
    turn = 1;
    for (int i = 0; i < 3; ++i)
    {
        for (int j = 0; j < 3; ++j)
        {
            sign[i][j] = ' ';

        }
    }
}

void startGame()
{
    while (!gmov)
    {
        table();
        if ((second_player_bot && turn % 2 != 0) || (!second_player_bot && turn % 2 != 0))
        {
            input(); // Player 1's turn
        }
        else if (second_player_bot && turn % 2 == 0)
        {
            pl = findBestMove(sign); // Bot's turn
        }
        else
        {
            input(); // Player 2's turn
        }
        logic();
        Sleep(10);
    }
}


void table()
{
    system("cls");
    cout << endl << endl << endl << endl;
    cout << "     " << "|" << "    " << "|" << endl
        << "  " << sign[0][0] << "  " << "|" << "  " << sign[0][1] << " " << "|" << " " << sign[0][2] << endl
        << " " << "----" << "|" << "----" << "|" << "----" << endl
        << "     " << "|" << "    " << "|" << endl
        << "  " << sign[1][0] << "  " << "|" << "  " << sign[1][1] << " " << "|" << " " << sign[1][2] << endl
        << " " << "----" << "|" << "----" << "|" << "----" << endl
        << "     " << "|" << "    " << "|" << endl
        << "  " << sign[2][0] << "  " << "|" << "  " << sign[2][1] << " " << "|" << " " << sign[2][2] << endl;

    if (turn % 2 != 0)
    {
        cout << "Player 1: ";
    }
    else
    {
        cout << "Player 2: ";
    }
}

void input()
{
    char vb;
    bool validMove = false;

    while (!validMove) {
        cin >> vb;

        switch (vb)
        {
        case '1':
            pl = p1;
            break;

        case '2':
            pl = p2;
            break;

        case '3':
            pl = p3;
            break;

        case '4':
            pl = p4;
            break;

        case '5':
            pl = p5;
            break;

        case '6':
            pl = p6;
            break;

        case '7':
            pl = p7;
            break;

        case '8':
            pl = p8;
            break;

        case '9':
            pl = p9;
            break;

        case '0':
            system("cls");
            exit(0);

        default:
            continue;
        }

        int row = (pl + 1 - 1) / 3;
        int col = (pl + 1 - 1) % 3;

        if (sign[row][col] == ' ') {
            validMove = true;
        }
        else {
            cout << "Position occupied! Choose another position: ";
        }
    }
}

void logic()
{
    if (turn % 2 != 0)
    {
        xo = 'X';
    }
    else
    {
        xo = 'O';
    }

    switch (pl)
    {
    case p1:
        sign[0][0] = xo;
        break;

    case p2:
        sign[0][1] = xo;
        break;

    case p3:
        sign[0][2] = xo;
        break;

    case p4:
        sign[1][0] = xo;
        break;

    case p5:
        sign[1][1] = xo;
        break;

    case p6:
        sign[1][2] = xo;
        break;

    case p7:
        sign[2][0] = xo;
        break;

    case p8:
        sign[2][1] = xo;
        break;

    case p9:
        sign[2][2] = xo;
        break;

    default:
        break;
    }

    for (int i = 0; i < 3; ++i) {
        if (sign[i][0] == xo && sign[i][1] == xo && sign[i][2] == xo) {
            win = true;
            winpage(turn);
            return;
        }
    }

    for (int i = 0; i < 3; ++i) {
        if (sign[0][i] == xo && sign[1][i] == xo && sign[2][i] == xo) {
            win = true;
            winpage(turn);
            return;
        }
    }

    if ((sign[0][0] == xo && sign[1][1] == xo && sign[2][2] == xo) ||
        (sign[0][2] == xo && sign[1][1] == xo && sign[2][0] == xo)) {
        win = true;
        winpage(turn);
        return;
    }

    if (turn == 9 && !win) {
        winpage(0);
        return;
    }

    ++turn;
}

void winpage(int player)
{
    int plnumb = 0;
    if (player % 2 == 0)
    {
        plnumb = 2;
    }
    else
    {
        plnumb = 1;
    }
    char ch = 0;
    
    if (player == 0)
        cout << "\nIt's a draw!" << endl;
    else
        cout << "Player " << plnumb << " wins!" << endl;
    gmov = true;

    cout << endl << "\n Press any key to return to homepage: ";
    plnumb = 0;
    cin >> ch;
    while (ch != 0)
    {
        ch = 0;
        welcome();

    }
}

void instro()
{
    char ch = 0;

    system("cls");

    cout << endl << endl
        << "          " << "Game starts from player 1. Player 1 plays with 'X', so player 2 plays with 'O'." << endl
        << "          " << "Table is 3 by 3. By clicking on a position, you will make your move. Players win when a player gets 3 in a row horizontally, vertically, or diagonally." << endl
        << "          " << "In order to place 'X' or 'O', enter the number of the position." << endl
        << "          " << "If you want to terminate the game while playing, press 0." << endl << endl;

    cout << "     " << "|" << "    " << "|" << endl
        << "  1  " << "|" << " 2  " << "|" << "  3 " << endl
        << " " << "----" << "|" << "----" << "|" << "----" << endl
        << "     " << "|" << "    " << "|" << endl
        << " 4   " << "|" << " 5  " << "|" << "  6  " << endl
        << " " << "----" << "|" << "----" << "|" << "----" << endl
        << "     " << "|" << "    " << "|" << endl
        << " 7   " << "|" << " 8  " << "|" << " 9  ";

    cout << endl << endl << "\n Press any key to return to homepage: ";
    cin >> ch;
    while (ch != 0)
    {
        ch = 0;
        welcome();
    }
}

int main()
{
    welcome();
}

int minimax(char sign[3][3], int depth, bool isMaximizer) {
    int score = evaluate(sign);

    if (score == 10 || score == -10) {
        return score;
    }

    if (depth == 0) {
        return 0;
    }

    if (isMaximizer) {
        int bestScore = -1000;

        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                if (sign[i][j] == ' ') {
                    sign[i][j] = 'O';
                    bestScore = max(bestScore, minimax(sign, depth - 1, !isMaximizer));
                    sign[i][j] = ' ';
                }
            }
        }

        return bestScore;
    }
    else {
        int bestScore = 1000;

        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                if (sign[i][j] == ' ') {
                    sign[i][j] = 'X';
                    bestScore = min(bestScore, minimax(sign, depth - 1, !isMaximizer));
                    sign[i][j] = ' ';
                }
            }
        }

        return bestScore;
    }
}

int evaluate(char sign[3][3]) {
    // Check rows, columns, and diagonals for a win
    for (int i = 0; i < 3; ++i) {
        if (sign[i][0] == sign[i][1] && sign[i][1] == sign[i][2]) {
            if (sign[i][0] == 'O') return 10; 
            else if (sign[i][0] == 'X') return -10; 
        }
        if (sign[0][i] == sign[1][i] && sign[1][i] == sign[2][i]) {
            if (sign[0][i] == 'O') return 10; 
            else if (sign[0][i] == 'X') return -10; 
        }
    }
    if (sign[0][0] == sign[1][1] && sign[1][1] == sign[2][2]) {
        if (sign[0][0] == 'O') return 10; 
        else if (sign[0][0] == 'X') return -10; 
    }
    if (sign[0][2] == sign[1][1] && sign[1][1] == sign[2][0]) {
        if (sign[0][2] == 'O') return 10; 
        else if (sign[0][2] == 'X') return -10; 
    }

    // Check for blocking opponent's win
    for (int i = 0; i < 3; ++i) {
        if ((sign[i][0] == sign[i][1] && sign[i][0] != ' ' && sign[i][2] == ' ') ||
            (sign[i][1] == sign[i][2] && sign[i][1] != ' ' && sign[i][0] == ' ') ||
            (sign[i][0] == sign[i][2] && sign[i][0] != ' ' && sign[i][1] == ' ')) {
            return -5; 
        }
        if ((sign[0][i] == sign[1][i] && sign[0][i] != ' ' && sign[2][i] == ' ') ||
            (sign[1][i] == sign[2][i] && sign[1][i] != ' ' && sign[0][i] == ' ') ||
            (sign[0][i] == sign[2][i] && sign[0][i] != ' ' && sign[1][i] == ' ')) {
            return -5; 
    }
    if ((sign[0][0] == sign[1][1] && sign[0][0] != ' ' && sign[2][2] == ' ') ||
        (sign[1][1] == sign[2][2] && sign[1][1] != ' ' && sign[0][0] == ' ') ||
        (sign[0][0] == sign[2][2] && sign[0][0] != ' ' && sign[1][1] == ' ') ||
        (sign[0][2] == sign[1][1] && sign[0][2] != ' ' && sign[2][0] == ' ') ||
        (sign[1][1] == sign[2][0] && sign[1][1] != ' ' && sign[0][2] == ' ') ||
        (sign[0][2] == sign[2][0] && sign[0][2] != ' ' && sign[1][1] == ' ')) {
        return -5; 
    }

    
    int botScore = 0;
    int opponentScore = 0;
    if (sign[1][1] == 'O') botScore += 2; 
    else if (sign[1][1] == 'X') opponentScore += 2;
    if (sign[0][0] == 'O' || sign[0][2] == 'O' || sign[2][0] == 'O' || sign[2][2] == 'O') botScore += 1; 
    else if (sign[0][0] == 'X' || sign[0][2] == 'X' || sign[2][0] == 'X' || sign[2][2] == 'X') opponentScore += 1;

    return botScore - opponentScore;
}


position findBestMove(char sign[3][3]) {
    int bestMove = -1000;
    position bestPosition;

    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            if (sign[i][j] == ' ') {
                sign[i][j] = 'O';
                int moveValue = minimax(sign, 2, false);
                sign[i][j] = ' ';
                if (moveValue > bestMove) {
                    bestMove = moveValue;
                    bestPosition = static_cast<position>(i * 3 + j);
                }
            }
        }
    }

    return bestPosition;
}
}