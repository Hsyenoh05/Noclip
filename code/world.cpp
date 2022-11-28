#include "world.h"
#include "player.h"
#include "object.h"

#include "levels/level_0.h"

world* game_object::game_world = nullptr;
player* game_object::main_player = nullptr;
irr::IrrlichtDevice* game_object::irr_device = nullptr;
irr::scene::ISceneManager* game_object::irr_scene = nullptr;
irr::video::IVideoDriver* game_object::irr_video = nullptr;
irr::gui::IGUIEnvironment* game_object::irr_gui = nullptr;
irr::scene::ITriangleSelector* game_object::irr_collision = nullptr;
irr::scene::ICameraSceneNode* game_object::irr_camera = nullptr;
int game_object::res_x = 0;
int game_object::res_y = 0;

void world::initializer()
{
    if (ready)
    {
        device = irr::createDevice(irr::video::EDT_OPENGL, irr::core::dimension2d<irr::u32>(window_x, window_y), 32, is_fullscreen, false, true, &receiver);
        game_object::irr_device = device;
        scene_manager = device->getSceneManager();
        video_driver = device->getVideoDriver();
        game_object::irr_scene = scene_manager;
        game_object::irr_video = video_driver;

        printf(":(");

        collision_manager = scene_manager->getSceneCollisionManager();

        gui_environment = device->getGUIEnvironment();
        game_object::irr_gui = gui_environment;
        gui_skin = gui_environment->getSkin();

        ludio_font = gui_environment->getFont("assets/fonts/ludio.xml");

        fps_count = gui_environment->addStaticText(L"FPS:???", irr::core::recti(window_x - 95, 0, window_x, window_y));

        device->setWindowCaption(L"Noclip"); /* window name */
        gui_environment->addStaticText(L"0.0.1", irr::core::recti(0, 0, window_x, window_y)); /* version number */

        gui_skin->setFont(ludio_font);                                                          /*   set up   */
        gui_skin->setColor(irr::gui::EGDC_BUTTON_TEXT, irr::video::SColor(255, 255, 255, 255)); /*  main font */

        previous_time = device->getTimer()->getTime(); /* previous cpu tick */

        init_player(); /* initialize  player */
    }
}

void world::init_player()
{
    player* mainplayer = new player(this, irr_scene, 1.4, 0.85); /* add new player */
}

void world::frame_delta_time()
{
    const irr::u32 current_time = device->getTimer()->getTime();                    /* current cpu tick */
    const irr::f32 delta_time = (irr::f32)(current_time - previous_time) / 1000.0f; /* frame-independent time ticking */
    previous_time = current_time;                                                   /* make previous tick equal to current tick */
}

void world::raycast()
{
    irr::core::line3d<irr::f32> raycast; /* initialize raycast */
    raycast.start = game_object::irr_camera->getPosition(); /* begin raycast */
    raycast.end = raycast.start + (game_object::irr_camera->getTarget() - raycast.start).normalize() * raycast_distance; /* end raycast */

    irr::core::vector3df intersection;   /* initialize raycast hit point */
    irr::core::triangle3df hit_triangle; /*   detect raycasted polygon   */

    irr::scene::ISceneNode* selected_object = collision_manager->getSceneNodeAndCollisionPointFromRay(raycast, intersection, hit_triangle, id_raycastable, 0); /* detect selected object */

    if (selected_object)
    {
        if (receiver.mouse_state.left_button_is_down == true)
        {
            printf("."); /* print something */
        }
    }
}


void world::render_text(bool render_fps, bool render_debug)
{
    if (render_fps == true)
    {
        int current_fps = video_driver->getFPS(); /* get current framerate count */
        if (previous_fps != current_fps)
        {
            irr::core::stringw fps_string = L"FPS:"; /* setup fps string */
            fps_string += current_fps;               /* add current framerate per second count to the string */
            fps_count->setText(fps_string.c_str());  /* update fps counter */
            previous_fps = current_fps;              /* update framerate count */
        }
    }

}

world::world(bool launcher_enabled)
{
    use_launcher = launcher_enabled;

    if (use_launcher)
    {
        launcher();
    }

    if (!ready)
    {
        exit(1);
    }

    initializer(); /* initializer */

    level_0::load_place(); /* load place */
}

/// while loop ///
bool world::run()
{
    while (device->run())
    {
        if (device->isWindowActive())
        {
            video_driver->beginScene(true, true, irr::video::SColor(255, 0, 0, 0));

            scene_manager->drawAll();
            gui_environment->drawAll();

            video_driver->endScene();

            render_text(true, false);

            raycast();

            // close game
            if (receiver.is_key_down(irr::KEY_F12))
            {
                device->closeDevice();
                return 0;
            }
        }
        else
        {
            device->yield();
        }
    }
}

world::~world()
{
    device->drop();
}
