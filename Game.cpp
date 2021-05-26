#include "Game.h"
#include "LinkedList.h"
#include "Player.h"
#include "Board.h"
#include "Tile.h"
#include "GameInit.h"
#include "GameSaver.h"
#include "HighScoreSaver.h"
#include "HighScoreLoader.h"

#include <map>
#include <algorithm>
#include <iostream>
#include <sstream>
#include <string>
#include <ios>
#include <limits>
#define ASCII_CONVERTER_DIGIT 48
#define ASCII_CONVERTER_LETTER 65
//Due to implementation of columns, we are operating with cols 1 to 26 for indexing
#define COLUMN_MAX 26
#define COLUMN_MIN 1
#define ROW_MAX 25
#define ROW_MIN 0

using std::cin;
using std::cout;
using std::endl;
using std::getline;
using std::string;

Game::Game(Player *player1, Player *player2, LinkedList *bag, Board *board, Player *currentPlayer, bool isEnhanced)
{
    this->player1 = player1;
    this->player2 = player2;
    this->player3 = nullptr;
    this->player4 = nullptr;
    this->bag = bag;
    this->board = board;
    this->currentPlayer = currentPlayer;
    this->terminateGame = false;
    this->gameOver = false;
    this->isEnhanced = isEnhanced;
    players.push_back(player1);
    players.push_back(player2);
    playerCount = 2;
}

Game::Game(Player *player1, Player *player2, Player *player3, LinkedList *bag, Board *board, Player *currentPlayer, bool isEnhanced)
{
    this->player1 = player1;
    this->player2 = player2;
    this->player3 = player3;
    this->player4 = nullptr;
    this->bag = bag;
    this->board = board;
    this->currentPlayer = currentPlayer;
    this->terminateGame = false;
    this->gameOver = false;
    this->isEnhanced = isEnhanced;
    players.push_back(player1);
    players.push_back(player2);
    players.push_back(player3);
    playerCount = 3;
}

Game::Game(Player *player1, Player *player2, Player *player3, Player *player4, LinkedList *bag, Board *board, Player *currentPlayer, bool isEnhanced)
{
    this->player1 = player1;
    this->player2 = player2;
    this->player3 = player3;
    this->player4 = player4;
    this->bag = bag;
    this->board = board;
    this->currentPlayer = currentPlayer;
    this->terminateGame = false;
    this->gameOver = false;
    this->isEnhanced = isEnhanced;
    players.push_back(player1);
    players.push_back(player2);
    players.push_back(player3);
    players.push_back(player4);
    playerCount = 4;
}

Game::~Game()
{
    delete player1;
    delete player2;

    if (player3 != nullptr)
    {
        delete player3;
    }
    if (player4 != nullptr)
    {
        delete player4;
    }

    delete bag;
    delete board;
}

