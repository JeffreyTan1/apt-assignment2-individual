#include "HighScoreSaver.h"
#include "HighScoreLoader.h"
#include <iostream>

HighScoreSaver::HighScoreSaver(std::map<int, std::string> currentGameScores)
{
    HighScoreLoader *highScoreLoader = new HighScoreLoader();
    std::map<int, std::string> currentHighScores = highScoreLoader->getHighScores();

    std::map<int, std::string>::iterator it;

    for (it = currentGameScores.begin(); it != currentGameScores.end(); it++)
    {
        currentHighScores.insert(std::pair<int, std::string>(it->first, it->second));
    }

    int iterations = currentHighScores.size() - 5;
    for (int i = 0; i < iterations; i++)
    {
        currentHighScores.erase(currentHighScores.begin());
    }

    outFile.open("HIGHSCORES.txt");

    for (it = currentHighScores.begin(); it != currentHighScores.end(); it++)
    {
        outFile << it->first << " " << it->second << std::endl;
    }
}