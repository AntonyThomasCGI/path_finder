#ifndef SQUARE_HPP
#define SQUARE_HPP

#include <map>

#include <glad/glad.h>
#include <glm/glm.hpp>

#include "common.hpp"
#include "shader.hpp"
#include "square_renderer.hpp"


// Define possible square states.
enum SquareType {AIR, WALL, START, END, PATH};

const float SQUARE_SIZE(40.0f);


class Square
{
public:
    Vec2i coords;
    SquareType type;
    Square *parent;

    Square();
    Square(Vec2i coords_, SquareType type_ = AIR);
    ~Square();

    void draw(SquareRenderer &renderer);
};


#endif
