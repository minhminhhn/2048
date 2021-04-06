#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <ctime>
//#include "SDL_until.h";
using namespace std;
const int SCREEN_WIDTH = 523;
const int SCREEN_HEIGHT = 650;
const string WINDOW_TITLE = "2048";
SDL_Window* window;
SDL_Renderer* renderer;
SDL_Surface *surface[20];
SDL_Texture *texture[20];
void logSDLError(std::ostream& os,const std::string &msg, bool fatal);
void initSDL(SDL_Window* &window, SDL_Renderer* &renderer, int SCREEN_WIDTH, int SCREEN_HEIGHT, const string &WINDOW_TITLE );
void quitSDL(SDL_Window* window, SDL_Renderer* renderer);
void* random(int **a);
void LoadMedia(int ob,int x,int y,SDL_Renderer *renderer);
void* printvectorImg(int **a);

void logSDLError(std::ostream& os,
                 const std::string &msg, bool fatal)
{
    os << msg << " Error: " << SDL_GetError() << std::endl;
    if (fatal) {
        SDL_Quit();
        exit(1);
    }
}

void initSDL(SDL_Window* &window, SDL_Renderer* &renderer, int SCREEN_WIDTH, int SCREEN_HEIGHT, const string &WINDOW_TITLE )
{
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
        logSDLError(std::cout, "SDL_Init", true);

    window = SDL_CreateWindow(WINDOW_TITLE.c_str(), SDL_WINDOWPOS_CENTERED,
       SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

    if (window == nullptr) logSDLError(std::cout, "CreateWindow", true);

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED |
                                              SDL_RENDERER_PRESENTVSYNC);

    if (renderer == nullptr) logSDLError(std::cout, "CreateRenderer", true);

    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
    SDL_RenderSetLogicalSize(renderer, SCREEN_WIDTH, SCREEN_HEIGHT);
    surface[0] = IMG_Load("background.png");
    texture[0]= SDL_CreateTextureFromSurface(renderer,surface[0]);
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
	surface[10] = IMG_Load("1024.png");
	texture[10] = SDL_CreateTextureFromSurface( renderer, surface[10] );
	surface[11] = IMG_Load("2048.png");
	texture[11] = SDL_CreateTextureFromSurface( renderer, surface[11] );
	surface[12] = IMG_Load("4096.png");
	texture[12] = SDL_CreateTextureFromSurface( renderer, surface[12] );
	surface[13] = IMG_Load("8192.png");
}

void quitSDL(SDL_Window* window, SDL_Renderer* renderer)
{
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}

void LoadMedia(int ob,int x,int y,SDL_Renderer *renderer)
{
    SDL_Rect dest={x,y,surface[ob]->w,surface[ob]->h};
    SDL_RenderCopy(renderer,texture[ob],NULL,&dest);
}

void* print(int **a)
{
    SDL_RenderClear(renderer);
    LoadMedia(0,0,0,renderer);
    for(int i=0; i<4; i++){
        for(int j=0; j<4; j++){
              cout << a[i][j] << ' ';
              if (a[i][j]!=0) LoadMedia(a[i][j],j*111+48,i*111+192,renderer);
        }
        cout << endl;
    }
    cout << endl;
    SDL_RenderPresent(renderer);
}

void* random(int **a)
{
    int n= rand() % 2 + 1;
    int x, y;


    while(n>0)
    {
    x= rand() % 4;
    y= rand() % 4;
    if(a[x][y]==0) {
        a[x][y]=1;
        n--;
        }
    }
}

bool checkLeft(int **a)
{
    int x = 0,k=0 ;
    for(int i=0; i<4; i++){
        for(int j=0;j<4;j++)
        {
            if(a[i][j]==0)
            {
                k=1;
            }
        }
        if(k=1) return true;
    }
    return false;
}

void rushUp(int **&a) {
	for (int i = 1; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			if (a[i][j] != 0) {
				for (int k = i; k > 0; --k) {
					if (a[k - 1][j] == 0) {
						a[k - 1][j] = a[k][j];
						a[k][j] = 0;
					}
				}
			}
		}
	}
}

