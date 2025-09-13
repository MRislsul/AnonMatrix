#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QIcon>
#include <jni.h>
#include <android/log.h>
#include <netdb.h>
#include <arpa/inet.h>

#define LOG_TAG "AnonMatrix"
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO, LOG_TAG, __VA_ARGS__)

class AndroidNetworkManager {
public:
    static bool checkTorConnection() {
        // Android-specific network implementation
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

extern "C" JNIEXPORT jint JNICALL
Java_org_anonmatrix_MainActivity_main(JNIEnv* env, jobject thiz) {
    // Android-specific initialization
    QGuiApplication app(__argc, __argv);
    app.setWindowIcon(QIcon(":/assets/icon_android.png"));
    
    if (!AndroidNetworkManager::checkTorConnection()) {
        LOGI("Tor connection failed");
        return JNI_ERR;
    }
    
    QQmlApplicationEngine engine;
    engine.load(QUrl("qrc:/main.qml"));
    
    return app.exec();
}