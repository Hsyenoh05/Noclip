#ifndef PLACE_H
#define PLACE_H

#include "../game_object.h"
#include "../world.h"

class place : public game_object
{
protected:
    int angle = 0;

public:
    static void load_place(const irr::io::path& place_mesh_file, const irr::io::path& place_col_file);
};

#endif // PLACE_H
