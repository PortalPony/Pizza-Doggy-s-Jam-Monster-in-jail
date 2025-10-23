#ifndef MONSTERCONTROLLER_H
#define MONSTERCONTROLLER_H

//#include <godot_cpp/godot.hpp>
#include <godot_cpp/classes/node3d.hpp>
#include "Classes/MonsterShackle.h"

using namespace godot;

class MonsterController : public Node3D
{
	GDCLASS(MonsterController, Node3D);

	bool startTrigger = false;
	double timer = 0.0;   // accumulates time
    double interval = 2.0; // seconds
	static const int monsterShacklesCount = 5;

	double maxHealth = 100;
	double health = 10;

	Array monster_shackle_paths;

public:
    void _ready();

	void _process(double delta);

	// Monster shackle bind methods
	void set_monster_shackle_paths(const Array &paths);
	Array get_monster_shackle_paths() const;

	void add_monster_shackle_path(const NodePath &p);
	void remove_monster_shackle_at(int index);

protected:
	static void _bind_methods();
};


#endif // MONSTERCONTROLLER_H