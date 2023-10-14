

#include "common.hpp"


bool Vec2i::operator == (const Vec2i& coords_)
{
    return (x == coords_.x && y == coords_.y);
}
