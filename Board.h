#ifndef ASSIGN2_BOARD_H
#define ASSIGN2_BOARD_H
#include <vector>
#include <string>

#define ROWS 26
#define COLS 27
#define STATE_TOKEN_LEN 5

using std::vector;

class Tile;

class Board
{
public:
    Board();
    vector<vector<Tile *>> getBoard();
    ~Board();
    void printBoard();

    void placeTile(Tile *tile, int row, int col);
    Tile *getTileAt(int row, int col);
    std::string getState();
    bool hasTileAt(int row, int col);
    void printPrettyBoard();

private:
    vector<vector<Tile *>>
        board;
};

#endif // ASSIGN2_BOARD_H
