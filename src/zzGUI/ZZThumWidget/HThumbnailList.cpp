#include "HThumbnailList.h"
#include "LitImgItemWidget.h"

#include <QLayout>

HThumbnailList::HThumbnailList(QWidget* parent)
    : QWidget { parent }
    , m_pListWidget(nullptr)
{
    InitWidget();
}

bool HThumbnailList::InitWidget()
{
    m_pListWidget = new QListWidget(this);
    // 决定列表的“流动方向”。
    m_pListWidget->setFlow(QListView::LeftToRight);
    // 设置列表的“视图模式”。
    m_pListWidget->setViewMode(QListView::ListMode);

    m_pListWidget->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    m_pListWidget->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);

    m_pListWidget->setHorizontalScrollMode(QListView::ScrollPerPixel);
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
        this, &HThumbnailList::OnCurrentRowChanged);

    return true;
}

void HThumbnailList::addImage(QImage& qImage)
{
    LitImgItemWidget* pImgItemWidget = new LitImgItemWidget();
    pImgItemWidget->setImage(qImage);

    QListWidgetItem* pItem = new QListWidgetItem();
    pItem->setSizeHint(QSize(160, 110));

    m_pListWidget->addItem(pItem);
    m_pListWidget->setItemWidget(pItem,
        pImgItemWidget);
    m_listImage.push_back(qImage);
}

void HThumbnailList::addImage(const QString& strPath)
{
    QImage qImage(strPath);
    addImage(strPath);
}

void HThumbnailList::addImages(QList<QImage>& qImages)
{
    for (QImage& img : qImages) {
        addImage(img);
    }
}

void HThumbnailList::clearAllImages()
{
    m_pListWidget->clear();
    m_listImage.clear();
}

QImage HThumbnailList::getCurrentImage()
{
    int nCurRow = m_pListWidget->currentRow();
    if (nCurRow < 0 || nCurRow >= m_listImage.size()) {
        return QImage();
    }
    return m_listImage[nCurRow];
}

void HThumbnailList::OnCurrentRowChanged(int nCurRow)
{
    if (nCurRow < 0 || nCurRow >= m_listImage.size()) {
        return;
    }

    QImage curImage = m_listImage[nCurRow];
    SigSelectImageChanged(curImage);
}
