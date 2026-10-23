#include "customimageview.h"
#include "customgraphicsview.h"

#include <QLayout>
#include <QPixmap>

CustomImageView::CustomImageView(QWidget* parent)
    : QWidget(parent)
    , m_pGraphicsView(Q_NULLPTR)
{
    InitWidget();
}

CustomImageView::~CustomImageView() = default;

bool CustomImageView::InitWidget()
{
    // 创建内部视图
    m_pGraphicsView = new CustomGraphicsView(this);

    // 用布局让它铺满整个 CustomImageView
    QHBoxLayout* pViewLayout = new QHBoxLayout(this);
    pViewLayout->setSpacing(0);
    pViewLayout->setContentsMargins(0, 0, 0, 0);
    pViewLayout->addWidget(m_pGraphicsView);

    return true;
}

// 设置图片
void CustomImageView::SetImage(QImage& qImage)
{
    m_qImage = qImage;
    m_pGraphicsView->SetImage(qImage); // 转交给内部视图
}

void CustomImageView::OnSendImage(QImage& qImage)
{
    SetImage(qImage);
}
