
#ifndef ASSIGN2_TILE_H
#define ASSIGN2_TILE_H
#include <string>

#include <string>

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

   Colour colour;
   Shape shape;
};

#endif // ASSIGN2_TILE_H
