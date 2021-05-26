#include "GameSaver.h"
#include "Player.h"
#include "Board.h"
#include "LinkedList.h"
#include <iostream>
using std::endl;

GameSaver::GameSaver(Player *player1, Player *player2, Board *board, LinkedList *bag, Player *currentPlayer, std::string outputFileName, int playerCount)
{
    outFile.open("Tests/" + outputFileName + ".txt");

    outFile << playerCount << endl;
    outputPlayer(player1);
    outputPlayer(player2);

    outFile << "26,26" << endl;

    outFile << board->getState() << endl;
    outFile << bag->toString() << endl;
    outFile << currentPlayer->getName();
}

GameSaver::GameSaver(Player *player1, Player *player2, Player *player3, Board *board, LinkedList *bag, Player *currentPlayer, std::string outputFileName, int playerCount)
{
    outFile.open("Tests/" + outputFileName + ".txt");

    outFile << playerCount << endl;
    outputPlayer(player1);
    outputPlayer(player2);
    outputPlayer(player3);

    outFile << "26,26" << endl;

    outFile << board->getState() << endl;
    outFile << bag->toString() << endl;
    outFile << currentPlayer->getName();
}
GameSaver::GameSaver(Player *player1, Player *player2, Player *player3, Player *player4, Board *board, LinkedList *bag, Player *currentPlayer, std::string outputFileName, int playerCount)
{
    outFile.open("Tests/" + outputFileName + ".txt");

    outFile << playerCount << endl;
    outputPlayer(player1);
    outputPlayer(player2);
    outputPlayer(player3);
    outputPlayer(player4);

    outFile << "26,26" << endl;

    outFile << board->getState() << endl;
    outFile << bag->toString() << endl;
    outFile << currentPlayer->getName();
}

void GameSaver::outputPlayer(Player *player)
{
    outFile << player->getName() << endl;
    outFile << player->getPoints() << endl;
    outFile << player->getHand()->toString() << endl;
}
