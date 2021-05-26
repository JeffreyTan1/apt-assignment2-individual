#ifndef ASSIGN2_HIGH_SCORE_SAVER_H
#define ASSIGN2_HIGH_SCORE_SAVER_H
#include <fstream>
#include <string>
#include <map>

class HighScoreSaver
{
public:
    HighScoreSaver(std::map<std::string, int> currGameScores);

private:
    std::ofstream outFile;
};

#endif // ASSIGN2_HIGH_SCORE_SAVER_H
