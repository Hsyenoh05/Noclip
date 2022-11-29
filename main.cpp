/*                                                    */
/*     This game is based on the Backrooms fandom     */
/* (https://backrooms.fandom.com/wiki/Backrooms_Wiki) */
/*             and the Backrooms wikidot              */
/*        (http://backrooms-wiki.wikidot.com/)        */
/*   and is licensed under the CC BY-SA 3.0 license   */
/*                                                    */

#include "code/world.h"

int main()
{
    world* gameworld = new world(true);

    while (gameworld->run()) {};

    delete gameworld;

    return 0;
}
