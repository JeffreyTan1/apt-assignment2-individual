
#ifndef ASSIGN2_GAMEINIT_H
#define ASSIGN2_GAMEINIT_H
#include <fstream>
#include <string>
#define COLOUR_NUM 6
#define SHAPE_NUM 6
#define TILES_COPIES 2
#define SEED 11
#define INIT_HAND_SIZE 6
#define NEW_PLAYER_POINTS 0

class Node;
class Tile;
class Player;
class LinkedList;
class Board;

class GameInit
{
public:
   GameInit();
   GameInit(std::string filename);
   ~GameInit();

   Player *getPlayer1();
   Player *getPlayer2();
   Board *getBoard();
   LinkedList *getBag();
   int getBHeight();
   int getBWidth();
   Player *getCurrPlayer();
   bool getEofInput();

private:
   void
   newRandomBag();

   void newPlayer(int pNum);
   void loadPlayer(std::string line1, std::string line2, std::string line3, int pNum);
   void loadBoardSize(std::string line1);
   void loadBoardState(std::string line1);
   void loadBagState(std::string line1);
   void loadCurrPlayer(std::string line1);
   Player *player1;
   Player *player2;
   Player *currPlayer;

   Board *board;
   LinkedList *bag;
   int bHeight;
   int bWidth;

   bool eofInput = false;

   std::ifstream saveFile;
};

#endif // ASSIGN2_GAMEINIT_H
