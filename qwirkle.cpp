
#include "LinkedList.h"
#include "GameInit.h"
#include "Game.h"
#include "Player.h"

#include <map>
#include <iostream>
#include <exception>
#include <limits>
#include "Board.h"
#include "GameInit.h"
#include "Game.h"
#include "HighScoreLoader.h"
#include "HighScoreSaver.h"

#define EXIT_SUCCESS 0
#define CHOICE_1 1
#define CHOICE_2 2
#define CHOICE_3 3
#define CHOICE_4 4
#define CHOICE_5 5

using std::cin;
using std::cout;
using std::endl;

bool isEnhanced = false;

void runMenu(int userChoice, bool *stop);
void closeProgMsg();

int main(int argc, char **argv)
{

   if (argc > 1)
   {
      std::string strArgv(argv[1]);
      if (strArgv == "-e")
      {
         isEnhanced = true;
      }
   }

   cout << "Welcome to Qwirkle!" << endl;
   cout << "-------------------" << endl;

   bool stop = false;
   bool *stopPtr = &stop;
   int userChoice;

   while (!stop)
   {
      cout << "Menu" << endl;
      cout << "---" << endl;
      cout << "1. New Game" << endl;
      cout << "2. Load game" << endl;
      cout << "3. Credits (Show student information)" << endl;
      cout << "4. Quit" << endl;
      //isolate enhanced behaviour
      if (isEnhanced)
      {
         cout << "5. High Scores" << endl;
      }
      cout << "> ";
      cin >> userChoice;

      //isolate enhanced behaviour
      bool whileCondition = isEnhanced ? (cin.fail() || userChoice < CHOICE_1 || userChoice > CHOICE_5) && !stop : (cin.fail() || userChoice < CHOICE_1 || userChoice > CHOICE_4) && !stop;
      while (whileCondition)
      {
         if (cin.eof())
         {
            closeProgMsg();
            stop = true;
         }
         else
         {
            cout << "Invalid input, please try again \n> ";
            cin.clear();
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            cin >> userChoice;
         }
      }

      if (!stop)
      {
         runMenu(userChoice, stopPtr);
      }
   }
   return EXIT_SUCCESS;
}

void runMenu(int userChoice, bool *stop)
{
   if (userChoice == CHOICE_1)
   {
      int numPlayers = 0;
      cout << endl
           << "Starting a New Game" << endl
           << endl;

      bool eofInput = false;
      if (isEnhanced)
      {

         while (!(numPlayers <= 4 && numPlayers >= 2) && !eofInput)
         {

            cout << endl
                 << "How many players? (2-4 Players)"
                 << endl;

            cin >> numPlayers;
            if (cin.eof())
            {
               eofInput = true;
            }
            else
            {
               cin.clear();
               cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            }
         }
      }
      else
      {
         numPlayers = 2;
      }

      if (!eofInput)
      {
         GameInit *gameInit = new GameInit(numPlayers);

         Game *game;

         if (numPlayers == 2)
         {
            game = new Game(gameInit->getPlayer1(), gameInit->getPlayer2(), gameInit->getBag(), gameInit->getBoard(), gameInit->getCurrPlayer(), isEnhanced);
         }
         else if (numPlayers == 3)
         {
            game = new Game(gameInit->getPlayer1(), gameInit->getPlayer2(), gameInit->getPlayer3(), gameInit->getBag(), gameInit->getBoard(), gameInit->getCurrPlayer(), isEnhanced);
         }
         else
         {
            game = new Game(gameInit->getPlayer1(), gameInit->getPlayer2(), gameInit->getPlayer3(), gameInit->getPlayer4(), gameInit->getBag(), gameInit->getBoard(), gameInit->getCurrPlayer(), isEnhanced);
         }

         if (!gameInit->getEofInput())
         {
            game->executeGameplay();
         }

         else
         {
            closeProgMsg();
         }

         delete game;

         *stop = true;
      }
      else
      {
         cout << endl
              << "Goodbye" << endl;
         *stop = true;
      }
   }
   else if (userChoice == CHOICE_2)
   {
      //Load game
      std::string fileName;
      cout << endl
           << "Enter the filename from which to load a game" << endl;
      cin >> fileName;
      try
      {

         //TODO: I HAVE NO IDEA IF LOADING WITH IS ENHANCED WORKS OR WHATEVER IM SCARED
         GameInit *gameInit = new GameInit(fileName);

         cout << "Qwirkle game successfully loaded" << endl;
         Game *game;
         if (gameInit->getPlayerCount() == 2)
         {
            game = new Game(gameInit->getPlayer1(), gameInit->getPlayer2(), gameInit->getBag(), gameInit->getBoard(), gameInit->getCurrPlayer(), isEnhanced);
         }
         else if (gameInit->getPlayerCount() == 3)
         {
            game = new Game(gameInit->getPlayer1(), gameInit->getPlayer2(), gameInit->getPlayer3(), gameInit->getBag(), gameInit->getBoard(), gameInit->getCurrPlayer(), isEnhanced);
         }
         else
         {
            game = new Game(gameInit->getPlayer1(), gameInit->getPlayer2(), gameInit->getPlayer3(), gameInit->getPlayer4(), gameInit->getBag(), gameInit->getBoard(), gameInit->getCurrPlayer(), isEnhanced);
         }

         delete gameInit;
         //cin.ignore();
         game->executeGameplay();
         delete game;
         *stop = true;
      }
      catch (const std::invalid_argument &e)
      {
         cout << "File not found!" << endl;
      }
   }
   else if (userChoice == CHOICE_3)
   {
      //Credits
      std::string names[4] = {"Jeffrey Tan", "Mohammad Mahir Haque", "Sharshwot Karki", "Sidhra Fernando-Plant"};
      std::string studentIds[4] = {"S3851781",
                                   "S3815004",
                                   "S3841123",
                                   "S3873756"};
      std::string emailExt = "@student.rmit.edu.au";
      std::string emails[4] = {studentIds[0] + emailExt,
                               studentIds[1] + emailExt,
                               studentIds[2] + emailExt,
                               studentIds[3] + emailExt};

      cout << endl
           << "---------------------------------------" << endl;
      for (int i = 0; i < 4; i++)
      {
         cout << "Name: " << names[i] << endl;
         cout << "Student ID: " << studentIds[i] << endl;
         cout << "Email: " << emails[i] << endl
              << endl;
      }
      cout << "---------------------------------------" << endl;
   }
   else if (userChoice == CHOICE_4)
   {
      //Quit
      closeProgMsg();
      *stop = true;
   }
   else if (userChoice == CHOICE_5)
   {
      HighScoreLoader *highScoreLoader = new HighScoreLoader();
      std::map<int, std::string> highScores = highScoreLoader->getHighScores();

      for (auto i = highScores.begin();
           i != highScores.end(); i++)
      {
         std::cout << endl
                   << i->first
                   << "    BY    "
                   << i->second << endl
                   << endl;
      }

      delete highScoreLoader;
   }
}

void closeProgMsg()
{
   cout << "Goodbye" << endl;
}