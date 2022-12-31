#pragma once
#include "raylib.h"
#include <vector>
#include <map>
#include <string>
using namespace std;


struct seed_Obj {
                    Vector3 size;
                    Vector3 pos;
                    BoundingBox BB;
                    unsigned int model_index;
                    Color color;
};          


Model load_model(const char *model_loc, const char *texture_loc);

BoundingBox update_BB_pos(Vector3 size, Vector3 pos);



//extern map<string, Model> level_models;
extern Model level_models[];
extern Model bullets_model;  // temp


extern vector<seed_Obj> floor_tiles;
extern vector<seed_Obj> * ptr_floor_tiles;
extern vector<seed_Obj> level_objects;
extern vector<seed_Obj> * ptr_level_objects;
void load_level_models();
