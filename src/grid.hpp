#ifndef GRID_HPP
#define GRID_HPP

#include <stdexcept>

#include <glm/glm.hpp>

#include "square.hpp"


// https://stackoverflow.com/a/21944048
template <typename T>
T** create2DArray(unsigned nrows, unsigned ncols, const T& val = T())
{
   if (nrows == 0)
        throw std::invalid_argument("number of rows is 0");
   if (ncols == 0)
        throw std::invalid_argument("number of columns is 0");
   T** ptr = nullptr;
   T* pool = nullptr;
   try
   {
       ptr = new T*[nrows];  // allocate pointers (can throw here)
       pool = new T[nrows*ncols]{val};  // allocate pool (can throw here)

       // now point the row pointers to the appropriate positions in
       // the memory pool
       for (unsigned i = 0; i < nrows; ++i, pool += ncols )
           ptr[i] = pool;

       // Done.
       return ptr;
   }
   catch (std::bad_alloc& ex)
   {
       delete [] ptr; // either this is nullptr or it was allocated
       throw ex;  // memory allocation error
   }
};

template <typename T>
void delete2DArray(T** arr)
{
   delete [] arr[0];  // remove the pool
   delete [] arr;     // remove the pointers
};


class Grid
{
public:
    unsigned int height, width;

    // Keep reference of start/end squares.
    Square* start;
    Square* end;

    //Square *square;
    Grid(unsigned int height_, unsigned int width_);
    ~Grid();

    Square* squareAtScreenPos(int x, int y);
    void render(SquareRenderer &renderer);

    Square* at(int x, int y);
private:
    Square* **grid;
};


#endif