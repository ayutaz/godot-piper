#!/bin/bash

echo "========================================"
echo "GodotPiper Build Script"
echo "========================================"
echo ""

# Check if godot-cpp exists
if [ ! -d "godot-cpp" ]; then
    echo "Error: godot-cpp not found!"
    echo "Please clone godot-cpp first:"
    echo "git clone https://github.com/godotengine/godot-cpp.git -b 4.3"
    exit 1
fi

# Default values
PLATFORM=""
TARGET="template_debug"
ARCH=""
JOBS=4

# Detect platform
if [[ "$OSTYPE" == "linux-gnu"* ]]; then
    PLATFORM="linux"
    ARCH="x86_64"
elif [[ "$OSTYPE" == "darwin"* ]]; then
    PLATFORM="macos"
    # Detect architecture on macOS
    if [[ $(uname -m) == "arm64" ]]; then
        ARCH="arm64"
    else
        ARCH="x86_64"
    fi
elif [[ "$OSTYPE" == "msys" ]] || [[ "$OSTYPE" == "cygwin" ]]; then
    PLATFORM="windows"
    ARCH="x86_64"
else
    echo "Unknown platform: $OSTYPE"
    exit 1
fi

# Parse arguments
while [[ $# -gt 0 ]]; do
    case $1 in
        --platform)
            PLATFORM="$2"
            shift 2
            ;;
        --target)
            TARGET="$2"
            shift 2
            ;;
        --arch)
            ARCH="$2"
            shift 2
            ;;
        --jobs)
            JOBS="$2"
            shift 2
            ;;
        *)
            echo "Unknown option: $1"
            exit 1
            ;;
    esac
done

echo "Building for:"
echo "  Platform: $PLATFORM"
echo "  Target: $TARGET"
echo "  Architecture: $ARCH"
echo "  Jobs: $JOBS"
echo ""

# Build godot-cpp first
echo "Building godot-cpp..."
cd godot-cpp
scons platform=$PLATFORM target=$TARGET arch=$ARCH -j$JOBS
if [ $? -ne 0 ]; then
    echo "Error building godot-cpp!"
    cd ..
    exit 1
fi
cd ..

# Build GodotPiper
echo ""
echo "Building GodotPiper..."
scons platform=$PLATFORM target=$TARGET arch=$ARCH -j$JOBS
if [ $? -ne 0 ]; then
    echo "Error building GodotPiper!"
    exit 1
fi

echo ""
echo "========================================"
echo "Build completed successfully!"
echo "========================================"