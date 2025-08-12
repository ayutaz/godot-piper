# GodotPiper - Neural Text-to-Speech for Godot Engine

[![Godot 4.3+](https://img.shields.io/badge/Godot-4.3+-blue.svg)](https://godotengine.org)
[![License](https://img.shields.io/badge/License-Apache%202.0-blue.svg)](LICENSE)
[![Platform](https://img.shields.io/badge/Platform-Windows%20|%20Linux%20|%20macOS%20|%20Android-green.svg)](https://github.com/ayutaz/godot-piper)

高品質なニューラル音声合成プラグイン for Godot Engine。[piper-plus](https://github.com/ayutaz/piper-plus)をベースとした、多言語対応のText-to-Speechソリューション。

[English](README_EN.md) | 日本語

## 🎯 特徴

- 🎤 **高品質な音声合成** - piper-plusの最先端ニューラルネットワークモデル
- 🌍 **多言語対応** - 日本語、英語、ドイツ語、フランス語、スペイン語、中国語など40言語以上
- 🚀 **高速推論** - ONNX Runtime による最適化された推論
- 📱 **マルチプラットフォーム** - Windows、Linux、macOS、Android対応
- 🔧 **GDScript統合** - シンプルで使いやすいAPI
- 📚 **カスタム辞書** - 専門用語や固有名詞の読み方をカスタマイズ
- ⚡ **GPU推論対応** - CUDA/DirectML による高速化（オプション）

## 📋 要件

- Godot Engine 4.3以上
- 対応プラットフォーム:
  - Windows (x64)
  - Linux (x64/ARM64)
  - macOS (Intel/Apple Silicon)
  - Android (ARM64)

## 🚀 クイックスタート

### インストール

1. [Releases](https://github.com/ayutaz/godot-piper/releases)から最新版をダウンロード
2. `addons/godot_piper`フォルダをプロジェクトにコピー
3. プロジェクト設定 > プラグイン から「GodotPiper」を有効化

### 基本的な使い方

```gdscript
extends Node

var tts: PiperTTS

func _ready():
    # PiperTTSインスタンスを作成
    tts = PiperTTS.new()
    add_child(tts)
    
    # モデルを初期化
    tts.initialize(
        "res://models/ja_JP-kokoro-medium.onnx",
        "res://models/ja_JP-kokoro-medium.onnx.json"
    )
    
    # テキストを音声に変換
    var audio_stream = tts.synthesize("こんにちは、世界！")
    
    # 音声を再生
    var player = AudioStreamPlayer.new()
    add_child(player)
    player.stream = audio_stream
    player.play()
```

## 🔧 ビルド方法

### 必要なもの

- Git
- Python 3.8以上
- SCons
- C++17対応コンパイラ
  - Windows: Visual Studio 2022以上
  - Linux: GCC 9以上
  - macOS: Xcode 12以上

### ビルド手順

1. リポジトリをクローン
```bash
git clone https://github.com/ayutaz/godot-piper.git
cd godot-piper
```

2. godot-cppをクローン
```bash
git clone https://github.com/godotengine/godot-cpp.git -b 4.3
```

3. ビルドスクリプトを実行

**Windows:**
```batch
build.bat
```

**Linux/macOS:**
```bash
chmod +x build.sh
./build.sh
```

### プラットフォーム別ビルド

```bash
# Windows 64-bit
scons platform=windows target=template_release arch=x86_64

# Linux 64-bit
scons platform=linux target=template_release arch=x86_64

# macOS Universal (Intel + Apple Silicon)
scons platform=macos target=template_release arch=universal

# Android ARM64
scons platform=android target=template_release arch=arm64
```

## 📖 API リファレンス

### PiperTTS クラス

#### メソッド

| メソッド | 説明 |
|---------|------|
| `initialize(model_path: String, config_path: String) -> bool` | TTSエンジンを初期化 |
| `synthesize(text: String) -> AudioStreamWAV` | テキストを音声に変換 |
| `synthesize_raw(text: String) -> PackedByteArray` | 生のPCMデータを取得 |
| `load_voice(voice_path: String) -> bool` | 音声モデルをロード |
| `unload_voice() -> void` | 音声モデルをアンロード |
| `is_voice_loaded() -> bool` | 音声モデルがロード済みか確認 |
| `get_speakers() -> Dictionary` | 利用可能な話者リストを取得 |

#### プロパティ

| プロパティ | 型 | 説明 | デフォルト |
|-----------|-----|------|-----------|
| `speaker_id` | int | 話者ID | 0 |
| `speed` | float | 話速 (0.1-3.0) | 1.0 |
| `noise_scale` | float | ノイズスケール (0.0-1.0) | 0.667 |
| `length_scale` | float | 長さスケール (0.1-3.0) | 1.0 |
| `noise_w` | float | ノイズ幅 (0.0-1.0) | 0.8 |

#### 静的メソッド

| メソッド | 説明 |
|---------|------|
| `get_available_languages() -> PackedStringArray` | 対応言語リストを取得 |
| `is_language_supported(language: String) -> bool` | 言語がサポートされているか確認 |

## 🗺️ ロードマップ

### Phase 1: 基礎実装 ✅
- [x] GDExtension基本構造
- [x] ビルドシステム構築
- [x] 基本的なTTS API

### Phase 2: 機能拡張 🚧
- [ ] piper-plus C++コア統合
- [ ] 日本語対応（OpenJTalk）
- [ ] カスタム辞書機能
- [ ] ストリーミング音声生成

### Phase 3: 最適化 📅
- [ ] GPU推論サポート
- [ ] モバイル最適化
- [ ] WebAssembly対応（実験的）

## 🤝 コントリビューション

プルリクエストや Issue の報告を歓迎します！詳細は [CONTRIBUTING.md](CONTRIBUTING.md) をご覧ください。

## 📄 ライセンス

このプロジェクトは Apache License 2.0 でライセンスされています。詳細は [LICENSE](LICENSE) ファイルをご覧ください。

## 🙏 謝辞

- [piper-plus](https://github.com/ayutaz/piper-plus) - コアTTSエンジン
- [Godot Engine](https://godotengine.org) - ゲームエンジン
- [ONNX Runtime](https://onnxruntime.ai) - 推論エンジン
- [OpenJTalk](http://open-jtalk.sourceforge.net/) - 日本語音素化エンジン

## 📞 サポート

- [Issue Tracker](https://github.com/ayutaz/godot-piper/issues)
- [Discussions](https://github.com/ayutaz/godot-piper/discussions)

---

Made with ❤️ for the Godot community