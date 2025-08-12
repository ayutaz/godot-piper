@echo off
setlocal enabledelayedexpansion

echo ========================================
echo GodotPiper Build Script for Windows
echo ========================================
echo.

REM Check if godot-cpp exists
if not exist "godot-cpp" (
    echo Error: godot-cpp not found!
    echo Please clone godot-cpp first:
    echo git clone https://github.com/godotengine/godot-cpp.git -b 4.3
    exit /b 1
)

REM Parse arguments
set PLATFORM=windows
set TARGET=template_debug
set ARCH=x86_64

:parse_args
if "%1"=="" goto build
if "%1"=="--platform" (
    set PLATFORM=%2
    shift
    shift
    goto parse_args
)
if "%1"=="--target" (
    set TARGET=%2
    shift
    shift
    goto parse_args
)
if "%1"=="--arch" (
    set ARCH=%2
    shift
    shift
    goto parse_args
)
shift
goto parse_args

:build
echo Building for:
echo   Platform: %PLATFORM%
echo   Target: %TARGET%
echo   Architecture: %ARCH%
echo.

REM Build godot-cpp first
echo Building godot-cpp...
cd godot-cpp
call scons platform=%PLATFORM% target=%TARGET% arch=%ARCH% -j4
if errorlevel 1 (
    echo Error building godot-cpp!
    cd ..
    exit /b 1
)
cd ..

REM Build GodotPiper
echo.
echo Building GodotPiper...
call scons platform=%PLATFORM% target=%TARGET% arch=%ARCH% -j4
if errorlevel 1 (
    echo Error building GodotPiper!
    exit /b 1
)

echo.
echo ========================================
echo Build completed successfully!
echo ========================================

endlocal