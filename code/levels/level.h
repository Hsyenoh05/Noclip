#ifndef LEVEL_H
#define LEVEL_H

#include "../game_object.h"
#include "../world.h"

class level : public game_object
{
protected:
    int angle = 0;

public:
    static void load_place(const irr::io::path& place_mesh_file, const irr::io::path& place_col_file);
};

#endif // LEVEL_H
