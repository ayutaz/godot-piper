#ifndef GODOT_PIPER_REGISTER_TYPES_H
#define GODOT_PIPER_REGISTER_TYPES_H

#include <godot_cpp/core/class_db.hpp>

using namespace godot;

void initialize_godot_piper_module(ModuleInitializationLevel p_level);
void uninitialize_godot_piper_module(ModuleInitializationLevel p_level);

#endif // GODOT_PIPER_REGISTER_TYPES_H