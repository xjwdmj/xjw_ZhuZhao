#include "mainwindow.h"

#include "ZZConfigWidget/zzconfigwidget.h"
#include "ZZConfigWidget/zzprocessthread.h"
#include "ZZLogWidget/zzlogwidget.h"
#include "ZZThumWidget/HThumbnailList.h"
#include "ZZThumWidget/LitImgItemWidget.h"
#include "ZZThumWidget/VThumbnailList.h"
#include "ZZViewWidget/customimageview.h"

#include <QLabel>
#include <QLayout>
#include <QListWidget>
#include <QSplitter>
#include <QWidget>

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
    , m_pConfigWidget(Q_NULLPTR)
    , m_pLogWidget(Q_NULLPTR)
    , m_pHThumList(Q_NULLPTR)
    , m_pVThumList(Q_NULLPTR)
    , m_pImageView(Q_NULLPTR)
{
    // this->setMinimumSize(1000, 600);
    // this->setFixedSize(1000, 600);
    InitWidget();

    // 👇 注册监听：我关心以下三种消息
    ListenerManger::Instance()->registerMessage(MESSAGE::ZHUZHAO_UPDATE_SRCIMAGE | MESSAGE::ZHUZHAO_UPDATE_RESULTI | MESSAGE::ZHUZHAO_RUNONCE,
        this);
    // 首次进入时，主动刷新一次（虽然现在没有图，但保持原项目一致）
    ListenerManger::Instance()->notify(MESSAGE::ZHUZHAO_UPDATE_SRCIMAGE);
}
MainWindow::~MainWindow() = default;

void MainWindow::InitWidget()
{
    /*
    LitImgItemWidget* pItem = new LitImgItemWidget(this);
    pItem->setFixedSize(150, 200);
    QImage testImg("C:\\Users\\Lenovo\\Desktop\\qt\\test_zzGUI\\ZZThumWidget\\icon\\nullImg.png");
    pItem->setImage(testImg);
    // 作为主窗口的中心部件
    this->setCentralWidget(pItem);
    this->setMinimumSize(300, 200);
    */

    /*
    m_pConfigWidget = new ZZConfigWidget(this);

    QHBoxLayout* pConfigwidgetLayout = new QHBoxLayout;
    pConfigwidgetLayout->addWidget(m_pConfigWidget, 0, Qt::AlignLeft | Qt::AlignTop);

    QWidget* p_Widget = new QWidget(this);
    p_Widget->setLayout(pConfigwidgetLayout);

    this->setCentralWidget(p_Widget);
    // this->setMinimumSize(400, 300);
    */

    m_pConfigWidget = new ZZConfigWidget(this);

    m_pVThumList = new VThumbnailList(this);
    m_pVThumList->setFixedWidth(130);

    m_pHThumList = new HThumbnailList(this);
    m_pHThumList->setFixedHeight(130);

    m_pImageView = new CustomImageView(this);

    ZZLogWidget* m_pLogWidget = new ZZLogWidget(this);

    QWidget* pRightViewWidget = new QWidget(this);
    QVBoxLayout* pRightViewLayout = new QVBoxLayout(pRightViewWidget);
    pRightViewLayout->setContentsMargins(0, 0, 0, 0);
    pRightViewLayout->addWidget(m_pImageView);
    pRightViewLayout->addWidget(m_pHThumList);

    QWidget* pRightWidget = new QWidget(this);
    QHBoxLayout* pRightLayout = new QHBoxLayout(pRightWidget);
    pRightLayout->addWidget(m_pVThumList);
    pRightLayout->addWidget(pRightViewWidget);

    QWidget* pLeftWidget = new QWidget(this);
    QVBoxLayout* pVBoxLayout = new QVBoxLayout(pLeftWidget);
    pVBoxLayout->addWidget(m_pConfigWidget);
    pVBoxLayout->addWidget(m_pLogWidget);

    QSplitter* pMainSplitter = new QSplitter(Qt::Horizontal, this);
    pMainSplitter->addWidget(pLeftWidget);
    pMainSplitter->addWidget(pRightWidget);
    pMainSplitter->setStretchFactor(0, 1);
    pMainSplitter->setStretchFactor(1, 4);

    this->setCentralWidget(pMainSplitter);

    connect(m_pVThumList, &VThumbnailList::SigSelectImageChanged,
        m_pImageView, &CustomImageView::OnSendImage);
    connect(m_pHThumList, &HThumbnailList::SigSelectImageChanged,
        m_pImageView, &CustomImageView::OnSendImage);

    // 创建线程对象
    m_pRunProcess = new ZZProcessThread();
    // 当线程跑完时，Qt 会自动发出 finished 信号，连到我们的槽函数
    connect(m_pRunProcess, &ZZProcessThread::finished, this, &MainWindow::OnProcessThreadFinished);
}

void MainWindow::RespondMessage(int message)
{
    if ((message & MESSAGE::ZHUZHAO_UPDATE_SRCIMAGE) == MESSAGE::ZHUZHAO_UPDATE_SRCIMAGE) {
        // 输入图像变了：收集所有已加载的图，刷新 VThumbnailList
        QList<QImage> images;
        m_pConfigWidget->GetLoadedImages(images);

        m_pVThumList->clearAllImages();
        m_pVThumList->addImages(images);

        qDebug() << "[MainWindow]输入图像数量:" << images.size();
    }

    if ((message & MESSAGE::ZHUZHAO_UPDATE_RESULTI) == MESSAGE::ZHUZHAO_UPDATE_RESULTI) {
        // 结果图像变了：刷新 HThumbnailList（接算法时用）
    }

    if ((message & MESSAGE::ZHUZHAO_RUNONCE) == MESSAGE::ZHUZHAO_RUNONCE) {
        // 单次运行算法（下一阶段再做）
        QList<QImage> srcImages;
        QList<float> Slants;
        QList<float> Tilts;

        m_pConfigWidget->GetPhotometricStereoParams(srcImages, Slants, Tilts);
        if (srcImages.size() < 3) {
            qDebug() << "[Mainwindow]输入图不足3张，无法运行";
            return;
        }

        m_pRunProcess->SetPhotometricStereoParams(srcImages, Slants, Tilts);
        m_pRunProcess->start(); // 启动子线程

        qDebug() << "[MainWindow] 子线程已启动";
    }
}
void MainWindow::OnProcessThreadFinished()
{
    qDebug() << "[MainWindow] 子线程运行完毕";
    // 从子线程拿结果图
    QList<QImage> dstImages;
    m_pRunProcess->GetResultImages(dstImages);

    // 显示到 HThumbnailList
    m_pHThumList->clearAllImages();
    m_pHThumList->addImages(dstImages);
}
