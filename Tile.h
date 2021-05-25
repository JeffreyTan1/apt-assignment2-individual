
#ifndef ASSIGN2_TILE_H
#define ASSIGN2_TILE_H
#include <string>

#include <string>

#define RESET_COLOR "\033[0m"
#define RED_COLOR "\033[31m"
#define ORANGE_COLOR "\u001b[38;5;209m"
#define YELLOW_COLOR "\033[33m"
#define GREEN_COLOR "\033[32m"
#define BLUE_COLOR "\033[34m"
#define PURPLE_COLOR "\033[35m"

// Define a Colour type
typedef char Colour;

// Define a Shape type
typedef int Shape;

class Tile
{
public:
   Tile(char colour, int shape);
   Tile();
   ~Tile();
   std::string toString();
   bool equals(char colour, int shape);

   std::string toPrettyString();

   Colour colour;
   Shape shape;
};

#endif // ASSIGN2_TILE_H
