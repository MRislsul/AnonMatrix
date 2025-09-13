#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QIcon>
#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <iostream>

#pragma comment(lib, "ws2_32.lib")
#pragma comment(lib, "crypt32.lib")

class WindowsNetworkManager {
public:
    static bool checkTorConnection() {
        // Windows-specific Winsock implementation
        WSADATA wsaData;
        if (WSAStartup(MAKEWORD(2,2), &wsaData) != 0) return false;
        
        SOCKET sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
        if (sock == INVALID_SOCKET) return false;
        
        sockaddr_in serv_addr;
        serv_addr.sin_family = AF_INET;
        serv_addr.sin_port = htons(9050);
        inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr);
        
        bool connected = connect(sock, (SOCKADDR*)&serv_addr, sizeof(serv_addr)) != SOCKET_ERROR;
        closesocket(sock);
        WSACleanup();
        return connected;
    }
};

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    // Windows-specific initialization
    QGuiApplication app(__argc, __argv);
    app.setWindowIcon(QIcon(":/assets/icon_windows.ico"));
    
    if (!WindowsNetworkManager::checkTorConnection()) {
        MessageBoxA(NULL, "Tor connection failed", "Error", MB_ICONERROR);
        return 1;
    }
    
    QQmlApplicationEngine engine;
    engine.load(QUrl("qrc:/main.qml"));
    
    return app.exec();
}s