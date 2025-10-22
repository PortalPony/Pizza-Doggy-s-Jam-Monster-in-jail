#include "ButtonController.h"
// #include <godot_cpp/godot.hpp>
// #include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/variant/utility_functions.hpp>
#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/classes/node.hpp>
#include <godot_cpp/classes/window.hpp>
#include <godot_cpp/classes/scene_tree.hpp>
#include <godot_cpp/classes/packed_scene.hpp>
#include <godot_cpp/classes/resource_loader.hpp>
#include <godot_cpp/classes/button.hpp>
#include <godot_cpp/classes/control.hpp>

using namespace godot;

void ButtonController::_bind_methods()
{
    ClassDB::bind_method(D_METHOD("on_button_hover"), &ButtonController::on_button_hover);

    ClassDB::bind_method(D_METHOD("set_sound", "onHoverSound"), &ButtonController::set_sound);
    ClassDB::bind_method(D_METHOD("get_sound"), &ButtonController::get_sound);

    ClassDB::bind_method(D_METHOD("set_audio_player_path", "path"), &ButtonController::set_audio_player_path);
    ClassDB::bind_method(D_METHOD("get_audio_player_path"), &ButtonController::get_audio_player_path);

    // playable method
    ClassDB::bind_method(D_METHOD("play_configured_sound"), &ButtonController::play_configured_sound);

    // expose properties to the editor
    ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "onHoverSound", PROPERTY_HINT_RESOURCE_TYPE, "AudioStream"),
                 "set_sound", "get_sound");

    ADD_PROPERTY(PropertyInfo(Variant::NODE_PATH, "audio_player"),
                 "set_audio_player_path", "get_audio_player_path");
}

void ButtonController::_ready()
{
    UtilityFunctions::print("Hello world from ButtonController");
}

void ButtonController::set_sound(const Ref<AudioStream> &s) {
    onHoverSound = s;
}

Ref<AudioStream> ButtonController::get_sound() const {
    return onHoverSound;
}

void ButtonController::set_audio_player_path(const NodePath &p) {
    audio_player_path = p;
}

NodePath ButtonController::get_audio_player_path() const {
    return audio_player_path;
}

void ButtonController::on_button_hover()
{
    UtilityFunctions::print("on hover");
    AudioStreamPlayer *player = memnew(AudioStreamPlayer);
        player->set_stream(onHoverSound);
        add_child(player);
        player->play();
}

void ButtonController::play_configured_sound()
{

}
