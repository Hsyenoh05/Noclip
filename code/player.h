#ifndef PLAYER_H
#define PLAYER_H

#include "world.h"

class player : public game_object
{
public:
    float player_height, player_width;

    int yaw, pitch;

    bool is_dead = false;

    irr::SKeyMap movement_keymap[8];

    irr::scene::ICameraSceneNode* player_camera;

    player(world* game_world_, irr::scene::ISceneManager* player_scene, float player_height, float player_width);
    ~player();
};

#endif // PLAYER_H
