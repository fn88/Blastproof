#include "raymath.h"
#include "draw.h"
#include "set_up.h"
#include "game_update.h"
#include "player.h"
#include "models.h"
#include "level1.h"
#include "enemies.h"
#include "projectiles.h"



void draw_player()
{
    DrawModel(player.model, player.pos, 1.0f, WHITE);
    //DrawBoundingBox(player.BB, RED);
}


void draw_enemies()
{
    for (auto it = enemies.begin(); it < enemies.end(); it++)
    {
        DrawModel((*it).model, (*it).pos, 1.0f, WHITE);
        //DrawBoundingBox((*it).BB, RED);
    }
}


void draw_projectiles()
{
    if (!bullets.empty())
    {
        for (auto it = bullets.begin(); it < bullets.end(); it++)
        {
            DrawModel((*it).model, (*it).pos, 1.0f, WHITE);
            //DrawBoundingBox((*it).BB, WHITE);
            DrawRay(b_ray, RED);
        }
    }
    if (!bullet_sparks.empty())
    {
        for (auto it = bullet_sparks.begin(); it < bullet_sparks.end(); it++)
        {
            DrawModel((*it).model, (*it).pos, 0.1f, WHITE);
        }
    }
}


void draw_level()
{
    for (auto it = level_objects.begin(); it < level_objects.end(); it++)
    {
        DrawModel((*it).model, (*it).pos, 1.0f, (*it).color);
        //DrawBoundingBox((*it).BB, WHITE);
    }
    for (auto it = generated_buildings.begin(); it < generated_buildings.end(); it++)
    {
        DrawModel((*it).model, (*it).pos, 1.0f, (*it).color);
        //DrawBoundingBox((*it).BB, RED);
    }
}


void draw_everything()
{
    BeginDrawing();
    ClearBackground(BLACK);
    BeginMode3D(cam);
    //-----------------------------
    draw_player();
    draw_enemies();
    draw_projectiles();
    draw_level();

    EndMode3D();
    //---------------------------
    DrawFPS(10, 10);
    if (info_tab_visible)
    {
        DrawText(TextFormat("player.colliding: %02i", int(player.colliding)), 50, 220, 30, {255, 255, 255, 100});
        DrawText(TextFormat("player.grounded: %02i", int(player.grounded)), 50, 250, 30, {255, 255, 255, 100});
        DrawText(TextFormat("player.time_not_grounded: %02i", int(player.time_not_grounded)), 50, 280, 30, {255, 255, 255, 100});
        DrawText(TextFormat("player.pos: %01f, %01f, %01f", player.pos.x, player.pos.y, player.pos.z), 50, 310, 30, {255, 255, 255, 100});
        DrawText(TextFormat("player.prev_pos: %01f, %01f, %01f", player.prev_pos.x, player.prev_pos.y, player.prev_pos.z), 50, 340, 30, {255, 255, 255, 100});
        DrawText(TextFormat("player.theta: %01f", player.theta*180/PI), 50, 460, 30, {255, 255, 255, 100});
        DrawText(TextFormat("player.speed: %01f", player.speed), 50, 490, 30, {255, 255, 255, 100});
    }
    DrawText(TextFormat("HEALTH: %02i", player.health), 50, 900, 30, WHITE);


    //----------------------------
    EndDrawing();
}


