#include "player.h"

player::player(world* game_world_, irr::scene::ISceneManager* player_scene, float player_height, float player_width)
{
    game_world_ = game_object::game_world;
    player_scene = game_object::irr_scene;

    movement_keymap[0].Action = irr::EKA_MOVE_FORWARD;
    movement_keymap[0].KeyCode = irr::KEY_KEY_W;

    movement_keymap[1].Action = irr::EKA_MOVE_BACKWARD;
    movement_keymap[1].KeyCode = irr::KEY_KEY_S;

    movement_keymap[2].Action = irr::EKA_STRAFE_LEFT;
    movement_keymap[2].KeyCode = irr::KEY_KEY_A;

    movement_keymap[3].Action = irr::EKA_STRAFE_RIGHT;
    movement_keymap[3].KeyCode = irr::KEY_KEY_D;

    player_camera = game_object::irr_scene->addCameraSceneNodeFPS(0, 100, 0.01, id_unraycastable, movement_keymap, 8, true, 0.0f);
    // player_camera = game_object::irr_scene->addCameraSceneNode(0, irr::core::vector3df(0, 2, 0), irr::core::vector3df(0, 0, 0), id_unraycastable);
    player_camera->setPosition(irr::core::vector3df(0, 5, 0));
    player_camera->setNearValue(0.5f);
    game_object::irr_device->getCursorControl()->setVisible(false);
    game_object::irr_camera = player_camera;
}

player::~player()
{
    game_object::irr_camera->remove();
}

void player::update()
{

}

void player::teleport(irr::core::vector3df& new_pos)
{
    player_camera->setPosition(new_pos);
}
