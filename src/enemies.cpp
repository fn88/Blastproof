#include "enemies.h"
#include "raylib.h"
#include "raymath.h"
#include "player.h"
#include "set_up.h"
#include "game_update.h"
#include "models.h"
#include "projectiles.h"


vector<entity_Obj> enemies{};
int num_enemies;

entity_Obj temp{0};


void create_enemies(int n)
{
    for (int i = 0; i < n; i++)
    {
        temp.id = i;
        //temp.target;
        temp.model = LoadModel("resources/models/player.obj");
        Texture2D temp_model_texture = LoadTexture("resources/textures/car1_texture.png");
        temp.model.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = temp_model_texture;
        temp.BB = GetModelBoundingBox(temp.model);
        temp.prev_BB = temp.BB;
        temp.pos = {float(rnd(200, 600)), float(rnd(200, 600)), 10.0f};
        temp.prev_pos = temp.pos;
        temp.size = {(temp.BB.max.x - temp.BB.min.x), (temp.BB.max.y - temp.BB.min.y), (temp.BB.max.z - temp.BB.min.z)};
        temp.theta = float(rnd(0, 628));
        temp.prev_theta = temp.theta;
        temp.phi = 0.0f;
        temp.prev_phi = temp.phi;
        temp.speed = 0.0f;
        temp.gravity = true;
        temp.grounded = false;
        temp.time_not_grounded = 0;
        temp.jumped = false;
        temp.colliding = false;
        temp.health = 100;

        temp.new_path_timer = 0;
        temp.path_dur = rnd(1, 100);
        temp.new_path_theta = 0.0f;
        temp.foe = rnd(0, n-1);
        temp.attacking_dur = 0;
        temp.exploring_dur = 0;

        enemies.push_back(temp);
    }
    
    num_enemies = n;
}

void pre_update_enemies()
{
    for (auto it = enemies.begin(); it < enemies.end(); it++)
    {
        (*it).prev_theta = (*it).theta;                
        (*it).prev_phi = (*it).phi;
        (*it).prev_pos = (*it).pos;
        (*it).prev_BB = (*it).BB;
    }
}

/*void aquire_target_for (int id)
{
    int target_id = rnd(0, num_enemies-1);
    if (enemies.at(id).id == id) enemies.at(id).target = 63;  // if enemy's target is it's own id, make player(id=63) the target
}*/

void enemy_shoot(int id)
{
    if ( fps_counter%5 == 1 ) 
    {
        float e_phi = enemies.at(id).phi;
        float e_theta = enemies.at(id).theta;
        float dir_x = cos(e_phi) * cos(e_theta);
        float dir_y = cos(e_phi) * sin(e_theta);
        float dir_z = sin(e_phi);
        Vector3 e_pos = { enemies.at(id).pos.x + (3.0f * dir_x),
                          enemies.at(id).pos.y + (3.0f * dir_y),
                          enemies.at(id).pos.z + (3.0f * dir_z) };

        shoot_bullet(e_pos, enemies.at(id).theta, enemies.at(id).phi); 
    }
}

void update_enemies_L1()  // Layer 1, outer, most general behavior
{
    for (int i = 0; i < num_enemies; i++)
    {
        if ( enemies.at(i).attacking_dur == 0 && 
             enemies.at(i).exploring_dur == 0 )
        {
            int choice = rnd(1, 1);
            switch (choice) 
            {
                case 0:
                {
                    enemies.at(i).exploring_dur = rnd(10, 30);
                    break;
                }
                case 1:
                {
                    enemies.at(i).attacking_dur = rnd(120, 240);
                    break;
                }
            }
        }
        if ( enemies.at(i).exploring_dur > 0 ) enemy_explore(i);
        if ( enemies.at(i).attacking_dur > 0 ) enemy_attack(i);
    update_enemy_dir(i);
    update_enemy_movement(i);
    }
}    

void enemy_explore(int id)
{
    entity_Obj * p_id = &enemies.at(id);
    (*p_id).new_path_timer++; 
    if ( (*p_id).new_path_timer > (*p_id).path_dur )
    {
        (*p_id).new_path_timer = 0;
        (*p_id).path_dur = rnd(30, 90);
        (*p_id).new_path_theta = (*p_id).theta + rnd(-12, 12) * PI/24;

        if ((*p_id).new_path_theta < 0) (*p_id).new_path_theta += 2*PI;  // keeping within 2PI
        if ((*p_id).new_path_theta > 2*PI) (*p_id).new_path_theta -= 2*PI;
    } 
    (*p_id).exploring_dur--;
}

