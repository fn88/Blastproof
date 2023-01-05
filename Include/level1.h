#pragma once
#include "raylib.h"
#include "models.h"
#include <vector>
using namespace std;

extern vector<model_Obj> level_objects;
extern vector<model_Obj> * ptr_level_objects;
extern int const level_size;
extern vector<model_Obj> generated_buildings;
extern vector<model_Obj> * ptr_generated_buildings;

void gen_floor();
void gen_buildings();
void place_some_models();