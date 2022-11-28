/*                                                    */
/*     This game is based on the Backrooms wiki       */
/* (https://backrooms.fandom.com/wiki/Backrooms_Wiki) */
/*   and is licensed under the CC BY-SA 3.0 license   */
/*                                                    */

#include <irrlicht.h>
#include "code/world.h"

int main()
{
    world* gameworld = new world(true);

    while (gameworld->run()) {};

    delete gameworld;

    return 0;
}
