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

std::string Tile::toPrettyString()
{
    std::string retval;

    if (colour == 'R')
    {
        retval = RED_COLOR + std::to_string(shape) + RESET_COLOR + " ";
    }
    else if (colour == 'O')
    {
        retval = ORANGE_COLOR + std::to_string(shape) + RESET_COLOR + " ";
    }
    else if (colour == 'Y')
    {
        retval = YELLOW_COLOR + std::to_string(shape) + RESET_COLOR + " ";
    }
    else if (colour == 'G')
    {
        retval = GREEN_COLOR + std::to_string(shape) + RESET_COLOR + " ";
    }
    else if (colour == 'B')
    {
        retval = BLUE_COLOR + std::to_string(shape) + RESET_COLOR + " ";
    }
    else if (colour == 'P')
    {
        retval = PURPLE_COLOR + std::to_string(shape) + RESET_COLOR + " ";
    }

    return retval;
}
