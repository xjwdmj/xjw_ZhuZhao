#include "zzlogwidget.h"
#include "ZZLogWidget/zzlogmessage.h"

#include <QDesktopServices>
#include <QLayout>

ZZLogWidget::ZZLogWidget(QWidget* parent)
    : QWidget { parent }
    , m_pClearBtn(Q_NULLPTR)
    , m_pHelperBtn(Q_NULLPTR)
    , m_pLogTextBrowser(Q_NULLPTR)
{
    this->setMinimumSize(300, 200);
    InitWidget();
}

bool ZZLogWidget::InitWidget() // 初始化界面
{
    // 1. 创建"清空日志"按钮
    m_pClearBtn = new QPushButton(this);
    m_pClearBtn->setText(tr("ClearLog"));
    m_pClearBtn->setFixedSize(120, 28);

    // 2. 创建"帮助"按钮
    m_pHelperBtn = new QPushButton(this);
    m_pHelperBtn->setText(tr("Helper"));
    m_pHelperBtn->setFixedHeight(28);

    // 让按钮的文字靠左显示，加个内边距
    m_pHelperBtn->setStyleSheet("QPushButtn{text-align:left};padding-left:12px;");
    // 让帮助按钮横向拉伸，占满剩余空间
    m_pHelperBtn->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);

    // 3. 创建日志显示框
    m_pLogTextBrowser = new QTextBrowser(this);

    // 4. 连接按钮点击信号到槽函数
    connect(m_pClearBtn, &QPushButton::clicked, this, &ZZLogWidget::OnClearBtnClicked);
    connect(m_pHelperBtn, &QPushButton::clicked, this, &ZZLogWidget::OnHelperBtnClicked);

    // 5. 关键：把日志系统的信号连到 QTextBrowser 的 append 槽
    //    只要 ZZLogMessage 发出 sigDebugHtmlData，日志框就自动追加这一行
    connect(ZZLogMessage::Instance(), &ZZLogMessage::sigDebugHtmlData, m_pLogTextBrowser, &QTextBrowser::append);

    QHBoxLayout* pBtnLayout = new QHBoxLayout;
    pBtnLayout->setContentsMargins(0, 0, 0, 0);
    pBtnLayout->setSpacing(0);
    pBtnLayout->addWidget(m_pHelperBtn);
    pBtnLayout->addWidget(m_pClearBtn);

    QWidget* pBtnWidget = new QWidget(this);
    pBtnWidget->setLayout(pBtnLayout);
    pBtnWidget->setFixedHeight(32);

    QVBoxLayout* pMainLayout = new QVBoxLayout(this);
    pBtnLayout->setContentsMargins(0, 0, 0, 0);
    pBtnLayout->setSpacing(0);
    pMainLayout->addWidget(m_pLogTextBrowser); // 上面：日志框
    pMainLayout->addWidget(pBtnWidget); // 下面：按钮区

    return true;
}

void ZZLogWidget::OnClearBtnClicked() // 清空按钮点击
{
    m_pLogTextBrowser->clear();
}
void ZZLogWidget::OnHelperBtnClicked() // 帮助按钮点击
{
    QDesktopServices::openUrl(QUrl("https://www.roundvision.cc/machinevision/zhuzhao/"));
}
