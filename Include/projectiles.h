#pragma once
#include "raylib.h"
#include <vector>
using namespace std;


struct simple_projectile {
                            Vector3 pos;
                            BoundingBox BB;
                            float theta;
                            float phi;
};

extern vector<simple_projectile> bullets;
extern Vector3 bullet_size;  // temp
extern int bulletsSIZE;


void update_projectiles();