void enemy_attack(int id)
{
    entity_Obj * p_id = &enemies[id];  // pointer to enemy
    entity_Obj * p_foe = &enemies[enemies[id].foe];  // pointer to enemy's foe

    float a = atan2( (*p_foe).pos.x - (*p_id).pos.x, (*p_foe).pos.y - (*p_id).pos.y);  // angle foe makes with respect to enemy('origin')
    if (a < 0) a =+ 2*PI;
    (*p_id).new_path_theta = a;
    if ( abs((*p_id).theta - a) < PI/10) enemy_shoot(id);
    enemies.at(id).attacking_dur--;
    
}


void update_enemy_movement(int id)  // temp
{
    entity_Obj * p_id = &enemies.at(id);
    // speed, traversing
    (*p_id).speed += 0.003f;
    if ((*p_id).speed > 0) (*p_id).speed -= sqrt(abs((*p_id).speed)) * 0.01f;
    if ((*p_id).speed < 0) (*p_id).speed += sqrt(abs((*p_id).speed)) * 0.01f;

    if (abs((*p_id).speed) < 0.001f) (*p_id).speed = 0.0f;
    (*p_id).pos.x += (*p_id).speed * cos((*p_id).theta);
    (*p_id).pos.y += (*p_id).speed * sin((*p_id).theta);
    (*p_id).BB = update_BB_pos((*p_id).size, (*p_id).pos);
}

void update_enemy_dir(int id)
{
    entity_Obj * p_id = &enemies.at(id);
    if ((*p_id).theta > 2*PI) (*p_id).theta -= 2*PI;
    if ((*p_id).theta < 0) (*p_id).theta += 2*PI;
    if ( (*p_id).new_path_theta > (*p_id).theta ) (*p_id).theta += 0.01;  // turning enemy towards the new direction
    else if ( (*p_id).new_path_theta < (*p_id).theta ) (*p_id).theta -= 0.01;

    //  inertia, coming to rest and preventing inf acceleration
    if (abs((*p_id).speed) < 0.001f) (*p_id).speed = 0.0f;
    else if ((*p_id).speed > 0) (*p_id).speed -= sqrt(abs((*p_id).speed)) * 0.008f;
    else if ((*p_id).speed < 0) (*p_id).speed += sqrt(abs((*p_id).speed)) * 0.008f;
    (*p_id).pos.x += (*p_id).speed * cos((*p_id).theta);
    (*p_id).pos.y += (*p_id).speed * sin((*p_id).theta);

    //  check if moving in reverse 180 portion of view
    float a = atan2(((*p_id).pos.y - (*p_id).prev_pos.y), ((*p_id).pos.x - (*p_id).prev_pos.x)) - (*p_id).theta;  // trig zero'd movement angle
    if ( (a > PI/2) || (a < -PI/2) ) (*p_id).speed *= -1.0f;
    else (*p_id).speed *= 1.0f;
}

void update_enemies_gravity()
{
    for (auto it = enemies.begin(); it < enemies.end(); it++)
    {
        if ((*it).gravity) 
        {
            if ((*it).grounded)
            {
                (*it).time_not_grounded = 0;
                (*it).jumped = false;
            }
            else
            {
                (*it).time_not_grounded += 1;
                (*it).pos.z += (-1) * pow(float((*it).time_not_grounded)/FPS, 2);  
            }
            if ((*it).jumped) (*it).pos.z += 0.3f;
        }
        update_BB_pos((*it).size, (*it).pos);
    }
}

void post_update_enemies()
{
    for (auto it = enemies.begin(); it < enemies.end(); it++)
    {
        (*it).BB = update_BB_pos((*it).size, (*it).pos);
    }
    update_enemies_model();
}

void update_enemies_model()
{
    for (auto it = enemies.begin(); it < enemies.end(); it++)
    {
        (*it).model.transform = MatrixRotateZ(-(*it).theta);
    }
}
//====================================================================================
void update_enemies()
{
    pre_update_enemies();

    update_enemies_L1();
    update_enemies_gravity();

    post_update_enemies();
}