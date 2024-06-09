#include <SDL2/SDL.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <time.h>

#define WINDOW_X 0 
#define WINDOW_Y 0 
#define WINDOW_WIDTH 1000
#define WINDOW_HEIGHT 1000 

#define GRID_SIZE 50
#define GRID_DIM 800

enum {
    SNAKE_UP,
    SNAKE_DOWN,
    SNAKE_LEFT,
    SNAKE_RIGHT
};

struct snake {
    int x;
    int y;
    int dir;
    struct snake *next;
};

typedef struct snake Snake;
Snake *head;
Snake *tail;

void init_snake(){
    Snake *new = malloc(sizeof(Snake));
    new->x = GRID_SIZE / 2;
    new->y = GRID_SIZE / 2;
    new->dir = SNAKE_UP;
    new->next = NULL;

    head = new;
    tail = new;
}

void increase_snake(){
    Snake *new = malloc(sizeof(Snake));
    new->x = tail->x;
    new->y = tail->y;

    switch(tail->dir) {
        case SNAKE_UP:
            new->y += 1;
            break;
        case SNAKE_DOWN:
            new->y -= 1;
            break;
        case SNAKE_LEFT:
            new->x += 1;
            break;
        case SNAKE_RIGHT:
            new->x -= 1;
            break;
    }

    new->dir = tail->dir;
    new->next = NULL;
    tail->next = new;
    tail = new;
}

void render_snake(SDL_Renderer *renderer, int x, int y){
    SDL_SetRenderDrawColor(renderer, 0x00, 0xff, 0x00, 255);
    int seg_size = GRID_DIM / GRID_SIZE;
    SDL_Rect seg;
    seg.w = seg_size;
    seg.h = seg_size;

    Snake *track = head;
    while(track != NULL){
        seg.x = x + track->x * seg_size;
        seg.y = y + track->y * seg_size;
        SDL_RenderFillRect(renderer, &seg);
        track = track->next;
    }
}

void render_grid(SDL_Renderer *renderer, int x, int y){
    SDL_SetRenderDrawColor(renderer, 0x55, 0x55, 0x55, 255);
    int cell_size = GRID_DIM / GRID_SIZE;
    SDL_Rect cell;
    cell.w = cell_size;
    cell.h = cell_size;

    for(int i = 0; i < GRID_SIZE; i++){
        for(int j = 0; j < GRID_SIZE; j++){
            cell.x = x + (i * cell_size);
            cell.y = y + (j * cell_size);
            SDL_RenderDrawRect(renderer, &cell);
        }
    }
}

int main(){
    srand(time(NULL));
    init_snake();
    
    SDL_Window *window;
    SDL_Renderer *renderer;

    if (SDL_Init(SDL_INIT_VIDEO) < 0){
        fprintf(stderr, "ERROR: SDL_INIT_VIDEO\n");
        return 1;
    }

    window = SDL_CreateWindow("Snake", WINDOW_X, WINDOW_Y, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_BORDERLESS);
    if (!window){
        fprintf(stderr, "ERROR: !window\n");
        SDL_Quit();
        return 1;
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer){
        fprintf(stderr, "ERROR: !renderer\n");
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    int grid_x = (WINDOW_WIDTH / 2) - (GRID_DIM / 2);
    int grid_y = (WINDOW_HEIGHT / 2) - (GRID_DIM / 2);

    bool quit = false;
    SDL_Event event;

    while (!quit){
        while (SDL_PollEvent(&event)){
            if (event.type == SDL_QUIT){
                quit = true;
            }
            else if (event.type == SDL_KEYDOWN){
                if (event.key.keysym.sym == SDLK_ESCAPE){
                    quit = true;
                }
            }
        }

        SDL_RenderClear(renderer);
        render_grid(renderer, grid_x, grid_y);
        render_snake(renderer, grid_x, grid_y);

        SDL_RenderPresent(renderer);

        // Increase snake every second for demonstration
        SDL_Delay(1000);
        increase_snake();
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
