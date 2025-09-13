$ErrorActionPreference = "Stop"

Write-Host "Building Windows version..."
mkdir build_win -Force
cd build_win

# Настройка Mingw64
$env:Path = "C:\mingw64\bin;$env:Path"
$QT_PATH = "C:\Qt\5.15.2\mingw81_64_static"

cmake .. -G "MinGW Makefiles" -DCMAKE_PREFIX_PATH=$QT_PATH -DCMAKE_C_COMPILER=gcc -DCMAKE_CXX_COMPILER=g++
mingw32-make -j4

# Deployment
windeployqt --release AnonMatrixWindows.exe
Copy-Item "C:\mingw64\bin\libgcc_s_seh-1.dll" .
Copy-Item "C:\mingw64\bin\libstdc++-6.dll" .

# Создание архива
7z a -mmt4 ..\deploy\AnonMatrix-Windows-x86_64.zip AnonMatrixWindows.exe *.dll

Write-Host "Build completed: deploy/AnonMatrix-Windows-x86_64.zip"