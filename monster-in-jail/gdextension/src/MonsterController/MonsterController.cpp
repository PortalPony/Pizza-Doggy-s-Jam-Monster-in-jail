#include "MonsterController.h"
#include "Classes/MonsterShackle.h"
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
#include <godot_cpp/classes/engine.hpp>

using namespace godot;

void MonsterController::_bind_methods()
{
    ClassDB::bind_method(D_METHOD("set_monster_shackle_paths", "paths"), &MonsterController::set_monster_shackle_paths);
    ClassDB::bind_method(D_METHOD("get_monster_shackle_paths"), &MonsterController::get_monster_shackle_paths);
    ClassDB::bind_method(D_METHOD("add_monster_shackle_path", "path"), &MonsterController::add_monster_shackle_path);
    ClassDB::bind_method(D_METHOD("remove_monster_shackle_at", "index"), &MonsterController::remove_monster_shackle_at);

    ADD_PROPERTY(
        PropertyInfo(Variant::ARRAY, "monster_shackle_paths"),
        "set_monster_shackle_paths", "get_monster_shackle_paths"
    );
}

void MonsterController::set_monster_shackle_paths(const Array &paths) {
    monster_shackle_paths = paths;
}

Array MonsterController::get_monster_shackle_paths() const {
    return monster_shackle_paths;
}

void MonsterController::add_monster_shackle_path(const NodePath &p) {
    monster_shackle_paths.append(p);
}

void MonsterController::remove_monster_shackle_at(int index) {
    if (index >= 0 && index < (int)monster_shackle_paths.size()) {
        monster_shackle_paths.remove_at(index);
    }
}

void MonsterController::_ready()
{
    UtilityFunctions::print("Hello world from MonsterController");
    if (Engine::get_singleton()->is_editor_hint()) {
            UtilityFunctions::print("Running in editor — skip runtime init");
            return;
    }

    startTrigger = true;
}

void MonsterController::_process(double delta)
{
    if (!startTrigger) return;

    timer += delta;

    // Lowers time to break each shackle
    for (int i = 0; i < (int)monster_shackle_paths.size(); i++)
    {
        Variant v = monster_shackle_paths[i];
        if (v.get_type() != Variant::NIL) {
            NodePath p = v;
            Node *node = get_node_or_null(p);
            MonsterShackle *ms = Object::cast_to<MonsterShackle>(node);
            if (ms) {
                if (ms->lowerTimeToBreakAndCheckLoose(delta))
                {
                    ms->playAnimation("lockLeg");
                }
            }
        }
    }

    if (timer >= interval) {
        timer = 0.0; // reset
        UtilityFunctions::print("Timer triggered!");
        // Do your repeated action here
        }
}
