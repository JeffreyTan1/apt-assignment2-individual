#include "Player.h"
#include "LinkedList.h"
#include <algorithm>

Player::Player(std::string name, int points, LinkedList *hand)
{
    this->name = name;
    this->points = points;
    this->hand = hand;
}

Player::~Player()
{
    delete hand;
}

std::string Player::getName()
{
    return name;
}

int Player::getPoints()
{
    return points;
}

LinkedList *Player::getHand()
{
    return hand;
}

bool Player::equals(Player *player)
{
    bool retval = false;
    if (this == player)
    {
        retval = true;
    }
    return retval;
}

void Player::addPoints(int pointsToAdd)
{
    points = points + pointsToAdd;
}