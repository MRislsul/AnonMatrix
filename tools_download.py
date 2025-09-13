#!/usr/bin/env python3
import platform
import requests
import os
import sys

class Downloader:
    BASE_URL = "https://github.com/your_username/AnonMatrix/releases/latest/download"
    
    PLATFORM_FILES = {
        "Linux": "AnonMatrix-Linux-x86_64.AppImage",
        "Windows": "AnonMatrix-Windows-x86_64.zip",
        "Darwin": "AnonMatrix-macOS-universal.dmg",
        "Android": "AnonMatrix-Android-arm64.apk",
        "iOS": "AnonMatrix-iOS-arm64.ipa"
    }
    
    def download(self):
        system = platform.system()
        filename = self.PLATFORM_FILES.get(system)
        
        if not filename:
            print(f"Unsupported platform: {system}")
            return False
            
        url = f"{self.BASE_URL}/{filename}"
        print(f"Downloading {filename}...")
        
        try:
            response = requests.get(url, stream=True)
            response.raise_for_status()
            
            with open(filename, 'wb') as f:
                for chunk in response.iter_content(chunk_size=8192):
                    f.write(chunk)
                    
            print(f"Download completed: {filename}")
            return True
            
        except Exception as e:
            print(f"Download failed: {e}")
            return False

if __name__ == "__main__":
    downloader = Downloader()
    downloader.download()