void Game::executeGameplay()
{
    cout
        << "Let's Play!" << endl
        << endl;
    while (!terminateGame && !gameOver)
    {

        string command = "";
        bool correctCommand = false;
        printGameStatus();
        do
        {
            cout << "> ";
            if (!cin.eof())
            {
                getline(cin, command);
                std::vector<string> commandSplit = processCommand(command);
                correctCommand = playTurn(commandSplit);
            }
            //check for EOF character
            else
            {
                terminateGame = true;
            }

        } while (!correctCommand && !terminateGame);

        //only if EOF is not done
        if (!terminateGame)
        {
            switchPlayer();

            if (playerCount == 2)
            {

                if (bag->isEmpty() && (player1->getHand()->isEmpty() || player2->getHand()->isEmpty()))
                {
                    gameOver = true;
                }
            }

            if (playerCount == 3)
            {
                if (bag->isEmpty() && (player1->getHand()->isEmpty() || player2->getHand()->isEmpty() || player3->getHand()->isEmpty()))
                {
                    gameOver = true;
                }
            }

            if (playerCount == 4)
            {
                if (bag->isEmpty() && (player1->getHand()->isEmpty() || player2->getHand()->isEmpty() || player3->getHand()->isEmpty() || player4->getHand()->isEmpty()))
                {
                    gameOver = true;
                }
            }
        }
    }
    if (gameOver == true)
    {
        cin.ignore(std::numeric_limits<char>::max(), '\n');
        cout << endl
             << "Game over" << endl;
        cout << "Score for " << player1->getName() << ": " << player1->getPoints() << endl;
        cout << "Score for " << player2->getName() << ": " << player2->getPoints() << endl;
        if (player3 != nullptr)
        {
            cout << "Score for " << player3->getName() << ": " << player3->getPoints() << endl;
        }
        if (player4 != nullptr)
        {
            cout << "Score for " << player4->getName() << ": " << player4->getPoints() << endl;
        }

        int highestScore = 0;
        Player *winner = nullptr;
        for (int i = 0; i < playerCount; i++)
        {
            if (players[i]->getPoints() > highestScore)
            {
                highestScore = players[i]->getPoints();
                winner = players[i];
            }
        }

        cout << "Player " << winner->getName() << " won!" << endl;

        //highscore message at end of game
        if (isEnhanced)
        {
            cout << endl
                 << "All-time high scores:" << endl;

            std::map<int, std::string> currentGameScores;

            for (unsigned int i = 0; i < players.size(); i++)
            {
                currentGameScores.insert(std::pair<int, std::string>(players[i]->getPoints(), players[i]->getName()));
            }

            HighScoreSaver *highScoreSaver = new HighScoreSaver(currentGameScores);
            delete highScoreSaver;

            HighScoreLoader *highScoreLoader = new HighScoreLoader();
            std::map<int, std::string> highScores = highScoreLoader->getHighScores();

            int position = 0;

            for (auto i = highScores.begin();
                 i != highScores.end(); i++)
            {
                position++;
                std::cout << endl
                          << std::to_string(position) << ". "
                          << i->first
                          << " achieved a score of:       "
                          << i->second << endl
                          << endl;
            }
            delete highScoreLoader;
        }
    }
    cout << endl
         << "Goodbye" << endl;
}

