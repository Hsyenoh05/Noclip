#ifndef LEVEL_H
#define LEVEL_H

#include "../game_object.h"
#include "../world.h"

enum class levels
{
    tutorial_level
};

class level : public game_object
{
protected:
    int angle = 0;

public:
    static levels level_id;

    static void load_model(const irr::io::path& place_mesh_file, const irr::io::path& place_col_file, bool is_lighting_enabled);

    static int load(levels level_id);
};

#endif // LEVEL_H
