#include "level.h"
#include "../object.h"
#include "../player.h"

#include "level_0.h"

void level::load_model(const irr::io::path& level_mesh_file, const irr::io::path& level_col_file, bool is_lighting_enabled)
{
    irr::scene::IMesh* level_mesh = game_object::irr_scene->getMesh(level_mesh_file);
    irr::scene::IMesh* level_col = game_object::irr_scene->getMesh(level_col_file);
    irr::scene::IMeshSceneNode* level_node;
    level_node = game_object::irr_scene->addOctreeSceneNode(level_mesh, 0, id_raycastable);
    level_node->setMaterialFlag(irr::video::EMF_LIGHTING, is_lighting_enabled);


    if (level_node)
    {
        game_object::irr_collision = game_object::irr_scene->createOctreeTriangleSelector(level_col, level_node, 128);
        level_node->setTriangleSelector(game_object::irr_collision);
    }

    if (game_object::irr_collision)
    {
        irr::scene::ISceneNodeAnimator* collision_animator = game_object::irr_scene->createCollisionResponseAnimator(game_object::irr_collision,
        game_object::irr_camera, irr::core::vector3df(0.5, 1.4, 0.5), irr::core::vector3df(0, -1, 0), irr::core::vector3df(0, 2, 0));

        game_object::irr_collision->drop();

        game_object::irr_camera->addAnimator(collision_animator);

        collision_animator->drop();
    }
}

int level::load(levels level_id)
{
    switch (level_id)
    {
    case levels::tutorial_level:
        level_0::generate();
        printf("loaded level 0: tutorial level");
        break;
    default:
        printf("please select a level id");
        break;
    }
}
