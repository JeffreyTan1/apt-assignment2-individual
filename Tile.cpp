#include "Tile.h"
#include "TileCodes.h"

Tile::Tile()
{
}

Tile::~Tile()
{
}

Tile::Tile(char colour, int shape)
{
    this->colour = colour;
    this->shape = shape;
}

bool Tile::equals(char colour, int shape)
{
    bool equal = false;
    if (this->colour == colour && this->shape == shape)
    {
        equal = true;
    }
    return equal;
}

std::string Tile::toString()
{
    std::string retval = colour + std::to_string(shape);
    return retval;
}