void moveUp(int **&a) {
	rushUp(a);

	for (int i = 1; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			if (a[i][j] != 0) {
				if (a[i - 1][j] == a[i][j]) {
					a[i - 1][j]++;
					//score += a[i - 1][j];
					a[i][j] = 0;

				}
			}
		}
	}

	rushUp(a);
	random(a);
	print(a);
}

void rushDown(int **&a) {
	for (int i = 0; i < 4; i++) {
		for (int j = 4 - 2; j >= 0; j--) {
			if (a[j][i] != 0) {
				for (int k = j; k < 4 - 1; ++k) {
					if (a[k + 1][i] == 0) {
						a[k + 1][i] = a[k][i];
						a[k][i] = 0;
					}
				}
			}
		}
	}
}

void moveDown(int **&a) {
	rushDown(a);

	for (int i = 0; i < 4; i++) {
		for (int j = 4 - 2; j >= 0; j--) {
			if (a[j][i] != 0) {
				if (a[j][i] == a[j + 1][i]) {
					a[j + 1][i] ++;
					//score += a[j + 1][i];
					a[j][i] = 0;
				}
			}
		}
	}

	rushDown(a);
	random(a);
	print(a);
}

void rushLeft(int**&a)
{
    for(int i=0; i<4; i++){
            for (int j = 1; j < 4; j++) {
                if (a[i][j] != 0) {
                    for (int k = j; k > 0; --k) {
                        if (a[i][k - 1] == 0) {
                            a[i][k - 1] = a[i][k];
                            a[i][k] = 0;
                        }
                    }
                }
            }
        }
}

void moveLeft(int**&a)
{
    rushLeft(a);
       for(int i = 0; i < 4; i++) {
		for (int j = 1; j < 4; j++) {
			if (a[i][j] != 0) {
				if (a[i][j] == a[i][j - 1]) {
					a[i][j - 1] ++;
					//score += a[i][j - 1];
					a[i][j] = 0;
				}
			}
		}
	}
	rushLeft(a);
	random(a);
	print(a);

}

void rushRight(int**&a)
{
   for (int i = 0; i < 4; i++) {
		for (int j = 2; j >= 0; j--) {
			if (a[i][j] != 0) {
				for (int k = j; k < 4 - 1; ++k) {
					if (a[i][k + 1] == 0) {
						a[i][k + 1] = a[i][k];
						a[i][k] = 0;
					}
				}
			}
		}
	}
}

void moveRight(int**&a)
{
    rushRight(a);

	for (int i = 0; i < 4; i++) {
		for (int j = 2; j >= 0; j--) {
			if (a[i][j] != 0) {
				if (a[i][j] == a[i][j + 1]) {
					a[i][j + 1] ++;
					//score += a[i][j + 1];
					a[i][j] = 0;
				}
			}
		}
	}

	rushRight(a);
	random(a);
	print(a);
}

void start(int **&a)
{
    for(int i=0; i<2; i++)
    {
    int x = rand() % 2 + 1;
    int y = rand() % 2 + 1;
    a[x][y]=1;
    }
    print(a);
}

int main(int argc, char* argv[])
{
    srand (time(NULL));

    initSDL(window, renderer, SCREEN_WIDTH, SCREEN_HEIGHT, WINDOW_TITLE);
    int** a= new int*[4];
    for(int i=0; i<4; i++)
        *(a+i)= new int[4];
    for (int i=0; i<4; i++)
        for (int j=0; j<4; j++) a[i][j]=0;
    start(a);
    SDL_Event e;
    int x=0, y=0;
    while(true)
    {
     while(SDL_PollEvent(&e)!=0)
     {

         if (e.type == SDL_QUIT) break; // neu quit thi dung
        if (e.type == SDL_KEYDOWN) {
        	switch (e.key.keysym.sym) {
        		case SDLK_LEFT:{
        		    if(checkLeft(a)){
        		    moveLeft(a);}
        		    break;
        		}
        		case SDLK_RIGHT:
        		    {
                    moveRight(a);
        		    break;
        		}
            	case SDLK_DOWN:{
            	    moveDown(a);
        		    break;
        		}
            	case SDLK_UP:{
            	    moveUp(a);
        		    break;
        		}
        		default: break;
			}
     }
     SDL_RenderPresent(renderer);
     }
    }
    quitSDL(window, renderer);
    return 0;
}
