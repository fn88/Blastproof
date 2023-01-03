#include "game_update.h"
#include "raylib.h"
#include "set_up.h"


int fps_counter = 0;

// mouse -------------------------------------------------------------
float mouse_theta;
float mouse_phi;
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
    mouse_theta = mouseDistX/(S_W/2.0f) * (cam.fovy/2.0f) * DEG2RAD; 
    mouse_phi = mouseDistY/(S_H/2.0f) * (cam.fovy/2.0f) * DEG2RAD;
}
//--------------------------------------------------------------------

void game_update()
{ 
    if (fps_counter < FPS) fps_counter++;
    else fps_counter =  0;
    update_mouse();
}




