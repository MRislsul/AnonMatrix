#!/bin/bash
set -e

echo "Installing AnonMatrix..."
OS=$(uname -s)

case $OS in
    Linux)
        chmod +x AnonMatrix-Linux-x86_64.AppImage
        sudo mv AnonMatrix-Linux-x86_64.AppImage /usr/local/bin/anonmatrix
        ;;
    Darwin)
        open AnonMatrix-macOS-universal.dmg
        ;;
    Windows)
        unzip AnonMatrix-Windows-x86_64.zip
        mv AnonMatrixWindows.exe /usr/local/bin/
        ;;
    *)
        echo "Unsupported OS: $OS"
        exit 1
        ;;
esac

echo "Installation completed!"