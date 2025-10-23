#ifndef CHARACTERCONTROLLER_H
#define CHARACTERCONTROLLER_H

//#include <godot_cpp/godot.hpp>
#include <godot_cpp/classes/node3d.hpp>
#include <godot_cpp/classes/character_body3d.hpp>
#include <godot_cpp/classes/camera3d.hpp>
#include <godot_cpp/classes/input.hpp>
#include <godot_cpp/classes/input_event_mouse_motion.hpp>

using namespace godot;

class CharacterController : public CharacterBody3D 
{
	GDCLASS(CharacterController, CharacterBody3D );

	double movementSpeed;
	double mouseSensitivity = 0.003f;
	Camera3D* camera = nullptr;
	float pitch = 0.0f;

public:
    void _ready();

	void _physics_process(double delta);

	void _input(Ref<InputEvent> event);

	// Character bind methods
	void set_movementSpeed(const double &mp);
	double get_movementSpeed() const;

protected:
	static void _bind_methods();
};


#endif // CHARACTERCONTROLLER_H