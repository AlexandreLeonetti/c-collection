#include "snake.h"
//https://www.youtube.com/watch?v=dZNmGWH91EQ
//20min

#if 0
//FULL SCREEN
#define WINDOW_X 0
#define WINDOW_Y 0
#define WINDOW_WIDTH 1980
#define WINDOW_HEIGHT 1080
#define SDL_BORDERLESS

#else
//STREAM
#define WINDOW_X 0 
#define WINDOW_Y 0 
#define WINDOW_WIDTH 1000
#define WINDOW_HEIGHT 1000 
#endif


#define GRID_SIZE 20
#define GRID_DIM 800


void render_grid(SDL_Renderer *renderer, int x, int y){
    SDL_SetRenderDrawColor(renderer, 0x55, 0x55, 0x55, 255);
    int cell_size = GRID_DIM / GRID_SIZE;

    SDL_Rect cell;
    cell.w =  cell_size;
    cell.h = cell_size;

    for(int i = 0; i< GRID_SIZE; i++){
        for(int j = 0; j<GRID_SIZE; j++){
            cell.x = x + (i*cell_size);
            cell.y = y + (j*cell_size);
            SDL_RenderDrawRect(renderer, &cell);
        }
    }



} 
 


int main(){
    SDL_Window *window;
    SDL_Renderer *renderer;

    if(SDL_INIT_VIDEO < 0){
        fprintf(stderr, "ERROR : SDL_INIT_VIDEO");
    }

    window = SDL_CreateWindow(
        "Snake",
       WINDOW_X,
       WINDOW_Y,
       WINDOW_WIDTH,
       WINDOW_HEIGHT,
       SDL_WINDOW_BORDERLESS
    );

    if(!window){
        fprintf(stderr, "ERROR : !window");
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    if(!renderer){
        fprintf(stderr, "!renderer");
    }


    SDL_SetRenderDrawColor(renderer, 0x00, 0xff, 0x00, 255);
    SDL_RenderPresent(renderer);

    //SDL_Delay(2000);
    bool quit = false;
    SDL_Event event ;

    while(!quit){
        while(SDL_PollEvent(&event)){
            switch(event.type){
                case SDL_QUIT:
                    quit = true;
                    break;
                case SDL_KEYUP:
                    break;
                case SDL_KEYDOWN:
                    switch(event.key.keysym.sym){
                        case SDLK_ESCAPE:
                            quit = true;
                            break;
                    }
            }
        }

    SDL_RenderClear(renderer);
    // render loop start

    render_grid(renderer, 200, 200);

    // render loop end
    SDL_SetRenderDrawColor(renderer, 0x00, 0xff, 0x00, 255);
    SDL_RenderPresent(renderer);

    }


    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();


    return 0;
}