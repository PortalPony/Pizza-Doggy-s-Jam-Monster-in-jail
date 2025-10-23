#ifndef MONSTERSHACKLE_H
#define MONSTERSHACKLE_H

//#include <godot_cpp/godot.hpp>
#include <godot_cpp/classes/node3d.hpp>
#include <godot_cpp/classes/animation_player.hpp>

using namespace godot;

class MonsterShackle : public Node3D
{
	GDCLASS(MonsterShackle, Node3D);

    double maxTimeToBreak;
	double timeToBreak;

    AnimationPlayer *g_ap = nullptr;

public:
    void _ready();

    bool lowerTimeToBreakAndCheckLoose(double delta);

    void playAnimation(const String &animation);

    // Monster shackle bind methods
    void set_maxTimeToBreak(const double &mttb);
	double get_maxTimeToBreak() const;

protected:
	static void _bind_methods();
};


#endif // MONSTERSHACKLE_H