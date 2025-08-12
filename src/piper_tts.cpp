#include "piper_tts.h"

#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/variant/utility_functions.hpp>

using namespace godot;

PiperTTS::PiperTTS() {
    // Constructor
}

PiperTTS::~PiperTTS() {
    // Cleanup
    if (piper_state != nullptr) {
        unload_voice();
    }
}

bool PiperTTS::initialize(const String &p_model_path, const String &p_config_path) {
    model_path = p_model_path;
    config_path = p_config_path;
    
    // TODO: Implement actual Piper initialization
    // This will involve loading the ONNX model and config
    
    UtilityFunctions::print("PiperTTS: Initializing with model: ", model_path);
    
    is_initialized = true;
    return true;
}

Ref<AudioStreamWAV> PiperTTS::synthesize(const String &p_text) {
    if (!is_initialized) {
        UtilityFunctions::push_error("PiperTTS: Not initialized. Please call initialize() first.");
        return Ref<AudioStreamWAV>();
    }
    
    // TODO: Implement actual synthesis using Piper
    // For now, return an empty AudioStreamWAV
    
    UtilityFunctions::print("PiperTTS: Synthesizing text: ", p_text);
    
    Ref<AudioStreamWAV> audio_stream;
    audio_stream.instantiate();
    
    // Placeholder: Create a simple sine wave for testing
    const int sample_rate = 22050;
    const float duration = 1.0f; // 1 second
    const int num_samples = sample_rate * duration;
    
    PackedByteArray audio_data;
    audio_data.resize(num_samples * 2); // 16-bit samples
    
    // Generate a simple 440Hz sine wave
    for (int i = 0; i < num_samples; i++) {
        float t = (float)i / sample_rate;
        float sample = sin(2.0f * Math_PI * 440.0f * t) * 0.3f;
        int16_t sample_int = (int16_t)(sample * 32767.0f);
        
        audio_data[i * 2] = sample_int & 0xFF;
        audio_data[i * 2 + 1] = (sample_int >> 8) & 0xFF;
    }
    
    audio_stream->set_data(audio_data);
    audio_stream->set_format(AudioStreamWAV::FORMAT_16_BITS);
    audio_stream->set_loop_mode(AudioStreamWAV::LOOP_DISABLED);
    audio_stream->set_loop_begin(0);
    audio_stream->set_loop_end(0);
    audio_stream->set_mix_rate(sample_rate);
    audio_stream->set_stereo(false);
    
    return audio_stream;
}

PackedByteArray PiperTTS::synthesize_raw(const String &p_text) {
    if (!is_initialized) {
        UtilityFunctions::push_error("PiperTTS: Not initialized. Please call initialize() first.");
        return PackedByteArray();
    }
    
    // TODO: Implement actual synthesis
    return PackedByteArray();
}

void PiperTTS::set_speaker_id(int p_speaker_id) {
    speaker_id = p_speaker_id;
}

int PiperTTS::get_speaker_id() const {
    return speaker_id;
}

void PiperTTS::set_speed(float p_speed) {
    speed = CLAMP(p_speed, 0.1f, 3.0f);
}

float PiperTTS::get_speed() const {
    return speed;
}

void PiperTTS::set_noise_scale(float p_noise_scale) {
    noise_scale = CLAMP(p_noise_scale, 0.0f, 1.0f);
}

float PiperTTS::get_noise_scale() const {
    return noise_scale;
}

void PiperTTS::set_length_scale(float p_length_scale) {
    length_scale = CLAMP(p_length_scale, 0.1f, 3.0f);
}

float PiperTTS::get_length_scale() const {
    return length_scale;
}

void PiperTTS::set_noise_w(float p_noise_w) {
    noise_w = CLAMP(p_noise_w, 0.0f, 1.0f);
}

float PiperTTS::get_noise_w() const {
    return noise_w;
}

bool PiperTTS::load_voice(const String &p_voice_path) {
    // TODO: Implement voice loading
    UtilityFunctions::print("PiperTTS: Loading voice from: ", p_voice_path);
    return true;
}

