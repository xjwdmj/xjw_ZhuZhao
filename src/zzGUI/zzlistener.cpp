#include "zzlistener.h"

ZZListener::ZZListener()
{
}

ListenerManger::ListenerManger() = default;
ListenerManger::~ListenerManger() = default;

ListenerManger* ListenerManger::Instance()
{
    static ListenerManger instance;
    return &instance;
}

void ListenerManger::registerMessage(int message, ZZListener* pListener)
{
    QMutexLocker locker(&m_mutex);
    m_listeners.append(qMakePair(message, pListener));
}

void ListenerManger::notify(int message)
{
    QMutexLocker locker(&m_mutex);
    for (auto& pair : m_listeners) {
        // 检查这个监听者是否关心 message 中的至少一个标志
        if ((pair.first & message) != 0) {
            pair.second->RespondMessage(message);
        }
    }
}