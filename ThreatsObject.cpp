#include "ThreatsObject.h"

ThreatsObject::ThreatsObject()
{
    x_val_threats = 0;
    y_val_threats = 0;
    is_move_threats = false;
}

ThreatsObject::~ThreatsObject()
{

}

void ThreatsObject::HandleMoveThreats(const int& x_border, const int& y_border)
{
    rect_.y += y_val_threats;
    if (rect_.y > SCREEN_HEIGHT)
    {
        is_move_threats = false;
        rect_.y = -80;
    }
}