void PiperTTS::unload_voice() {
    // TODO: Implement voice unloading
    if (piper_state != nullptr) {
        // Clean up Piper state
        piper_state = nullptr;
    }
    is_initialized = false;
}

bool PiperTTS::is_voice_loaded() const {
    return is_initialized;
}

Dictionary PiperTTS::get_speakers() const {
    Dictionary speakers;
    // TODO: Load speaker information from model config
    speakers["default"] = 0;
    return speakers;
}

PackedStringArray PiperTTS::get_available_languages() {
    PackedStringArray languages;
    languages.append("en");
    languages.append("ja");
    languages.append("de");
    languages.append("fr");
    languages.append("es");
    languages.append("zh");
    // Add more languages as supported
    return languages;
}

bool PiperTTS::is_language_supported(const String &p_language) {
    PackedStringArray languages = get_available_languages();
    return languages.has(p_language);
}

void PiperTTS::_bind_methods() {
    // Methods
    ClassDB::bind_method(D_METHOD("initialize", "model_path", "config_path"), &PiperTTS::initialize);
    ClassDB::bind_method(D_METHOD("synthesize", "text"), &PiperTTS::synthesize);
    ClassDB::bind_method(D_METHOD("synthesize_raw", "text"), &PiperTTS::synthesize_raw);
    ClassDB::bind_method(D_METHOD("load_voice", "voice_path"), &PiperTTS::load_voice);
    ClassDB::bind_method(D_METHOD("unload_voice"), &PiperTTS::unload_voice);
    ClassDB::bind_method(D_METHOD("is_voice_loaded"), &PiperTTS::is_voice_loaded);
    ClassDB::bind_method(D_METHOD("get_speakers"), &PiperTTS::get_speakers);
    
    // Properties
    ClassDB::bind_method(D_METHOD("set_speaker_id", "speaker_id"), &PiperTTS::set_speaker_id);
    ClassDB::bind_method(D_METHOD("get_speaker_id"), &PiperTTS::get_speaker_id);
    ADD_PROPERTY(PropertyInfo(Variant::INT, "speaker_id"), "set_speaker_id", "get_speaker_id");
    
    ClassDB::bind_method(D_METHOD("set_speed", "speed"), &PiperTTS::set_speed);
    ClassDB::bind_method(D_METHOD("get_speed"), &PiperTTS::get_speed);
    ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "speed", PROPERTY_HINT_RANGE, "0.1,3.0,0.1"), "set_speed", "get_speed");
    
    ClassDB::bind_method(D_METHOD("set_noise_scale", "noise_scale"), &PiperTTS::set_noise_scale);
    ClassDB::bind_method(D_METHOD("get_noise_scale"), &PiperTTS::get_noise_scale);
    ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "noise_scale", PROPERTY_HINT_RANGE, "0.0,1.0,0.01"), "set_noise_scale", "get_noise_scale");
    
    ClassDB::bind_method(D_METHOD("set_length_scale", "length_scale"), &PiperTTS::set_length_scale);
    ClassDB::bind_method(D_METHOD("get_length_scale"), &PiperTTS::get_length_scale);
    ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "length_scale", PROPERTY_HINT_RANGE, "0.1,3.0,0.1"), "set_length_scale", "get_length_scale");
    
    ClassDB::bind_method(D_METHOD("set_noise_w", "noise_w"), &PiperTTS::set_noise_w);
    ClassDB::bind_method(D_METHOD("get_noise_w"), &PiperTTS::get_noise_w);
    ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "noise_w", PROPERTY_HINT_RANGE, "0.0,1.0,0.01"), "set_noise_w", "get_noise_w");
    
    // Static methods
    ClassDB::bind_static_method("PiperTTS", D_METHOD("get_available_languages"), &PiperTTS::get_available_languages);
    ClassDB::bind_static_method("PiperTTS", D_METHOD("is_language_supported", "language"), &PiperTTS::is_language_supported);
}