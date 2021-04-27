#include "game.h"
#include <iostream>
#include <fstream>
#include <cmath>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
using namespace std;
const int SCREEN_WIDTH = 523;
const int SCREEN_HEIGHT = 650;
const string WINDOW_TITLE = "2048";
SDL_Window* window;
SDL_Renderer* renderer;
SDL_Surface *surface[26];
SDL_Texture *texture[26];
TTF_Font *Font = NULL;
Mix_Chunk* sound[2];
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
    if( TTF_Init() == -1 ) logSDLError(cout, TTF_GetError(), true );
    if( Mix_OpenAudio( 22050, MIX_DEFAULT_FORMAT, 2, 4096 ) ==-1 ) logSDLError(cout, Mix_GetError(), true);

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
	surface[14] = IMG_Load("16384.png");
	texture[14] = SDL_CreateTextureFromSurface( renderer, surface[14] );
	surface[15] = IMG_Load("32768.png");
	texture[15] = SDL_CreateTextureFromSurface( renderer, surface[15] );
	surface[16] = IMG_Load("65536.png");
	texture[16] = SDL_CreateTextureFromSurface( renderer, surface[16] );
	surface[17] = IMG_Load("start.png");
	texture[17] = SDL_CreateTextureFromSurface( renderer, surface[17] );
	surface[18] = IMG_Load("start1.png");
	texture[18] = SDL_CreateTextureFromSurface( renderer, surface[18] );
	surface[19] = IMG_Load("start2.png");
	texture[19] = SDL_CreateTextureFromSurface( renderer, surface[19] );
	surface[20] = IMG_Load("start3.png");
	texture[20] = SDL_CreateTextureFromSurface( renderer, surface[20] );
	surface[21] = IMG_Load("nnnnn1.png");
	texture[21] = SDL_CreateTextureFromSurface( renderer, surface[21] );
	surface[22] = IMG_Load("nnnnn2.png");
	texture[22] = SDL_CreateTextureFromSurface( renderer, surface[22] );
	surface[23] = IMG_Load("end.png");
	texture[23] = SDL_CreateTextureFromSurface( renderer, surface[23] );
	surface[25] = IMG_Load("score.png");
	texture[25] = SDL_CreateTextureFromSurface( renderer, surface[25] );
	sound[0]= Mix_LoadWAV("backgroud.wav");
	sound[1]= Mix_LoadWAV("end.wav");
}

