#include "raymath.h"
#include "projectiles.h"
#include "level1.h"
#include "enemies.h"
#include "audio.h"
#include "set_up.h"

Ray b_ray = {0};
vector<simple_projectile> bullets{};
vector<simple_projectile> bullet_sparks{};  // explosion sparks upon hit/impact
Vector3 bullet_size = {3.0f, 2.0f, 2.0f};  // bigger than model size for BB/collisions


void shoot_bullet(Vector3 pos, float theta, float phi)
{
    Model b = level_models[3];
    b.transform = MatrixRotateXYZ({0.0f, phi, -theta});
    float b_speed = 10.0f + float(rnd(1, 10))/20.0f;
    float b_theta = theta + float(rnd(-10, 10))/5000.0f;  // spread
    float b_phi = phi + float(rnd(-10, 10))/5000.0f;  // spread
    unsigned int b_total_dur = rnd(90, 120);
    unsigned int b_cur_dur = 0;
    float dir_x = cos(b_phi) * cos(b_theta);
    float dir_y = cos(b_phi) * sin(b_theta);
    float dir_z = sin(b_phi);
    bullets.push_back(simple_projectile{b, pos, {dir_x, dir_y, dir_z}, update_BB_pos(bullet_size, pos), b_total_dur, b_cur_dur, b_speed});
    PlaySoundMulti(bullet_shots[rnd(0, 3)]);
}

void bullet_sparks_made(Vector3 pos)
{
    int a = rnd(2, 8);  // number of sparks
    for (int i = 0; i < a; i++)
    {
        unsigned int bs_total_dur = rnd(1, 5);
        unsigned int bs_cur_dur = 0;
        float bs_speed = 2.0f + float(rnd(1, 10))/10;
        float bs_theta = float(rnd(1, 628)) / 100.0f;
        float bs_phi = float(rnd(1, 628)) / 100.0f;
        float dir_x = cos(bs_phi) * cos(bs_theta);
        float dir_y = cos(bs_phi) * sin(bs_theta);
        float dir_z = sin(bs_phi);
        Model bs = level_models[3];
        bs.transform = MatrixRotateXYZ({0.0f, bs_phi, -bs_theta});
        bullet_sparks.push_back(simple_projectile{bs, pos, {dir_x, dir_y, dir_z}, update_BB_pos(bullet_size, pos), bs_total_dur, bs_cur_dur, bs_speed});
    }
}
//-------------------------------------------

void bc_generated_buildings()
{
    if (!bullets.empty())
    {
        for (auto it1 = bullets.begin(); it1 < bullets.end(); it1++)
        {
            for (auto it2 = generated_buildings.begin(); it2 < generated_buildings.end(); it2++)
            {
                if ( CheckCollisionBoxSphere((*it2).BB, (*it1).pos, (*it1).speed) )
                {
                    float cx = (*it1).speed * (*it1).dir.x;  
                    float cy = (*it1).speed * (*it1).dir.y;  
                    float cz = (*it1).speed * (*it1).dir.z; 
                    Vector3 p = {(*it1).pos.x + cx, (*it1).pos.y + cy, (*it1).pos.z + cz};  
                    for (int i = 4; i < 9; i++)
                    {
                        Vector3 bs_pos = { p.x - cx*(float(i)/4), p.y - cy*(float(i)/4), p.z - cz*(float(i)/4) };
                        if ( CheckCollisionBoxSphere( (*it2).BB, bs_pos, 0.1f) )
                        {

                        bullet_sparks_made(bs_pos);
                        bullets.erase(it1);
                        it2 = generated_buildings.end();
                        break;
                        }
                    }
                }
            }
        }
    }
}  

void bc_entities()
{
    if (!enemies.empty())
    {
        for (auto it1 = bullets.begin(); it1 < bullets.end(); it1++)
        {
            for (auto it2 = enemies.begin(); it2 < enemies.end(); it2++)
            {
                if ( CheckCollisionBoxSphere((*it2).BB, (*it1).pos, (*it1).speed) )
                {
                    float cx = (*it1).speed * (*it1).dir.x;  
                    float cy = (*it1).speed * (*it1).dir.y;  
                    float cz = (*it1).speed * (*it1).dir.z; 
                    Vector3 p = {(*it1).pos.x + cx, (*it1).pos.y + cy, (*it1).pos.z + cz};  
                    for (int i = 0; i < 9; i++)
                    {
                        Vector3 bs_pos = { p.x - cx*(float(i)/4), p.y - cy*(float(i)/4), p.z - cz*(float(i)/4) };
                        if ( CheckCollisionBoxSphere( (*it2).BB, {bs_pos}, 1.0f) )
                        {
                            bullet_sparks_made({bs_pos});
                            (*it2).health -= 10;
                            bullets.erase(it1);
                            (*it2).foe = (*it1).owner_id;
                            it2 = enemies.end();
                            break;
                        }
                    }
                }
            }
        }
    }
//--------PLAYER------------------
    for (auto it1 = bullets.begin(); it1 < bullets.end(); it1++)
    {
        if ( CheckCollisionBoxSphere(player.BB, (*it1).pos, (*it1).speed) )
        {
            float cx = (*it1).speed * (*it1).dir.x;  
            float cy = (*it1).speed * (*it1).dir.y;  
            float cz = (*it1).speed * (*it1).dir.z; 
            Vector3 p = {(*it1).pos.x + cx, (*it1).pos.y + cy, (*it1).pos.z + cz};  
            for (int i = 0; i < 9; i++)
            {
                Vector3 bs_pos = { p.x - cx*(float(i)/4), p.y - cy*(float(i)/4), p.z - cz*(float(i)/4) };
                if ( CheckCollisionBoxSphere( player.BB, {bs_pos}, 1.0f) )
                {
                    bullet_sparks_made({bs_pos});
                    player.health -= 10;
                    bullets.erase(it1);
                    break;
                }
            }
        }
    }
}

void bc_level_objects()
{
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

void all_bullets_collisions()
{
    bc_generated_buildings();
    bc_entities();
    //bc_level_objects();
}
//-------------------------------------------
void bullets_pos()
{
    if (!bullets.empty())
    {
        for (auto it = bullets.begin(); it < bullets.end(); it++)
        {
            if ( (*it).cur_dur < (*it).total_dur ) 
            {
                (*it).cur_dur++;
                (*it).pos.x = (*it).pos.x + ((*it).speed * (*it).dir.x);  //cos((*it).phi) * cos((*it).theta));  
                (*it).pos.y = (*it).pos.y + ((*it).speed * (*it).dir.y);  //cos((*it).phi) * sin((*it).theta));  
                (*it).pos.z = (*it).pos.z + ((*it).speed * (*it).dir.z);  //sin((*it).phi));
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
                (*it).pos.x = (*it).pos.x + ((*it).speed * (*it).dir.x);  //cos((*it).phi) * cos((*it).theta));  
                (*it).pos.y = (*it).pos.y + ((*it).speed * (*it).dir.y);  //cos((*it).phi) * sin((*it).theta));  
                (*it).pos.z = (*it).pos.z + ((*it).speed * (*it).dir.z);  //sin((*it).phi));
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
    bullets_pos();
    all_bullets_collisions();
}

void update_projectiles()
{
    update_bullets();
}
