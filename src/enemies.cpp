#include "enemies.h"
#include "raylib.h"
#include "raymath.h"
#include "player.h"
#include "set_up.h"
#include "models.h"


vector<entity_Obj> enemies{};

entity_Obj enemyONE{0};
int new_path_timer = 0;
int path_dur = rnd(1, 100);
float new_path_theta = 0.0f;


void create_enemyONE()
{
    enemyONE.model = LoadModel("resources/models/player.obj");
    enemyONE.BB = GetModelBoundingBox(enemyONE.model);
    enemyONE.prev_BB = enemyONE.BB;
    enemyONE.pos = {400.0f, 400.0f, 10.0f};
    enemyONE.prev_pos = enemyONE.pos;
    enemyONE.size = {(enemyONE.BB.max.x - enemyONE.BB.min.x), (enemyONE.BB.max.y - enemyONE.BB.min.y), (enemyONE.BB.max.z - enemyONE.BB.min.z)};
    enemyONE.theta = 0.0f;
    enemyONE.prev_theta = 0.0f;
    enemyONE.phi = 0.0f;
    enemyONE.prev_phi = 0.0f;
    enemyONE.speed = 0.0f;
    enemyONE.gravity = true;
    enemyONE.grounded = false;
    enemyONE.time_not_grounded = 0;
    enemyONE.jumped = false;
    enemyONE.moving = false;
    enemyONE.moving_in_reverse = false;
    enemyONE.colliding = false;

    Texture2D enemyONE_model_texture = LoadTexture("resources/textures/car1_texture.png");
    enemyONE.model.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = enemyONE_model_texture;
    enemies.push_back(enemyONE);

}

entity_Obj * ptr_enemyONE = &enemyONE;


void update_enemyONE_BB()
{
    enemyONE.BB = update_BB_pos(enemyONE.size, enemyONE.pos);
}

void update_enemyONE_gravity()
{
    if (enemyONE.gravity) 
    {
        if (enemyONE.grounded)
        {
            enemyONE.time_not_grounded = 0;
            enemyONE.jumped = false;
        }
        else
        {
            enemyONE.time_not_grounded += 1;
            enemyONE.pos.z += (-1) * pow(float(enemyONE.time_not_grounded)/FPS, 2);  
        }
        if (enemyONE.jumped) enemyONE.pos.z += 0.3f;
    }
    update_enemyONE_BB();
}

void update_pathing()  // temp
{
    new_path_timer += 1; 
    if ( new_path_timer >= path_dur )
    {
        path_dur = rnd(30, 90);
        new_path_theta = enemyONE.theta + rnd(-12, 12) * PI/24;
        new_path_timer = 0;
    } 
    if (new_path_theta < 0) new_path_theta += 2*PI;
    
    if (new_path_theta > 2*PI) new_path_theta -= 2*PI;
    if ( new_path_theta > enemyONE.theta ) enemyONE.theta += 0.01;
    if ( new_path_theta < enemyONE.theta ) enemyONE.theta -= 0.01;

    enemyONE.speed += 0.005f;
    if (enemyONE.speed > 0) enemyONE.speed -= sqrt(abs(enemyONE.speed)) * 0.01f;
    if (enemyONE.speed < 0) enemyONE.speed += sqrt(abs(enemyONE.speed)) * 0.01f;

    if (abs(enemyONE.speed) < 0.001f) enemyONE.speed = 0.0f;
    enemyONE.pos.x += enemyONE.speed * cos(enemyONE.theta);
    enemyONE.pos.y += enemyONE.speed * sin(enemyONE.theta);
    enemyONE.BB = update_BB_pos(enemyONE.size, enemyONE.pos);

}

void update_enemyONE_dir()
{                
    if (enemyONE.theta > 2*PI) enemyONE.theta -= 2*PI;
    if (enemyONE.theta < 0) enemyONE.theta += 2*PI;

    if (enemyONE.phi >  PI/2.2f) enemyONE.phi =  PI/2.2f;
    if (enemyONE.phi < -PI/2.2f) enemyONE.phi = -PI/2.2f;
    //  check if enemyONE is not at standstill
    if (abs(enemyONE.pos.x - enemyONE.prev_pos.x) > 0.0001 || abs(enemyONE.pos.y - enemyONE.prev_pos.y) > 0.0001) enemyONE.moving = true;
    else 
    {
        enemyONE.moving = false;
        enemyONE.moving_in_reverse = false;
    }
    //  check if enemyONE moving in reverse 180 portion of view
    if (enemyONE.moving)
    {
        float a = atan2((enemyONE.pos.y - enemyONE.prev_pos.y), (enemyONE.pos.x - enemyONE.prev_pos.x)) - enemyONE.theta;  // zero'd movement direction
        if (a < 0) a += 2*PI;
        if ( (a > PI/2) && (a < 3*PI/2) ) enemyONE.moving_in_reverse = true;
        else enemyONE.moving_in_reverse = false;
    }
}

void update_enemyONE_model()
{
    enemyONE.model.transform = MatrixRotateZ(-enemyONE.theta);
}

//------------------------------------------------------------------------------------------
void update_enemyONE()
{
    enemyONE.prev_theta = enemyONE.theta;                
    enemyONE.prev_phi = enemyONE.phi;
    enemyONE.prev_pos = enemyONE.pos;
    enemyONE.prev_BB = enemyONE.BB;
    update_pathing();
    update_enemyONE_dir();
    update_enemyONE_gravity();
    update_enemyONE_model();
    
    update_enemyONE_BB();

}