#include <bits/stdc++.h>
#include <windows.h>
#include <SDL.h>
#include <SDL_image.h>

using namespace std;
const int SCREEN_WIDTH  = 680;
const int SCREEN_HEIGHT = 800;
SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;
SDL_Texture* texture[10];
SDL_Surface* surface[10];

void initWindow();
void loadMedia(string path,int x,int y, int w, int h);
void startGame();

void initWindow()
{
	if( SDL_Init( SDL_INIT_VIDEO ) >= 0 )
	{
		window = SDL_CreateWindow( "NXPGaming - 2048", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
		if( window != NULL )
		{
			renderer = SDL_CreateRenderer( window, -1, SDL_RENDERER_ACCELERATED );
			if( renderer != NULL )
            {
				SDL_SetRenderDrawColor( renderer, 0xFF, 0xFF, 0xFF, 0xFF );
                //Initialize PNG loading
				int imgFlags = IMG_INIT_PNG;
				if( !( IMG_Init( imgFlags ) & imgFlags ) )
				{
					printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
					//success = false;
				}

            }
		}
	}
	surface[0] = IMG_Load("background.png");
	texture[0] = SDL_CreateTextureFromSurface( renderer, surface[0] );
	surface[1] = IMG_Load("2.png");
	texture[1] = SDL_CreateTextureFromSurface( renderer, surface[1] );
	surface[2] = IMG_Load("4.png");
	texture[2] = SDL_CreateTextureFromSurface( renderer, surface[2] );
	surface[3] = IMG_Load("8.png");
	texture[3] = SDL_CreateTextureFromSurface( renderer, surface[3] );
	surface[4] = IMG_Load("16.png");
	texture[4] = SDL_CreateTextureFromSurface( renderer, surface[4] );
	surface[5] = IMG_Load("32.png");
	texture[5] = SDL_CreateTextureFromSurface( renderer, surface[5] );
	surface[6] = IMG_Load("64.png");
	texture[6] = SDL_CreateTextureFromSurface( renderer, surface[6] );
	surface[7] = IMG_Load("128.png");
	texture[7] = SDL_CreateTextureFromSurface( renderer, surface[7] );
	surface[8] = IMG_Load("256.png");
	texture[8] = SDL_CreateTextureFromSurface( renderer, surface[8] );
	surface[9] = IMG_Load("512.png");
	texture[9] = SDL_CreateTextureFromSurface( renderer, surface[9] );

}
void loadMedia(int ob,int x,int y)
{
	SDL_Rect dest = {x, y,surface[ob]->w,surface[ob]->h};

    SDL_RenderCopy(renderer, texture[ob], NULL, &dest);
}
void startGame()
{
    loadMedia(3,0,0);
     SDL_RenderPresent(renderer);
}


int main(int argc, char* argv[])
{

    startGame();
    return 0;
}
