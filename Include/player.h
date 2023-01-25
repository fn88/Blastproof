#pragma once
#include "raylib.h"
#include "set_up.h"


struct entity_Obj {
                    unsigned int id;
                    unsigned int target;
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
                    float steer;  // -/+ left/right
                    bool colliding;
                    int health;

                    //---------------------------
                    int new_path_timer = 0;     
                    int path_dur = rnd(1, 100);
                    float new_path_theta = 0.0f;
                    int foe;
                    int attacking_dur;
                    int exploring_dur;

};

extern entity_Obj player;
extern entity_Obj * ptr_player;

void create_player();

void pre_update_player();
void update_player_gravity();
void update_player_model();
void update_player_controls();
void update_player();