bool Game::playTurn(vector<string> userInput)
{
    bool returnVal = false;

    if (userInput.size() > 0 && userInput.size() < INPUT_SIZE_MAX)
    {

        if (userInput[INPUT_POS_1] == "PLACE" && userInput[INPUT_POS_2] != "" && userInput[INPUT_POS_3] == "AT" && userInput[INPUT_POS_4] != "" && !(userInput[INPUT_POS_2].length() > 2))
        {

            int locationRow = (userInput[INPUT_POS_4].at(0)) - ASCII_CONVERTER_LETTER;
            std::string colVal = userInput[INPUT_POS_4];

            int tileIndex = currentPlayer->getHand()->existsAt(userInput[INPUT_POS_2].at(0), (userInput[INPUT_POS_2].at(1)) - ASCII_CONVERTER_DIGIT);

            //If the LinkedList returns a index for the found tile
            if (tileIndex > -1)
            {
                Tile *tile = currentPlayer->getHand()->get(tileIndex);
                if (colVal.length() >= 2)
                {
                    char temp[2] = {colVal[1], colVal[2]};
                    std::string tempStr = temp;

                    try
                    {
                        int value = std::stoi(tempStr);
                        int locationCol = value + 1;
                        try
                        {
                            if (tileNum == 0)
                            {

                                if (playTile(tile, locationRow, locationCol))
                                {
                                    tileNum++;
                                    tileLocations.push_back(std::pair<int, int>(locationRow, locationCol));
                                }

                                if (isEnhanced)
                                {
                                    printGameStatus();
                                }

                                //Non enhanced games don't have multi-tile functionality
                                if (!isEnhanced)
                                {
                                    if (invalidMoveBackCompat)
                                    {
                                        returnVal = false;
                                    }
                                    else
                                    {
                                        returnVal = true;
                                    }
                                    invalidMoveBackCompat = false;
                                    if (!bag->isEmpty())
                                    {
                                        drawCard();
                                    }
                                    tileNum = 0;
                                    turnNum++;
                                }
                            }
                            else if (tileNum == 1)
                            {
                                if (neighbourToFirst(locationRow, locationCol))
                                {

                                    if (playTile(tile, locationRow, locationCol))
                                    {
                                        tileNum++;
                                        tileLocations.push_back(std::pair<int, int>(locationRow, locationCol));
                                    }
                                    printGameStatus();
                                    setDirectionFromFirst(locationRow, locationCol);
                                }
                                else
                                {
                                    cout << "Second tile needs to be in the same line as your first." << endl
                                         << endl;
                                }
                            }
                            else
                            {
                                if (neighbourToFirst(locationRow, locationCol) && isInDirectionOfFirst(locationRow, locationCol))
                                {
                                    if (playTile(tile, locationRow, locationCol))
                                    {
                                        tileNum++;
                                        tileLocations.push_back(std::pair<int, int>(locationRow, locationCol));
                                    }
                                    printGameStatus();
                                }
                                else
                                {
                                    cout << "Tile needs to be in the same line direction as you first and second tiles." << endl
                                         << endl;
                                }
                            }
                        }
                        catch (std::invalid_argument &e)
                        {
                            cout << "Location code is invalid!" << endl;
                        }
                    }
                    catch (std::invalid_argument &e)
                    {
                        cout << "Location code is invalid!" << endl;
                    }
                }
                else
                {
                    cout << "Location code is invalid!" << endl;
                }
            }
            else
            {
                cout << "That tile is not in your hand. Try again: " << endl;
            }
        }
        else if (userInput[INPUT_POS_1] == "REPLACE" && userInput[INPUT_POS_2] != "" && userInput.size() == 2 && !(userInput[INPUT_POS_2].length() > 2))
        { //user is replacing tile
            if (!(tileNum > 0))
            {
                int tileIndex = currentPlayer->getHand()->existsAt(userInput[INPUT_POS_2].at(0), (userInput[INPUT_POS_2].at(1)) - ASCII_CONVERTER_DIGIT);
                //If the LinkedList returns a index for the found tile
                if (tileIndex > -1)
                {
                    Tile *tile = currentPlayer->getHand()->get(tileIndex);
                    replaceTile(tile);
                    returnVal = true;
                }
                else
                {
                    cout << "That tile is not in your hand. Try again: " << endl;
                }
                //the case where user does replace command at the start of the game, still allow placement of first tile
                if (turnNum == 1)
                {
                    turnNum--;
                }
            }
            else
            {
                cout << "You cannot replace a tile on a turn where you've placed a tile!" << endl
                     << endl;
            }
        }
        else if (userInput[INPUT_POS_1] == "SAVE" && userInput.size() > 1)
        { //user is saving game
            std::string outputFileName;

            outputFileName = userInput[INPUT_POS_2];

            if (playerCount == 2)
            {
                GameSaver *gs = new GameSaver(player1, player2, board, bag, currentPlayer, outputFileName, playerCount);
                delete gs;
            }
            else if (playerCount == 3)
            {
                GameSaver *gs = new GameSaver(player1, player2, player3, board, bag, currentPlayer, outputFileName, playerCount);
                delete gs;
            }
            else
            {
                GameSaver *gs = new GameSaver(player1, player2, player3, player4, board, bag, currentPlayer, outputFileName, playerCount);
                delete gs;
            }

            //Don't switch player turn when saving
            returnVal = false;
            cout << endl
                 << "Game successfully saved" << endl
                 << endl;
        }

        //END is part of the multitile enhanced functionality
        else if (userInput[INPUT_POS_1] == "END" && isEnhanced)
        {
            if (!bag->isEmpty())
            {
                drawCard();
            }

            if (tileNum > 0)
            {
                updatePoints(tileLocations[0].first, tileLocations[0].second);
                turnNum++;
            }

            // if more than one tile is placed
            if (tileNum > 1)
            {
                cout << "update using next" << endl;
                Orientation checkOrientation;
                if (orientation == vertical)
                {
                    checkOrientation = horizontal;
                }
                else
                {
                    checkOrientation = vertical;
                }

                //diregarding the first tile
                for (unsigned int i = 1; i < tileLocations.size(); i++)
                {
                    updatePointsNonFirst(tileLocations[i].first, tileLocations[i].second, checkOrientation);
                }
            }

            tileLocations.clear();
            tileNum = 0;
            orientation = undirected;
            returnVal = true;
        }
        else if (userInput[INPUT_POS_1] == "QUIT")
        { //user is quitting game
            terminateGame = true;
        }
        //Help command is enhanced feature
        else if (userInput[INPUT_POS_1] == "HELP" && isEnhanced)
        {
            cout << "Available commands: " << endl
                 << endl;
            cout << "PLACE (TILE) AT (LOCATION) - Places a tile in your hand on the board." << endl;
            cout << "e.g. PLACE B4 AT A9" << endl
                 << endl;
            cout << "PASS - Finishes your turn." << endl
                 << endl;
            cout << "REPLACE (TILE) - Replaces a tile in your hand with one from the bag." << endl;
            cout << "e.g. REPLACE B4" << endl
                 << endl;
            cout << "SAVE (FILENAME) - Saves the game to a file which can be loaded later." << endl
                 << endl;
            cout << "QUIT - Closes program" << endl
                 << endl;
        }
        else
        {
            cout << "Command not recognised. Please try again: " << endl
                 << endl;

            returnVal = false;
        }
    }
    else
    {

        cout << "Command not recognised. Please try again: " << endl
             << endl;
        returnVal = false;
    }
    return returnVal;
}

