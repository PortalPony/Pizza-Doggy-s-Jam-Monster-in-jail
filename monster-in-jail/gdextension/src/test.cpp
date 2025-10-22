#include "test.h"
// #include <godot_cpp/godot.hpp>
// #include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/variant/utility_functions.hpp>

using namespace godot;

// void Test::_bind_methods()
// {

// }

void Test::_ready()
{
    UtilityFunctions::print("Hello world from gd extension");
}