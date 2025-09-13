#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QIcon>
#include <iostream>
#include <CoreFoundation/CoreFoundation.h>
#include <SystemConfiguration/SystemConfiguration.h>

class MacNetworkManager {
public:
    static bool checkTorConnection() {
        // macOS-specific network checking
        CFStringRef proxySettingsKey = CFSTR("SOCKSProxy");
        CFDictionaryRef proxySettings = SCDynamicStoreCopyProxies(NULL);
        
        if (proxySettings) {
            CFTypeRef socksProxy = CFDictionaryGetValue(proxySettings, proxySettingsKey);
            if (socksProxy) {
                CFRelease(proxySettings);
                return true;
            }
            CFRelease(proxySettings);
        }
        return false;
    }
};

int main(int argc, char *argv[]) {
    // macOS-specific initialization
    QGuiApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication app(argc, argv);
    app.setWindowIcon(QIcon(":/assets/icon_mac.icns"));
    
    if (!MacNetworkManager::checkTorConnection()) {
        std::cerr << "Tor connection failed" << std::endl;
        return 1;
    }
    
    QQmlApplicationEngine engine;
    engine.load(QUrl("qrc:/main.qml"));
    
    return app.exec();
}