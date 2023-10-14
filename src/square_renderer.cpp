
#include <iostream>

#include "square_renderer.hpp"


SquareRenderer::SquareRenderer(Shader &shader_)
    : shader(shader_)
{
    this->initRenderData();
}


SquareRenderer::~SquareRenderer()
{
    glDeleteVertexArrays(1, &this->quadVAO);
}


void SquareRenderer::drawSquare(glm::vec2 position, glm::vec2 size, glm::vec3 color)
{
    this->shader.Use();

    glm::mat4 transform = glm::mat4(1.0f);
    transform = glm::translate(transform, glm::vec3(position, 0.0f));
    //transform = glm::rotate(transform, glm::radians(rotate), glm::vec3(0.0f, 0.0f, 1.0f));
    transform = glm::scale(transform, glm::vec3(size, 1.0f));

    this->shader.SetMatrix4("transform", transform);

    this->shader.SetVector3f("color", color);

    glBindVertexArray(this->quadVAO);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    glBindVertexArray(0);
}


void SquareRenderer::initRenderData()
{
    // configure vao/vbo
    unsigned int VBO;
    float vertices[] = {
        // pos
        0.0f, 1.0f,
        1.0f, 0.0f,
        0.0f, 0.0f,

        0.0f, 1.0f,
        1.0f, 1.0f,
        1.0f, 0.0f,
    };

    glGenVertexArrays(1, &this->quadVAO);
    glGenBuffers(1, &VBO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindVertexArray(this->quadVAO);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}