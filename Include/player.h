#pragma once
#include "raylib.h"


struct entity_Obj {
                    Model model;
                    Vector3 size;
                    Vector3 pos;
                    Vector3 prev_pos;
                    BoundingBox BB;
                    BoundingBox prev_BB;
                    float theta;
                    float prev_theta;
                    float phi;
                    float prev_phi;
                    float speed;
                    bool gravity;
                    bool grounded;
                    int time_not_grounded;
                    bool jumped;
                    bool moving;
                    bool moving_in_reverse;
                    bool colliding;
                    //bool attack1;
                    //bool action1;
                    //unsigned int anim_fc;
};

extern entity_Obj player;
extern entity_Obj * ptr_player;

void create_player();
void update_player_dir();
void update_player_BB();
void update_player_gravity();
void update_player_model();
void update_player_controls();
void update_player();
