#include "GameInit.h"
#include "Tile.h"
#include "LinkedList.h"
#include "Board.h"
#include "Player.h"
#include <iostream>
#include <sstream>
#include <cstring>
#include <algorithm>
#include <random>

#define ASCII_CONVERTER_DIGIT 48
#define ASCII_CONVERTER_LETTER 65
using std::atoi;
using std::cin;
using std::cout;
using std::endl;
using std::getline;
using std::ifstream;
using std::stoi;

GameInit::~GameInit()
{
}

GameInit::GameInit(int numPlayers)
{
    board = new Board();
    bag = new LinkedList();
    newRandomBag();

    for (int i = 1; i <= numPlayers; i++)
    {
        if (!eofInput)
        {
            newPlayer(i);
            cout << endl;
        }
    }
    currPlayer = player1;
    //End of initialiser
}

void GameInit::newRandomBag()
{
    //create a vector containing all tiles
    std::vector<Tile *> allTiles;

    char colours[COLOUR_NUM] = {'R', 'O', 'Y', 'G', 'B', 'P'};

    int shapes[SHAPE_NUM] = {1, 2, 3, 4, 5, 6};

    for (int i = 0; i < TILES_COPIES; i++)
    {
        for (int j = 0; j < COLOUR_NUM; j++)
        {
            for (int k = 0; k < SHAPE_NUM; k++)
            {
                Tile *newTile = new Tile(colours[j], shapes[k]);
                allTiles.push_back(newTile);
            }
        }
    }

    //shuffle the vector
    std::default_random_engine engine(SEED);
    std::shuffle(allTiles.begin(), allTiles.end(), engine);
    //add tiles to bag
    for (int i = 0; i < COLOUR_NUM * SHAPE_NUM * TILES_COPIES; i++)
    {
        bag->addBack(allTiles.at(i));
    }
}

void GameInit::newPlayer(int pNum)
{
    bool cont = true;
    std::string name;
    while (cont)
    {
        cout << "Enter a name for player " << pNum << " (uppercase characters only)" << endl;
        cout << "> ";
        cin >> name;
        cont = false;
        int nameLen = name.length();
        for (int i = 0; i < nameLen; i++)
        {
            if (!isupper(name[i]))
            {
                cont = true;
            }
        }
        if (cont)
        {
            cout << "Please use uppercase characters only" << endl;
        }
        if (cin.eof())
        {
            eofInput = true;
            cont = false;
        }
    }

    if (cin.eof())
    {
        eofInput = true;
    }

    std::transform(name.begin(), name.end(), name.begin(), ::toupper);

    LinkedList *hand = new LinkedList();
    for (int i = 0; i < INIT_HAND_SIZE; i++)
    {
        hand->addBack(bag->get(0));

        bag->removeFront();
    }

    if (pNum == 1)
    {
        player1 = new Player(name, NEW_PLAYER_POINTS, hand);
    }
    else if (pNum == 2)
    {
        player2 = new Player(name, NEW_PLAYER_POINTS, hand);
    }
    else if (pNum == 3)
    {
        player3 = new Player(name, NEW_PLAYER_POINTS, hand);
    }
    else if (pNum == 4)
    {
        player4 = new Player(name, NEW_PLAYER_POINTS, hand);
    }
}

GameInit::GameInit(std::string filename, bool isEnhanced)
{
    board = new Board();
    bag = new LinkedList();

    ifstream saveFile(filename + ".txt");

    if (isEnhanced)
    {
        std::string input;
        std::getline(saveFile, input);
        playerCount = stoi(input);
    }
    else
    {
        //In the case that the game is not enhanced, the playercoutn will always be 2
        playerCount = 2;
    }

    std::string line1;
    std::string line2;
    std::string line3;

    for (int i = 0; i < playerCount; i++)
    {
        std::getline(saveFile, line1);
        std::getline(saveFile, line2);
        std::getline(saveFile, line3);
        loadPlayer(line1, line2, line3, i + 1);
    }

    std::string line4;
    std::getline(saveFile, line4);
    loadBoardSize(line4);

    std::string line5;
    std::getline(saveFile, line5);
    loadBoardState(line5);

    std::string line6;
    std::getline(saveFile, line6);
    loadBagState(line6);

    std::string line7;
    std::getline(saveFile, line7);
    loadCurrPlayer(line7);

    saveFile.close();
    //End of initialiser
}

