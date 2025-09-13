#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QIcon>
#include <Foundation/Foundation.h>
#include <SystemConfiguration/SystemConfiguration.h>

class iOSNetworkManager {
public:
    static bool checkTorConnection() {
        // iOS-specific network checking
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
    // iOS-specific initialization
    QGuiApplication app(argc, argv);
    app.setWindowIcon(QIcon(":/assets/icon_ios.png"));
    
    if (!iOSNetworkManager::checkTorConnection()) {
        NSLog(@"Tor connection failed");
        return 1;
    }
    
    QQmlApplicationEngine engine;
    engine.load(QUrl("qrc:/main.qml"));
    
    return app.exec();
}