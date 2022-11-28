#include "place.h"
#include "../object.h"
#include "../player.h"

void place::load_place(const irr::io::path& place_mesh_file, const irr::io::path& place_col_file)
{
    irr::scene::IMesh* place_mesh = game_object::irr_scene->getMesh(place_mesh_file);
    irr::scene::IMesh* place_col = game_object::irr_scene->getMesh(place_col_file);
    irr::scene::IMeshSceneNode* place_id;
    place_id = game_object::irr_scene->addOctreeSceneNode(place_mesh, 0, id_raycastable);
    place_id->setMaterialFlag(irr::video::EMF_LIGHTING, false);

    if (place_id)
    {
        game_object::irr_collision = game_object::irr_scene->createOctreeTriangleSelector(place_col, place_id, 128);
        place_id->setTriangleSelector(game_object::irr_collision);
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
