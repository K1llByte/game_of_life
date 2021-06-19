#include "game.hpp"


template<std::size_t Width, std::size_t Height>
void GameOfLife<Width,Height>::set_cell(const size_t x, const size_t y)
{
    // Set state bit
    this->grid[y][x] |= STATE_MASK;

#ifdef CONTINUOUS_GRID

    // Set neighbourhood vectors 
    const size_t x_plus  = (x+1) % Width;
    const size_t x_minus = (x == 0) ? Width-1 : x-1;
    const size_t y_plus  = (y+1) % Height;
    const size_t y_minus = (y == 0) ? Height-1 : y-1;

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

#else

    // SOLUTION 1

    // const size_t x_plus  = (x+1) % Width;
    // const size_t x_minus = (x == 0) ? Width-1 : x-1;
    // const size_t y_plus  = (y+1) % Height;
    // const size_t y_minus = (y == 0) ? Height-1 : y-1;

    // const uint8_t inc = 0b00000010;
    // size_t inc_x_plus  = inc;
    // size_t inc_x_minus = inc;
    // size_t inc_y_plus  = inc;
    // size_t inc_y_minus = inc;

    // if(x == Width-1)
    //     inc_x_plus = 0;
    
    // if(x == 0)
    //     inc_x_minus = 0;

    // if(y == Height-1)
    //     inc_y_plus = 0;

    // if(y == 0)
    //     inc_y_minus = 0;

    // this->grid[y_minus][x_minus] += inc_y_minus | inc_x_minus;
    // this->grid[y_minus][x      ] += inc_y_minus;
    // this->grid[y_minus][x_plus ] += inc_y_minus | inc_x_plus;
    // this->grid[y      ][x_minus] += inc_x_minus;
    // this->grid[y      ][x_plus ] += inc_x_plus;
    // this->grid[y_plus ][x_minus] += inc_y_plus | inc_x_minus;
    // this->grid[y_plus ][x      ] += inc_y_plus;
    // this->grid[y_plus ][x_plus ] += inc_y_plus | inc_x_plus;

    // SOLUTION 2

    const bool x_not_overflow  = x != Width-1;
    const bool x_not_underflow = x != 0;
    const bool y_not_overflow  = y != Height-1;
    const bool y_not_underflow = y != 0;

    const uint8_t inc = 0b00000010;

    if(y_not_underflow)
    {
        this->grid[y-1][x] += inc;

        if(x_not_underflow)
            this->grid[y-1][x-1] += inc;
    
        if(x_not_overflow)
            this->grid[y-1][x+1] += inc;
    }

    if(x_not_underflow)
        this->grid[y][x-1] += inc;

    if(x_not_overflow)
        this->grid[y][x+1] += inc;

    if(y_not_overflow)
    {
        this->grid[y+1][x] += inc;

        if(x_not_underflow)
            this->grid[y+1][x-1] += inc;
    
        if(x_not_overflow)
            this->grid[y+1][x+1] += inc;
    }

#endif

}


template<std::size_t Width, std::size_t Height>
void GameOfLife<Width,Height>::clear_cell(const size_t x, const size_t y)
{
    // Clear state bit
    this->grid[y][x] &= NEIGHBOURS_MASK;

#ifdef CONTINUOUS_GRID

    // Set neighbourhood vectors
    const size_t x_plus  = (x+1) % Width;
    const size_t x_minus = (x == 0) ? Width-1 : x-1;
    const size_t y_plus  = (y+1) % Height;
    const size_t y_minus = (y == 0) ? Height-1 : y-1;

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

#else

    // SOLUTION 1

    // const size_t x_plus  = (x+1) % Width;
    // const size_t x_minus = (x == 0) ? Width-1 : x-1;
    // const size_t y_plus  = (y+1) % Height;
    // const size_t y_minus = (y == 0) ? Height-1 : y-1;

    // const uint8_t dec = 0b00000010;
    // size_t dec_x_plus  = dec;
    // size_t dec_x_minus = dec;
    // size_t dec_y_plus  = dec;
    // size_t dec_y_minus = dec;

    // if(x == Width-1)
    //     dec_x_plus = 0;
    
    // if(x == 0)
    //     dec_x_minus = 0;

    // if(y == Height-1)
    //     dec_y_plus = 0;

    // if(y == 0)
    //     dec_y_minus = 0;

    // this->grid[y_minus][x_minus] -= dec_y_minus | dec_x_minus;
    // this->grid[y_minus][x      ] -= dec_y_minus;
    // this->grid[y_minus][x_plus ] -= dec_y_minus | dec_x_plus;
    // this->grid[y      ][x_minus] -= dec_x_minus;
    // this->grid[y      ][x_plus ] -= dec_x_plus;
    // this->grid[y_plus ][x_minus] -= dec_y_plus | dec_x_minus;
    // this->grid[y_plus ][x      ] -= dec_y_plus;
    // this->grid[y_plus ][x_plus ] -= dec_y_plus | dec_x_plus;

    // SOLUTION 2

    const bool x_not_overflow  = x != Width-1;
    const bool x_not_underflow = x != 0;
    const bool y_not_overflow  = y != Height-1;
    const bool y_not_underflow = y != 0;

    const uint8_t dec = 0b00000010;

    if(y_not_underflow)
    {
        this->grid[y-1][x] -= dec;

        if(x_not_underflow)
            this->grid[y-1][x-1] -= dec;
    
        if(x_not_overflow)
            this->grid[y-1][x+1] -= dec;
    }

    if(x_not_underflow)
        this->grid[y][x-1] -= dec;

    if(x_not_overflow)
        this->grid[y][x+1] -= dec;

    if(y_not_overflow)
    {
        this->grid[y+1][x] -= dec;

        if(x_not_underflow)
            this->grid[y+1][x-1] -= dec;
    
        if(x_not_overflow)
            this->grid[y+1][x+1] -= dec;
    }

#endif
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
    // for(size_t i = 0 ; i < Height ; ++i)
    // {
    //     for(size_t j = 0 ; j < Width ; ++j)
    //     {
    //         if(this->grid[i][j] & STATE_MASK)
    //             std::cout << "\u001b[37m" << int(this->grid[i][j] >> 1) << "\u001b[0m" << ' ';
    //         else
    //             std::cout << "\u001b[30m" << int(this->grid[i][j] >> 1) << "\u001b[0m" << ' ';
    //     }
    //     std::cout << '\n';
    // }
    // std::cout << '\n';

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