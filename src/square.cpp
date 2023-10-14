
#include <iostream>

#include "square.hpp"

#include "glm/gtx/string_cast.hpp"

static std::map<int, glm::vec3> colorMap{
    {AIR, glm::vec3(1.0f)},
    {WALL, glm::vec3(0.0f)},
    {START, glm::vec3(0.3f, 0.7f, 0.4f)},
    {END, glm::vec3(0.7f, 0.3f, 0.4f)},
    {PATH, glm::vec3(0.85f, 0.85f, 0.4f)}
};


Square::Square()
{
    coords = Vec2i{0, 0};
    type = AIR;
}


Square::Square(Vec2i coords_, SquareType type_)
    : coords(coords_), type(type_)
{
}


Square::~Square()
{
}



void Square::draw(SquareRenderer &renderer)
{
    float xOffset = static_cast<float>(this->coords.x);
    float yOffset = static_cast<float>(this->coords.y);
    float xReal = (xOffset + 1.0f) * SQUARE_SIZE - SQUARE_SIZE;  //+ xOffset * 2;
    float yReal = (yOffset + 1.0f) * SQUARE_SIZE - SQUARE_SIZE;  // + yOffset * 2;

    glm::vec2 position = glm::vec2(xReal, yReal);
    glm::vec2 size = glm::vec2(SQUARE_SIZE);

    renderer.drawSquare(position, size, colorMap[this->type]);
};
