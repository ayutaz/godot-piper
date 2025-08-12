@tool
extends EditorPlugin

const PLUGIN_NAME = "GodotPiper"

func _enter_tree():
	print("GodotPiper: Plugin activated")
	# Add custom types or autoload singletons here if needed
	# add_custom_type("PiperTTS", "Node", preload("res://addons/godot_piper/scripts/piper_tts.gd"), preload("res://addons/godot_piper/icons/tts.svg"))

func _exit_tree():
	print("GodotPiper: Plugin deactivated")
	# Remove custom types or autoload singletons here if needed
	# remove_custom_type("PiperTTS")