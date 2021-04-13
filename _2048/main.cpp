#include <iostream>
#include <SDL.h>
#include <ctime>
#include <cmath>
#include <SDL_image.h>
#include <SDL_ttf.h>

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
void LoadMedia(int ob,int x,int y);


void logSDLError(std::ostream& os,const std::string &msg, bool fatal)
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
    surface[0] = IMG_Load("nnnnn.png");
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
	texture[13] = SDL_CreateTextureFromSurface( renderer, surface[13] );
	surface[14] = IMG_Load("start.png");
	texture[14] = SDL_CreateTextureFromSurface( renderer, surface[14] );
	surface[15] = IMG_Load("start1.png");
	texture[15] = SDL_CreateTextureFromSurface( renderer, surface[15] );
	surface[16] = IMG_Load("start2.png");
	texture[16] = SDL_CreateTextureFromSurface( renderer, surface[16] );
	surface[17] = IMG_Load("start3.png");
	texture[17] = SDL_CreateTextureFromSurface( renderer, surface[17] );
	surface[18] = IMG_Load("nnnnn1.png");
	texture[18] = SDL_CreateTextureFromSurface( renderer, surface[18] );
	surface[19] = IMG_Load("nnnnn2.png");
	texture[19] = SDL_CreateTextureFromSurface( renderer, surface[19] );
}

void quitSDL(SDL_Window* window, SDL_Renderer* renderer)
{
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}

void LoadMedia(int ob,int x,int y)
{
    SDL_Rect dest={x,y,surface[ob]->w,surface[ob]->h};
    SDL_RenderCopy(renderer,texture[ob],NULL,&dest);
}
int luythua(int &a)
{
    int n=0;
    while (a>1)
    {
        a/=2;
        n++;
    }
    return n;
}
void* print(int **a)
{
    SDL_RenderClear(renderer);
    LoadMedia(0,0,0);
    //LoadMedia(13,115,303);
    //LoadMedia(14,115,389);
    //LoadMedia(15,115,475);
    for(int i=0; i<4; i++){
        for(int j=0; j<4; j++){
              cout << a[i][j] << ' ';
              if (a[i][j]!=0) LoadMedia(a[i][j],j*111+48,i*111+192);
        }
        cout << endl;
    }


    SDL_RenderPresent(renderer);
}

void* random(int **a)
{
    int n=1;
    while(n>0)
    {
    int x= rand() % 4;
    int y= rand() % 4;
    if(a[x][y]==0) {
        a[x][y]=1;
        n--;
        }
    }
}

void rushUp(int **&a , int &n) {
	for (int i = 1; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			if (a[i][j] != 0) {
				for (int k = i; k > 0; --k) {
					if (a[k - 1][j] == 0) {
						a[k - 1][j] = a[k][j];
						a[k][j] = 0;
						n++;
					}
				}
			}
		}
	}
}

void moveUp(int **&a,int &score) {
    int n=0;
	rushUp(a,n);

	for (int i = 1; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			if (a[i][j] != 0) {
				if (a[i - 1][j] == a[i][j]) {
					a[i - 1][j]++;
					score += pow(2,a[i - 1][j]);
					a[i][j] = 0;
					n++;

				}
			}
		}
	}

	rushUp(a,n);
	if (n>0){
	random(a);
    print(a);
    cout << "score = " << score << endl;
	}
}

void rushDown(int **&a, int &n) {
	for (int i = 0; i < 4; i++) {
		for (int j = 4 - 2; j >= 0; j--) {
			if (a[j][i] != 0) {
				for (int k = j; k < 4 - 1; ++k) {
					if (a[k + 1][i] == 0) {
						a[k + 1][i] = a[k][i];
						a[k][i] = 0;
						n++;
					}
				}
			}
		}
	}
}

void moveDown(int **&a,int &score) {
    int n=0;
	rushDown(a,n);
	for (int i = 0; i < 4; i++) {
		for (int j = 4 - 2; j >= 0; j--) {
			if (a[j][i] != 0) {
				if (a[j][i] == a[j + 1][i]) {
					a[j + 1][i] ++;
					score += pow(2,a[j + 1][i]);
					a[j][i] = 0;
					n++;
				}
			}
		}
	}

	rushDown(a,n);
	if (n>0){
	random(a);
    print(a);
    cout << "score = " << score << endl;
	}
}

void rushLeft(int**&a, int &n)
{
    for(int i=0; i<4; i++){
            for (int j = 1; j < 4; j++) {
                if (a[i][j] != 0) {
                    for (int k = j; k > 0; --k) {
                        if (a[i][k - 1] == 0) {
                            a[i][k - 1] = a[i][k];
                            a[i][k] = 0;
                            n++;
                        }
                    }
                }
            }
        }
}

void moveLeft(int**&a,int &score)
{
    int n=0;
    rushLeft(a,n);
       for(int i = 0; i < 4; i++) {
		for (int j = 1; j < 4; j++) {
			if (a[i][j] != 0) {
				if (a[i][j] == a[i][j - 1]) {
					a[i][j - 1] ++;
					score += pow(2,a[i][j - 1]);
					a[i][j] = 0;
					n++;
				}
			}
		}
	}
	rushLeft(a,n);
	if (n>0){
	random(a);
	print(a);
	cout << "score = " << score << endl;
	}

}

