#include "raylib.h"
#include "collisions.h"
#include "enemies.h"
#include "player.h"


void collisions(entity_Obj &entity, vector<model_Obj> * models)
{
    entity.colliding = false;
    for (auto it = (*models).begin(); it < (*models).end(); it++)
    {
        if (CheckCollisionBoxes(entity.BB, (*it).BB))
        {
            entity.colliding = true;
            if (entity.prev_BB.min.x > (*it).BB.max.x)  // check if player collides from +X direction
            {
                if ((entity.BB.max.x > (*it).BB.min.x) && (entity.BB.min.x < (*it).BB.max.x))
                {
                    if ((entity.prev_BB.max.y > (*it).BB.min.y) && (entity.prev_BB.min.y < (*it).BB.max.y))
                    {
                        if ((entity.prev_BB.max.z > (*it).BB.min.z) && (entity.prev_BB.min.z < (*it).BB.max.z))
                        {
                            entity.pos.x = (*it).BB.max.x + (entity.size.x/2 + 0.001f);
                        }
                    }
                }
            }
            if (entity.prev_BB.max.x < (*it).BB.min.x)  // check if player collides from -X direction
            {
                if ((entity.BB.max.x > (*it).BB.min.x) && (entity.BB.min.x < (*it).BB.max.x))
                {
                    if ((entity.prev_BB.max.y > (*it).BB.min.y) && (entity.prev_BB.min.y < (*it).BB.max.y))
                    {
                        if ((entity.prev_BB.max.z > (*it).BB.min.z) && (entity.prev_BB.min.z < (*it).BB.max.z))
                        {
                            entity.pos.x = (*it).BB.min.x - (entity.size.x/2 + 0.001f);
                        }
                    }
                }
            }
            if (entity.prev_BB.min.y > (*it).BB.max.y)  // check if player collides from +Y direction
            {
                if ((entity.prev_BB.max.x > (*it).BB.min.x) && (entity.prev_BB.min.x <= (*it).BB.max.x))
                {
                    if ((entity.BB.max.y > (*it).BB.min.y) && (entity.BB.min.y < (*it).BB.max.y))
                    {
                        if ((entity.prev_BB.max.z > (*it).BB.min.z) && (entity.prev_BB.min.z < (*it).BB.max.z))
                        {
                            entity.pos.y = (*it).BB.max.y + (entity.size.y/2 + 0.001f);
                        }
                    }
                }
            }
            if (entity.prev_BB.max.y < (*it).BB.min.y)  // check if player collides from -Y direction
            {
                if ((entity.prev_BB.max.x > (*it).BB.min.x) && (entity.prev_BB.min.x < (*it).BB.max.x))
                {
                    if ((entity.BB.max.y > (*it).BB.min.y) && (entity.BB.min.y < (*it).BB.max.y))
                    {
                        if ((entity.prev_BB.max.z > (*it).BB.min.z) && (entity.prev_BB.min.z < (*it).BB.max.z))
                        {
                            entity.pos.y = (*it).BB.min.y - (entity.size.y/2 + 0.001f);
                        }
                    }
                }
            }
            if (entity.prev_BB.min.z > (*it).BB.max.z)  // check if player collides from +Z direction            ++++++++++++++++++
            {
                if ((entity.prev_BB.max.x > (*it).BB.min.x) && (entity.prev_BB.min.x < (*it).BB.max.x))
                {
                    if ((entity.prev_BB.max.y > (*it).BB.min.y) && (entity.prev_BB.min.y < (*it).BB.max.y))
                    {
                        if ((entity.BB.max.z > (*it).BB.min.z) && (entity.BB.min.z < (*it).BB.max.z))
                        {
                            entity.pos.z = (*it).BB.max.z + (entity.size.z/2 + 0.001f);
                        }
                    }
                }
            }
            if (entity.prev_BB.max.z < (*it).BB.min.z)  // check if player collides from -Z direction
            {
                if ((entity.BB.max.z > (*it).BB.min.z) && (entity.BB.min.z < (*it).BB.max.z))
                {
                    if ((entity.prev_BB.max.y > (*it).BB.min.y) && (entity.prev_BB.min.y < (*it).BB.max.y))
                    {
                        if ((entity.prev_BB.max.x > (*it).BB.min.x) && (entity.prev_BB.min.x < (*it).BB.max.x)) 
                        {
                            entity.pos.z = (*it).BB.min.z - (entity.size.z/2 + 0.001f);
                        }
                    }
                }
            }
        }
    }
    entity.BB = update_BB_pos(entity.size, entity.pos);
}

void gravity_collisions(entity_Obj &entity, vector<model_Obj> * models)
{
    entity.grounded = false;
    BoundingBox dZ_BB = update_BB_pos(entity.size, Vector3{entity.pos.x, entity.pos.y, (entity.pos.z - 0.002f)});  // dZ - delta z (0.002)
    for (auto it = (*models).begin(); it < (*models).end(); it++)
    {
        if (CheckCollisionBoxes(dZ_BB, (*it).BB))  
        {
            entity.grounded = true;
            entity.time_not_grounded = 0;
            break;
        }
    }
}

