g++ src\MAIN_file.cpp src\set_up.cpp src\draw.cpp src\player.cpp src\game_update.cpp src\models.cpp src\collisions.cpp src\level1.cpp src\enemies.cpp src\projectiles.cpp  src\audio.cpp -o GAME2.exe -std=c++17 -O1  -Wno-missing-braces -Wno-narrowing -Wunused-variable -I include/ -L lib/ -lraylib -lopengl32 -lgdi32 -lwinmm 