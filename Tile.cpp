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

    std::string shapeUnicode;

    if (shape == 1)
    {
        shapeUnicode = "\U000025EF";
    }
    else if (shape == 2)
    {
        shapeUnicode = "\U00002726";
    }
    else if (shape == 3)
    {
        shapeUnicode = "\U000025C6";
    }
    else if (shape == 4)
    {
        shapeUnicode = "\U000025FC";
    }
    else if (shape == 5)
    {
        shapeUnicode = "\U0001F7CC";
    }
    else
    {
        shapeUnicode = "\U00002618";
    }

    if (colour == 'R')
    {
        retval = RED_COLOR + shapeUnicode + RESET_COLOR + std::to_string(shape);
    }
    else if (colour == 'O')
    {
        retval = ORANGE_COLOR + shapeUnicode + RESET_COLOR + std::to_string(shape);
    }
    else if (colour == 'Y')
    {
        retval = YELLOW_COLOR + shapeUnicode + RESET_COLOR + std::to_string(shape);
    }
    else if (colour == 'G')
    {
        retval = GREEN_COLOR + shapeUnicode + RESET_COLOR + std::to_string(shape);
    }
    else if (colour == 'B')
    {
        retval = BLUE_COLOR + shapeUnicode + RESET_COLOR + std::to_string(shape);
    }
    else if (colour == 'P')
    {
        retval = PURPLE_COLOR + shapeUnicode + RESET_COLOR + std::to_string(shape);
    }

    return retval;
}
