#include "ZZLogWidget/zzlogmessage.h"
#include "mainwindow.h"

#include <QApplication>

#include <QTranslator>

int main(int argc, char* argv[])
{
    QApplication a(argc, argv);

    ZZLogMessage::Instance()->installMessageHandler();
    QDEBUG("启动日志系统");

    // 加载翻译器
    QTranslator* pTranslator = new QTranslator();
    if (pTranslator->load(":/Resouce/translate/language_ch.qm")) {
        a.installTranslator(pTranslator);
        qDebug() << "[main] 翻译文件加载成功";
    } else {
        qDebug() << "[main] 翻译文件加载失败，路径或资源有问题";
    }

    MainWindow w;
    w.show();
    return QApplication::exec();
}
