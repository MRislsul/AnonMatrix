#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QIcon>
#include <QtQuickControls2/QQuickStyle>
#include <iostream>

// Linux-specific includes
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>

class LinuxNetworkManager {
public:
    static bool checkTorConnection() {
        // Linux-specific socket implementation
        int sock = socket(AF_INET, SOCK_STREAM, 0);
        if (sock < 0) return false;
        
        struct sockaddr_in serv_addr;
        serv_addr.sin_family = AF_INET;
        serv_addr.sin_port = htons(9050);
        inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr);
        
        bool connected = connect(sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) >= 0;
        close(sock);
        return connected;
    }
};

int main(int argc, char *argv[]) {
    // Linux-specific initialization
    qputenv("QT_QPA_PLATFORM", "xcb");
    qputenv("QML_XHR_ALLOW_FILE_READ", "1");
    
    QGuiApplication app(argc, argv);
    app.setWindowIcon(QIcon(":/assets/icon_linux.png"));
    
    // Linux-specific network check
    if (!LinuxNetworkManager::checkTorConnection()) {
        std::cerr << "Tor connection failed" << std::endl;
        return 1;
    }
    
    QQmlApplicationEngine engine;
    engine.load(QUrl("qrc:/main.qml"));
    
    return app.exec();
}s