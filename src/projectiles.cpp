#include "raymath.h"
#include "projectiles.h"
#include "level1.h"
#include "enemies.h"
#include "audio.h"
#include "set_up.h"



vector<simple_projectile> bullets{};
vector<simple_projectile> bullet_sparks{};  // explosion sparks upon hit/impact
Vector3 bullet_size = {1.0f, 1.0f, 1.0f};  // bigger than model size for BB/collisions

void shoot_bullet(Vector3 pos, float theta, float phi)
{
    Model b = level_models[3];
    float b_speed = 10.0f + float(rnd(1, 10))/20.0f;
    float b_theta = theta + float(rnd(-10, 10))/5000.0f;  // spread
    float b_phi = phi + float(rnd(-10, 10))/5000.0f;  // spread
    unsigned int b_total_dur = rnd(90, 120);
    unsigned int b_cur_dur = 0;
    bullets.push_back(simple_projectile{b, pos, update_BB_pos(bullet_size, pos), b_total_dur, b_cur_dur, b_speed, b_theta, b_phi});
    PlaySoundMulti(bullet_shots[rnd(0, 3)]);
}


void bullet_sparks_made(Vector3 pos)
{
    int a = rnd(50, 100);  // number of sparks
    for (int i = 0; i < a; i++)
    {
        unsigned int bs_total_dur = rnd(3, 10);
        unsigned int bs_cur_dur = 0;
        float bs_speed = 2.0f + float(rnd(1, 10))/10;
        float bs_theta = float(rnd(1, 628)) / 100.0f;
        float bs_phi = float(rnd(1, 628)) / 100.0f;
        Model bs = level_models[3];
        bs.transform = MatrixRotateXYZ({0.0f, bs_phi, -bs_theta});
        bullet_sparks.push_back(simple_projectile{bs, pos, update_BB_pos(bullet_size, pos), bs_total_dur, bs_cur_dur, bs_speed, bs_theta, bs_phi});
    }
}


void bullets_collisions()
{
    if (!bullets.empty())
    {
        for (auto it1 = bullets.begin(); it1 < bullets.end(); it1++)
        {
            for (auto it2 = generated_buildings.begin(); it2 < generated_buildings.end(); it2++)
            {
                if ( CheckCollisionBoxSphere((*it2).BB, (*it1).pos, (*it1).speed) )
                {
                    Ray b_ray = {(*it1).pos, {  cos((*it1).phi) * cos((*it1).theta), 
                                                cos((*it1).phi) * sin((*it1).theta),
                                                sin((*it1).phi)  } };
                    RayCollision b_hit_spot = GetRayCollisionBox(b_ray, (*it2).BB); 
                    if ( (b_hit_spot.distance - (*it1).speed) < 3.0f )  // <------- 3.0f temp
                    {
                        bullet_sparks_made(b_hit_spot.point);
                        bullets.erase(it1);
                        break;
                    }
                }
            }
        }
       for (auto it1 = bullets.begin(); it1 < bullets.end(); it1++)
       {
            if ( CheckCollisionBoxes((*it1).BB, enemyONE.BB) ) 
            {
                bullet_sparks_made((*it1).pos);
                bullets.erase(it1);
                break;
            }
       }
       for (auto it1 = bullets.begin(); it1 < bullets.end(); it1++)
       {
            for (auto it2 = level_objects.begin(); it2 < level_objects.end(); it2++)
            {
                if ( CheckCollisionBoxes((*it1).BB, (*it2).BB) ) 
                {
                    bullet_sparks_made((*it1).pos);
                    bullets.erase(it1);
                    break;
                }
            }

        }
    }
}


void bullets_pos()
{
    if (!bullets.empty())
    {
        for (auto it = bullets.begin(); it < bullets.end(); it++)
        {
            if ( (*it).cur_dur < (*it).total_dur ) 
            {
                (*it).cur_dur++;
                (*it).pos.x = (*it).pos.x + ((*it).speed * cos((*it).phi) * cos((*it).theta));  
                (*it).pos.y = (*it).pos.y + ((*it).speed * cos((*it).phi) * sin((*it).theta));  
                (*it).pos.z = (*it).pos.z + ((*it).speed * sin((*it).phi));
                (*it).BB = update_BB_pos(bullet_size, (*it).pos);
            }
            else 
            {
                bullets.erase(it);
                continue;
            }
        }
    }
    if (!bullet_sparks.empty())
    {
        for (auto it = bullet_sparks.begin(); it < bullet_sparks.end(); it++)
        {
            if ( (*it).cur_dur < (*it).total_dur ) 
            {
                (*it).cur_dur++;
                (*it).pos.x = (*it).pos.x + ((*it).speed * cos((*it).phi) * cos((*it).theta)); 
                (*it).pos.y = (*it).pos.y + ((*it).speed * cos((*it).phi) * sin((*it).theta));  
                (*it).pos.z = (*it).pos.z + ((*it).speed * sin((*it).phi));
            }
            if ( (*it).cur_dur >= (*it).total_dur )
            {
                bullet_sparks.erase(it);
                continue;
            }
        }
    }


} 


void update_bullets()
{
    bullets_collisions();
    bullets_pos();
}


void update_projectiles()
{
    update_bullets();
}
