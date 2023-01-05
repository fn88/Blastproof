#include "models.h"
#include "raylib.h"
#include "raymath.h"


Model level_models[4];


BoundingBox update_BB_pos(Vector3 size, Vector3 pos)
{
    BoundingBox moved_box = {Vector3({  pos.x - size.x/2, 
                                        pos.y - size.y/2, 
                                        pos.z - size.z/2}), 
                             Vector3({  pos.x + size.x/2, 
                                        pos.y + size.y/2, 
                                        pos.z + size.z/2}) };
    return moved_box;
} 

Model load_model(const char *model_file, const char *texture_file)
{
    Model model = LoadModel(model_file);
    Texture2D texture = LoadTexture(texture_file);
    model.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = texture;
    return model;
}


void load_level_models()
{
    level_models[0] = load_model("resources/models/level_floor.obj", "resources/textures/floor_texture.png");  // level_floor
    level_models[1] = load_model("resources/models/box1.obj", "resources/textures/floor_texture.png");          // box
    level_models[2] = load_model("resources/models/blenderXYZwidget.obj", "resources/textures/blenderXYZwidgetTexture.png");  // xyzwidget
    level_models[3] = load_model("resources/models/bullet.obj", "resources/textures/bullet_texture.png");  // bullet

    //level_models[4] = load_model("resources/models/level_floor.obj", "resources/textures/floor_texture.png");
    //level_models[5] = load_model("resources/models/level_floor.obj", "resources/textures/floor_texture.png");

}
    
