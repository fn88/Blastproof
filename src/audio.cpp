#include "audio.h"


float master_volume = 0.1;

map<string, Sound> sounds;
Sound bullet_shots[4];

void load_sounds()
{
    sounds.insert(pair<string, Sound>("bullet_shot1", LoadSound("resources/audio/bullet_shot1.ogg")));
    sounds.insert(pair<string, Sound>("bullet_shot2", LoadSound("resources/audio/bullet_shot2.ogg")));
    sounds.insert(pair<string, Sound>("bullet_shot3", LoadSound("resources/audio/bullet_shot3.ogg")));
    sounds.insert(pair<string, Sound>("bullet_shot4", LoadSound("resources/audio/bullet_shot4.ogg")));
    bullet_shots[0] = LoadSound("resources/audio/bullet_shot1.ogg");
    SetSoundVolume(bullet_shots[0], master_volume);
    bullet_shots[1] = LoadSound("resources/audio/bullet_shot2.ogg");
    SetSoundVolume(bullet_shots[1], master_volume);
    bullet_shots[2] = LoadSound("resources/audio/bullet_shot3.ogg");
    SetSoundVolume(bullet_shots[2], master_volume);
    bullet_shots[3] = LoadSound("resources/audio/bullet_shot4.ogg");
    SetSoundVolume(bullet_shots[3], master_volume);

}
