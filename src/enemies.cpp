#include "enemies.h"
#include "raylib.h"
#include "raymath.h"
#include "player.h"
#include "set_up.h"
#include "models.h"


vector<entity_Obj> enemies{};

entity_Obj temp{0};
int new_path_timer = 0;
int path_dur = rnd(1, 100);
float new_path_theta = 0.0f;


void create_enemies(int n)
{
    for (int i = 0; i < n; i++)
    {
        temp.model = LoadModel("resources/models/player.obj");
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
        temp.moving = false;
        temp.moving_in_reverse = false;
        temp.colliding = false;

        Texture2D temp_model_texture = LoadTexture("resources/textures/car1_texture.png");
        temp.model.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = temp_model_texture;
        enemies.push_back(temp);
    }
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

void update_enemies_pathing()  // temp
{
    for (auto it = enemies.begin(); it < enemies.end(); it++)
    {
        new_path_timer += 1; 
        if ( new_path_timer >= path_dur )
        {
            path_dur = rnd(30, 90);
            new_path_theta = (*it).theta + rnd(-12, 12) * PI/24;
            new_path_timer = 0;
        } 
        if (new_path_theta < 0) new_path_theta += 2*PI;
        
        if (new_path_theta > 2*PI) new_path_theta -= 2*PI;
        if ( new_path_theta > (*it).theta ) (*it).theta += 0.01;
        if ( new_path_theta < (*it).theta ) (*it).theta -= 0.01;

        (*it).speed += 0.005f;
        if ((*it).speed > 0) (*it).speed -= sqrt(abs((*it).speed)) * 0.01f;
        if ((*it).speed < 0) (*it).speed += sqrt(abs((*it).speed)) * 0.01f;

        if (abs((*it).speed) < 0.001f) (*it).speed = 0.0f;
        (*it).pos.x += (*it).speed * cos((*it).theta);
        (*it).pos.y += (*it).speed * sin((*it).theta);
        (*it).BB = update_BB_pos((*it).size, (*it).pos);
    }

}

void update_enemies_dir()
{
    for (auto it = enemies.begin(); it < enemies.end(); it++)
    {                
        if ((*it).theta > 2*PI) (*it).theta -= 2*PI;
        if ((*it).theta < 0) (*it).theta += 2*PI;

        if ((*it).phi >  PI/2.2f) (*it).phi =  PI/2.2f;
        if ((*it).phi < -PI/2.2f) (*it).phi = -PI/2.2f;
        //  check if (*it) is not at standstill
        if (abs((*it).pos.x - (*it).prev_pos.x) > 0.0001 || abs((*it).pos.y - (*it).prev_pos.y) > 0.0001) (*it).moving = true;
        else 
        {
            (*it).moving = false;
            (*it).moving_in_reverse = false;
        }
        //  check if (*it) moving in reverse 180 portion of view
        if ((*it).moving)
        {
            float a = atan2(((*it).pos.y - (*it).prev_pos.y), ((*it).pos.x - (*it).prev_pos.x)) - (*it).theta;  // zero'd movement direction
            if (a < 0) a += 2*PI;
            if ( (a > PI/2) && (a < 3*PI/2) ) (*it).moving_in_reverse = true;
            else (*it).moving_in_reverse = false;
        }
    }
}

void update_enemies_model()
{
    for (auto it = enemies.begin(); it < enemies.end(); it++)
    {
        (*it).model.transform = MatrixRotateZ(-(*it).theta);
    }
}

//------------------------------------------------------------------------------------------
void update_enemies()
{
    for (auto it = enemies.begin(); it < enemies.end(); it++)
    {
        (*it).prev_theta = (*it).theta;                
        (*it).prev_phi = (*it).phi;
        (*it).prev_pos = (*it).pos;
        (*it).prev_BB = (*it).BB;
        update_enemies_pathing();
        update_enemies_dir();
        update_enemies_gravity();
        update_enemies_model();
    }
}