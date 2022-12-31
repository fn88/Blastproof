#pragma once
#include "raylib.h"
#include <string>
#include <map>
using namespace std;


extern map<string, Sound> sounds;
extern Sound bullet_shots[];

void load_sounds();