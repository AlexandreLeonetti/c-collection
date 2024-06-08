#include "snake.h"
//https://www.youtube.com/watch?v=dZNmGWH91EQ
//7min24


int main(){
    SDL_Window *window;
    SDL_Renderer *renderer;

    if(SDL_INIT_VIDEO < 0){
        fprinf(stderr, "ERROR : SDL_INIT_VIDEO");
    }

    window = SDL_CreateWindow(
        "",
    );


    return 0;
}