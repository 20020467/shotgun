#include "ExplosionObject.h"

ExplosionObject::ExplosionObject()
{
    frame_ = 0;
}

ExplosionObject::~ExplosionObject()
{

}

// Set vị trí clip nổ
void ExplosionObject::SetClip()
{
    clip_right[0].x = 0;
    clip_right[0].y = 0;
    clip_right[0].w = EXP_WIDTH;
    clip_right[0].h = EXP_HEIGHT;

    clip_right[1].x = EXP_WIDTH;
    clip_right[1].y = 0;
    clip_right[1].w = EXP_WIDTH;
    clip_right[1].h = EXP_HEIGHT;

    clip_right[2].x = 2 * EXP_WIDTH;
    clip_right[2].y = 0;
    clip_right[2].w = EXP_WIDTH;
    clip_right[2].h = EXP_HEIGHT;

    clip_right[3].x = 3 * EXP_WIDTH;
    clip_right[3].y = 0;
    clip_right[3].w = EXP_WIDTH;
    clip_right[3].h = EXP_HEIGHT;
}

void ExplosionObject::ShowExplosion(SDL_Renderer* des, const int& x, const int& y)
{
    if (frame_ >= 4)
    {
        frame_ = 0;
    }

    //LoadImg("img//exp_main1.png", des);
    rect_.x = x;
    rect_.y = y;
    SDL_Rect renderQuad = {rect_.x, rect_.y, 100, 100};
    SDL_RenderCopy(des, p_object_, NULL, &renderQuad);

    //LoadImg("img//exp_main2.png", des);
    rect_.x = x;
    rect_.y = y;
    renderQuad = {rect_.x, rect_.y, 100, 100};
    SDL_RenderCopy(des, p_object_, NULL, &renderQuad);

    LoadImg("img//exp_main3.png", des);
    rect_.x = x;
    rect_.y = y;
    renderQuad = {rect_.x, rect_.y, 100, 100};
    SDL_RenderCopy(des, p_object_, NULL, &renderQuad);

   // LoadImg("img//exp_main4.png", des);
    rect_.x = x;
    rect_.y = y;
    renderQuad = {rect_.x, rect_.y, 100, 100};
    SDL_RenderCopy(des, p_object_, NULL, &renderQuad);
}
