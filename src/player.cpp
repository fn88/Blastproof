#include "raymath.h"
#include "player.h"
#include "models.h"
#include "projectiles.h"
#include "set_up.h"
#include "game_update.h"
#include "audio.h"

#include <iostream>


entity_Obj player{0};

void create_player()
{
    player.model = LoadModel("resources/models/player.obj");
    player.BB = GetModelBoundingBox(player.model);
    player.prev_BB = player.BB;
    player.pos = {350.0f, 350.0f, 10.0f};
    player.prev_pos = player.pos;
    player.size = {(player.BB.max.x - player.BB.min.x), (player.BB.max.y - player.BB.min.y), (player.BB.max.z - player.BB.min.z)};
    player.theta = PI/4;
    player.prev_theta = 0.0f;
    player.phi = 0.0f;
    player.prev_phi = 0.0f;
    player.speed = 0.0f;
    player.gravity = true;
    player.grounded = false;
    player.time_not_grounded = 0;
    player.jumped = false;
    player.moving = false;
    player.moving_in_reverse = false;
    player.colliding = false;

    Texture2D player_model_texture = LoadTexture("resources/textures/car1_texture.png");
    player.model.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = player_model_texture;

}
entity_Obj * ptr_player = &player;

void update_player_BB()
{
    player.BB = update_BB_pos(player.size, player.pos);
}

void update_player_gravity()
{
    if (player.gravity)  // if player is affected by gravity G-key
    {
        if (player.grounded)
        {
            player.time_not_grounded = 0;
            player.jumped = false;
        }
        else
        {
            player.time_not_grounded += 1;
            player.pos.z += (-1) * pow(float(player.time_not_grounded)/FPS, 2);  
        }
        if (player.jumped) player.pos.z += 0.3f;
    }
    update_player_BB();
}


void update_player_dir()
{                
    if (player.theta > 2*PI) player.theta -= 2*PI;
    if (player.theta < 0) player.theta += 2*PI;

    if (player.phi >  PI/2.2f) player.phi =  PI/2.2f;
    if (player.phi < -PI/2.2f) player.phi = -PI/2.2f;
    //  check if player is not at standstill
    if (abs(player.pos.x - player.prev_pos.x) > 0.0001 || abs(player.pos.y - player.prev_pos.y) > 0.0001) player.moving = true;
    else 
    {
        player.moving = false;
        player.moving_in_reverse = false;
    }
    //  check if player moving in reverse 180 portion of view
    if (player.moving)
    {
        float a = atan2((player.pos.y - player.prev_pos.y), (player.pos.x - player.prev_pos.x)) - player.theta;  // trig zero'd movement angle
        if (a < 0) a += 2*PI;
        if ( (a > PI/2) && (a < 3*PI/2) ) player.moving_in_reverse = true;
        else player.moving_in_reverse = false;
    }

    if (IsMouseButtonDown(1))
    {
        cam_theta -= mouse_theta;
        cam_phi -= mouse_phi;
        cam.position.x = player.pos.x;
        cam.position.y = player.pos.y;
        cam.position.z = player.pos.z + 4.0f;

        cam.target.x = player.pos.x + (10 * (cos(cam_phi) * cos(cam_theta)));
        cam.target.y = player.pos.y + (10 * (cos(cam_phi) * sin(cam_theta)));
        cam.target.z = player.pos.z + (10 * sin(cam_phi)) + 3.0f;
    }
    else
    {
        cam_theta = player.theta;
        cam_phi = player.phi;
        cam.position.x = player.pos.x + 10*(cos(player.theta - PI));
        cam.position.y = player.pos.y + 10*(sin(player.theta - PI));
        cam.position.z = player.pos.z + 3.0f; // + 10*(cos(player.phi));

        cam.target.x = player.pos.x; // + (cos(player.phi) * cos(player.theta));
        cam.target.y = player.pos.y; // + (cos(player.phi) * sin(player.theta));
        cam.target.z = player.pos.z + 2.0f;
    }

}

void update_player_model()
{
    player.model.transform = MatrixRotateZ(-player.theta);
}


void update_player_controls()
{
    if (IsKeyDown(KEY_W)) 
    {
        player.speed += 0.01f;
        player.moving = true;
    }
    if (IsKeyDown(KEY_S)) 
    {
        player.speed -= 0.01f;
        player.moving = true;
    }

    if (IsKeyDown(KEY_A)) 
    {
        if (player.moving_in_reverse) player.theta -= 0.01f;
        else if (player.moving) player.theta += 0.01f;
    }
    if (IsKeyDown(KEY_D)) 
    {   
        if (player.moving_in_reverse) player.theta += 0.01f;
        else if (player.moving) player.theta -= 0.01f;
    }

    if (IsKeyPressed(KEY_SPACE))
    {
        if (player.grounded)
        {
            player.jumped = true;
            player.grounded = false;
        }
    }

    if (IsKeyDown(KEY_Q)) 
    {
         player.pos = {0.0f, 0.0f, 4.5f}; 
         player.time_not_grounded = 0;
    }

    if (IsKeyDown(KEY_R))
    {
        player.pos.z += 0.03;
    }

    if (IsKeyDown(KEY_F))
    {
        player.pos.z -= 0.03;
    }

    if (IsKeyPressed(KEY_GRAVE)) 
    {
        if (info_tab_visible) info_tab_visible = false;
        else info_tab_visible = true;
    }

    if (IsKeyPressed(KEY_G))
    {
        player.time_not_grounded = 0;
        player.jumped = false;
        
        if (player.gravity) player.gravity = false;
        else player.gravity = true;
    update_player_BB();
    }

    if (IsMouseButtonDown(0))
    {
        if ( fps_counter%5 == 1 )
        {
            shoot_bullet({player.pos.x, player.pos.y, player.pos.z + 1.0f}, player.theta, player.phi);
        }
    }
}

void update_player()
{
    player.prev_theta = player.theta;                
    player.prev_phi = player.phi;
    player.prev_pos = player.pos;
    player.prev_BB = player.BB;
    if (player.speed > 0)
    {
        player.speed -= sqrt(abs(player.speed)) * 0.008f;
    }
    if (player.speed < 0)
    {
        player.speed += sqrt(abs(player.speed)) * 0.008f;
    }
    if (abs(player.speed) < 0.001f) player.speed = 0.0f;
    player.pos.x += player.speed * cos(player.theta);
    player.pos.y += player.speed * sin(player.theta);

    update_player_dir();
    update_player_controls();
    update_player_gravity();
    update_player_model();
    
    update_player_BB();

}