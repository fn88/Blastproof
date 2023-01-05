#pragma once
#include "player.h"  //entity_Obj
#include "level1.h"  // model_Obj


void all_collisions();
void player_collisions();
void enemies_collisions();
void gravity_collisions(entity_Obj &entity, vector<model_Obj> * placed_objects);
void collisions(entity_Obj &entity, vector<model_Obj> * placed_objects);
void collisions_generated(entity_Obj &entity, vector<model_Obj> * generated_models);
void entity_collisions(entity_Obj &e1, entity_Obj &e2);