void collisions_generated(entity_Obj &entity, vector<model_Obj> * models)
{
    entity.colliding = false;
    for (auto it = (*models).begin(); it < (*models).end(); it++)
    {
        if (CheckCollisionBoxes(entity.BB, (*it).BB))
        {
            entity.colliding = true;
            if (entity.prev_BB.min.x > (*it).BB.max.x)  // check if player collides from +X direction
            {
                if ((entity.BB.max.x > (*it).BB.min.x) && (entity.BB.min.x < (*it).BB.max.x))
                {
                    if ((entity.prev_BB.max.y > (*it).BB.min.y) && (entity.prev_BB.min.y < (*it).BB.max.y))
                    {
                        if ((entity.prev_BB.max.z > (*it).BB.min.z) && (entity.prev_BB.min.z < (*it).BB.max.z))
                        {
                            entity.pos.x = (*it).BB.max.x + (entity.size.x/2 + 0.001f);
                        }
                    }
                }
            }
            if (entity.prev_BB.max.x < (*it).BB.min.x)  // check if player collides from -X direction
            {
                if ((entity.BB.max.x > (*it).BB.min.x) && (entity.BB.min.x < (*it).BB.max.x))
                {
                    if ((entity.prev_BB.max.y > (*it).BB.min.y) && (entity.prev_BB.min.y < (*it).BB.max.y))
                    {
                        if ((entity.prev_BB.max.z > (*it).BB.min.z) && (entity.prev_BB.min.z < (*it).BB.max.z))
                        {
                            entity.pos.x = (*it).BB.min.x - (entity.size.x/2 + 0.001f);
                        }
                    }
                }
            }
            if (entity.prev_BB.min.y > (*it).BB.max.y)  // check if player collides from +Y direction
            {
                if ((entity.prev_BB.max.x > (*it).BB.min.x) && (entity.prev_BB.min.x <= (*it).BB.max.x))
                {
                    if ((entity.BB.max.y > (*it).BB.min.y) && (entity.BB.min.y < (*it).BB.max.y))
                    {
                        if ((entity.prev_BB.max.z > (*it).BB.min.z) && (entity.prev_BB.min.z < (*it).BB.max.z))
                        {
                            entity.pos.y = (*it).BB.max.y + (entity.size.y/2 + 0.001f);
                        }
                    }
                }
            }
            if (entity.prev_BB.max.y < (*it).BB.min.y)  // check if player collides from -Y direction
            {
                if ((entity.prev_BB.max.x > (*it).BB.min.x) && (entity.prev_BB.min.x < (*it).BB.max.x))
                {
                    if ((entity.BB.max.y > (*it).BB.min.y) && (entity.BB.min.y < (*it).BB.max.y))
                    {
                        if ((entity.prev_BB.max.z > (*it).BB.min.z) && (entity.prev_BB.min.z < (*it).BB.max.z))
                        {
                            entity.pos.y = (*it).BB.min.y - (entity.size.y/2 + 0.001f);
                        }
                    }
                }
            }
            if (entity.prev_BB.min.z > (*it).BB.max.z)  // check if player collides from +Z direction            ++++++++++++++++++
            {
                if ((entity.prev_BB.max.x > (*it).BB.min.x) && (entity.prev_BB.min.x < (*it).BB.max.x))
                {
                    if ((entity.prev_BB.max.y > (*it).BB.min.y) && (entity.prev_BB.min.y < (*it).BB.max.y))
                    {
                        if ((entity.BB.max.z > (*it).BB.min.z) && (entity.BB.min.z < (*it).BB.max.z))
                        {
                            entity.pos.z = (*it).BB.max.z + (entity.size.z/2 + 0.001f);
                        }
                    }
                }
            }
            if (entity.prev_BB.max.z < (*it).BB.min.z)  // check if player collides from -Z direction
            {
                if ((entity.BB.max.z > (*it).BB.min.z) && (entity.BB.min.z < (*it).BB.max.z))
                {
                    if ((entity.prev_BB.max.y > (*it).BB.min.y) && (entity.prev_BB.min.y < (*it).BB.max.y))
                    {
                        if ((entity.prev_BB.max.x > (*it).BB.min.x) && (entity.prev_BB.min.x < (*it).BB.max.x)) 
                        {
                            entity.pos.z = (*it).BB.min.z - (entity.size.z/2 + 0.001f);
                        }
                    }
                }
            }
        }
    }
    entity.BB = update_BB_pos(entity.size, entity.pos);
}

