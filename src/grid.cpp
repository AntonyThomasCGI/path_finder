
#include <iostream>

#include "grid.hpp"


Grid::Grid(unsigned int height_, unsigned int width_)
    : height(height_), width(width_)
{
    grid = create2DArray<Square*>(height, width);
    for (int i = 0; i < height; i++ ) {
        for (int j = 0; j < width; j++ ) {
            grid[i][j] = new Square(Vec2i{j, i});
        }
    }

    // Place start/end squares.
    int halfHeight = (height - height % 2) / 2;
    int thirdWidth = (width - width % 3) / 3;
    this->start = grid[halfHeight][thirdWidth];
    this->end = grid[halfHeight][thirdWidth * 2];
    this->start->type = START;
    this->end->type = END;
};


Grid::~Grid()
{
    for (unsigned int i = 0; i < height; i++ ) {
        for (unsigned int j = 0; j < width; j++ ) {
            delete grid[i][j];
        }
    }
    delete2DArray(grid);
}


Square* Grid::squareAtScreenPos(int x, int y)
{
    int i = (y - y % static_cast<int>(SQUARE_SIZE)) / SQUARE_SIZE;
    int j = (x - x % static_cast<int>(SQUARE_SIZE)) / SQUARE_SIZE;
    if (j < 0 || j >= this->width || i < 0 || i >= this-> height)
        return {};
    return grid[i][j];
}

Square* Grid::at(int x, int y)
{
    return grid[y][x];
}


void Grid::render(SquareRenderer &renderer)
{
    for (int i = 0; i < height; i++ ) {
        for (int j = 0; j < width; j++ ) {
            grid[i][j]->draw(renderer);
        }
    }
};
