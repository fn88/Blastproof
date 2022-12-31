#pragma once
#include "raylib.h"
#include "models.h"
#include <vector>
using namespace std;


struct model_Obj {
                    Model model;
                    Vector3 size;
                    Vector3 pos;
                    BoundingBox BB;
                    Color color;
};      

extern int const level_size;
extern vector<model_Obj>generated_buildings;
extern vector<model_Obj> * ptr_generated_buildings;

void gen_floor();
void gen_buildings();
void place_some_models();