bool Game::isInLineOfFirst(int newRow, int newCol)
{
    bool inLine = false;
    if (newRow == tileLocations[0].first)
    {
        inLine = true;
    }
    if (newRow == tileLocations[0].second)
    {
        inLine = true;
    }
    return inLine;
}

void Game::setDirectionFromFirst(int newRow, int newCol)
{

    if (newCol > tileLocations[0].second || newCol < tileLocations[0].second)
    {
        orientation = horizontal;
    }

    if (newRow > tileLocations[0].first || newRow < tileLocations[0].first)
    {
        orientation = vertical;
    }
}

bool Game::isInDirectionOfFirst(int newRow, int newCol)
{

    bool isInDir = false;
    if (orientation == horizontal)
    {
        if (newRow == tileLocations[0].first)
        {
            isInDir = true;
        }
    }
    if (orientation == vertical)
    {
        if (newCol == tileLocations[0].second)
        {
            isInDir = true;
        }
    }

    return isInDir;
}

bool Game::neighbourToFirst(int row, int col)
{
    Direction d;
    bool tileFound = false;
    if (row < ROW_MAX)
    {
        if (board->hasTileAt(row + 1, col))
        {
            d = Down;
            tileFound = checkLineForFirst(row + 1, col, d);
        }
    }
    if (row > ROW_MIN)
    {
        if (board->hasTileAt(row - 1, col) && !tileFound)
        {
            d = Up;
            tileFound = checkLineForFirst(row - 1, col, d);
        }
    }
    if (col < COLUMN_MAX)
    {
        if (board->hasTileAt(row, col + 1) && !tileFound)
        {
            d = Right;
            tileFound = checkLineForFirst(row, col + 1, d);
        }
    }
    if (col > COLUMN_MIN)
    {
        if (board->hasTileAt(row, col - 1) && !tileFound)
        {
            d = Left;
            tileFound = checkLineForFirst(row, col - 1, d);
        }
    }

    return tileFound;
}

bool Game::checkLineForFirst(int row, int col, Game::Direction direction)
{
    bool retVal = false;

    int y = 0;
    int x = 0;

    if (direction == Up)
    {
        y = -1;
    }
    else if (direction == Down)
    {
        y = 1;
    }
    else if (direction == Left)
    {
        x = -1;
    }
    else if (direction == Right)
    {
        x = 1;
    }

    if (row == tileLocations[0].first && col == tileLocations[0].second)
    {
        retVal = true;
    }
    else if (row + y >= ROW_MIN && row + y <= ROW_MAX && col + x >= COLUMN_MIN && col + x <= COLUMN_MAX)
    {
        if (!board->hasTileAt(row + y, col + x))
        {
            retVal = false;
        }
        else
        {
            retVal = checkLineForFirst(row + y, col + x, direction);
        }
    }
    return retVal;
}

bool Game::playTile(Tile *tile, int row, int col)
{
    bool returnVal = true;

    if (isValidMove(tile, row, col) && (hasAdjoiningTile(row, col) || turnNum == 1))
    { //and move is legal

        board->placeTile(tile, row, col);
        if (!isEnhanced)
        {
            updatePoints(row, col);
        }
        //update the score

        currentPlayer->getHand()->removeElement(tile);
    }
    else
    {
        cout << "Invalid move. Try again: " << endl;

        if (!isEnhanced)
        {
            invalidMoveBackCompat = true;
        }
        returnVal = false;
    }

    return returnVal;
}

