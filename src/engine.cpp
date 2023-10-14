
#include <iostream>

#include <glad/glad.h>
#include <glm/glm.hpp>

#include "a_star.hpp"
#include "engine.hpp"
#include "grid.hpp"
#include "shader.hpp"
#include "square.hpp"
#include "square_renderer.hpp"


Grid *grid;
SquareRenderer *renderer;


Engine::Engine(unsigned int width_, unsigned int height_)
    : width(width_), height(height_), mouseMode(IDLE)
{ }

Engine::~Engine()
{
    delete grid;
    delete renderer;
}


void Engine::init()
{
    glm::mat4 projection = glm::ortho(0.0f, static_cast<float>(this->width), static_cast<float>(this->height), 0.0f, -1.0f, 1.0f);

    Shader squareShader = loadShaderFromFile("C:\\dev\\path_finder\\shaders\\square.vert", "C:\\dev\\path_finder\\shaders\\square.frag", nullptr);
    squareShader.SetMatrix4("projection", projection, true);

    renderer = new SquareRenderer(squareShader);

    int gridY = (this->height - this->height % static_cast<int>(SQUARE_SIZE)) / SQUARE_SIZE + 1;
    int gridX = (this->width - this->width % static_cast<int>(SQUARE_SIZE)) / SQUARE_SIZE + 1;
    grid = new Grid(gridY, gridX);
};

void Engine::processInput(float dt)
{
    if (this->keys[GLFW_KEY_F3] && !this->keysProcessed[GLFW_KEY_F3])
    {
        // Toggle wire frame
        if (this->wireFrameMode) {
            this->wireFrameMode = false;
            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        } else {
            this->wireFrameMode = true;
            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        }
        this->keysProcessed[GLFW_KEY_F3] = true;
    }
    if (this->mouse[GLFW_MOUSE_BUTTON_LEFT] && !this->mouseProcessed[GLFW_MOUSE_BUTTON_LEFT])
    {
        Square *square = grid->squareAtScreenPos(this->cursorPos.x, this->cursorPos.y);
        if (square)
        {
            if (this->mouseMode == IDLE) {
                // Set mouse mode state based on what square was clicked on.
                if (square->type == START)
                    this->mouseMode = DRAG_START_EVENT;
                else if (square->type == END)
                    this->mouseMode = DRAG_END_EVENT;
                else
                    this->mouseMode = DRAW_EVENT;
            }
            switch (this->mouseMode) {
                case DRAW_EVENT:
                    if (square->type == AIR || square->type == WALL || square->type == PATH)
                        square->type = this->keys[GLFW_KEY_LEFT_CONTROL] ? AIR : WALL;
                    break;
                case DRAG_START_EVENT:
                    if (square->type != START && square->type != WALL) {
                        grid->start->type = AIR;
                        square->type = START;
                        grid->start = square;
                    }
                    break;
                case DRAG_END_EVENT:
                    if (square->type != END && square->type != WALL) {
                        grid->end->type = AIR;
                        square->type = END;
                        grid->end = square;
                    }
                    break;
            }
        }

        this->mouseProcessed[GLFW_MOUSE_BUTTON_LEFT] = true;
    }
    if (this->keys[GLFW_KEY_SPACE] && !this->keysProcessed[GLFW_KEY_SPACE])
    {
        // Clear any previous path tiles.
        grid->clearPath();
        if (!this->keys[GLFW_KEY_LEFT_SHIFT])
        {
            // Do new a* search.
            AStar::Generator gen;
            gen.setHeuristic(AStar::Heuristic::euclidean);
            gen.setGrid(grid);

            auto path = gen.findPath(grid->start->coords, grid->end->coords);

            // Color the path.
            for (auto &coord : path) {
                Square *sqr = grid->at(coord.x, coord.y);
                if (sqr->type == AIR)
                    sqr->type = PATH;
            }
        }
        this->keysProcessed[GLFW_KEY_SPACE] = true;
    }
};

void Engine::update(float dt)
{

};

void Engine::render()
{
    grid->render(*renderer);
};


void Engine::resize(unsigned int width_, unsigned int height_)
{
    this->width = width_;
    this->height = height_;

    glm::mat4 projection = glm::ortho(0.0f, static_cast<float>(width_), static_cast<float>(height_), 0.0f, -1.0f, 1.0f);
    renderer->shader.SetMatrix4("projection", projection, true);
};