void entity_collisions(entity_Obj &e1, entity_Obj &e2)
{
    e1.colliding = false;
    if (CheckCollisionBoxes(e1.BB, e2.BB))
    {
        e1.colliding = true;
        if (e1.prev_BB.min.x > e2.BB.max.x)  // check if player collides from +X direction
        {
            if ((e1.BB.max.x > e2.BB.min.x) && (e1.BB.min.x < e2.BB.max.x))
            {
                if ((e1.prev_BB.max.y > e2.BB.min.y) && (e1.prev_BB.min.y < e2.BB.max.y))
                {
                    if ((e1.prev_BB.max.z > e2.BB.min.z) && (e1.prev_BB.min.z < e2.BB.max.z))
                    {
                        e1.pos.x = e2.BB.max.x + (e1.size.x/2 + 0.001f);
                    }
                }
            }
        }
        if (e1.prev_BB.max.x < e2.BB.min.x)  // check if player collides from -X direction
        {
            if ((e1.BB.max.x > e2.BB.min.x) && (e1.BB.min.x < e2.BB.max.x))
            {
                if ((e1.prev_BB.max.y > e2.BB.min.y) && (e1.prev_BB.min.y < e2.BB.max.y))
                {
                    if ((e1.prev_BB.max.z > e2.BB.min.z) && (e1.prev_BB.min.z < e2.BB.max.z))
                    {
                        e1.pos.x = e2.BB.min.x - (e1.size.x/2 + 0.001f);
                    }
                }
            }
        }
        if (e1.prev_BB.min.y > e2.BB.max.y)  // check if player collides from +Y direction
        {
            if ((e1.prev_BB.max.x > e2.BB.min.x) && (e1.prev_BB.min.x <= e2.BB.max.x))
            {
                if ((e1.BB.max.y > e2.BB.min.y) && (e1.BB.min.y < e2.BB.max.y))
                {
                    if ((e1.prev_BB.max.z > e2.BB.min.z) && (e1.prev_BB.min.z < e2.BB.max.z))
                    {
                        e1.pos.y = e2.BB.max.y + (e1.size.y/2 + 0.001f);
                    }
                }
            }
        }
        if (e1.prev_BB.max.y < e2.BB.min.y)  // check if player collides from -Y direction
        {
            if ((e1.prev_BB.max.x > e2.BB.min.x) && (e1.prev_BB.min.x < e2.BB.max.x))
            {
                if ((e1.BB.max.y > e2.BB.min.y) && (e1.BB.min.y < e2.BB.max.y))
                {
                    if ((e1.prev_BB.max.z > e2.BB.min.z) && (e1.prev_BB.min.z < e2.BB.max.z))
                    {
                        e1.pos.y = e2.BB.min.y - (e1.size.y/2 + 0.001f);
                    }
                }
            }
        }
        if (e1.prev_BB.min.z > e2.BB.max.z)  // check if player collides from +Z direction            ++++++++++++++++++
        {
            if ((e1.prev_BB.max.x > e2.BB.min.x) && (e1.prev_BB.min.x < e2.BB.max.x))
            {
                if ((e1.prev_BB.max.y > e2.BB.min.y) && (e1.prev_BB.min.y < e2.BB.max.y))
                {
                    if ((e1.BB.max.z > e2.BB.min.z) && (e1.BB.min.z < e2.BB.max.z))
                    {
                        e1.pos.z = e2.BB.max.z + (e1.size.z/2 + 0.001f);
                    }
                }
            }
        }
        if (e1.prev_BB.max.z < e2.BB.min.z)  // check if player collides from -Z direction
        {
            if ((e1.BB.max.z > e2.BB.min.z) && (e1.BB.min.z < e2.BB.max.z))
            {
                if ((e1.prev_BB.max.y > e2.BB.min.y) && (e1.prev_BB.min.y < e2.BB.max.y))
                {
                    if ((e1.prev_BB.max.x > e2.BB.min.x) && (e1.prev_BB.min.x < e2.BB.max.x)) 
                    {
                        e1.pos.z = e2.BB.min.z - (e1.size.z/2 + 0.001f);
                    }
                }
            }
        }
    }
    e1.BB = update_BB_pos(e1.size, e1.pos);
}


void player_collisions()
{
    collisions(player, ptr_level_objects);
    collisions_generated(player, ptr_generated_buildings);
    gravity_collisions(player, ptr_level_objects);
    for (auto it = enemies.begin(); it < enemies.end(); it++) entity_collisions(player, *it);
}

void enemies_collisions()
{
    for (auto it = enemies.begin(); it < enemies.end(); it++) collisions((*it), ptr_level_objects);
    for (auto it = enemies.begin(); it < enemies.end(); it++) collisions_generated((*it), ptr_generated_buildings);
    for (auto it = enemies.begin(); it < enemies.end(); it++) gravity_collisions((*it), ptr_level_objects);
}


void all_collisions()
{
    player_collisions();
    enemies_collisions();
}