#include "world.h"

unsigned short window_w = 640, window_h = 480;
bool use_fullscreen = false;
bool is_ready;

struct launcher_context
{
    irr::IrrlichtDevice *launcher_device;
};

enum
{
    launcher_button_play,
    launcher_button_fullscreen,
    launcher_button_res_1,
    launcher_button_res_2,
    launcher_button_res_3,
    launcher_button_res_4,
    launcher_button_res_5,
    launcher_button_res_6,
    launcher_button_res_7,
    launcher_button_res_8,
    launcher_button_res_9,
    launcher_button_res_10,
    launcher_button_res_11,
    launcher_button_res_12
};

irr::gui::IGUIButton* button_fullscreen;

class launcher_receiver : public irr::IEventReceiver
{
public:
    launcher_receiver(launcher_context & context) : Context(context) { }

    virtual bool OnEvent(const irr::SEvent& launcher_event)
    {
        if (launcher_event.EventType == irr::EET_GUI_EVENT)
		{
			irr::s32 id = launcher_event.GUIEvent.Caller->getID();

			switch(launcher_event.GUIEvent.EventType)
			{
			case irr::gui::EGET_BUTTON_CLICKED:
				switch(id)
				{
				case launcher_button_play:
                {
                    is_ready = true;
                    printf("game launched!\n");
                }
                return true;

            case launcher_button_fullscreen:
                {
                    if (use_fullscreen == false)
                    {
                        use_fullscreen = true;
                        printf("fullscreen on!\n");
                        button_fullscreen->setText(L"Fullscreen:ON");
                    }
                    else
                    {
                        if (use_fullscreen == true)
                        {
                            use_fullscreen = false;
                            printf("fullscreen off!\n");
                            button_fullscreen->setText(L"Fullscreen:OFF");
                        }
                    }

                }
                return true;

            case launcher_button_res_1:
                {
                    window_w = 320;
                    window_h = 240;
                    printf("resolution changed to 320 x 240!\n");
                }
                return true;

            case launcher_button_res_2:
                {
                    window_w = 400;
                    window_h = 300;
                    printf("resolution changed to 400 x 300!\n");
                }
                return true;

            case launcher_button_res_3:
                {
                    window_w = 640;
                    window_h = 480;
                    printf("resolution changed to 640 x 480!\n");
                }
                return true;

            case launcher_button_res_4:
                {
                    window_w = 800;
                    window_h = 600;
                    printf("resolution changed to 800 x 600!\n");
                }
                return true;

            case launcher_button_res_5:
                {
                    window_w = 1024;
                    window_h = 768;
                    printf("resolution changed to 1024 x 768!\n");
                }
                return true;

            case launcher_button_res_6:
                {
                    window_w = 1280;
                    window_h = 720;
                    printf("resolution changed to 1280 x 720!\n");
                }
                return true;

            case launcher_button_res_7:
                {
                    window_w = 1280;
                    window_h = 768;
                    printf("resolution changed to 1280 x 768!\n");
                }
                return true;

            case launcher_button_res_8:
                {
                    window_w = 1360;
                    window_h = 768;
                    printf("resolution changed to 1360 x 768!\n");
                }
                return true;

            case launcher_button_res_9:
                {
                    window_w = 1366;
                    window_h = 768;
                    printf("resolution changed to 1366 x 768!\n");
                }
                return true;

            case launcher_button_res_10:
                {
                    window_w = 1600;
                    window_h = 900;
                    printf("resolution changed to 1600 x 900!\n");
                }
                return true;

            case launcher_button_res_11:
                {
                    window_w = 1920;
                    window_h = 1080;
                    printf("resolution changed to 1920 x 1080!\n");
                }
                return true;

            case launcher_button_res_12:
                {
                    window_w = 2560;
                    window_h = 1440;
                    printf("resolution changed to 2560 x 1440!\n");
                }
                return true;

				default:
					return false;
				}
				break;

			default:
				break;
			}
		}

		return false;
	}

private:
	launcher_context & Context;
};

