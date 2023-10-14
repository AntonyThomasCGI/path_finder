
#ifndef ENGINE_HPP
#define ENGINE_HPP

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "common.hpp"


enum MouseMode {IDLE, DRAW_EVENT, DRAG_START_EVENT, DRAG_END_EVENT};


class Engine
{
public:
    // inputs
    bool keys[1024];
    bool keysProcessed[1024];
    bool mouse[3];
    bool mouseProcessed[3];
    Vec2i cursorPos;
    MouseMode mouseMode;

    unsigned int width;
    unsigned int height;

    bool wireFrameMode = false;

    Engine(unsigned int width, unsigned int height);
    ~Engine();

    void init();
    void processInput(float dt);
    void update(float dt);
    void render();
    void resize(unsigned int width_, unsigned int height_);
};


#endif
