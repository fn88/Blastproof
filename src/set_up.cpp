#include "set_up.h"



int S_W = 3200;//GetMonitorWidth(0);
int S_H = 2000;//GetMonitorWidth(0);
int FPS = 60;
float mouse_sensitivity = 3.0f;

int LVL_SIZE_X = 360;
int LVL_SIZE_Y = 360;
int LVL_SIZE_Z = 360;
Camera cam = {0};
float cam_theta = 0.0f;
float cam_phi = 0.0f;

bool info_tab_visible = false;

int rnd(int one, int two)
{
    int value = GetRandomValue(one, two);
    return value;
}

void set_up_window()
{
    SetConfigFlags(FLAG_MSAA_4X_HINT); 
    InitWindow(S_W, S_H, "game2");
    SetMousePosition(S_W/2.0f, S_H/2.0f);
    HideCursor();
    SetTargetFPS(FPS);
    InitAudioDevice();
}

void set_up_cam()
{
    cam.fovy = 40.0f;
    cam.up = {0.0f, 0.0f, 1.0f};
    cam.projection = CAMERA_PERSPECTIVE;
    cam.position = {10.0f, 10.0f, 10.0f};
    cam.target = {0.0f, 0.0f, 0.0f};
}

