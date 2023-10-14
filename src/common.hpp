#ifndef COMMON_HPP
#define COMMON_HPP


struct Vec2i
{
    int x, y;

    bool operator == (const Vec2i& coords_);
    friend Vec2i operator + (const Vec2i& left_, const Vec2i& right_)
    {
        return { left_.x + right_.x, left_.y + right_.y };
    }
};


#endif
