#include <SDL3/SDL.h>
#include <iostream>
#include <cmath>

// 1. THE PUZZLE MAP (16x16)
const int MAP_SIZE = 16;
int worldMap[MAP_SIZE][MAP_SIZE] = {
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
    {1,2,0,0,0,0,1,0,0,0,0,0,0,0,0,1},
    {1,1,1,1,1,0,1,0,1,1,1,1,1,1,0,1},
    {1,0,0,0,1,0,1,0,1,0,0,0,0,1,0,1},
    {1,0,1,0,1,0,0,0,1,0,1,1,0,1,0,1},
    {1,0,1,0,1,1,1,1,1,0,1,0,0,1,0,1},
    {1,0,1,0,0,0,0,0,0,0,1,0,1,1,0,1},
    {1,0,1,1,1,1,1,1,1,1,1,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1},
    {1,1,1,1,1,1,1,1,1,1,1,0,1,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,1,0,1,0,1,1},
    {1,0,1,1,1,1,1,1,1,0,1,0,1,0,0,1},
    {1,0,1,0,0,0,0,0,1,0,1,0,1,1,0,1},
    {1,0,1,0,1,1,1,0,1,0,1,0,0,0,0,1},
    {1,0,0,0,1,0,0,0,1,0,0,0,1,1,3,1},
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
};

int main(int argc, char* argv[]) {
    if (!SDL_Init(SDL_INIT_VIDEO)) return 1;
    SDL_Window* window = nullptr;
    SDL_Renderer* renderer = nullptr;
    if (!SDL_CreateWindowAndRenderer("3D Maze Puzzle", 640, 480, 0, &window, &renderer)) return 1;

    // Start at the Green Entry (Tile 1,1)
    float playerX = 1.5f;
    float playerY = 1.5f;
    float playerA = 0.0f;
    float FOV = M_PI / 3.0f;

    bool running = true;
    SDL_Event event;

    while (running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_EVENT_QUIT) running = false;
        }

        const bool* keys = SDL_GetKeyboardState(NULL);
        if (keys[SDL_SCANCODE_A]) playerA -= 0.05f; 
        if (keys[SDL_SCANCODE_D]) playerA += 0.05f; 
        if (keys[SDL_SCANCODE_W]) {
            float nX = playerX + cos(playerA) * 0.06f;
            float nY = playerY + sin(playerA) * 0.06f;
            if(worldMap[(int)nY][(int)nX] == 0 || worldMap[(int)nY][(int)nX] > 1) { playerX = nX; playerY = nY; }
        }
        if (keys[SDL_SCANCODE_S]) {
            float nX = playerX - cos(playerA) * 0.06f;
            float nY = playerY - sin(playerA) * 0.06f;
            if(worldMap[(int)nY][(int)nX] == 0 || worldMap[(int)nY][(int)nX] > 1) { playerX = nX; playerY = nY; }
        }

        // Win Condition Check
        if (worldMap[(int)playerY][(int)playerX] == 3) {
            std::cout << "MAZE CONQUERED! YOU FOUND THE EXIT!" << std::endl;
            running = false;
        }

        // Sky and Floor
        SDL_SetRenderDrawColor(renderer, 10, 10, 20, 255); // Deep space sky
        SDL_FRect sky = {0,0,640,240}; SDL_RenderFillRect(renderer, &sky);
        SDL_SetRenderDrawColor(renderer, 20, 20, 20, 255); // Dark floor
        SDL_FRect floor = {0,240,640,240}; SDL_RenderFillRect(renderer, &floor);

        for (int i = 0; i < 640; i++) {
            float rayAngle = (playerA - FOV/2.0f) + ((float)i / 640.0f) * FOV;
            float rayX = playerX; float rayY = playerY;
            int hitType = 0;

            while (worldMap[(int)rayY][(int)rayX] == 0 || (rayX == playerX && rayY == playerY)) {
                rayX += cos(rayAngle) * 0.01f;
                rayY += sin(rayAngle) * 0.01f;
                hitType = worldMap[(int)rayY][(int)rayX];
                if (hitType != 0) break;
            }

            float distance = sqrt(pow(rayX - playerX, 2) + pow(rayY - playerY, 2)) * cos(rayAngle - playerA);
            float wallHeight = 480.0f / distance;

            // COLOR LOGIC FOR PUZZLE
            if (hitType == 1) SDL_SetRenderDrawColor(renderer, 100, 100, 100, 255); // Gray Walls
            else if (hitType == 2) SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);   // Green Entry
            else if (hitType == 3) SDL_SetRenderDrawColor(renderer, 255, 215, 0, 255); // Gold Exit
            
            SDL_RenderLine(renderer, (float)i, (480-wallHeight)/2, (float)i, (480+wallHeight)/2);
        }
        SDL_RenderPresent(renderer);
        SDL_Delay(10);
    }
    SDL_Quit();
    return 0;
}
      