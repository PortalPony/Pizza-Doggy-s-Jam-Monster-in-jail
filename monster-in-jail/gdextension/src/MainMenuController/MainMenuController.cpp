#include "MainMenuController.h"
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

void MainMenuController::_bind_methods()
{
    ClassDB::bind_method(D_METHOD("on_button_pressed"), &MainMenuController::on_button_pressed);
}

void MainMenuController::_ready()
{
    UtilityFunctions::print("Hello world from MainMenuController");
}

void MainMenuController::load_play_scene()
{
    UtilityFunctions::print("Hello world from gd extension: play");

    SceneTree *tree = get_tree();
        if (!tree) return;

        Node *root = tree->get_root();
        if (!root) return;

        // Remove current children except the controller
        for (int i = root->get_child_count() - 1; i >= 0; i--) {
            Node *child = root->get_child(i);
            if (child == this) continue;
            root->remove_child(child);
            child->queue_free();
        }

        // Load and add the new scene
        Ref<PackedScene> new_scene = ResourceLoader::get_singleton()->load("res://Scenes/PlayTest.tscn");
        if (new_scene.is_valid()) {
            Node *instance = new_scene->instantiate();
            root->add_child(instance);
        }
}

void MainMenuController::quit_game()
{
    UtilityFunctions::print("Hello world from gd extension: quit");

    SceneTree *tree = get_tree();
    tree->quit();
}

void MainMenuController::on_button_pressed(const String &action)
{
    if (action == "Play")
    {
        load_play_scene();
    }
    else if (action == "Quit")
    {
        quit_game();
    }
}
