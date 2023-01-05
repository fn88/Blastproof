#pragma once
#include "raylib.h"
#include <vector>
#include <map>
#include <string>
using namespace std;


struct model_Obj {
                    Model model;
                    Vector3 size;
                    Vector3 pos;
                    BoundingBox BB;
                    Color color;
};          


Model load_model(const char *model_loc, const char *texture_loc);

BoundingBox update_BB_pos(Vector3 size, Vector3 pos);


extern Model level_models[];
extern Model bullets_model;  // temp


extern vector<model_Obj> floor_tiles;
extern vector<model_Obj> * ptr_floor_tiles;
extern vector<model_Obj> level_objects;
extern vector<model_Obj> * ptr_level_objects;
void load_level_models();
