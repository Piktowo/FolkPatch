@echo off
chcp 65001 >nul
setlocal enabledelayedexpansion

REM Configure paths
set SDK_DIR=C:\Users\youxi\AppData\Local\Android\Sdk
set NDK_DIR=%SDK_DIR%\ndk\29.0.14206865
set TOOLCHAIN=%NDK_DIR%\toolchains\llvm\prebuilt\windows-x86_64

REM Source and output
set SOURCE_FILE=FolkS\Hide.c
set OUTPUT_DIR=app\src\main\assets\Service

REM Create output directory
if not exist "%OUTPUT_DIR%" mkdir "%OUTPUT_DIR%"

echo ========================================
echo Building ARM64 Android Executable
echo ========================================
echo Source: %SOURCE_FILE%
echo Target: arm64-v8a
echo Output: %OUTPUT_DIR%\Hide
echo.

echo Compiling...
call "%TOOLCHAIN%\bin\aarch64-linux-android21-clang.cmd" -static -o "%OUTPUT_DIR%\Hide" "%SOURCE_FILE%"
if %errorlevel% equ 0 (
    echo.
    echo ========================================
    echo [SUCCESS] Build complete!
    echo ========================================
    echo Output: %OUTPUT_DIR%\Hide
    echo.
) else (
    echo.
    echo ========================================
    echo [FAILED] Build error!
    echo ========================================
    echo.
)

:endlocal
pause
