#pragma once
#include "player.h"
#include <vector>
using namespace std;

extern vector<entity_Obj> enemies;
extern entity_Obj enemyONE;
extern entity_Obj * ptr_enemyONE;

extern float new_path_theta;  // temp

void create_enemyONE();
void update_enemyONE_dir();
void update_enemyONE_BB();
void update_enemyONE_gravity();
void update_enemyONE_model();
void update_enemyONE();

