#include "CharacterController.h"
// #include <godot_cpp/godot.hpp>
// #include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/variant/utility_functions.hpp>
#include <godot_cpp/classes/character_body3d.hpp>
#include <godot_cpp/classes/input.hpp>
#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/classes/node.hpp>
#include <godot_cpp/classes/window.hpp>
#include <godot_cpp/classes/scene_tree.hpp>
#include <godot_cpp/classes/packed_scene.hpp>
#include <godot_cpp/classes/resource_loader.hpp>
#include <godot_cpp/classes/button.hpp>
#include <godot_cpp/classes/control.hpp>
#include <godot_cpp/classes/engine.hpp>
#include <godot_cpp/variant/vector3.hpp>
#include <godot_cpp/variant/basis.hpp>

using namespace godot;

void CharacterController::_bind_methods()
{
    ClassDB::bind_method(D_METHOD("set_movementSpeed", "movementSpeed"), &CharacterController::set_movementSpeed);
    ClassDB::bind_method(D_METHOD("get_movementSpeed"), &CharacterController::get_movementSpeed);

    // ClassDB::bind_method(D_METHOD("_physics_process"), &CharacterController::_physics_process);

    // expose properties to the editor
    ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "movementSpeed", PROPERTY_HINT_RESOURCE_TYPE, "Input"),
                 "set_movementSpeed", "get_movementSpeed");
}

void CharacterController::set_movementSpeed(const double &speed) {
    movementSpeed = speed;
}

double CharacterController::get_movementSpeed() const {
    return movementSpeed;
}

void CharacterController::_ready()
{
    UtilityFunctions::print("Hello world from CharacterController");

    camera = get_node<Camera3D>(NodePath("Camera"));
    Input::get_singleton()->set_mouse_mode(Input::MOUSE_MODE_CAPTURED);
}

void CharacterController::_physics_process(double delta) {
    UtilityFunctions::print("Physics");

    Vector3 velocity = get_velocity();

    // Movement input
    Vector3 direction = Vector3();
    Input* input = Input::get_singleton();
    if (input->is_action_pressed("move_forward")) direction.z -= 1;
    if (input->is_action_pressed("move_back")) direction.z += 1;
    if (input->is_action_pressed("move_left")) direction.x -= 1;
    if (input->is_action_pressed("move_right")) direction.x += 1;

    direction = direction.normalized();

    Vector3 rotated_dir = get_transform().basis.xform(direction);

    velocity.x = rotated_dir.x * movementSpeed;
    velocity.z = rotated_dir.z * movementSpeed;

    set_velocity(velocity);

    // Move the character
    move_and_slide();
}

void CharacterController::_input(Ref<InputEvent> event) 
{
    Ref<InputEventMouseMotion> mouse_event = event;
    if (mouse_event.is_valid()) {
        // Rotate horizontally (yaw)
        rotate_y(-mouse_event->get_relative().x * mouseSensitivity);

        // Rotate camera vertically (pitch)
        pitch -= mouse_event->get_relative().y * mouseSensitivity;
        pitch = Math::clamp(pitch, -1.5f, 1.5f); // Limit looking up/down ~ +/- 90 deg

        if (camera)
            camera->set_rotation(Vector3(pitch, 0, 0));
    }
}
