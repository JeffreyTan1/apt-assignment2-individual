#ifndef ASSIGN2_PLAYER_H
#define ASSIGN2_PLAYER_H

#include <string>

class LinkedList;
class Tile;

class Player
{
public:
    Player(std::string name, int points, LinkedList *hand);

    ~Player();

    std::string getName();

    int getPoints();

    LinkedList *getHand();

    bool equals(Player *player);

    void addPoints(int pointsToAdd);

private:
    std::string name;
    int points;
    LinkedList *hand;
};

#endif // ASSIGN2_NODE_H