void GameInit::loadPlayer(std::string line1, std::string line2, std::string line3, int pNum)
{
    int points = stoi(line2);
    std::stringstream ss(line3);

    LinkedList *hand = new LinkedList();

    while (ss.good())
    {
        std::string substr;
        std::getline(ss, substr, ',');
        char colour = substr.at(0);
        int shape = substr.at(1) - ASCII_CONVERTER_DIGIT;
        Tile *newTile = new Tile(colour, shape);
        hand->addBack(newTile);
    }

    if (pNum == 1)
    {
        player1 = new Player(line1, points, hand);
    }
    else if (pNum == 2)
    {
        player2 = new Player(line1, points, hand);
    }
    else if (pNum == 3)
    {
        player3 = new Player(line1, points, hand);
    }
    else
    {
        player4 = new Player(line1, points, hand);
    }
}

void GameInit::loadBoardSize(std::string line4)
{
    std::stringstream ss(line4);

    for (int i = 0; i < 2; i++)
    {
        std::string substr;
        std::getline(ss, substr, ',');
        if (i == 0)
        {
            bHeight = stoi(substr);
        }
        else
        {
            bWidth = stoi(substr);
        }
    }
}

void GameInit::loadBoardState(std::string line5)
{
    if (line5 != "")
    {
        std::stringstream ss(line5);
        int iter = 0;
        while (ss.good())
        {
            char tileChar;
            int tileShape;
            int boardRow;
            int boardCol;

            std::string substr;
            std::getline(ss, substr, ',');

            if (iter == 0)
            {
                tileChar = substr.at(0);
                tileShape = (int)substr.at(1) - ASCII_CONVERTER_DIGIT;
                boardRow = (int)substr.at(3) - ASCII_CONVERTER_LETTER;
                if (substr.length() > 4)
                {

                    boardCol = stoi((substr.substr(4, 5)));
                }
                else
                {
                    boardCol = (int)substr.at(4) - ASCII_CONVERTER_DIGIT;
                }
            }
            else
            {
                tileChar = substr.at(1);
                tileShape = (int)substr.at(2) - ASCII_CONVERTER_DIGIT;
                boardRow = (int)substr.at(4) - ASCII_CONVERTER_LETTER;
                if (substr.length() > 5)
                {

                    boardCol = stoi((substr.substr(5, 6)));
                }
                else
                {
                    boardCol = (int)substr.at(5) - ASCII_CONVERTER_DIGIT;
                }
            }

            Tile *newTile = new Tile(tileChar, tileShape);

            board->placeTile(newTile, boardRow, boardCol);

            iter++;
        }
    }
}

void GameInit::loadBagState(std::string line6)
{
    std::stringstream ss(line6);

    while (ss.good())
    {
        std::string substr;
        std::getline(ss, substr, ',');
        char colour = substr.at(0);
        int shape = substr.at(1) - ASCII_CONVERTER_DIGIT;

        Tile *newTile = new Tile(colour, shape);
        bag->addBack(newTile);
    }
}

void GameInit::loadCurrPlayer(std::string line7)
{
    if (player1->getName() == line7)
    {
        currPlayer = player1;
    }
    else if (player2->getName() == line7)
    {
        currPlayer = player2;
    }
}

Player *GameInit::getPlayer1()
{
    return player1;
}

Player *GameInit::getPlayer2()
{
    return player2;
}

Player *GameInit::getPlayer3()
{
    return player3;
}

Player *GameInit::getPlayer4()
{
    return player4;
}

Board *GameInit::getBoard()
{
    return board;
}

LinkedList *GameInit::getBag()
{
    return bag;
}

int GameInit::getBHeight()
{
    return bHeight;
}

int GameInit::getBWidth()
{
    return bWidth;
}

int GameInit::getPlayerCount()
{
    return playerCount;
}

Player *GameInit::getCurrPlayer()
{
    return currPlayer;
}

bool GameInit::getEofInput()
{
    return eofInput;
}