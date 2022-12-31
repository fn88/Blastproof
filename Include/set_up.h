#pragma once 
#include "raylib.h"   


extern int S_W;
extern int S_H;
extern int FPS;
extern int LVL_SIZE_X; 
extern int LVL_SIZE_Y;
extern int LVL_SIZE_Z;
extern Camera cam;
extern float cam_theta;
extern float cam_phi;
extern float mouse_sensitivity;

extern bool info_tab_visible;
extern int rnd(int one, int two);

void set_up_window();
void set_up_cam();



