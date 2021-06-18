#include "game.hpp"

// #include <array>
// #include <cstdint>
// #include <SDL.h>
// #include <iostream>

// #define CONTINUOUS_GRID

// #define STATE_MASK      0b00000001
// #define NEIGHBOURS_MASK 0b00011110

// template<std::size_t Width, std::size_t Height>
// using Grid = std::array<std::array<uint8_t,Width>,Height>;

// template<std::size_t Width = 200, std::size_t Height = 200>
// class GameOfLife
// {
//     private:
//         Grid<Width,Height> grid;
//         Grid<Width,Height> aux_grid;

//     public:
//         GameOfLife() = default;
//         GameOfLife(const Grid<Width,Height>& in_grid) : grid(in_grid) {};

//         void set_cell(const size_t x, const size_t y);
//         void clear_cell(const size_t x, const size_t y);
//         void update();
//         void draw(SDL_Renderer* , const int , const int);
//         void set_random_grid(const unsigned seed, const size_t samples = 200);
// };


template<std::size_t Width, std::size_t Height>
void GameOfLife<Width,Height>::set_cell(const size_t x, const size_t y)
{
    // Set state bit
    this->grid[y][x] |= STATE_MASK;

    // Set neighbourhood vectors 
    const size_t x_plus = (x+1) % Width;
    const size_t x_minus = (x-1) % Width;
    const size_t y_plus = (y+1) % Height;
    const size_t y_minus = (y-1) % Height;

    // Update neighbourhood's neighbour count 

    // We'll increment 2 instead of 1
    // because the cell value has the state
    // on the first bit
    const uint8_t inc = 0b00000010;
    this->grid[y_minus][x_minus] += inc;
    this->grid[y_minus][x      ] += inc;
    this->grid[y_minus][x_plus ] += inc;
    this->grid[y      ][x_minus] += inc;
    this->grid[y      ][x_plus ] += inc;
    this->grid[y_plus ][x_minus] += inc;
    this->grid[y_plus ][x      ] += inc;
    this->grid[y_plus ][x_plus ] += inc;
}


template<std::size_t Width, std::size_t Height>
void GameOfLife<Width,Height>::clear_cell(const size_t x, const size_t y)
{
    // Clear state bit
    this->grid[y][x] &= NEIGHBOURS_MASK;

    // Set neighbourhood vectors 
    const size_t x_plus = (x+1) % Width;
    const size_t x_minus = (x-1) % Width;
    const size_t y_plus = (y+1) % Height;
    const size_t y_minus = (y-1) % Height;

    // Update neighbourhood's neighbour count 

    // We'll decrement 2 instead of 1
    // because the cell value has the state
    // on the first bit
    const uint8_t dec = 0b00000010;
    this->grid[y_minus][x_minus] -= dec;
    this->grid[y_minus][x      ] -= dec;
    this->grid[y_minus][x_plus ] -= dec;
    this->grid[y      ][x_minus] -= dec;
    this->grid[y      ][x_plus ] -= dec;
    this->grid[y_plus ][x_minus] -= dec;
    this->grid[y_plus ][x      ] -= dec;
    this->grid[y_plus ][x_plus ] -= dec;
}


template<std::size_t Width, std::size_t Height>
void GameOfLife<Width,Height>::update()
{
    memcpy(&aux_grid, &grid, Width*Height);

    for(int i = 0 ; i < Height ; ++i)
    {
        for(int j = 0 ; j < Width ; ++j)
        {
            const uint8_t val = aux_grid[i][j];
            // If cell isn't dead or has neighbours
            if(val != 0)
            {
                const uint8_t neighbours = val >> 1;

                // If cell is alive
                if(val & STATE_MASK)
                {
                    // Check starvation or overpopulation
                    if((neighbours != 2) && (neighbours != 3))
                        this->clear_cell(j,i);
                }
                // If cell has neighbours
                else
                {
                    if(neighbours == 3)
                        this->set_cell(j,i);
                }
            }
        }
    }
}


template<std::size_t Width, std::size_t Height>
void GameOfLife<Width,Height>::draw(SDL_Renderer* renderer, const int win_width, const int win_height)
{
    const int pixel_height = win_height / Height;
    const int pixel_width = win_width / Width;
    SDL_SetRenderDrawColor( renderer, 255, 255, 255, 255 );
    for(int i = 0 ; i < Height ; ++i)
    {
        for(int j = 0 ; j < Width ; ++j)
        {
            const SDL_Rect big_pixel{ 
                j*pixel_width,
                i*pixel_height,
                pixel_width,
                pixel_height
            };

            if(this->grid[i][j] & STATE_MASK)
                SDL_RenderFillRect( renderer, &big_pixel );
        }
    }
}


template<std::size_t Width, std::size_t Height>
void GameOfLife<Width,Height>::set_random_grid(const unsigned seed, const size_t samples)
{
    srand(seed);
    for(size_t i = 0 ; i < samples ; ++i)
    {
        const size_t x = rand() % (Width - 1);
        const size_t y = rand() % (Height - 1);
        this->set_cell(x,y);
    }
}