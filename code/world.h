#ifndef WORLD_H
#define WORLD_H

#include "game_object.h"

enum
{
    id_raycastable = 1 << 0, // object can be hit by raycast
    id_unraycastable = 0, // object can not be hit with raycast
    id_interactable = 1 << 1 // object gets highlighted when looked at (unused)
};

class event_receiver : public irr::IEventReceiver
{
public:
    struct mouse_states
    {
        irr::core::position2di position;
        bool left_button_is_down = false;
        bool right_button_is_down = false;
    } mouse_state;

    virtual bool OnEvent(const irr::SEvent& event)
    {
        if (event.EventType == irr::EET_KEY_INPUT_EVENT)
        {
            key_is_down[event.KeyInput.Key] = event.KeyInput.PressedDown;
        }
        if (event.EventType == irr::EET_MOUSE_INPUT_EVENT)
        {
            switch(event.MouseInput.Event)
            {
            case irr::EMIE_LMOUSE_PRESSED_DOWN:
                mouse_state.left_button_is_down = true;
                break;
            case irr::EMIE_LMOUSE_LEFT_UP:
                mouse_state.left_button_is_down = false;
                break;
            case irr::EMIE_RMOUSE_PRESSED_DOWN:
                mouse_state.right_button_is_down = true;
                break;
            case irr::EMIE_RMOUSE_LEFT_UP:
                mouse_state.right_button_is_down = false;
                break;
            case irr::EMIE_MOUSE_MOVED:
                mouse_state.position.X = event.MouseInput.X;
                mouse_state.position.Y = event.MouseInput.Y;
                break;
            default:
                break;
            }
        }

        return false;
    }
    virtual bool is_key_down(irr::EKEY_CODE key_code)
    {
        return key_is_down[key_code];
    }

    const mouse_states & get_mouse_state(void) const
    {
        return mouse_state;
    }

    event_receiver()
    {
        for (irr::u32 i = 0; i < irr::KEY_KEY_CODES_COUNT; ++i)
        {
            key_is_down[i] = false;
        }
    }

private:
    bool key_is_down[irr::KEY_KEY_CODES_COUNT];
};

/// main class ///
class world : public game_object
{
protected:
    void initializer();                                   /*           */
    void init_player();                                   /*           */
    void frame_delta_time();                              /* functions */
    void raycast();                                       /*           */
    void render_text(bool render_fps, bool render_debug); /*           */
public:
    // launcher variables
    bool use_launcher;  /* toggle launcher */
    bool ready; /* if true, the game will start after using the launcher */
    int launcher(); /* open launcher */

    // variables
    unsigned short window_x = 640, window_y = 480; /* screen resolution's width and height */
    bool is_fullscreen = false;                /* toggle fullscreen */
    int previous_fps = -1;             /* previous cpu tick */
    int raycast_distance = 4;          /* distance of the player's raycast */

    irr::u32 previous_time;

    // initializing devices
    event_receiver receiver;                    /* make event receiver instance */
    irr::IrrlichtDevice* device;                /* initialize irrlicht device */
    irr::scene::ISceneManager* scene_manager;   /* initialize scene manager */
    irr::video::IVideoDriver* video_driver;     /* initialize video driver */
    irr::gui::IGUIEnvironment* gui_environment; /* initialize gui environment */

    // setting main font
    irr::gui::IGUISkin* gui_skin;   /* gui skin */
    irr::gui::IGUIFont* ludio_font; /* main font */

    // text
    irr::gui::IGUIStaticText* fps_count;  /* fps counter text */
    irr::gui::IGUIStaticText* debug_text; /* debug text */

    // collision
    irr::scene::ITriangleSelector* collision_selector;     /* collision selector */
    irr::scene::ISceneNode* interactable_object;           /* interactable object */
    irr::scene::ISceneCollisionManager* collision_manager; /* collision manager */

    world(bool launcher_enabled); /* game constructor */
    ~world(); /* game destructor */

    bool run(); /* while loop */
};

#endif // WORLD_H
