#ifndef ASSIGN2_GAME_H
#define ASSIGN2_GAME_H

#include <string>
#include <vector>

#define INPUT_SIZE_MAX 5
#define ASCII_CONVERTER_DIGIT 48
#define ASCII_CONVERTER_LETTER 65
#define INPUT_POS_1 0
#define INPUT_POS_2 1
#define INPUT_POS_3 2
#define INPUT_POS_4 3

class LinkedList;
class Tile;
class Board;
class Player;

class Game
{
public:
    Game(Player *player1, Player *player2, LinkedList *bag, Board *board, Player *currentPlayer, bool isEnhanced);
    Game(Player *player1, Player *player2, Player *player3, LinkedList *bag, Board *board, Player *currentPlayer, bool isEnhanced);
    Game(Player *player1, Player *player2, Player *player3, Player *player4, LinkedList *bag, Board *board, Player *currentPlayer, bool isEnhanced);

    ~Game();
    void executeGameplay();
    enum Direction
    {
        Up,
        Down,
        Left,
        Right
    };

    enum Orientation
    {
        horizontal,
        vertical,
        undirected
    };

private:
    bool playTurn(std::vector<std::string> userInput);
    void switchPlayer();
    bool playTile(Tile *tile, int row, int col);
    void replaceTile(Tile *tile);
    void drawCard();
    bool isValidMove(Tile *userTile, int row, int col);
    bool hasAdjoiningTile(int row, int col);
    bool checkNeighbours(int row, int col, bool diffShape, Tile *originalTile, bool isRow);
    void updatePoints(int row, int col);
    void updatePointsNonFirst(int row, int col, Game::Orientation orientation);
    int countNeighbours(int row, int col);
    int countLine(int row, int col, Game::Direction direction);

    bool neighboursContains(Tile *tile, int row, int col);
    bool checkLine(int row, int col, Game::Direction direction, Tile *searchTile);

    bool playRound();
    void printGameStatus();

    bool neighbourToFirst(int row, int col);
    bool checkLineForFirst(int row, int col, Game::Direction direction);
    bool isInLineOfFirst(int newRow, int newCol);
    void setDirectionFromFirst(int newRow, int newCol);
    bool isInDirectionOfFirst(int newRow, int newCol);

    std::vector<std::string> processCommand(std::string inputString);

    std::vector<Player *> players;

    std::vector<std::pair<int, int>> tileLocations;

    Player *player1;
    Player *player2;
    Player *player3;
    Player *player4;
    int playerCount;
    LinkedList *bag;
    Board *board;
    Player *currentPlayer;
    bool terminateGame;
    bool gameOver;
    int turnNum = 1;
    int tileNum = 0;
    bool invalidMoveBackCompat = false;

    bool isEnhanced = false;

    Game::Orientation orientation = undirected;
};

#endif // ASSIGN2_GAME_H