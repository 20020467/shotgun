#ifndef COMMONFUNC_H_INCLUDED
#define COMMONFUNC_H_INCLUDED


#include <vector>
#include <cstdlib>
#include <ctime>
#include <windows.h>
#include <string>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>


static SDL_Window* g_window = NULL;
static SDL_Renderer* g_screen = NULL;
static SDL_Event g_event;

const int SCREEN_WIDTH = 1199;
const int SCREEN_HEIGHT = 800;
const int SCREEN_BPP = 32;
static int quaivat_rand;
static int x_rand = 0;
static int num_threats_over = 0;
static int mark_value = 0;
static int speed_threat = 1;

const int COLOR_KEY_R = 255;
const int COLOR_KEY_G = 255;
const int COLOR_KEY_B = 255;

static Mix_Chunk* gBulletMainMusic = NULL;
static Mix_Chunk* gCollisionMusic = NULL;

//font
static TTF_Font* font_mark = NULL;
static TTF_Font* font_time = NULL;

namespace SDLCommonFunc
{
    bool CheckCollision(const SDL_Rect& object1, const SDL_Rect& object2);
    void ApplySurfaceClip(SDL_Surface* src, SDL_Renderer* des, SDL_Rect* clip, int x, int y);
}

#endif // COMMONFUNC_H_INCLUDED
