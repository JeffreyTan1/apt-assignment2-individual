#include <iostream>
#include "Tile.h"
#include "Board.h"

#define COLUMN_MAX 26
#define COLUMN_MIN 1
#define ROW_MAX 25
#define ROW_MIN 0

using std::cout;
using std::endl;
using std::string;

//class Tile;

//contains uppercase letters A to Z
string init[COLUMN_MAX];

Board::Board()
{
    for (int ch = 'a'; ch <= 'z'; ch++)
    {
        init[ch - 'a'] = ::toupper(ch);
    }
    vector<vector<Tile *>> vec(ROW_MAX + 1, vector<Tile *>(COLUMN_MAX + 1));
    this->board = vec;
}
Board::~Board()
{
    for (int i = 0; i < ROW_MAX + 1; i++)
    {
        for (int j = 0; j < COLUMN_MAX + 1; ++j)
        {
            if (!(board[i][j] == nullptr))
            {
                delete board[i][j];
            }
        }
    }
}

vector<vector<Tile *>> Board::getBoard()
{
    return this->board;
}

void Board::printBoard()
{
    for (int i = 0; i < 2; i++)
    {
        for (int j = 0; j < COLUMN_MAX; j++)
        {
            if (i == 0 && j == 0)
            {
                cout << "   " << j << "  ";
            }
            else if (i == 0 && j < 10)
            {
                cout << j << "  ";
            }
            else if (i == 0 && j > 9)
            {
                cout << j << " ";
            }
            else if (i == 1 && j == 0)
            {
                cout << "  -"
                     << "--";
            }
            else if (i == 1 && j == COLUMN_MAX - 1)
            {
                cout << "----";
            }
            else if (i == 1)
            {
                cout << "---";
            }
        }
        cout << endl;
    }

    for (int i = 0; i < ROWS; i++)
    {
        cout << init[i] << " ";
        for (int j = 0; j < COLS; ++j)
        {
            if (!(board[i][j] == nullptr))
            {
                string ptv = board[i][j]->toString();
                cout << ptv + "|";
            }
            else if (j == 0)
            {
                cout << "|";
            }
            else
            {
                cout << "  |";
            }
        }
        cout << endl;
    }
}

void Board::printPrettyBoard()
{
    for (int i = 0; i < 2; i++)
    {
        for (int j = 0; j < COLUMN_MAX; j++)
        {
            if (i == 0 && j == 0)
            {
                cout << "   " << j << "  ";
            }
            else if (i == 0 && j < 10)
            {
                cout << j << "  ";
            }
            else if (i == 0 && j > 9)
            {
                cout << j << " ";
            }
            else if (i == 1 && j == 0)
            {
                cout << "  -"
                     << "--";
            }
            else if (i == 1 && j == COLUMN_MAX - 1)
            {
                cout << "----";
            }
            else if (i == 1)
            {
                cout << "---";
            }
        }
        cout << endl;
    }

    for (int i = 0; i < ROWS; i++)
    {
        cout << init[i] << " ";
        for (int j = 0; j < COLS; ++j)
        {
            if (!(board[i][j] == nullptr))
            {
                string ptv = board[i][j]->toPrettyString();
                cout << ptv + "|";
            }
            else if (j == 0)
            {
                cout << "|";
            }
            else
            {
                cout << "  |";
            }
        }
        cout << endl;
    }
}

void Board::placeTile(Tile *tile, int row, int col)
{
    if (col > COLUMN_MAX + 1)
    {
        board[row][col - 1] = tile;
    }
    else
    {
        board[row][col] = tile;
    }
}

Tile *Board::getTileAt(int row, int col)
{
    Tile *tile = nullptr;
    if (row >= ROW_MIN && col >= COLUMN_MIN && row <= ROW_MAX && col <= COLUMN_MAX)
    {
        tile = board[row][col];
    }
    return tile;
}

std::string Board::getState()
{
    std::string stateString = "";

    for (int i = 0; i < ROW_MAX + 1; i++)
    {
        for (int j = 0; j < COLUMN_MAX + 1; ++j)
        {
            if (!(board[i][j] == nullptr))
            {

                stateString = stateString + board[i][j]->toString() + "@" + init[i] + std::to_string(j) + ", ";
            }
        }
    }

    //get rid of last space and comma
    if (stateString.length() > STATE_TOKEN_LEN)
    {
        stateString.pop_back();
        stateString.pop_back();
    }

    return stateString;
}

bool Board::hasTileAt(int row, int col)
{
    bool hasTile = false;
    if (board[row][col] != nullptr)
    {
        hasTile = true;
    }

    return hasTile;
}
