#ifndef ASSIGN2_HIGH_SCORE_LOADER_H
#define ASSIGN2_HIGH_SCORE_LOADER_H
#include <fstream>
#include <string>
#include <map>

class HighScoreLoader
{
public:
    HighScoreLoader();
    std::map<int, std::string> getHighScores();

private:
    std::map<int, std::string> highScores;
    std::ifstream highScoreFile;
};

#endif // ASSIGN2_HIGH_SCORE_LOADER_H
