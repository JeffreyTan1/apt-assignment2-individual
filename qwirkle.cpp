
#include "LinkedList.h"
#include "GameInit.h"
#include "Game.h"
#include "Player.h"

#include <iostream>
#include <exception>
#include <limits>
#include "Board.h"
#include "GameInit.h"
#include "Game.h"

#define EXIT_SUCCESS 0
#define CHOICE_1 1
#define CHOICE_2 2
#define CHOICE_3 3
#define CHOICE_4 4

using std::cin;
using std::cout;
using std::endl;

void runMenu(int userChoice, bool *stop);
void closeProgMsg();

int main(void)
{
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
      cout << "> ";
      cin >> userChoice;
      while ((cin.fail() || userChoice < CHOICE_1 || userChoice > CHOICE_4) && !stop)
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
      cout << endl
           << "Starting a New Game" << endl
           << endl;
      GameInit *gameInit = new GameInit();
      Game *game = new Game(gameInit->getPlayer1(), gameInit->getPlayer2(), gameInit->getBag(), gameInit->getBoard(), gameInit->getCurrPlayer());

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
   else if (userChoice == CHOICE_2)
   {
      //Load game
      std::string fileName;
      cout << endl
           << "Enter the filename from which to load a game" << endl;
      cin >> fileName;
      try
      {
         GameInit *gameInit = new GameInit(fileName);
         cout << "Qwirkle game successfully loaded" << endl;
         Game *game = new Game(gameInit->getPlayer1(), gameInit->getPlayer2(), gameInit->getBag(), gameInit->getBoard(), gameInit->getCurrPlayer());
         delete gameInit;
         cin.ignore();
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
}

void closeProgMsg()
{
   cout << "Goodbye" << endl;
}