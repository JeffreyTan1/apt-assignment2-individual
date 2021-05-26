#include "HighScoreSaver.h"
#include "HighScoreLoader.h"
#include <iostream>

HighScoreSaver::HighScoreSaver(std::map<std::string, int> currentGameScores)
{
    HighScoreLoader *highScoreLoader = new HighScoreLoader();
    std::map<std::string, int> currentHighScores = highScoreLoader->getHighScores();

    std::map<std::string, int>::iterator it;

    for (it = currentGameScores.begin(); it != currentGameScores.end(); it++)
    {
        currentHighScores.insert(std::pair<std::string, int>(it->first, it->second));
    }

    //TODO: take into account when the highscores are not initalised in the file yet
    for (unsigned int i = 0; i < currentGameScores.size(); i++)
    {
        currentHighScores.erase(std::prev(currentHighScores.end()));
    }

    outFile.open("HIGHSCORES.txt");

    for (it = currentHighScores.begin(); it != currentHighScores.end(); it++)
    {
        outFile << it->first << " " << it->second << std::endl;
    }
}