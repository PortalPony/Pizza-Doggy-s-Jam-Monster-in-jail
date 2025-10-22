#ifndef BUTTONCONTROLLER_H
#define BUTTONCONTROLLER_H

#include <godot_cpp/godot.hpp>
#include <godot_cpp/classes/node3d.hpp>
#include <godot_cpp/variant/node_path.hpp>
#include <godot_cpp/classes/ref.hpp>
#include <godot_cpp/classes/audio_stream.hpp>
#include <godot_cpp/classes/audio_stream_player.hpp>


using namespace godot;

class ButtonController : public Node3D
{
	GDCLASS(ButtonController, Node3D);

public:
	void on_button_hover();

    void _ready();

	// Sound functions
	void set_sound(const Ref<AudioStream> &s);
    Ref<AudioStream> get_sound() const;

    void set_audio_player_path(const NodePath &p);
    NodePath get_audio_player_path() const;

    // call to play the configured sound
    void play_configured_sound();

protected:
	static void _bind_methods();

private:
	Ref<AudioStream> onHoverSound;
    NodePath audio_player_path;
};


#endif // BUTTONCONTROLLER_H