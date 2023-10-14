#ifndef SQUARE_RENDERER_HPP
#define SQUARE_RENDERER_HPP

#include <glad/glad.h>
#include <glm/glm.hpp>

#include "shader.hpp"


class SquareRenderer
{
public:
    Shader shader;

    SquareRenderer(Shader &shader_);
    ~SquareRenderer();

    void drawSquare(glm::vec2 position, glm::vec2 size = glm::vec2(1.0f), glm::vec3 color = glm::vec3(1.0f));

private:
    unsigned int quadVAO;
    void initRenderData();
};


#endif