int world::launcher()
{
    is_ready = false;

    unsigned short launcher_window_x = 640, launcher_window_y = 480;

    irr::IrrlichtDevice* launcher_device = irr::createDevice(irr::video::EDT_OPENGL, irr::core::dimension2d<irr::u32>(launcher_window_x, launcher_window_y), 32, false);

    launcher_device->setWindowCaption(L"Noclip Launcher");

    irr::scene::ISceneManager* launcher_scene = launcher_device->getSceneManager();
    irr::video::IVideoDriver* launcher_driver = launcher_device->getVideoDriver();
    irr::gui::IGUIEnvironment* launcher_gui = launcher_device->getGUIEnvironment();
    irr::gui::IGUISkin* launcher_gui_skin = launcher_gui->getSkin();
    irr::gui::IGUIFont* launcher_ludio_font = launcher_gui->getFont("assets/fonts/ludio.xml");
    launcher_gui_skin->setFont(launcher_ludio_font);
    launcher_gui_skin->setColor(irr::gui::EGDC_BUTTON_TEXT, irr::video::SColor(255, 0, 0, 0));

    /* gui */
    irr::video::ITexture* button = launcher_driver->getTexture("assets/user_interface/launcher/button.png");
    irr::video::ITexture* button_pressed = launcher_driver->getTexture("assets/user_interface/launcher/button_pressed.png");
    irr::video::ITexture* button_big = launcher_driver->getTexture("assets/user_interface/launcher/button_big.png");
    irr::video::ITexture* button_big_pressed = launcher_driver->getTexture("assets/user_interface/launcher/button_big_pressed.png");
    irr::video::ITexture* base_texture = launcher_driver->getTexture("assets/user_interface/launcher/base.png");

    irr::gui::IGUIImage* base = launcher_gui->addImage(irr::core::rect<irr::s32>(0, 0, launcher_window_x, launcher_window_y));
    base->setImage(base_texture);

    irr::gui::IGUIButton* button_play = launcher_gui->addButton(irr::core::rect<irr::s32>(520, 434, 630, 470), 0, launcher_button_play, L"Play");
    button_play->setImage(button, irr::core::rect<irr::s32>(0, 0, 110, 36));
    button_play->setPressedImage(button_pressed, irr::core::rect<irr::s32>(0, 0, 110, 36));

    button_fullscreen = launcher_gui->addButton(irr::core::rect<irr::s32>(10, 434, 232, 470), 0, launcher_button_fullscreen, L"Fullscreen:OFF");
    button_fullscreen->setImage(button_big, irr::core::rect<irr::s32>(0, 0, 222, 36));
    button_fullscreen->setPressedImage(button_big_pressed, irr::core::rect<irr::s32>(0, 0, 222, 36));

    irr::gui::IGUIButton* button_res_1 = launcher_gui->addButton(irr::core::rect<irr::s32>(10, 196, 120, 232), 0, launcher_button_res_1, L"320x240");
    button_res_1->setImage(button, irr::core::rect<irr::s32>(0, 0, 110, 36));
    button_res_1->setPressedImage(button_pressed, irr::core::rect<irr::s32>(0, 0, 110, 36));

    irr::gui::IGUIButton* button_res_2 = launcher_gui->addButton(irr::core::rect<irr::s32>(122, 196, 232, 232), 0, launcher_button_res_2, L"400x300");
    button_res_2->setImage(button, irr::core::rect<irr::s32>(0, 0, 110, 36));
    button_res_2->setPressedImage(button_pressed, irr::core::rect<irr::s32>(0, 0, 110, 36));

    irr::gui::IGUIButton* button_res_3 = launcher_gui->addButton(irr::core::rect<irr::s32>(10, 234, 120, 270), 0, launcher_button_res_3, L"640x480");
    button_res_3->setImage(button, irr::core::rect<irr::s32>(0, 0, 110, 36));
    button_res_3->setPressedImage(button_pressed, irr::core::rect<irr::s32>(0, 0, 110, 36));

    irr::gui::IGUIButton* button_res_4 = launcher_gui->addButton(irr::core::rect<irr::s32>(122, 234, 232, 270), 0, launcher_button_res_4, L"800x600");
    button_res_4->setImage(button, irr::core::rect<irr::s32>(0, 0, 110, 36));
    button_res_4->setPressedImage(button_pressed, irr::core::rect<irr::s32>(0, 0, 110, 36));

    irr::gui::IGUIButton* button_res_5 = launcher_gui->addButton(irr::core::rect<irr::s32>(10, 272, 120, 308), 0, launcher_button_res_5, L"1024x768");
    button_res_5->setImage(button, irr::core::rect<irr::s32>(0, 0, 110, 36));
    button_res_5->setPressedImage(button_pressed, irr::core::rect<irr::s32>(0, 0, 110, 36));

    irr::gui::IGUIButton* button_res_6 = launcher_gui->addButton(irr::core::rect<irr::s32>(122, 272, 232, 308), 0, launcher_button_res_6, L"1280x720");
    button_res_6->setImage(button, irr::core::rect<irr::s32>(0, 0, 110, 36));
    button_res_6->setPressedImage(button_pressed, irr::core::rect<irr::s32>(0, 0, 110, 36));

    irr::gui::IGUIButton* button_res_7 = launcher_gui->addButton(irr::core::rect<irr::s32>(10, 310, 120, 346), 0, launcher_button_res_7, L"1280x768");
    button_res_7->setImage(button, irr::core::rect<irr::s32>(0, 0, 110, 36));
    button_res_7->setPressedImage(button_pressed, irr::core::rect<irr::s32>(0, 0, 110, 36));

    irr::gui::IGUIButton* button_res_8 = launcher_gui->addButton(irr::core::rect<irr::s32>(122, 310, 232, 346), 0, launcher_button_res_8, L"1360x768");
    button_res_8->setImage(button, irr::core::rect<irr::s32>(0, 0, 110, 36));
    button_res_8->setPressedImage(button_pressed, irr::core::rect<irr::s32>(0, 0, 110, 36));

    irr::gui::IGUIButton* button_res_9 = launcher_gui->addButton(irr::core::rect<irr::s32>(10, 348, 120, 384), 0, launcher_button_res_9, L"1366x768");
    button_res_9->setImage(button, irr::core::rect<irr::s32>(0, 0, 110, 36));
    button_res_9->setPressedImage(button_pressed, irr::core::rect<irr::s32>(0, 0, 110, 36));

    irr::gui::IGUIButton* button_res_10 = launcher_gui->addButton(irr::core::rect<irr::s32>(122, 348, 232, 384), 0, launcher_button_res_10, L"1600x900");
    button_res_10->setImage(button, irr::core::rect<irr::s32>(0, 0, 110, 36));
    button_res_10->setPressedImage(button_pressed, irr::core::rect<irr::s32>(0, 0, 110, 36));

    irr::gui::IGUIButton* button_res_11 = launcher_gui->addButton(irr::core::rect<irr::s32>(10, 386, 120, 422), 0, launcher_button_res_11, L"1920x1080");
    button_res_11->setImage(button, irr::core::rect<irr::s32>(0, 0, 110, 36));
    button_res_11->setPressedImage(button_pressed, irr::core::rect<irr::s32>(0, 0, 110, 36));

    irr::gui::IGUIButton* button_res_12 = launcher_gui->addButton(irr::core::rect<irr::s32>(122, 386, 232, 422), 0, launcher_button_res_12, L"2560x1440");
    button_res_12->setImage(button, irr::core::rect<irr::s32>(0, 0, 110, 36));
    button_res_12->setPressedImage(button_pressed, irr::core::rect<irr::s32>(0, 0, 110, 36));

    irr::gui::IGUIImage* current_res = launcher_gui->addImage(irr::core::rect<irr::s32>(10, 148, 232, 184));
    current_res->setImage(button_big);
    irr::gui::IGUIStaticText* current_res_text = launcher_gui->addStaticText(L"Current:640x480", irr::core::recti(20, 160, 232, 184));

    irr::gui::IGUIImage* developer = launcher_gui->addImage(irr::core::rect<irr::s32>(264, 434, 486, 470));
    developer->setImage(button_big);
    irr::gui::IGUIStaticText* developer_name = launcher_gui->addStaticText(L"Game by:Hsyenoh05", irr::core::recti(274, 447, 480, 460));

    irr::gui::IGUIImage* launcher_game = launcher_gui->addImage(irr::core::rect<irr::s32>(10, 10, 232, 46));
    launcher_game->setImage(button_big);
    irr::gui::IGUIStaticText* launcher_game_text = launcher_gui->addStaticText(L"Noclip Launcher", irr::core::recti(32, 23, 232, 46));

    launcher_context context;
    context.launcher_device = launcher_device;

    launcher_receiver receiverl(context);

    launcher_device->setEventReceiver(&receiverl);

    while (launcher_device->run() && !is_ready)
    {
        if (launcher_device->isWindowActive())
        {
            launcher_driver->beginScene(true, true, irr::video::SColor(255, 255, 255, 255));

            launcher_scene->drawAll();
            launcher_gui->drawAll();

            launcher_driver->endScene();

            irr::core::stringw res_string = L"Current:";
            res_string += window_w;
            res_string += "x";
            res_string += window_h;
            current_res_text->setText(res_string.c_str());
        }
    }

    window_x = window_w;
    window_y = window_h;
    is_fullscreen = use_fullscreen;
    ready = is_ready;

    launcher_device->setEventReceiver(0);
    launcher_device->closeDevice();
    launcher_device->run();
    launcher_device->drop();

    return 1;
}
