#ifndef EXPLOSIONOBJECT_H_INCLUDED
#define EXPLOSIONOBJECT_H_INCLUDED

#include "BaseObject.h"
#include "CommonFunc.h"

const int EXP_WIDTH = 165;
const int EXP_HEIGHT = 165;

class ExplosionObject : public BaseObject
{
public:
    ExplosionObject();
    ~ExplosionObject();

    void SetClip();
    void SetFrame(const int& fr)
    {
        frame_ = fr;
    }
    void ShowExplosion(SDL_Renderer* des,const int& x, const int& y);

private:
    int frame_;
    SDL_Rect clip_right[4];
};

#endif // EXPLOSIONOBJECT_H_INCLUDED
