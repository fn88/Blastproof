#pragma once
#include "raylib.h"
#include <vector>
using namespace std;


struct simple_projectile {
                            Model model;
                            Vector3 pos;
                            BoundingBox BB;
                            unsigned int total_dur;
                            unsigned int cur_dur;
                            float speed;
                            float theta;
                            float phi;
};


extern vector<simple_projectile> bullets;
extern vector<simple_projectile> bullet_sparks; 
//extern vector<vector<simple_projectile>> bullet_sparks_group;

extern Vector3 bullet_size; 

void shoot_bullet(Vector3 pos, float theta, float phi);
void bullet_sparks_made(Vector3);
void update_projectiles();

