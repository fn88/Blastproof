#include "raylib.h"
#include "set_up.h"
#include "game_update.h"
#include "player.h"
#include "draw.h"
#include "models.h"
#include "collisions.h"
#include "level1.h"
#include "enemies.h"
#include "projectiles.h"
#include "audio.h"
#include <time.h>
#include <iostream>
using namespace std;


//char a = 'a';
//char b = 'b';
//char c = 'c';
//cout << endl << a << endl << endl;
//cout << endl << b << endl << endl;;
//cout << endl << c << endl << endl;


int main()
{

    SetRandomSeed(time(0));
    set_up_window();
    set_up_cam();
    create_player();
    create_enemyONE();
    load_level_models();
    load_sounds();

    //make_temp_bullet();

    gen_floor();
    gen_buildings();
    place_some_models();

    while (!WindowShouldClose())
    {
        game_update();
        update_player();
        update_enemyONE();
        update_projectiles();
        all_collisions();
        draw_everything();
    }

    CloseWindow();
    return 0;
}

