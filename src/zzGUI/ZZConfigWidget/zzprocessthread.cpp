#include "zzprocessthread.h"
#include "ImageConvert.h"
#include "PhotometricStereo.h"
#include <QDebug>

ZZProcessThread::ZZProcessThread() { }

// 主线程调用：把输入参数存到成员变量
void ZZProcessThread::SetPhotometricStereoParams(QList<QImage>& srcImages,
    QList<float>& Slants,
    QList<float>& Tilts)
{
    m_srcImages = srcImages;
    m_Slants = Slants; // 输入 slant 角度
    m_Tilts = Tilts;
}

// 主线程调用：把结果拷贝出去
void ZZProcessThread::GetResultImages(QList<QImage>& dstImages)
{
    dstImages = m_dstImages;
}

void ZZProcessThread::run()
{
    qDebug() << "[Thread]开始执行算法";

    // ========== 第 1 步：QImage 转 cv::Mat（灰度图） ==========
    std::vector<cv::Mat> srcMats;
    for (auto& qimg : m_srcImages) {
        // 算法要求灰度图
        QImage gray = qimg.convertToFormat(QImage::Format_Grayscale8);
        // 转成 cv::Mat
        cv::Mat mat = QImage2cvMat(gray);
        srcMats.push_back(mat);
    }

    // ========== 第 2 步：QList<float> 转 std::vector<float> ==========角度转换
    std::vector<float> slants(m_Slants.begin(), m_Slants.end());
    std::vector<float> tilts(m_Tilts.begin(), m_Tilts.end());

    // ========== 第 3 步：调用算法 ==========
    cv::Mat dstHeight; // 输出：高度图
    cv::Mat dstGradient; // 输出：梯度图
    cv::Mat dstAlbedo; // 输出：反照率图

    uint32_t ret = ZhuZhao::PhotometricStereo(
        srcMats,
        dstHeight,
        dstGradient,
        dstAlbedo,
        srcMats.size(),
        slants,
        tilts);

    if (ret != 0) {
        qDebug() << "[Thread] 算法执行失败，错误码:" << ret;
        return;
    }

    qDebug() << "[Thread] 算法执行成功";

    // ========== 第 4 步：cv::Mat 转回 QImage ==========
    m_dstImages.clear();
    m_dstImages.push_back(cvMat2QImage(dstHeight));
    m_dstImages.push_back(cvMat2QImage(dstGradient));
    m_dstImages.push_back(cvMat2QImage(dstAlbedo));

    qDebug() << "[Thread] 算法执行完毕，结果数量:" << m_dstImages.size();

}