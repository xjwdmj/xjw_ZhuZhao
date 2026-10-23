#include "VThumbnailList.h"
#include "LitImgItemWidget.h"

#include <QLayout>

VThumbnailList::VThumbnailList(QWidget* parent)
    : QWidget { parent }
    , m_pListWidget(nullptr)
{
    InitWidget();
}

bool VThumbnailList::InitWidget()
{
    m_pListWidget = new QListWidget(this);
    // 决定列表的“流动方向”。
    m_pListWidget->setFlow(QListView::TopToBottom);
    // 设置列表的“视图模式”。
    m_pListWidget->setViewMode(QListView::ListMode);

    m_pListWidget->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    m_pListWidget->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    m_pListWidget->setVerticalScrollMode(QListView::ScrollPerPixel);
    // 设置选择模式,一次只能选中一张图
    m_pListWidget->setSelectionMode(QListView::SingleSelection);
    // 设置列表控件本身不要抢焦点。
    m_pListWidget->setFocusPolicy(Qt::NoFocus);
    // 设置每一项之间的间距（像素）
    m_pListWidget->setSpacing(4);

    QVBoxLayout* pLayout = new QVBoxLayout(this);
    pLayout->setContentsMargins(0, 0, 0, 0);
    pLayout->addWidget(m_pListWidget);

    connect(m_pListWidget, &QListWidget::currentRowChanged,
        this, &VThumbnailList::OnCurrentRowChanged);

    return true;
}

void VThumbnailList::addImage(QImage& qImage)
{
    LitImgItemWidget* pImgItemWidget = new LitImgItemWidget();
    pImgItemWidget->setImage(qImage);

    QListWidgetItem* pItem = new QListWidgetItem();
    pItem->setSizeHint(QSize(110, 110));

    m_pListWidget->addItem(pItem);
    m_pListWidget->setItemWidget(pItem,
        pImgItemWidget);
    m_listImage.push_back(qImage);
}

void VThumbnailList::addImage(const QString& strPath)
{
    QImage qImage(strPath);
    addImage(strPath);
}

void VThumbnailList::addImages(QList<QImage>& qImages)
{
    for (QImage& img : qImages) {
        addImage(img);
    }
}

void VThumbnailList::clearAllImages()
{
    m_pListWidget->clear();
    m_listImage.clear();
}

QImage VThumbnailList::getCurrentImage()
{
    int nCurRow = m_pListWidget->currentRow();
    if (nCurRow < 0 || nCurRow >= m_listImage.size()) {
        return QImage();
    }
    return m_listImage[nCurRow];
}

void VThumbnailList::OnCurrentRowChanged(int nCurRow)
{
    if (nCurRow < 0 || nCurRow >= m_listImage.size()) {
        return;
    }

    QImage curImage = m_listImage[nCurRow];
    SigSelectImageChanged(curImage);
}
