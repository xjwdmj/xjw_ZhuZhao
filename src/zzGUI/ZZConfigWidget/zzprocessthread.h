#ifndef ZZPROCESSTHREAD_H
#define ZZPROCESSTHREAD_H

#include <QImage>
#include <QList>
#include <QThread>

class ZZProcessThread : public QThread {
public:
    ZZProcessThread();

    // 设置输入参数（主线程调用，把数据塞进来）
    void SetPhotometricStereoParams(QList<QImage>& srcImages,
        QList<float>& Slants,
        QList<float>& Tilts);

    // 获取结果（主线程调用，把数据拿出去）
    void GetResultImages(QList<QImage>& dstImages);

protected:
    void run() override; // 👈 重写 run，在里面执行算法

private:
    QList<QImage> m_srcImages; // 输入图

    QList<float> m_Slants; // 输入 slant 角度
    QList<float> m_Tilts; // 输入 tilt 角度

    QList<QImage> m_dstImages; // 结果图
};

#endif // ZZPROCESSTHREAD_H
