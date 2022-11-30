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

void world::initializer()
{
    device = irr::createDevice(irr::video::EDT_OPENGL, irr::core::dimension2d<irr::u32> /* initialize */
    (window_x, window_y), 32, is_fullscreen, false, true, &receiver);                   /*   device   */
    scene_manager = device->getSceneManager(); /* initialize scene manager */
    video_driver = device->getVideoDriver(); /* initialize video driver */

    collision_manager = scene_manager->getSceneCollisionManager(); /* initialize collision manager */

    gui_environment = device->getGUIEnvironment(); /* initialize gui environment */

    game_object::irr_device = device;       /*                      */
    game_object::irr_scene = scene_manager; /*    instances for     */
    game_object::irr_video = video_driver;  /* non-member functions */
    game_object::irr_gui = gui_environment; /*                      */

    gui_skin = gui_environment->getSkin();  /* initialize gui skin */

    irr_scene->getParameters()->setAttribute(irr::scene::B3D_TEXTURE_PATH, "assets/textures");

    ludio_font = gui_environment->getFont("assets/fonts/ludio.xml"); /* load main font */

    fps_count = gui_environment->addStaticText(L"FPS:???", irr::core::recti(window_x - 95, 0, window_x, window_y)); /* fps counter */
    debug_text = gui_environment->addStaticText(L"DEBUG", irr::core::recti(0, window_y / 2, window_x, window_y)); /* fps counter */

    device->setWindowCaption(L"Noclip"); /* window name */
    gui_environment->addStaticText(L"0.0.1", irr::core::recti(0, 0, window_x, window_y)); /* version number */

    gui_skin->setFont(ludio_font);                                                          /*   set up   */
    gui_skin->setColor(irr::gui::EGDC_BUTTON_TEXT, irr::video::SColor(255, 255, 255, 255)); /*  main font */

    previous_time = device->getTimer()->getTime(); /* previous cpu tick */

    init_player(); /* initialize  player */
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
    if (render_debug == true)
    {
        irr::core::stringw debug_string = L"Camera Target X:";
        debug_string += game_object::irr_camera->getTarget().X;
        debug_string += L"\n\nCamera Target Y:";
        debug_string += game_object::irr_camera->getTarget().Y;
        debug_string += L"\n\nCamera Position X:";
        debug_string += game_object::irr_camera->getPosition().X;
        debug_string += L"\n\nCamera Position Y:";
        debug_string += game_object::irr_camera->getPosition().Y;
        debug_string += L"\n\nCamera Position Z:";
        debug_string += game_object::irr_camera->getPosition().Z;
        debug_string += L"\n\nCamera Rotation X:";
        debug_string += game_object::irr_camera->getRotation().X;
        debug_string += L"\n\nCamera Rotation Y:";
        debug_string += game_object::irr_camera->getRotation().Y;
        debug_string += L"\n\nCamera Rotation Z:";
        debug_string += game_object::irr_camera->getRotation().Z;

        debug_text->setText(debug_string.c_str());
    }

}

world::world(bool launcher_enabled)
{
    use_launcher = launcher_enabled;

    if (use_launcher)
    {
        launcher();

        if (!ready)
        {
            exit(1);
        }
    }

    ready = true;

    initializer(); /* initializer */

    level::load(levels::tutorial_level);

    object::light(255, 255, 255, irr::core::vector3df(0, 2, 0), 5.0f, true);

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

            render_text(true, true);

            raycast();

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
