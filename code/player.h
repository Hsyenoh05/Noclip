#ifndef PLAYER_H
#define PLAYER_H

#include "world.h"

class player : public game_object
{
public:
    float player_height, player_width;

    irr::SKeyMap movement_keymap[8];

    irr::scene::ICameraSceneNode* player_camera;

    player(world* game_world_, irr::scene::ISceneManager* player_scene, float player_height, float player_width);
    ~player();

    void teleport(irr::core::vector3df& new_pos);
    void update();
};

#endif // PLAYER_H
