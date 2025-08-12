#include "register_types.h"

#include <gdextension_interface.h>
#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/core/defs.hpp>
#include <godot_cpp/godot.hpp>

#include "piper_tts.h"

using namespace godot;

void initialize_godot_piper_module(ModuleInitializationLevel p_level) {
    if (p_level != MODULE_INITIALIZATION_LEVEL_SCENE) {
        return;
    }

    // Register the PiperTTS class
    ClassDB::register_class<PiperTTS>();
}

void uninitialize_godot_piper_module(ModuleInitializationLevel p_level) {
    if (p_level != MODULE_INITIALIZATION_LEVEL_SCENE) {
        return;
    }

    // Cleanup code here if needed
}

extern "C" {
// Initialization function
GDExtensionBool GDE_EXPORT godot_piper_library_init(GDExtensionInterfaceGetProcAddress p_get_proc_address, 
                                                    const GDExtensionClassLibraryPtr p_library, 
                                                    GDExtensionInitialization *r_initialization) {
    
    godot::GDExtensionBinding::InitObject init_obj(p_get_proc_address, p_library, r_initialization);

    init_obj.register_initializer(initialize_godot_piper_module);
    init_obj.register_terminator(uninitialize_godot_piper_module);
    init_obj.set_minimum_library_initialization_level(MODULE_INITIALIZATION_LEVEL_SCENE);

    return init_obj.init();
}
}