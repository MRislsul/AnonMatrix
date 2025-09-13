#!/bin/bash
set -e

echo "Building iOS IPA..."
mkdir -p build_ios
cd build_ios

# Настройка Xcode build
export QT_DIR=$HOME/Qt/5.15.2/ios
xcodebuild -project AnonMatrixiOS.xcodeproj -configuration Release -arch arm64

# Создание IPA
xcrun -sdk iphoneos PackageApplication -v build/Release-iphoneos/AnonMatrixiOS.app -o ../deploy/AnonMatrix-iOS-arm64.ipa

echo "Build completed: deploy/AnonMatrix-iOS-arm64.ipa"