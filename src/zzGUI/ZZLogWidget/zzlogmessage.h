#ifndef ZZLOGMESSAGE_H
#define ZZLOGMESSAGE_H

#include <QDebug>
#include <QObject>
#define QDEBUG(message) qDebug() << "[FUNCTION]:" << __FUNCTION__ << "[LINE]:" << __LINE__ << "[LOG]:" << message;
#define QWARNING(message) qWarning() << "[FUNCTION]:" << __FUNCTION__ << "[LINE]:" << __LINE__ << "[LOG]:" << message;
#define QCRITICAL(message) qCritical() << "[FUNCTION]:" << __FUNCTION__ << "[LINE]:" << __LINE__ << "[LOG]:" << message;
#define QFATAL(message) qFatal() << "[FUNCTION]:" << __FUNCTION__ << "[LINE]:" << __LINE__ << "[LOG]:" << message;

class ZZLogMessage : public QObject {
    Q_OBJECT

public:
    static ZZLogMessage* Instance();

    void installMessageHandler();
    void uninstallMessageHandler();

    // 日志路径
    QString logPath();
    QString logName();

private:
    explicit ZZLogMessage(QObject* parent = nullptr);
    ~ZZLogMessage();

    static ZZLogMessage* m_pLogInstance; // 单例唯一实例

signals:
    // 信号 1：纯文本日志
    void sigDebugStrData(const QString& str);
    // 信号 2：带 HTML 颜色的日志
    void sigDebugHtmlData(const QString& str);
};

#endif // ZZLOGMESSAGE_H
