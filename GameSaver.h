#ifndef ASSIGN2_GAME_SAVER_H
#define ASSIGN2_GAME_SAVER_H
#include <fstream>

class Player;
class Board;
class LinkedList;

class GameSaver
{
public:
    GameSaver(Player *player1, Player *player2, Board *board, LinkedList *bag, Player *currentPlayer, std::string outputFileName);

private:
    void outputPlayer(Player *player);
    void outputBoard(Board *board);

    std::ofstream outFile;
};

#endif // ASSIGN2_GAME_SAVER_H
