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
    // game.set_random_grid(0, 30);

    // int tmp = 0;

    // Main Loop
    SDL_Event event;
    bool next = false;
    bool pause = false;
    bool quit = false;
    while(!quit)
    {
        
        // Event Loop
        while(SDL_PollEvent(&event) != 0) 
        {
            switch( event.type )
            {
                case SDL_KEYDOWN:
                    switch (event.key.keysym.scancode)
                    {
                        case SDL_SCANCODE_SPACE:
                            pause = !pause;
                            std::cout << "Paused: " << (pause ? "true" : "false") << '\n';
                            break;

                        case SDL_SCANCODE_RIGHT:
                            next = true;
                            break;
                    
                        default:
                            break;
                    }
                    break;

                case SDL_KEYUP:
                    break;

                case SDL_QUIT:
                    quit = true;
                    break;

                default:
                    break;
            }
        }

        // Clear with background color
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);
        SDL_Delay(TIME_DELAY);

        // ====== Draw Space ====== //

        // if(tmp == 0)
        // {
        //     game.save("test.gol");
        // }

        // if(tmp == 10)
        // {
        //     game.load("test.gol");
        // }

        // ++tmp;

        game.draw(renderer, window_width, window_height);
        if(!pause)
            game.update();

        if(next && pause)
        {
            game.update();
            next = false;
        }
        

        // ======================== //


        // Draw buffer to screen
        SDL_RenderPresent(renderer);
    }

    // Destroy window 
    SDL_DestroyWindow(window); 
    // Quit SDL subsystems 
    SDL_Quit();
}