bool Game::isValidMove(Tile *userTile, int row, int col)
{
    bool returnVal = true;
    bool diffShape = false;
    bool neighbour1check = true;
    bool neighbour2check = true;
    bool neighbour3check = true;
    bool neighbour4check = true;
    bool isRow = true;
    int newRow = 0;
    int newCol = 0;
    //First check if the row and col are within the board
    if (!(row >= ROW_MIN && col >= COLUMN_MIN && row <= ROW_MAX && col <= COLUMN_MAX))
    {
        returnVal = false;
    }
    else if (board->getTileAt(row, col) != nullptr)
    {
        returnVal = false;
    }
    else if (neighboursContains(userTile, row, col))
    {
        returnVal = false;
    }
    else
    {
        for (int j = 0; j < 2; j++)
        {
            for (int i = -1; i < 2; i++)
            {
                if (j == 0)
                { //first check column
                    newRow = row + i;
                    newCol = col;
                    isRow = false;
                }
                else
                { //then check row
                    newRow = row;
                    newCol = col + i;
                    isRow = true;
                }
                Tile *currentTile = board->getTileAt(newRow, newCol);
                if (currentTile != nullptr)
                {
                    diffShape = false;
                    //if neither colour nor shape are the same, move is not valid
                    if (currentTile->shape != userTile->shape && currentTile->colour != userTile->colour)
                    {
                        returnVal = false;
                    }
                    else if (currentTile->colour == userTile->colour)
                    {
                        //if the colour is the same, all shapes in this line should be different
                        diffShape = true;
                        returnVal = checkNeighbours(newRow, newCol, diffShape, currentTile, isRow);
                    }
                    else
                    {
                        //otherwise, the colour should be different ie. diffShape=false as it was initialised
                        returnVal = checkNeighbours(newRow, newCol, diffShape, currentTile, isRow);
                    }
                    if (j == 0 && i == -1)
                    {
                        neighbour1check = returnVal;
                    }
                    else if (j == 0 && i == 1)
                    {
                        neighbour2check = returnVal;
                    }
                    else if (j == 1 && i == -1)
                    {
                        neighbour3check = returnVal;
                    }
                    else if (j == 1 && i == 1)
                    {
                        neighbour4check = returnVal;
                    }
                }
            }
        }
        returnVal = neighbour1check && neighbour2check && neighbour3check && neighbour4check;
    }
    return returnVal;
}

bool Game::hasAdjoiningTile(int row, int col)
{
    bool hasAdjoining = false;

    if (row < ROW_MAX)
    {
        if (board->hasTileAt(row + 1, col))
        {
            hasAdjoining = true;
        }
    }
    if (row > ROW_MIN)
    {
        if (board->hasTileAt(row - 1, col))
        {
            hasAdjoining = true;
        }
    }

    if (col < COLUMN_MAX)
    {
        if (board->hasTileAt(row, col + 1))
        {
            hasAdjoining = true;
        }
    }
    if (col > COLUMN_MIN)
    {
        if (board->hasTileAt(row, col - 1))
        {
            hasAdjoining = true;
        }
    }

    return hasAdjoining;
}

void Game::replaceTile(Tile *tile)
{
    currentPlayer->getHand()->removeElement(tile);
    bag->addBack(tile);
    Tile *newTile = bag->get(0);
    bag->removeFront();
    currentPlayer->getHand()->addBack(newTile);
}

void Game::drawCard()
{
    for (int i = 0; i < tileNum; i++)
    {
        Tile *newTile = bag->get(0);
        bag->removeFront();
        currentPlayer->getHand()->addBack(newTile);
    }
}

void Game::switchPlayer()
{
    if (playerCount == 2)
    {
        if (currentPlayer->equals(player1))
        {
            currentPlayer = player2;
        }
        else
        {
            currentPlayer = player1;
        }
    }

    if (playerCount == 3)
    {
        if (currentPlayer->equals(player1))
        {
            currentPlayer = player2;
        }
        else if (currentPlayer->equals(player2))
        {
            currentPlayer = player3;
        }
        else
        {
            currentPlayer = player1;
        }
    }

    if (playerCount == 4)
    {
        if (currentPlayer->equals(player1))
        {
            currentPlayer = player2;
        }
        else if (currentPlayer->equals(player2))
        {
            currentPlayer = player3;
        }
        else if (currentPlayer->equals(player3))
        {
            currentPlayer = player4;
        }
        else
        {
            currentPlayer = player1;
        }
    }
}

