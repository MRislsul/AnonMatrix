#!/bin/bash
set -e

echo "Building macOS universal binary..."
mkdir -p build_macos
cd build_macos

# Установка путей к Qt
export PATH="/opt/homebrew/opt/qt5/bin:$PATH"
export LDFLAGS="-L/opt/homebrew/opt/qt5/lib"
export CPPFLAGS="-I/opt/homebrew/opt/qt5/include"

cmake .. -DCMAKE_PREFIX_PATH=/opt/homebrew/opt/qt5
make -j$(sysctl -n hw.logicalcpu)

# Создание DMG
macdeployqt AnonMatrixMacOS.app -dmg
hdiutil convert AnonMatrixMacOS.dmg -format UDZO -o ../deploy/AnonMatrix-macOS-universal.dmg

echo "Build completed: deploy/AnonMatrix-macOS-universal.dmg"