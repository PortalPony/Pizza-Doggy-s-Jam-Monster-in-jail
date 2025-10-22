#ifndef MAINMENUCONTROLLER_H
#define MAINMENUCONTROLLER_H

//#include <godot_cpp/godot.hpp>
#include <godot_cpp/classes/node3d.hpp>

using namespace godot;

class MainMenuController : public Node3D
{
	GDCLASS(MainMenuController, Node3D);

	void load_play_scene();

	void quit_game();

public:
	void on_button_pressed(const String &action);

    void _ready();

protected:
	static void _bind_methods();
};


#endif // MAINMENUCONTROLLER_H