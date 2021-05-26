#include "HighScoreLoader.h"
#include <iostream>
#include <sstream>
#include <cstring>
#include <vector>
#define HIGH_SCORE_NUM 5
using std::ifstream;

HighScoreLoader::HighScoreLoader()
{
    ifstream highScoreFile("HIGHSCORES.txt");
    std::string line;
    for (int i = 0; i < HIGH_SCORE_NUM; i++)
    {
        std::getline(highScoreFile, line);
        std::vector<std::string>
            tokens;

        std::stringstream ss(line);

        std::string tempStr;

        while (getline(ss, tempStr, ' '))
        {
            tokens.push_back(tempStr);
        }

        highScores.insert(std::pair<std::string, int>(tokens[0], std::stoi(tokens[1])));
    }
}
std::map<std::string, int> HighScoreLoader::getHighScores()
{
    return highScores;
}