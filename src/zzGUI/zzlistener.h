#ifndef ZZLISTENER_H
#define ZZLISTENER_H

#include <QList>
#include <QMutex>
#include <QMutexLocker>
#include <QPair>

namespace MESSAGE {
enum {
    ZHUZHAO_UPDATE_SRCIMAGE = 1 << 0, // 1 输入图像列表变化（加载了新图）
    ZHUZHAO_UPDATE_RESULTI = 1 << 1, // 2 结果图像变化
    ZHUZHAO_RUNONCE = 1 << 2, // 4 运行一次算法
};
}

// ============ 监听者接口 ============
// 谁想接收消息，就继承这个类，重写 RespondMessage
class ZZListener {
public:
    ZZListener();
    virtual ~ZZListener() { };
    virtual void RespondMessage(int message) = 0;
};

// ============ 消息管理器（单例） ============
class ListenerManger {
public:
    static ListenerManger* Instance();

    // 注册监听者，声明它关心哪些消息（用 | 组合）
    void registerMessage(int message, ZZListener* pListener);

    // 发出消息（可以是组合消息）
    void notify(int message);

private:
    ListenerManger();
    ~ListenerManger();

    // 每一项：关心的消息掩码 + 监听者指针
    QList<QPair<int, ZZListener*>> m_listeners;
    QMutex m_mutex;
};
#endif // ZZLISTENER_H
