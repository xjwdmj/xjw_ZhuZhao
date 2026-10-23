#include "zzoneparamwidget.h"
#include "zzlistener.h"

#include <QDebug>
#include <QFileDialog>
#include <QLayout>
#include <QMessageBox>

ZZOneParamWidget::ZZOneParamWidget(QWidget* parent)
    : QWidget { parent }
    , m_pSlantLable(Q_NULLPTR)
    , m_pSlantSpinBox(Q_NULLPTR)

    , m_pTiltLable(Q_NULLPTR)
    , m_pTiltSpinBox(Q_NULLPTR)

    , m_pLoadImageBtn(Q_NULLPTR)
//, m_pImage(Q_NULLPTR)
{

    InitWidget();
}

void ZZOneParamWidget::InitWidget()
{
    QFont font("Microsoft YaHei", 12);
    font.setBold(true);
    m_pTiltLable = new QLabel(this);
    m_pTiltLable->setText(tr("param"));
    m_pTiltLable->setFont(font);

    m_pSlantLable = new QLabel(this);
    m_pSlantLable->setText(tr("slant"));
    m_pSlantSpinBox = new QDoubleSpinBox(this);
    m_pSlantSpinBox->setRange(-360, 360);
    m_pSlantSpinBox->setValue(0);

    m_pTiltLable = new QLabel(this);
    m_pTiltLable->setText(tr("tilt"));
    m_pTiltSpinBox = new QDoubleSpinBox(this);
    m_pTiltSpinBox->setRange(-360, 360);
    m_pTiltSpinBox->setValue(0);

    m_pLoadImageBtn = new QPushButton(this);
    m_pLoadImageBtn->setText(tr("load"));

    // 信号槽链接，注意要在m_PLoadImageBtn按钮new出来之后再连接
    // 作用：告诉 Qt："当用户点击 m_pLoadImageBtn 时，自动调用 OnSingLoadimageBtnClicked 函数。"
    connect(m_pLoadImageBtn, &QPushButton::clicked, this, &ZZOneParamWidget::OnSingLoadimageBtnClicked);

    QHBoxLayout* pTitleLayout = new QHBoxLayout;
    pTitleLayout->setContentsMargins(0, 0, 0, 0);
    pTitleLayout->addWidget(m_pTiltLable);
    QHBoxLayout* pParamLayout = new QHBoxLayout;
    pParamLayout->setContentsMargins(0, 0, 0, 0);
    pParamLayout->setSpacing(0);
    pParamLayout->addWidget(m_pSlantLable);
    pParamLayout->addWidget(m_pSlantSpinBox);
    pParamLayout->addWidget(m_pTiltLable);
    pParamLayout->addWidget(m_pTiltSpinBox);
    pParamLayout->addWidget(m_pLoadImageBtn);

    QWidget* pTitleWidget = new QWidget(this);
    pTitleWidget->setLayout(pTitleLayout);
    QWidget* pParamWidget = new QWidget(this);
    pParamWidget->setLayout(pParamLayout);

    QVBoxLayout* pVlayout = new QVBoxLayout(this);
    pVlayout->setSpacing(0);
    pVlayout->setContentsMargins(0, 0, 0, 0);
    pVlayout->addWidget(pTitleWidget);
    pVlayout->addWidget(pParamWidget);
}

// 在 OnSingLoadimageBtnClicked 末尾发消息  notify
void ZZOneParamWidget::OnSingLoadimageBtnClicked(bool clicked)
{
    /*
QString fileName = QFileDialog::getOpenFileName(
    this,                                     // 父窗口
    "选择图片",                                // 对话框标题
    "D:/",                                    // 默认目录
    "图片 (*.png *.jpg *.jpeg *.bmp);;所有文件 (*.*)"  // 过滤器
);
     */

    // 👇这一行就是弹出文件选择对话框的地方
    QString srcImPath = QFileDialog::getOpenFileName(this,
        tr("select image"),
        "",
        tr("image") + "(*.png *.jpg *.jpeg *.bmp)");
    if (srcImPath.isEmpty()) {
        qDebug() << "[load] 用户取消选择";
        return;
    }

    qDebug() << "[load] 选中的文件路径:" << srcImPath; //  打印路径

    // 加载图像  或者 // QImage m_qImage(srcImPath);
    m_pImage = QImage(srcImPath);
    if (m_pImage.isNull()) {
        qDebug() << "[load] 加载失败:" << srcImPath;

        // QMessageBox::information(this, tr("Error"), tr("Load Image Failed!"));
        QMessageBox::information(this,
            tr("Error"),
            tr("Load Image Failes"));
        return;
    }
    qDebug() << "[load] 加载成功，尺寸:" << m_pImage.size(); //  打印尺寸

    // 👇 关键：发消息，通知所有监听者"输入图像更新了"
    ListenerManger::Instance()->notify(MESSAGE::ZHUZHAO_UPDATE_SRCIMAGE);
}

QImage ZZOneParamWidget::GetQImage()
{
    return m_pImage;
}

float ZZOneParamWidget::GetSlantAngle()
{
    return m_pSlantSpinBox->value();
}

float ZZOneParamWidget::GetTiltAngle()
{
    return m_pTiltSpinBox->value();
}