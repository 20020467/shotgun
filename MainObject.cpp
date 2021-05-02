#include "MainObject.h"
#include "CommonFunc.h"


MainObject::MainObject()
{
    x_pos_ = 0;
    y_pos_ = 0;
    x_val_ = 0;
    y_val_ = 0;

}

MainObject::~MainObject()
{

}



bool MainObject::LoadImg(std::string path, SDL_Renderer* screen)
{
    bool ret = BaseObject::LoadImg(path, screen);

    return ret;
}

void MainObject::Show(SDL_Renderer* des)
{
    LoadImg("img//goku.png", des);

    rect_.x = x_pos_-40;
    rect_.y = y_pos_;

    SDL_Rect renderQuad = {rect_.x, rect_.y, 80, 80};
    SDL_RenderCopy(des, p_object_, NULL, &renderQuad);
}

void MainObject::HandelInputAction(SDL_Event events, SDL_Renderer* screen , Mix_Chunk* gBulletMainMusic)
{
    if( events.type == SDL_MOUSEMOTION )
	{

		SDL_GetMouseState( &x_pos_, &y_pos_ );

	}

	if (events.type == SDL_MOUSEBUTTONDOWN && events.button.button == SDL_BUTTON_LEFT )
    {
        Mix_PlayChannel( -1 , gBulletMainMusic , 0);
        BulletObject* p_bullet = new BulletObject();
        p_bullet->LoadImg("img//ngocrong4sao.png", screen);
        p_bullet->SetRect(rect_.x+24, rect_.y);
        p_bullet->set_y_val(20);
        p_bullet->set_is_move(true);

        p_bullet_list_.push_back(p_bullet);
    }


}

void MainObject::HandelThreatsAction(SDL_Renderer* screen )
{
    if ((SDL_GetTicks()%90) == 0)
    {
        quaivat_rand = rand()%4;
        int array[9]={0,120,240,360,480,600,720,840,960};
        ThreatsObject* p_threats = new ThreatsObject();
        switch(quaivat_rand)
        {
            case 0:p_threats->LoadImg("img//quaivat.png", screen);
            break;

            case 1:p_threats->LoadImg("img//cell.png", screen);
            break;

            case 2:p_threats->LoadImg("img//berrus.png", screen);
            break;

            case 3:p_threats->LoadImg("img//frieza.png", screen);
            break;
        }


        if (p_threats_list_.size() == 0)
        {
            x_rand = array[rand()%9];

        }
        else
        {
            int y = array[rand()%9];
            while (y == x_rand)
            {
                y = array[rand()%9];
            }
            x_rand = y;
        }
        p_threats->SetRect(x_rand, -80);

        p_threats->set_y_val_threats(3);
        p_threats->set_is_move_threats(true);

        p_threats_list_.push_back(p_threats);
    }
}

void MainObject::HandleBullet(SDL_Renderer* des)
{
    for (int i=0; i < p_bullet_list_.size(); i++)
    {
        BulletObject* p_bullet = p_bullet_list_.at(i);
        if (p_bullet != NULL)
        {
            if (p_bullet->get_is_move() == true)
            {
                p_bullet->HandleMove(SCREEN_WIDTH, SCREEN_HEIGHT);
                p_bullet->Render(des);
            }
            else
            {
                p_bullet_list_.erase(p_bullet_list_.begin() + i);
                if (p_bullet != NULL)
                {
                    delete p_bullet;
                    p_bullet = NULL;
                }
            }
        }
    }
}

void MainObject::HandleThreats(SDL_Renderer* des)
{
    for (int i=0; i < p_threats_list_.size(); i++)
    {
        ThreatsObject* p_threats = p_threats_list_.at(i);
        if (p_threats != NULL)
        {
            if (p_threats->get_is_move_threats() == true)
            {
                p_threats->HandleMoveThreats(SCREEN_WIDTH, SCREEN_HEIGHT);
                p_threats->Render(des);
            }
            else
            {
                p_threats_list_.erase(p_threats_list_.begin() + i);
                if (p_threats != NULL)
                {
                    delete p_threats;
                    p_threats = NULL;
                }
            }
        }
    }
}

void MainObject::RemoveBullet(const int& idx)
{
    int size = p_bullet_list_.size();
    if (size > 0 && idx < size)
    {
        BulletObject* p_bullet = p_bullet_list_.at(idx);
        p_bullet_list_.erase(p_bullet_list_.begin() + idx);

        if (p_bullet)
        {
            delete p_bullet;
            p_bullet = NULL;
        }
    }
}

void MainObject::CheckCollisionThreats(MainObject p_player)
{

}
