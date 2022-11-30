#include "object.h"

void object::light(float light_red, float light_green, float light_blue, const irr::core::vector3df& light_position, irr::f32 light_radius, bool has_lens_flare)
{
    irr::scene::ILightSceneNode* light = game_object::irr_scene->addLightSceneNode(game_object::irr_camera, light_position, irr::video::SColor(255, light_red, light_green, light_blue), light_radius);

    if (has_lens_flare == true)
    {
        irr::scene::IBillboardSceneNode* lens_flare = game_object::irr_scene->addBillboardSceneNode(0);
            lens_flare->setParent(light);
            lens_flare->setSize(irr::core::dimension2d<irr::f32>(2.0f, 2.0f));
            lens_flare->setColor(irr::video::SColor(255, light_red, light_green, light_blue));
            lens_flare->setMaterialType(irr::video::EMT_TRANSPARENT_ADD_COLOR);
            lens_flare->setMaterialTexture(0, game_object::irr_video->getTexture("assets/particles/lens_flare.png"));
            lens_flare->setMaterialFlag(irr::video::EMF_LIGHTING, false);
            lens_flare->setID(id_unraycastable);

        // white circle in the middle of the lens flare (to make it seem more realistic)
        irr::scene::IBillboardSceneNode* lens_flare_center = game_object::irr_scene->addBillboardSceneNode(0);
            lens_flare_center->setParent(light);
            lens_flare_center->setSize(irr::core::dimension2d<irr::f32>(2.0f, 2.0f));
            lens_flare_center->setMaterialType(irr::video::EMT_TRANSPARENT_ADD_COLOR);
            lens_flare_center->setMaterialTexture(0, game_object::irr_video->getTexture("assets/particles/lens_flare_center.png"));
            lens_flare_center->setMaterialFlag(irr::video::EMF_LIGHTING, false);
            lens_flare_center->setID(id_unraycastable);
    }
}
