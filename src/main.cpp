#include "game.cpp"
#include <iostream>
#include <SDL.h>

#define TIME_DELAY 500

int main()
{
    const int window_width = 400;
    const int window_height = 400;
    
    // SDL stuff
    SDL_Init(SDL_INIT_VIDEO);
    //SDL_Init(SDL_INIT_EVERYTHING);

    SDL_Window* window = SDL_CreateWindow(
        "The Game of Life",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        window_width,
        window_height,
        SDL_WINDOW_SHOWN
    );
    
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);

    // Instanciate game objects
    GameOfLife<10,10> game{};

    // Glider 
    game.set_cell(5,1);
    game.set_cell(6,2);
    game.set_cell(6,3);
    game.set_cell(5,3);
    game.set_cell(4,3);

    // Random grid
    //game.set_random_grid(0, 30);

    // Main Loop
    SDL_Event e;
    bool quit = false;
    while(!quit)
    {
        // Event Loop
        while(SDL_PollEvent(&e) != 0) 
        {
            if(e.type == SDL_QUIT)
                quit = true;
        }

        // Clear with background color
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);
        SDL_Delay(TIME_DELAY);

        // ====== Draw Space ====== //

        game.draw(renderer, window_width, window_height);
        game.update();

        // ======================== //

        // Draw buffer to screen
        SDL_RenderPresent(renderer);
    }

    // Destroy window 
    SDL_DestroyWindow(window); 
    // Quit SDL subsystems 
    SDL_Quit();
}