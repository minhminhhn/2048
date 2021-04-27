#ifndef GAME__H_
#define GAME__H_
#include <iostream>
#include <fstream>
#include <cmath>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>


using namespace std;


void logSDLError(std::ostream& os,const std::string &msg, bool fatal);
void initSDL(SDL_Window* &window, SDL_Renderer* &renderer, int SCREEN_WIDTH, int SCREEN_HEIGHT, const string &WINDOW_TITLE );
void quitSDL();
void loadscore(int score, int x, int y);
void LoadMedia(int ob,int x,int y);
void* print(int **a,const int score, int &highscore);
void* random(int **a);
void rushUp(int **&a , int &n);
void moveUp(int **&a,int &score, int &highscore);
void rushDown(int **&a, int &n);
void moveDown(int **&a,int &score, int &highscore);
void rushLeft(int**&a, int &n);
void moveLeft(int**&a,int &score, int &highscore);
void rushRight(int**&a, int &n);
void moveRight(int**&a,int &score, int &highscore);
bool checklose(int** a);
void outscore(int*&a, int score);
void startgame();
void score();
void start();

#endif // GAME__H_

