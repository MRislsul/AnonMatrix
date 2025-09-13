#!/bin/bash
set -e

echo "Building Linux version..."
mkdir -p build_linux
cd build_linux

# Статическая сборка Qt и зависимостей
export PKG_CONFIG_PATH="/opt/qt5-static/lib/pkgconfig:$PKG_CONFIG_PATH"
cmake .. -DCMAKE_BUILD_TYPE=Release -DCMAKE_PREFIX_PATH=/opt/qt5-static
make -j$(nproc)

# Создание AppImage
wget -nc "https://github.com/linuxdeploy/linuxdeploy/releases/download/continuous/linuxdeploy-x86_64.AppImage"
chmod +x linuxdeploy-x86_64.AppImage
./linuxdeploy-x86_64.AppImage --appdir AppDir -e AnonMatrixLinux -d ../assets/anonmatrix.desktop -i ../assets/icon.png --output appimage

mv AnonMatrixLinux-*.AppImage ../deploy/AnonMatrix-Linux-x86_64.AppImage
echo "Build completed: deploy/AnonMatrix-Linux-x86_64.AppImage"