#ifndef GAME_HPP
#define GAME_HPP

#include <array>
#include <cstdint>
#include <SDL.h>
#include <iostream>

#define CONTINUOUS_GRID

#define STATE_MASK      0b00000001
#define NEIGHBOURS_MASK 0b00011110

template<std::size_t Width, std::size_t Height>
using Grid = std::array<std::array<uint8_t,Width>,Height>;

template<std::size_t Width = 200, std::size_t Height = 200>
class GameOfLife
{
    private:
        Grid<Width,Height> grid;
        Grid<Width,Height> aux_grid;

    public:
        GameOfLife() = default;
        GameOfLife(const Grid<Width,Height>& in_grid) : grid(in_grid) {};

        void set_cell(const size_t x, const size_t y);
        void clear_cell(const size_t x, const size_t y);
        void update();
        void draw(SDL_Renderer* , const int , const int);
        void set_random_grid(const unsigned seed, const size_t samples = 200);
};

#endif // GAME_HPP