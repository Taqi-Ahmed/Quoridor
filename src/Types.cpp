#include "Types.h"

bool Position::operator==(const Position &other) const
{
    return x == other.x && y == other.y;
}

bool Position::operator<(const Position &other) const
{
    if (x != other.x) {
        return x < other.x;
    }

    return y < other.y;
}

Position Position::operator+(const Position &other) const
{
    return {x + other.x, y + other.y};
}

Position Position::operator-(const Position &other) const
{
    return {x - other.x, y - other.y};
}

