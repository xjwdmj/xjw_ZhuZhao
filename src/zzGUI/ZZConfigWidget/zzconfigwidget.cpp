#include "zzconfigwidget.h"
#include "../zzlistener.h"
#include "zzoneparamwidget.h"

#include <QLayout>

ZZConfigWidget::ZZConfigWidget(QWidget* parent)
    : QWidget { parent }
    , m_pTitleLabel(Q_NULLPTR)
    , m_pResBtn(Q_NULLPTR)
    , m_pRunBtn(Q_NULLPTR)
//, m_pOneParam(Q_NULLPTR)
{
    this->setMinimumSize(350, 200);
    InitWidget();
}

void ZZConfigWidget::InitWidget()
{
    auto CreatOneParam = [&]() -> ZZOneParamWidget* {
        auto m_pParamWidget = new ZZOneParamWidget;
        m_pParamWidget->setFixedHeight(80);
        m_pParamWidgetList.push_back(m_pParamWidget);

        return m_pParamWidget;
    };

    // this->setFixedSize(350, 200);
    //   创建一个对象
    QFont font("Microsoft YaHei", 12);
    font.setBold(true);
    m_pTitleLabel = new QLabel(this);
    m_pTitleLabel->setFixedHeight(35);
    m_pTitleLabel->setFont(font);
    m_pTitleLabel->setText(tr("Param Config"));
    m_pResBtn = new QPushButton(this);
    m_pResBtn->setText(tr("Reset"));
    m_pResBtn->setFixedSize(90, 30);
    m_pRunBtn = new QPushButton(this);
    m_pRunBtn->setText(tr("RunOnce"));
    m_pRunBtn->setFixedSize(90, 30);
    // 连接 RunOnce 点击信号
    connect(m_pRunBtn, &QPushButton::clicked, this, []() {
        ListenerManger::Instance()->notify(MESSAGE::ZHUZHAO_RUNONCE);
    });

    // m_pOneParam = new ZZOneParamWidget(this);

    // 创建布局
    QHBoxLayout* pTitleLayout = new QHBoxLayout;
    pTitleLayout->addWidget(m_pTitleLabel);
    pTitleLayout->addStretch();
    pTitleLayout->setContentsMargins(0, 0, 0, 0); // 设置边距
    pTitleLayout->setSpacing(0);
    QWidget* pTitleWidget = new QWidget(this);
    pTitleWidget->setLayout(pTitleLayout);

    QHBoxLayout* pBtnLayout = new QHBoxLayout;
    pBtnLayout->addStretch();
    pBtnLayout->addWidget(m_pResBtn);
    pBtnLayout->addWidget(m_pRunBtn);
    pBtnLayout->setContentsMargins(0, 0, 0, 0); // 设置边距
    pBtnLayout->addSpacing(8);
    QWidget* pBtnWidget = new QWidget(this);
    pBtnWidget->setLayout(pBtnLayout);
    pBtnWidget->setStyleSheet("background-color:darkgray"); // 设置背景色

    QVBoxLayout* pMainLayout = new QVBoxLayout;
    pMainLayout->setContentsMargins(0, 0, 0, 0); // 设置边距
    pMainLayout->setSpacing(0); // 设置布局中所有相邻子项之间的统一间距
    pMainLayout->addWidget(pTitleWidget);
    // pMainLayout->addWidget(m_pOneParam);
    pMainLayout->addWidget(CreatOneParam());
    pMainLayout->addWidget(CreatOneParam());
    pMainLayout->addWidget(CreatOneParam());
    pMainLayout->addWidget(CreatOneParam());

    pMainLayout->addStretch();
    pMainLayout->addWidget(pBtnWidget);

    this->setLayout(pMainLayout);
}

void ZZConfigWidget::GetLoadedImages(QList<QImage>& images)
{
    images.clear();
    for (auto pParamWidget : m_pParamWidgetList) {
        QImage img = pParamWidget->GetQImage();
        if (img.isNull()) {
            continue; // 跳过还没加载图的面板
        }
        images.push_back(img);
    }
}

void ZZConfigWidget::GetPhotometricStereoParams(QList<QImage>& srcImages,
    QList<float>& Slants,
    QList<float>& Tilts)
{
    srcImages.clear();
    Slants.clear();
    Tilts.clear();
    for (auto pParamWidget : m_pParamWidgetList) {
        QImage img = pParamWidget->GetQImage();
        if (img.isNull()) {
            continue;
        }
        srcImages.push_back(img);
        Slants.push_back(pParamWidget->GetSlantAngle());
        Tilts.push_back(pParamWidget->GetTiltAngle());
    }
}