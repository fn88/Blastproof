#include "game_update.h"
#include "raylib.h"
#include "set_up.h"


// mouse -------------------------------------------------------------
float theta;
float phi;
float mousePosX;
float mousePosY;
float mouseDistX;
float mouseDistY;

void update_mouse()
{
    mousePosX = (float)GetMouseX();
    mousePosY = (float)GetMouseY();
    mouseDistX = mouse_sensitivity * (mousePosX - (S_W/2.0f));
    mouseDistY = mouse_sensitivity * (mousePosY - (S_H/2.0f));
    SetMousePosition(S_W/2.0f, S_H/2.0f);
    theta = mouseDistX/(S_W/2.0f) * (cam.fovy/2.0f) * DEG2RAD; 
    phi = mouseDistY/(S_H/2.0f) * (cam.fovy/2.0f) * DEG2RAD;
}
//--------------------------------------------------------------------

void game_update()
{ 
    update_mouse();
}




