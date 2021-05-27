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

    if (shape == CIRCLE)
    {
        shapeUnicode = CIRCLE_UNICODE;
    }
    else if (shape == STAR_4)
    {
        shapeUnicode = FOUR_STAR_UNICODE;
    }
    else if (shape == DIAMOND)
    {
        shapeUnicode = DIAMOND_UNICODE;
    }
    else if (shape == SQUARE)
    {
        shapeUnicode = SQUARE_UNICODE;
    }
    else if (shape == STAR_6)
    {
        shapeUnicode = SIX_STAR_UNICODE;
    }
    else
    {
        shapeUnicode = CLOVER_UNICODE;
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