bool Game::checkNeighbours(int row, int col, bool diffShape, Tile *originalTile, bool isRow)
{
    bool returnVal = true;
    Tile *neighbours[2] = {};
    if (isRow)
    {
        neighbours[0] = board->getTileAt(row, col + 1);
        neighbours[1] = board->getTileAt(row, col - 1);
    }
    else
    {
        neighbours[0] = board->getTileAt(row + 1, col);
        neighbours[1] = board->getTileAt(row - 1, col);
    }
    for (Tile *neighbour : neighbours)
    {
        if (neighbour != nullptr)
        {

            //cout << "neighbour found" << endl;
            if (neighbour->equals(originalTile->colour, originalTile->shape))
            {
                returnVal = true;
            }

            //if shape is meant to be different, check it is different
            if (diffShape && (neighbour->shape == originalTile->shape))
            {
                returnVal = false;
            }
            //if colour is meant to be different, check it is different
            else if (!diffShape && (neighbour->colour == originalTile->colour))
            {
                returnVal = false;
            }
        }
    }
    return returnVal;
}

void Game::updatePointsNonFirst(int row, int col, Game::Orientation checkOrientation)
{
    int pointsToAdd = 0;
    if (checkOrientation == vertical)
    {
        pointsToAdd = pointsToAdd + countLine(row, col, Up) - 1;
        pointsToAdd = pointsToAdd + countLine(row, col, Down) - 1;
    }
    else
    {
        pointsToAdd = pointsToAdd + countLine(row, col, Left) - 1;
        pointsToAdd = pointsToAdd + countLine(row, col, Right) - 1;
    }
    currentPlayer->addPoints(pointsToAdd);
}

void Game::updatePoints(int row, int col)
{
    int pointsToAdd = countNeighbours(row, col);
    currentPlayer->addPoints(pointsToAdd);
}

int Game::countNeighbours(int row, int col)
{
    bool upEmpty = true;
    bool downEmpty = true;
    bool leftEmpty = true;
    bool rightEmpty = true;
    int downVal = 0;
    int upVal = 0;
    int rightVal = 0;
    int leftVal = 0;

    Direction d;
    int count = 0;

    if (row < ROW_MAX)
    {
        if (board->hasTileAt(row + 1, col))
        {
            d = Down;
            downVal = countLine(row + 1, col, d) + 1;
            downEmpty = false;
        }
    }
    if (row > ROW_MIN)
    {
        if (board->hasTileAt(row - 1, col))
        {
            d = Up;
            upVal = countLine(row - 1, col, d) + 1;
            upEmpty = false;
        }
    }

    if (col < COLUMN_MAX)
    {
        if (board->hasTileAt(row, col + 1))
        {
            d = Right;
            rightVal = countLine(row, col + 1, d) + 1;
            rightEmpty = false;
        }
    }
    if (col > COLUMN_MIN)
    {
        if (board->hasTileAt(row, col - 1))
        {
            d = Left;
            leftVal = countLine(row, col - 1, d) + 1;
            leftEmpty = false;
        }
    }

    count = downVal + upVal + rightVal + leftVal;

    if (upEmpty && downEmpty && leftEmpty && rightEmpty)
    {
        count = 1;
    }

    // Check for any qwirkles created by adding a tile to the end of the line of tiles
    if (downVal == 6 || upVal == 6 || rightVal == 6 || leftVal == 6)
    {
        cout << endl
             << "QWIRKLE!!!" << endl
             << endl;
    }

    //eliminate the double count of the placed tile if the tile creates a line which extends both ways
    if (!upEmpty && !downEmpty)
    {
        count = count - 1;

        //checks for qwirkles when tile is placed between two lines connecting them vertically
        if (downVal + upVal - 1 == 6)
        {
            cout << "QWIRKLE!!!" << endl;
        }
    }

    if (!leftEmpty && !rightEmpty)
    {
        //checks for qwirkles when tile is placed between two lines connecting them horizontally
        if (leftVal + rightVal - 1 == 6)
        {
            cout << "QWIRKLE!!!" << endl;
        }
        count = count - 1;
    }

    return count;
}

