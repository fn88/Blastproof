#include "raymath.h"
#include "player.h"
#include "models.h"
#include "projectiles.h"
#include "set_up.h"
#include "game_update.h"
#include "audio.h"

#include <iostream>


entity_Obj player{0};
entity_Obj * ptr_player = &player;

void create_player()
{
    player.id = 63; 
    player.model = LoadModel("resources/models/player.obj");
    Texture2D player_model_texture = LoadTexture("resources/textures/car1_texture.png");
    player.model.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = player_model_texture;
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
    player.steer = 0.0f; 
    player.colliding = false;
    player.health = 100;

}

void pre_update_player()
{
    player.prev_theta = player.theta;                
    player.prev_phi = player.phi;
    player.prev_pos = player.pos;
    player.prev_BB = player.BB;
}

void update_player_controls()
{
    if (IsKeyDown(KEY_W)) 
    {
        player.speed += 0.01f;
    }
    if (IsKeyDown(KEY_S)) 
    {
        player.speed -= 0.01f;
    }
    if (IsKeyDown(KEY_A)) 
    {
        player.steer -= 0.001f;
    }
    if (IsKeyDown(KEY_D)) 
    {   
        player.steer += 0.001f;
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
    player.BB = update_BB_pos(player.size, player.pos);
    }

    if (IsMouseButtonDown(0))
    {
        if ( fps_counter%5 == 1 )
        {
        float dir_x = cos(player.phi) * cos(player.theta);
        float dir_y = cos(player.phi) * sin(player.theta);
        float dir_z = sin(player.phi);
        Vector3 b_pos = { player.pos.x + (3.0f * dir_x),
                          player.pos.y + (3.0f * dir_y),
                          player.pos.z + (3.0f * dir_z) };  // 3.0f = temp dist for bullets to be shot in front and not collide w/ shooter

            shoot_bullet(b_pos, player.theta, player.phi);
        }
    }
}
//==========================================MOVEMENT======================================================================
void update_player_movement()
{
    if (abs(player.steer) < 0.0001f) player.steer = 0.0f;
    else if (player.steer > 0) player.steer -= sqrt(abs(player.steer)) * 0.008f;  //  float #futurebug
    else if (player.steer < 0) player.steer += sqrt(abs(player.steer)) * 0.008f;
    if (player.speed > 0) player.theta -= player.steer;
    else if (player.speed < 0) player.theta += player.steer;
   
    //  keep angles within 2PI and 'gimbal-locked'
    if (player.theta > 2*PI) player.theta -= 2*PI;
    if (player.theta < 0) player.theta += 2*PI;

    if (player.phi >  PI/2.2f) player.phi =  PI/2.2f;
    if (player.phi < -PI/2.2f) player.phi = -PI/2.2f;
    //  check if player moving in reverse 180 portion of view
    float a = atan2((player.pos.y - player.prev_pos.y), (player.pos.x - player.prev_pos.x)) - player.theta;  // trig zero'd movement angle
    if ( a < -PI/2 || a > PI/2 ) player.speed *= 1.0f;
    else player.speed *= 1.0f;

    //  inertia, coming to rest and preventing inf acceleration
    if (abs(player.speed) < 0.0001f) player.speed = 0.0f;
    else if (player.speed < 0) player.speed += sqrt(abs(player.speed)) * 0.008f;
    else if (player.speed > 0) player.speed -= sqrt(abs(player.speed)) * 0.008f;
    player.pos.x += player.speed * cos(player.theta);
    player.pos.y += player.speed * sin(player.theta);


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

        cam.target.x = player.pos.x; 
        cam.target.y = player.pos.y; 
        cam.target.z = player.pos.z + 2.0f;
    }

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
    player.BB = update_BB_pos(player.size, player.pos);
}

void post_update_player()
{
    player.BB = update_BB_pos(player.size, player.pos);
    update_player_model();
}

void update_player_model()
{
    player.model.transform = MatrixRotateZ(-player.theta);
}



void update_player()
{
    pre_update_player();

    update_player_controls();
    update_player_movement();
    update_player_gravity();

    post_update_player();
}