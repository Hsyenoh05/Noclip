#ifndef OBJECT_H
#define OBJECT_H

#include "game_object.h"
#include "world.h"

class object : public game_object
{
public:
    static void light(float light_red, float light_green, float light_blue, const irr::core::vector3df& light_position, irr::f32 light_radius, bool has_lens_flare);
};

#endif // OBJECT_H