void rushRight(int**&a, int &n)
{
   for (int i = 0; i < 4; i++) {
		for (int j = 2; j >= 0; j--) {
			if (a[i][j] != 0) {
				for (int k = j; k < 4 - 1; ++k) {
					if (a[i][k + 1] == 0) {
						a[i][k + 1] = a[i][k];
						a[i][k] = 0;
						n++;
                    }
				}
			}
		}
	}
}

void moveRight(int**&a,int &score)
{
    int n=0;
    rushRight(a,n);
	for (int i = 0; i < 4; i++) {
		for (int j = 2; j >= 0; j--) {
			if (a[i][j] != 0) {
				if (a[i][j] == a[i][j + 1]) {
					a[i][j + 1] ++;
					score += pow(2,a[i][j + 1]);
					a[i][j] = 0;
					n++;
				}
			}
		}
	}

	rushRight(a,n);
	if (n>0){
	random(a);
    print(a);
    cout << "score = " << score << endl;
	}
}
void mouse(SDL_Event e, int**&a)
{
    int x, y;
        if(e.type == SDL_MOUSEMOTION)
        {
            SDL_GetMouseState(&x,&y);
            cout << x << ',' << y  << '\n';
            if ( 317<=x && x<=454 && 94<=y && y<=127 )
            {
                LoadMedia(18,316,94);

            }
            else if  ( 317<=x && x<=454 && 133<=y && y<=167 )
            {
                LoadMedia(19,316,133);
                if (e.type == SDL_MOUSEBUTTONDOWN) {
                        return;
                }
            }
            else {
                SDL_RenderClear(renderer);
                LoadMedia(0,0,0);
                for(int i=0; i<4; i++){
                    for(int j=0; j<4; j++){
                if (a[i][j]!=0) LoadMedia(a[i][j],j*111+48,i*111+192);
                        }
                }
            }
            SDL_RenderPresent(renderer);
        }

}
void startgame(int **&a, SDL_Event e)
{
    for (int i=0; i<4; i++)
        for (int j=0; j<4; j++) a[i][j]=0;
    for(int i=0; i<2; i++)
    {
    int x = rand() % 4;
    int y = rand() % 4;
    a[x][y]=1;
    }
    int score=0;
    print(a);
      while(true)
   {
      while(SDL_PollEvent(&e)!=0)
     {

         if (e.type == SDL_QUIT) break; // neu quit thi dung
            int x, y;
//            if(e.type == SDL_MOUSEMOTION)
//            {
            SDL_GetMouseState(&x,&y);
            //cout << x << ',' << y  << '\n';
            if ( 317<=x && x<=454 && 94<=y && y<=127 )
            {
                LoadMedia(18,316,94);
                if (e.type == SDL_MOUSEBUTTONDOWN) {
                        startgame(a,e);
                        return;
                }
            }
            else if  ( 317<=x && x<=454 && 133<=y && y<=167 )
            {
                LoadMedia(19,316,133);
                if (e.type == SDL_MOUSEBUTTONDOWN) {
                        return;
                }
            }
            else {
                SDL_RenderClear(renderer);
                LoadMedia(0,0,0);
                for(int i=0; i<4; i++){
                    for(int j=0; j<4; j++){
                if (a[i][j]!=0) LoadMedia(a[i][j],j*111+48,i*111+192);
                        }
                }
            }
            SDL_RenderPresent(renderer);
            //}
        if (e.type == SDL_KEYDOWN) {
        	switch (e.key.keysym.sym) {
        		case SDLK_LEFT:{
        		    moveLeft(a,score);
                    break;
        		}
        		case SDLK_RIGHT:{
                    moveRight(a,score);
        		    break;
        		}
            	case SDLK_DOWN:{
            	    moveDown(a,score);
        		    break;
        		}
            	case SDLK_UP:{
            	    moveUp(a,score);
        		    break;
        		}
        		case SDLK_ESCAPE: return ;
        		default: break;
                }
            }
        }
    }
}
void start(int **&a, SDL_Event e){
    LoadMedia(14,0,0);
    SDL_RenderPresent(renderer);
    bool quit = false;
    while (!quit)
    {
       while(SDL_PollEvent(&e)!=0){
        int x, y;
            SDL_GetMouseState(&x,&y);
            cout << x << ',' << y  << '\n';
            if ( 11<=x && x<=379 && 305<=y && y<=358){
                LoadMedia(14,0,0);
                LoadMedia(15,115,303);
                if (e.type == SDL_MOUSEBUTTONDOWN) {
                        startgame(a,e);
                        return;
                }
            }
            else if (119<=x && x<=379 && 389<=y && y<=444){
                LoadMedia(14,0,0);
                LoadMedia(16,115,389);
            }
            else if (119<=x && x<=379 && 477<=y && y<=530){
                LoadMedia(14,0,0);
                LoadMedia(17,115,475);
                if (e.type == SDL_MOUSEBUTTONDOWN) return;
            }
            else {
                SDL_RenderClear(renderer);
                LoadMedia(14,0,0);
            }
        SDL_RenderPresent(renderer);
       }
    }
}

int main(int argc, char* argv[])
{
    srand (time(NULL));

    initSDL(window, renderer, SCREEN_WIDTH, SCREEN_HEIGHT, WINDOW_TITLE);
    int** a= new int*[4];
    for(int i=0; i<4; i++)
        *(a+i)= new int[4];
    SDL_Event e;
    start(a,e);
    quitSDL(window, renderer);
    return 0;
}
