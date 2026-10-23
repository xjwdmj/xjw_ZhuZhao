#include "zzlogmessage.h"

#include <QDateTime>
#include <QDir>
#include <QFile>
#include <QMutex>
#include <QTextStream>

ZZLogMessage::ZZLogMessage(QObject* parent)
    : QObject { parent }
{
}
ZZLogMessage::~ZZLogMessage() { }

void outputMessage(QtMsgType type, const QMessageLogContext& context, const QString& msg)
{
    // 1. 加锁，防止多线程同时写日志
    // mutex只有一份，函数第一次调用时被创建，之后一直存在，直到程序结束。
    static QMutex mutex;
    QMutexLocker lock(&mutex); // 一个类，叫"锁管理器"或"智能

    // 2. 根据消息类型设置前缀和颜色
    QString text;
    QString MessageColor = "red";
    switch (type) {
    case QtDebugMsg:
        text = QString("[Debug]");
        MessageColor = "darkgray";
        break;
    case QtWarningMsg:
        text = QString("[Warning]");
        MessageColor = "darkorange";
        break;
    case QtCriticalMsg:
        text = QString("[Critical]");
        MessageColor = "red";
        break;
    case QtFatalMsg:
        text = QString("[Fatal]");
        MessageColor = "red";
        break;
    default:
        text = QString("Default");
        MessageColor = "red";
        break;
    }
    // 3. 获取单例
    ZZLogMessage* instance = ZZLogMessage::Instance();
    // 4. 拼接时间戳
    QString current_date_time = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss");
    QString current_time = QString("[%1]").arg(current_date_time);
    // 5. 拼成完整的一行文本
    QString message = QString("%1%2%3").arg(current_time).arg(text).arg(msg);

    // 6. 拼成 HTML（带颜色）
    QString messageHtml = QString("<font color=%1>" + message + "</font>").arg(MessageColor);

    // 7. 写入文件
    QFile file(instance->logPath() + instance->logName());
    file.open(QIODevice::WriteOnly | QIODevice::Append);
    QTextStream text_stream(&file);
    text_stream << message << "\r\n";
    file.flush();
    file.close();

    // 8. 发出信号，通知界面更新
    emit instance->sigDebugStrData(message);
    emit instance->sigDebugHtmlData(messageHtml);

    if (file.size() < 1024 * 1024) {
        return;
    }
    for (int loop = 1; loop < 100; ++loop) {
        QString fileName = QString("%1/log_%2.txt").arg(instance->logPath()).arg(loop);
        QFile logfile(fileName);
        if (logfile.size() < 4) {
            file.rename((fileName));
            return;
        }
    }
}

ZZLogMessage* ZZLogMessage::m_pLogInstance = nullptr;
ZZLogMessage* ZZLogMessage::Instance()
{
    if (!m_pLogInstance) {
        static QMutex mtx;
        QMutexLocker clocker(&mtx);
        if (!m_pLogInstance) {
            m_pLogInstance = new ZZLogMessage;
        }
    }
    return m_pLogInstance;
}

// 安装消息处理器
void ZZLogMessage::installMessageHandler()
{
    qInstallMessageHandler(outputMessage);
}

// 卸载消息处理器
void ZZLogMessage::uninstallMessageHandler()
{
    qInstallMessageHandler(nullptr);
}

// 日志存放路径
QString ZZLogMessage::logPath()
{
    QString current_data_file_name = QDateTime::currentDateTime().toString("yyyy-MM-dd");
    QDir dir(QString("log/%1").arg(current_data_file_name));
    if (!dir.exists()) {
        dir.mkpath("./");
    }
    return dir.path() + "/";
}

// 日志文件名
QString ZZLogMessage::logName()
{
    return "log.txt";
}