int Game::countLine(int row, int col, Game::Direction direction)
{
    int retVal = 0;

    int y = 0;
    int x = 0;

    if (direction == Up)
    {
        y = -1;
    }
    else if (direction == Down)
    {
        y = 1;
    }
    else if (direction == Left)
    {
        x = -1;
    }
    else if (direction == Right)
    {
        x = 1;
    }

    if (row + y >= ROW_MIN && row + y <= ROW_MAX && col + x >= COLUMN_MIN && col + x <= COLUMN_MAX)
    {
        if (!board->hasTileAt(row + y, col + x))
        {
            retVal = 1;
        }
        else
        {
            retVal = countLine(row + y, col + x, direction) + 1;
        }
    }
    else
    {
        retVal = 1;
    }

    return retVal;
}

bool Game::neighboursContains(Tile *tile, int row, int col)
{
    Direction d;
    bool tileFound = false;
    if (row < ROW_MAX)
    {
        if (board->hasTileAt(row + 1, col))
        {
            d = Down;
            tileFound = checkLine(row + 1, col, d, tile);
        }
    }
    if (row > ROW_MIN)
    {
        if (board->hasTileAt(row - 1, col) && !tileFound)
        {
            d = Up;
            tileFound = checkLine(row - 1, col, d, tile);
        }
    }
    if (col < COLUMN_MAX)
    {
        if (board->hasTileAt(row, col + 1) && !tileFound)
        {
            d = Right;
            tileFound = checkLine(row, col + 1, d, tile);
        }
    }
    if (col > COLUMN_MIN)
    {
        if (board->hasTileAt(row, col - 1) && !tileFound)
        {
            d = Left;
            tileFound = checkLine(row, col - 1, d, tile);
        }
    }

    return tileFound;
}

bool Game::checkLine(int row, int col, Game::Direction direction, Tile *searchTile)
{
    bool retVal = false;

    int y = 0;
    int x = 0;

    if (direction == Up)
    {
        y = -1;
    }
    else if (direction == Down)
    {
        y = 1;
    }
    else if (direction == Left)
    {
        x = -1;
    }
    else if (direction == Right)
    {
        x = 1;
    }

    if (board->getTileAt(row, col)->equals(searchTile->colour, searchTile->shape))
    {
        retVal = true;
    }
    else if (row + y >= ROW_MIN && row + y <= ROW_MAX && col + x >= COLUMN_MIN && col + x <= COLUMN_MAX)
    {
        if (!board->hasTileAt(row + y, col + x))
        {
            retVal = false;
        }
        else
        {
            retVal = checkLine(row + y, col + x, direction, searchTile);
        }
    }
    return retVal;
}

void Game::printGameStatus()
{
    cout << endl
         << currentPlayer->getName() << ", it's your turn" << endl;
    cout << "Score for " << player1->getName() << ": " << player1->getPoints() << endl;
    cout << "Score for " << player2->getName() << ": " << player2->getPoints() << endl;
    if (player3 != nullptr)
    {
        cout << "Score for " << player3->getName() << ": " << player3->getPoints() << endl;
    }
    if (player4 != nullptr)
    {
        cout << "Score for " << player4->getName() << ": " << player4->getPoints() << endl;
    }
    if (isEnhanced)
    {
        board->printPrettyBoard();
        cout << "Your hand is" << endl;
        cout << currentPlayer->getHand()->toPrettyString() << endl
             << endl;
    }
    else
    {
        board->printBoard();
        cout << "Your hand is" << endl;
        cout << currentPlayer->getHand()->toString() << endl
             << endl;
    }
}

std::vector<std::string> Game::processCommand(std::string inputString)
{
    //Make string uppercase to reduce invalid inputs
    std::transform(inputString.begin(), inputString.end(), inputString.begin(), ::toupper);
    std::vector<string> commandSplit;
    std::istringstream iss(inputString);
    for (string inputString; iss >> inputString;)
    {
        commandSplit.push_back(inputString);
    }
    return commandSplit;
}
