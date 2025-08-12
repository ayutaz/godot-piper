#ifndef GODOT_PIPER_TTS_H
#define GODOT_PIPER_TTS_H

#include <godot_cpp/classes/node.hpp>
#include <godot_cpp/classes/audio_stream_wav.hpp>
#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/variant/string.hpp>
#include <godot_cpp/variant/dictionary.hpp>
#include <godot_cpp/variant/packed_byte_array.hpp>

#include <memory>
#include <string>

namespace godot {

class PiperTTS : public Node {
    GDCLASS(PiperTTS, Node)

private:
    String model_path;
    String config_path;
    int speaker_id = 0;
    float speed = 1.0f;
    float noise_scale = 0.667f;
    float length_scale = 1.0f;
    float noise_w = 0.8f;
    
    bool is_initialized = false;
    
    // Internal Piper state (will be properly implemented later)
    void* piper_state = nullptr;

public:
    PiperTTS();
    ~PiperTTS();

    // Initialize the TTS engine with a model
    bool initialize(const String &p_model_path, const String &p_config_path);
    
    // Synthesize speech from text
    Ref<AudioStreamWAV> synthesize(const String &p_text);
    
    // Get raw audio data without creating AudioStreamWAV
    PackedByteArray synthesize_raw(const String &p_text);
    
    // Property setters and getters
    void set_speaker_id(int p_speaker_id);
    int get_speaker_id() const;
    
    void set_speed(float p_speed);
    float get_speed() const;
    
    void set_noise_scale(float p_noise_scale);
    float get_noise_scale() const;
    
    void set_length_scale(float p_length_scale);
    float get_length_scale() const;
    
    void set_noise_w(float p_noise_w);
    float get_noise_w() const;
    
    // Voice management
    bool load_voice(const String &p_voice_path);
    void unload_voice();
    bool is_voice_loaded() const;
    
    // Get available speakers from the current model
    Dictionary get_speakers() const;
    
    // Utility functions
    static PackedStringArray get_available_languages();
    static bool is_language_supported(const String &p_language);

protected:
    static void _bind_methods();
};

} // namespace godot

#endif // GODOT_PIPER_TTS_H