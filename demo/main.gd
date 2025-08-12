extends Control

var tts: PiperTTS
var audio_player: AudioStreamPlayer

@onready var text_input: TextEdit = $VBoxContainer/TextInput
@onready var synthesize_button: Button = $VBoxContainer/HBoxContainer/SynthesizeButton
@onready var play_button: Button = $VBoxContainer/HBoxContainer/PlayButton
@onready var status_label: Label = $VBoxContainer/StatusLabel
@onready var speaker_slider: HSlider = $VBoxContainer/SpeakerControls/SpeakerSlider
@onready var speaker_label: Label = $VBoxContainer/SpeakerControls/SpeakerLabel
@onready var speed_slider: HSlider = $VBoxContainer/SpeedControls/SpeedSlider
@onready var speed_label: Label = $VBoxContainer/SpeedControls/SpeedLabel

var audio_stream: AudioStreamWAV = null

func _ready():
	# Initialize PiperTTS
	tts = PiperTTS.new()
	add_child(tts)
	
	# Initialize AudioStreamPlayer
	audio_player = AudioStreamPlayer.new()
	add_child(audio_player)
	
	# Connect signals
	synthesize_button.pressed.connect(_on_synthesize_pressed)
	play_button.pressed.connect(_on_play_pressed)
	speaker_slider.value_changed.connect(_on_speaker_changed)
	speed_slider.value_changed.connect(_on_speed_changed)
	
	# Set initial values
	text_input.text = "Hello! This is a test of the GodotPiper text-to-speech system."
	play_button.disabled = true
	
	# Initialize TTS with a model (path to be configured)
	var model_path = "res://models/en_US-test-medium.onnx"
	var config_path = "res://models/en_US-test-medium.onnx.json"
	
	if tts.initialize(model_path, config_path):
		status_label.text = "Status: Ready"
		status_label.modulate = Color.GREEN
	else:
		status_label.text = "Status: Failed to initialize"
		status_label.modulate = Color.RED
		synthesize_button.disabled = true

func _on_synthesize_pressed():
	if text_input.text.is_empty():
		status_label.text = "Status: Please enter some text"
		status_label.modulate = Color.YELLOW
		return
	
	status_label.text = "Status: Synthesizing..."
	status_label.modulate = Color.YELLOW
	
	# Synthesize the text
	audio_stream = tts.synthesize(text_input.text)
	
	if audio_stream:
		status_label.text = "Status: Synthesis complete"
		status_label.modulate = Color.GREEN
		play_button.disabled = false
	else:
		status_label.text = "Status: Synthesis failed"
		status_label.modulate = Color.RED

func _on_play_pressed():
	if audio_stream:
		audio_player.stream = audio_stream
		audio_player.play()
		status_label.text = "Status: Playing audio"
		status_label.modulate = Color.CYAN

func _on_speaker_changed(value: float):
	tts.speaker_id = int(value)
	speaker_label.text = "Speaker: %d" % int(value)

func _on_speed_changed(value: float):
	tts.speed = value
	speed_label.text = "Speed: %.1fx" % value