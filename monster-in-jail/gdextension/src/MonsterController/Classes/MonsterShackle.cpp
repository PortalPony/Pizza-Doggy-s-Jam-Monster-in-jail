#include "MonsterShackle.h"
// #include <godot_cpp/godot.hpp>
// #include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/variant/utility_functions.hpp>
#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/classes/node3d.hpp>
#include <godot_cpp/classes/node.hpp>
#include <godot_cpp/classes/window.hpp>
#include <godot_cpp/classes/scene_tree.hpp>
#include <godot_cpp/classes/packed_scene.hpp>
#include <godot_cpp/classes/resource_loader.hpp>
#include <godot_cpp/classes/animation_player.hpp>
#include <godot_cpp/classes/button.hpp>
#include <godot_cpp/classes/control.hpp>
#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/godot.hpp>

using namespace godot;

void MonsterShackle::_bind_methods()
{
    ClassDB::bind_method(D_METHOD("set_maxTimeToBreak", "maxTimeToBreak"), &MonsterShackle::set_maxTimeToBreak);
    ClassDB::bind_method(D_METHOD("get_maxTimeToBreak"), &MonsterShackle::get_maxTimeToBreak);

    // expose properties to the editor
    ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "maxTimeToBreak", PROPERTY_HINT_RESOURCE_TYPE, "Input"),
                 "set_maxTimeToBreak", "get_maxTimeToBreak");
}

bool MonsterShackle::lowerTimeToBreakAndCheckLoose(double delta)
{
    timeToBreak -= delta;
    return timeToBreak <= 0;
}

void MonsterShackle::playAnimation(const String &animation) {
 if (!g_ap) {
        return;
    }
    if (!g_ap->has_animation(animation)) {
        return;
    }

    g_ap->play(animation);
}

void MonsterShackle::set_maxTimeToBreak(const double &mttb)
{
    maxTimeToBreak = mttb;
}

double MonsterShackle::get_maxTimeToBreak() const
{
    return maxTimeToBreak;
}

void MonsterShackle::_ready()
{
    UtilityFunctions::print("Hello world from MonsterShackle");

    g_ap = get_node<AnimationPlayer>(NodePath("shackle/AnimationPlayer"));
    if (!g_ap) {
        UtilityFunctions::printerr("AnimationPlayer not found at path: shackle/AnimationPlayer");
        return;
    }

    UtilityFunctions::print("Cached AnimationPlayer at: " + g_ap->get_path());

    timeToBreak = maxTimeToBreak;
}