void quitSDL()
{
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	TTF_CloseFont( Font );
	Mix_Quit();
	TTF_Quit();
	IMG_Quit();
	SDL_Quit();

void loadscore(int score, int x, int y)
{
    Font = TTF_OpenFont("Antonio-Bold.ttf",30);
    SDL_Color textColor = {255, 255, 255, 255};
    string s= to_string(score);
    surface[24] = TTF_RenderText_Solid(Font, s.c_str() , textColor);
    texture[24] = SDL_CreateTextureFromSurface(renderer, surface[24]);
    //222,20
    int _x = x+(129-surface[24]->w)/2;
    int _y = y+(76-surface[24]->h)/2;
    SDL_Rect dest={_x,_y,surface[24]->w,surface[24]->h};
    SDL_RenderCopy(renderer,texture[24],NULL,&dest);
}

void LoadMedia(int ob,int x,int y)
{
    SDL_Rect dest={x,y,surface[ob]->w,surface[ob]->h};
    SDL_RenderCopy(renderer,texture[ob],NULL,&dest);
}

void* print(int **a,const int score, int &highscore)
{
    SDL_RenderClear(renderer);
    LoadMedia(0,0,0);
    for(int i=0; i<4; i++){
        for(int j=0; j<4; j++){
              cout << a[i][j] << ' ';
              if (a[i][j]!=0) LoadMedia(a[i][j],j*111+48,i*111+192);
        }
        cout << endl;
    }

    if(score>highscore) highscore=score;
    loadscore(score ,285-55,25);
    loadscore(highscore ,430-55,25);
    cout << "score = " << score << endl;
    cout << "high score = " << highscore << endl << endl;
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

void moveUp(int **&a,int &score, int &highscore) {
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
    print(a,score,highscore);
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

void moveDown(int **&a,int &score, int &highscore) {
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
    print(a,score, highscore);
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

void moveLeft(int**&a,int &score, int &highscore)
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
	print(a,score,highscore);
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

void moveRight(int**&a,int &score, int &highscore)
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
    print(a,score,highscore);
	}
}

bool checklose(int** a)
{
    for (int i=0; i<4; i++)
        for (int j=0; j<4; j++)
           if (a[i][j]==0) return true;
    for (int i=0; i<4; i++)
        for (int j=0; j<3; j++)
            if (a[i][j]==a[i][j+1]) return true;
    for (int i=0; i<4; i++)
        for (int j=0; j<3; j++)
            if (a[j][i]==a[j+1][i]) return true;
    return false;
}
void outscore(int*&a, int score)
{
    if(score>a[4]) {
        a[4]=score;
        for(int i=0; i<5; i++)
            for(int j=i; j<5; j++)
                if (a[i]<a[j]) swap(a[i], a[j]);
    }
    ofstream outfile("highscore.txt");
    for(int i=0; i<5; i++)
        outfile << a[i] <<endl;
}
void startgame()
{
    int** a= new int*[4];
    for(int i=0; i<4; i++)
        *(a+i)= new int[4];
    for (int i=0; i<4; i++)
        for (int j=0; j<4; j++) a[i][j]=0;
    for(int i=0; i<2; i++)
    {
    int x = rand() % 4 ;
    int y = rand() % 4 ;
    a[x][y]=1;
    }
    int* scoree= new int[5];
    ifstream infile("highscore.txt");
    for(int i=0; i<5; i++)
        infile >> scoree[i];
    int highscore=scoree[0];
    SDL_Event e;
    int score=0;
    bool quit=true;
    print(a, score, highscore);
    while(quit==true)
    {
      while(SDL_PollEvent(&e)!=0)
     {

         if (e.type == SDL_QUIT) break; // neu quit thi dung
            int x, y;
            SDL_GetMouseState(&x,&y);
            //cout << x << ',' << y  << '\n';
            if ( 317<=x && x<=454 && 94<=y && y<=127 )
            {
                LoadMedia(21,316,94);
                if (e.type == SDL_MOUSEBUTTONDOWN) {
                        startgame();
                        return;
                }
            }
            else if  ( 317<=x && x<=454 && 133<=y && y<=167 )
            {
                LoadMedia(22,316,133);
                if (e.type == SDL_MOUSEBUTTONDOWN) {
                        return;
                }
            }
            else {
                SDL_RenderClear(renderer);
                LoadMedia(0,0,0);
                loadscore(score ,285-55,25);
                loadscore(highscore ,430-55,25);
                for(int i=0; i<4; i++){
                    for(int j=0; j<4; j++){
                if (a[i][j]!=0) LoadMedia(a[i][j],j*111+48,i*111+192);
                        }
                }
            }
            SDL_RenderPresent(renderer);

        if (e.type == SDL_KEYDOWN) {
        	switch (e.key.keysym.sym) {
        		case SDLK_LEFT:{
        		    moveLeft(a,score,highscore);
        		    quit=checklose(a);
        		    if(!quit) {
                    cout << "YOU LOSE" << endl;
                    outscore(scoree, score);
        		    }
                    break;
        		}
        		case SDLK_RIGHT:{
                    moveRight(a,score,highscore);
        		    quit=checklose(a);
        		    if(!quit) {
                    cout << "YOU LOSE" << endl;
                        outscore(scoree, score);
        		    }
        		    break;
        		}
            	case SDLK_DOWN:{
            	    moveDown(a,score,highscore);
        		    quit=checklose(a);
        		    if(!quit) {
                    cout << "YOU LOSE" << endl;
                        outscore(scoree, score);
        		    }
        		    break;
        		}
            	case SDLK_UP:{
            	    moveUp(a,score,highscore);
        		    quit=checklose(a);
        		    if(!quit) {
                    cout << "YOU LOSE" << endl;
                        outscore(scoree, score);
        		    }
        		    break;
        		}
        		case SDLK_ESCAPE: return ;
        		default: break;
                }
            }
        }
    }
    LoadMedia(23,65,81);
    Mix_Pause(-1);
    Mix_Volume(1, 60);
    Mix_PlayChannel(1,sound[1],0);
    while(true){
        while(SDL_PollEvent(&e)!=0)
        {
            int x, y;
            SDL_GetMouseState(&x,&y);
            SDL_RenderPresent(renderer);
            if(197<=x && x<=324 && 325<=y && y<=378)
                if (e.type == SDL_MOUSEBUTTONDOWN) {
                    Mix_Resume(-1);
                    startgame();
                    return;
                }
            if(197<=x && x<=324 && 406<=y && y<=459)
                if (e.type == SDL_MOUSEBUTTONDOWN) {
                        return;
                }
        }
    }
}
void score()
{
    SDL_Event e;
    LoadMedia(25,0,0);
    int* scoree= new int[5];
    ifstream infile("highscore.txt");
    for(int i=0; i<5; i++)
        infile >> scoree[i];
    for(int i=0; i<5; i++) loadscore(scoree[i], 210, 200+80*i);
    SDL_RenderPresent(renderer);
    while (true){
       while(SDL_PollEvent(&e)!=0){
        int x, y;
            SDL_GetMouseState(&x,&y);
            cout << x << ',' << y  << '\n';
            if(36<=x&&x<=112 && 38<=y&&y<=67)
                if (e.type == SDL_MOUSEBUTTONDOWN) return;
       }
    }
}
void start(){
    initSDL(window, renderer, SCREEN_WIDTH, SCREEN_HEIGHT, WINDOW_TITLE);
    SDL_Event e;
    LoadMedia(17,0,0);
    SDL_RenderPresent(renderer);
    bool quit = false;
    while (!quit)
    {
        Mix_Volume(-1, 1);
        Mix_PlayChannel(-1,sound[0],0);
       while(SDL_PollEvent(&e)!=0){
        int x, y;
            SDL_GetMouseState(&x,&y);
            cout << x << ',' << y  << '\n';
            if ( 119<=x && x<=379 && 305<=y && y<=358){
                LoadMedia(17,0,0);
                LoadMedia(18,115,303);
                if (e.type == SDL_MOUSEBUTTONDOWN) {
                        startgame();
                        return;
                }
            }
            else if (119<=x && x<=379 && 389<=y && y<=444){
                LoadMedia(17,0,0);
                LoadMedia(19,115,389);
                if (e.type == SDL_MOUSEBUTTONDOWN)
                {
                    score();
                }
            }
            else if (119<=x && x<=379 && 477<=y && y<=530){
                LoadMedia(17,0,0);
                LoadMedia(20,115,475);
                if (e.type == SDL_MOUSEBUTTONDOWN) return;
            }
            else {
                SDL_RenderClear(renderer);
                LoadMedia(17,0,0);
            }
        SDL_RenderPresent(renderer);
       }
    }
}

