#pragma once
#include "player.h"
#include <vector>
using namespace std;

extern vector<entity_Obj> enemies;

extern float new_path_theta;  // temp

void create_enemies(int n);
void update_enemies_dir();
void update_enemies_gravity();
void update_enemies_model();
void update_enemies();

