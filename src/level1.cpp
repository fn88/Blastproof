#include "level1.h"
#include "set_up.h"


int const LEVEL_SIZE = 42;  // in floor tiles
int const X = LEVEL_SIZE;  
int const Y = LEVEL_SIZE; 
int level_X;   // in meters
int level_Y; 


Vector3 floor_locs[X][Y]; 
vector<model_Obj> generated_buildings{};
vector<model_Obj> * ptr_generated_buildings = &generated_buildings;


void gen_floor()
{
    BoundingBox BBfloor_tile = GetModelBoundingBox(level_models[0]);
    Vector3 floor_tile_size = {BBfloor_tile.max.x - BBfloor_tile.min.x, BBfloor_tile.max.y - BBfloor_tile.min.y, BBfloor_tile.max.z - BBfloor_tile.min.z};
    level_X = LEVEL_SIZE * floor_tile_size.x;
    level_Y = LEVEL_SIZE * floor_tile_size.y;
    for (int h = 0; h < Y; h++)  // h = y. (rows)
    {
        for (int w = 0; w < X; w++)  // w = x. (columns)
        {
            floor_locs[w][h].x = (floor_tile_size.x * w) + floor_tile_size.x/2;
            floor_locs[w][h].y = (floor_tile_size.y * h) + floor_tile_size.y/2;
            floor_locs[w][h].z = 0.0f;
            BoundingBox BBfloor_tile= update_BB_pos(floor_tile_size, floor_locs[w][h]);
            level_objects.push_back(seed_Obj{floor_tile_size, floor_locs[w][h], BBfloor_tile, 0, GREEN});
        }
    }
}


void gen_buildings()
{
    //=============================== perimeter buildings ===================================================
    vector<int> temp_length{};
    int sum = 0; 
    float temp_bloc_x = 0.0f; 
    float temp_bloc_y = 0.0f; 
    // ---- bottom X row-------------------------------------------------------------------------------
    while (sum < level_X)
    {
        int bx = rnd(15, 45);
        temp_length.push_back(bx);
        sum += bx;
        if ( (level_X - sum) <= 45 && (level_X - sum) >= 15 )
        {
            bx = level_X - sum;  
            temp_length.push_back(bx);
            sum += bx;  // should break
        }
    }
    for (auto it = temp_length.begin(); it < temp_length.end(); it++)
    {
        float bsize_x = float(*it);
        float bsize_y = 20.0f;
        float bsize_z = float(rnd(50, 100));
        temp_bloc_x += float(*it);
        Vector3 bsize = {bsize_x, bsize_y, bsize_z};
        Vector3 bloc = {temp_bloc_x - bsize_x/2, -(bsize_y/2), float(bsize_z/2.0f)};
        BoundingBox bBB = update_BB_pos(bsize, bloc);
        Mesh b_mesh = GenMeshCube(bsize_x, bsize_y, bsize_z); 
        Model b_model = LoadModelFromMesh(b_mesh);
        Texture2D b_texture = LoadTexture("resources/textures/floor_texture.png");
        b_model.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = b_texture;
        Color b_color = {float(rnd(100, 200)), float(rnd(100, 200)), float(rnd(100, 200)), 255.0f};
        generated_buildings.push_back(model_Obj{b_model, bsize, bloc, bBB, b_color});
    }
    // -------- top X row---------------------------------------------------------------------
    temp_length.clear();
    sum = 0; 
    while (sum < level_X)
    {
        int bx = rnd(15, 45);
        temp_length.push_back(bx);
        sum += bx;
        if ( (level_X - sum) <= 45 && (level_X - sum) >= 15 )
        {
            bx = level_X - sum;  
            temp_length.push_back(bx);
            sum += bx;  // should break
        }
    }
    temp_bloc_x = 0.0f;
    for (auto it = temp_length.begin(); it < temp_length.end(); it++)
    {
        float bsize_x = float(*it);
        float bsize_y = 20.0f;
        float bsize_z = float(rnd(50, 100));
        temp_bloc_x += float(*it);
        Vector3 bsize = {bsize_x, bsize_y, bsize_z};
        Vector3 bloc = {temp_bloc_x - bsize_x/2, level_Y + (bsize_y/2), float(bsize_z/2.0f)};
        BoundingBox bBB = update_BB_pos(bsize, bloc);
        Mesh b_mesh = GenMeshCube(bsize_x, bsize_y, bsize_z); 
        Model b_model = LoadModelFromMesh(b_mesh);
        Texture2D b_texture = LoadTexture("resources/textures/floor_texture.png");
        b_model.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = b_texture;
        Color b_color = {float(rnd(100, 200)), float(rnd(100, 200)), float(rnd(100, 200)), 255.0f};
        generated_buildings.push_back(model_Obj{b_model, bsize, bloc, bBB, b_color});
    }    
    // -------- left x=0 column-------------------------------------------------------------------------------
    temp_length.clear();
    sum = 0; 
    while (sum < level_Y)
    {
        int by = rnd(15, 45);
        temp_length.push_back(by);
        sum += by;
        if ( (level_Y - sum) <= 45 && (level_Y - sum) >= 15 )
        {
            by = level_Y - sum;  
            temp_length.push_back(by);
            sum += by;  // should break
        }
    }
    temp_bloc_y = 0.0f;
    for (auto it = temp_length.begin(); it < temp_length.end(); it++)
    {
        float bsize_x = 20;
        float bsize_y = float(*it);
        float bsize_z = float(rnd(50, 100));
        temp_bloc_y += float(*it);
        Vector3 bsize = {bsize_x, bsize_y, bsize_z};
        Vector3 bloc = {-bsize_x/2, temp_bloc_y - (bsize_y/2), float(bsize_z/2.0f)};
        BoundingBox bBB = update_BB_pos(bsize, bloc);
        Mesh b_mesh = GenMeshCube(bsize_x, bsize_y, bsize_z); 
        Model b_model = LoadModelFromMesh(b_mesh);
        Texture2D b_texture = LoadTexture("resources/textures/floor_texture.png");
        b_model.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = b_texture;
        Color b_color = {float(rnd(100, 200)), float(rnd(100, 200)), float(rnd(100, 200)), 255.0f};
        generated_buildings.push_back(model_Obj{b_model, bsize, bloc, bBB, b_color});
    }    
}


void place_some_models()  // just temporary random models/objects
{
    BoundingBox BB1 = GetModelBoundingBox(level_models[2]);
    Vector3 size1 = {BB1.max.x - BB1.min.x, BB1.max.y - BB1.min.y, BB1.max.z - BB1.min.z};
    Vector3 pos1 = {300.0, 300.0, 30.0};
    BB1 = update_BB_pos(size1, pos1);
    level_objects.push_back(seed_Obj{size1, pos1, BB1, 2, WHITE});

    BoundingBox BB = GetModelBoundingBox(level_models[1]);
    Vector3 size = {BB.max.x - BB.min.x, BB.max.y - BB.min.y, BB.max.z - BB.min.z};
    Vector3 pos = {50.0, 50.0, 2.0};
    BB = update_BB_pos(size, pos);
    level_objects.push_back(seed_Obj{size, pos, BB, 1, WHITE});

    BoundingBox BB2 = GetModelBoundingBox(level_models[3]);
    Vector3 size2 = {BB2.max.x - BB2.min.x, BB2.max.y - BB2.min.y, BB2.max.z - BB2.min.z};
    Vector3 pos2 = {70.0, 70.0, 2.0};
    BB2 = update_BB_pos(size2, pos2);
    level_objects.push_back(seed_Obj{size2, pos2, BB2, 3, WHITE});
}
