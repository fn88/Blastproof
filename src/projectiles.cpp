#include "raymath.h"
#include "projectiles.h"
#include "level1.h"
#include "enemies.h"



vector<simple_projectile> bullets{};
float bullet_speed = 5.1f;
Vector3 bullet_size = {1.0f, 1.0f, 1.0f};  // bigger than model size for BB/collisions
int bulletsSIZE = bullets.size();  // temp
float bulletONEx;  // temp
float bulletONEy;  // temp
float bulletONEz;  // temp


void bullets_collisions()
{
    for (auto it1 = bullets.begin(); it1 < bullets.end(); it1++)
    {
        if ( (*it1).pos.x > 2000.0f || (*it1).pos.x < -2000.0f ) bullets.erase(it1); 
        if ( (*it1).pos.y > 2000.0f || (*it1).pos.y < -2000.0f ) bullets.erase(it1); 
        if ( (*it1).pos.z > 2000.0f || (*it1).pos.z < -2000.0f ) bullets.erase(it1); 
        for (auto it2 = generated_buildings.begin(); it2 < generated_buildings.end(); it2++)
        {
            if ( CheckCollisionBoxes((*it1).BB, (*it2).BB) ) 
            {
                bullets.erase(it1);
                break;
            }
        }

        for (auto it2 = enemies.begin(); it2 < enemies.end(); it2++)
        {
            if ( CheckCollisionBoxes((*it1).BB, (*it2).BB) ) bullets.erase(it1);
        }

        for (auto it2 = level_objects.begin(); it2 < level_objects.end(); it2++)
        {
            if ( CheckCollisionBoxes((*it1).BB, (*it2).BB) ) bullets.erase(it1);
        }

    }
}


void bullets_pos()
{
    for (auto it = bullets.begin(); it < bullets.end(); it++)
    {
        (*it).pos.x = (*it).pos.x + (bullet_speed * cos((*it).theta));  //(bullet_speed * cos((*it).phi) * cos((*it).theta));
        (*it).pos.y = (*it).pos.y + (bullet_speed * sin((*it).theta));  //(bullet_speed * cos((*it).phi) * sin((*it).theta));
        //(*it).pos.z = 3.0f;  // += (bullet_speed * sin((*it).phi));
        (*it).BB = update_BB_pos(bullet_size, (*it).pos);
    }
} 


void update_bullets()
{
    bullets_pos();
    bullets_collisions();
    bulletsSIZE = bullets.size();  // temp
    if ( !bullets.empty() ) 
    {
        bulletONEx = bullets[0].pos.x;
        bulletONEy = bullets[0].pos.y;
        bulletONEy = bullets[0].pos.z;
    }


}

void update_projectiles()
{
    update_bullets();
}
