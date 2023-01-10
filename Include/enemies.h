#pragma once
#include "player.h"
#include <vector>
using namespace std;

extern vector<entity_Obj> enemies;
extern int num_enemies;

extern float new_path_theta;  // temp


void pre_update_enemies();
void create_enemies(int n);

void update_enemies_L1();;
void explore();

void aquire_target_for(int id);
void update_enemies_dir();
void update_enemies_gravity();
void update_enemies_model();
void update_enemies();
void post_update_enemies();

