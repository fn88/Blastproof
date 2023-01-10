#pragma once
#include "raylib.h"
#include <vector>
using namespace std;

extern Ray b_ray;
struct simple_projectile {
                            Model model;
                            Vector3 pos;
                            Vector3 dir;
                            BoundingBox BB;
                            unsigned int total_dur;
                            unsigned int cur_dur;
                            float speed;
                            //float theta;
                            //float phi;
};


extern vector<simple_projectile> bullets;
extern vector<simple_projectile> bullet_sparks; 
//extern vector<vector<simple_projectile>> bullet_sparks_group;

extern Vector3 bullet_size; 

//Vector3 chain_sphere_collision(BoundingBox BB, Vector3 pos, int length, float radius);
void shoot_bullet(Vector3 pos, float theta, float phi);
void bullet_sparks_made(Vector3);
void update_projectiles();

