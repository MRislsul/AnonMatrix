#!/bin/bash
set -e

echo "Building Android APK..."
mkdir -p build_android
cd build_android

# Настройка переменных Android
export ANDROID_NDK_ROOT=$HOME/Android/Sdk/ndk/25.1.8937393
export ANDROID_SDK_ROOT=$HOME/Android/Sdk
export QT_DIR=$HOME/Qt/5.15.2/android

$QT_DIR/bin/qmake .. CONFIG+=release
make -j4

# Сборка APK
make apk
make install

# Подписывание APK
jarsigner -verbose -sigalg SHA1withRSA -digestalg SHA1 AnonMatrixAndroid.apk my-release-key

echo "Build completed: deploy/AnonMatrix-Android-arm64.apk"