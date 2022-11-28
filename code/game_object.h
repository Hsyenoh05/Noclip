#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

#include <irrlicht.h>
#include <SFML/Graphics.hpp>

class game_object
{
protected:
    static class world* game_world;
    static class player* main_player;
    static irr::IrrlichtDevice* irr_device;;
    static irr::scene::ITriangleSelector* irr_collision;
    static irr::scene::ICameraSceneNode* irr_camera;
public:
    static irr::scene::ISceneManager* irr_scene;
    static irr::video::IVideoDriver* irr_video;
    static irr::gui::IGUIEnvironment* irr_gui;
};

#endif // GAME_OBJECT_H
