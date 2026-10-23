#include "customgraphicsview.h"
#include "customimageitem.h"

#include <QLayout>
#include <QPainter>
#include <QWheelEvent>
// 缩放限制
#define ZOOMMAX 50 // 最大放大 50 倍
#define ZOOMMIN 0.1 // 最小缩小到 0.1 倍

CustomGraphicsView::CustomGraphicsView(QWidget* parent)
    : QGraphicsView(parent)
    , m_pScene(Q_NULLPTR)
    , m_pImageItem(Q_NULLPTR)
    , m_pPosInfoWidget(Q_NULLPTR)
    , m_pPosInfoLabel(Q_NULLPTR)
{
    // 关闭默认的滚动条（我们改用鼠标拖拽）
    this->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    // 抗锯齿，让线条更平滑
    this->setRenderHint(QPainter::Antialiasing);

    // 缩放时以视图中心为锚点
    this->setTransformationAnchor(QGraphicsView::AnchorViewCenter);

    // 解决拖动时背景残影
    this->setViewportUpdateMode(QGraphicsView::FullViewportUpdate);

    // 鼠标变成小手，可以拖拽画面
    setDragMode(QGraphicsView::ScrollHandDrag);

    // 设置一个巨大的场景矩形，防止拖动时出现边界限制
    this->setSceneRect(INT_MIN / 2, INT_MIN / 2, INT_MAX, INT_MAX);

    // 设置棋盘格背景
    setBackground();

    // 把视图中心移到 (0,0)
    centerOn(0, 0);

    // 初始化界面（创建场景、图元、信息栏）
    InitWidget();
}

bool CustomGraphicsView::InitWidget()
{
    // 1. 创建场景
    m_pScene = new QGraphicsScene(this);

    // 2. 创建图片图元
    m_pImageItem = new CustomImageItem();

    // 3. 把场景设置给视图
    this->setScene(m_pScene);

    // 4. 把图元添加到场景中
    m_pScene->addItem(m_pImageItem);

    // 5. 创建底部信息栏
    m_pPosInfoLabel = new QLabel(this);
    m_pPosInfoWidget = new QWidget(this);

    // 设置标签样式：浅绿色文字，半透明深色背景
    m_pPosInfoLabel->setStyleSheet("color:rgb(200,255,200); "
                                   "background-color:rgba(50,50,50,160); "
                                   "font: Microsoft YaHei; font-size: 15px;");

    m_pPosInfoLabel->setText(" W:0,H:0 | X:0,Y:0 | R:0,G:0,B:0");

    // 信息栏容器固定高度 25 像素
    m_pPosInfoWidget->setFixedHeight(25);

    // 初始位置放在视图底部（resizeEvent 里会更新）
    m_pPosInfoWidget->setGeometry(0, this->height() - 25, this->width(), 25);

    // 背景透明
    m_pPosInfoWidget->setStyleSheet("background-color:rgba(0,0,0,0);");

    // 用水平布局把标签放进去
    QHBoxLayout* pInfoLayout = new QHBoxLayout();
    pInfoLayout->setSpacing(0);
    pInfoLayout->setContentsMargins(0, 0, 0, 0);
    pInfoLayout->addWidget(m_pPosInfoLabel);
    m_pPosInfoWidget->setLayout(pInfoLayout);

    // 6. 连接图元的信号，当鼠标移动时更新标签文字
    connect(m_pImageItem, &CustomImageItem::RGBValue, this, [&](QString Infoval) {
        m_pPosInfoLabel->setText(Infoval);
    });

    return true;
}

// 设置要显示的图像
void CustomGraphicsView::SetImage(const QImage& image)
{
    // 保存一份 QImage 副本
    m_qImage = image.copy();

    // 转成 QPixmap 用于显示
    m_Image = QPixmap::fromImage(image);

    // 把图片宽高告诉图元，用于显示信息
    m_pImageItem->w = m_Image.width();
    m_pImageItem->h = m_Image.height();

    // 把图片设置给图元
    m_pImageItem->setPixmap(m_Image);

    // 自适应窗口大小并居中
    fitFrame();
    onCenter();
    show();
}

// 重写事件函数
void CustomGraphicsView::wheelEvent(QWheelEvent* event)
{
    QPoint scrollAmount = event->angleDelta();

    if ((scrollAmount).y() > 0 && (m_dZoomValue >= ZOOMMAX))
        return;
    if ((scrollAmount).y() < 0 && (m_dZoomValue <= ZOOMMAX))
        return;
    scrollAmount.y() > 0 ? onZoom(1.1) : onZoom(0.9);
}

// 双击左键：自适应并居中
void CustomGraphicsView::mouseDoubleClickEvent(QMouseEvent* event)
{
    if (event->button() == Qt::LeftButton) {
        fitFrame();
        onCenter();
    }
}

// 窗口大小变化时，重新自适应并调整信息栏位置
void CustomGraphicsView::resizeEvent(QResizeEvent* event)
{
    fitFrame();
    onCenter();
    m_pPosInfoWidget->setGeometry(0, this->height() - 25, this->width(), 25);

    QGraphicsView::resizeEvent(event);
}

// 绘制背景（棋盘格）
void CustomGraphicsView::paintEvent(QPaintEvent* event)
{
    QPainter paint(this->viewport());
    // 用平铺的方式绘制棋盘格背景
    paint.drawTiledPixmap(QRect(QPoint(0, 0), QPoint(this->width(), this->height())), m_tilePixmap);
    QGraphicsView::paintEvent(event);
}

// 让图片居中
void CustomGraphicsView::onCenter() // 居中显示
{
    // 把视图中心移到图片中心
    this->centerOn(m_pImageItem->pixmap().width() / 2, m_pImageItem->pixmap().height() / 2);
    // 把图元坐标设为 (0,0)，这样图片左上角就在场景原点
    m_pImageItem->setPos(0, 0);
}
// 缩放
void CustomGraphicsView::onZoom(float scaleFactor) // 缩放
{
    // 累乘缩放比例
    m_dZoomValue *= scaleFactor;
    // 调用 QGraphicsView 自带的 scale
    this->scale(scaleFactor, scaleFactor);
}

// 自适应窗口大小
void CustomGraphicsView::fitFrame() // 自适应大小
{
    // 如果窗口或图片尺寸无效，直接返回
    if (this->width() < 1 || m_Image.width() < 1)
        return;

    double winWidth = this->width();
    double winHeight = this->height();

    // 计算宽高分别需要缩放多少
    double ScaleWidth = (m_Image.width() + 1) / winWidth;
    double ScaleHeight = (m_Image.height() + 1) / winHeight;

    // 取较大的缩放比例，保证图片完全显示
    double s_temp = ScaleWidth >= ScaleHeight ? 1 / ScaleWidth : 1 / ScaleHeight;

    // 计算相对于当前缩放比例还需要缩放多少
    double scale = s_temp / m_dZoomValue;

    onZoom(scale);
    m_dZoomValue = s_temp;
}

// 设置棋盘格背景
void CustomGraphicsView::setBackground(bool enables, bool invertColor) // 设置背景
{
    if (enables) {
        // 填充底色
        m_tilePixmap.fill(invertColor ? QColor(220, 220, 220) : QColor(35, 35, 35));
        QPainter tilePainter(&m_tilePixmap);
        const QColor color(50, 50, 50, 255);
        const QColor invertedColor(210, 210, 210, 255);

        // 画两个交错的小方块，形成棋盘格
        tilePainter.fillRect(18, 18, 18, 18, invertColor ? invertedColor : color);
        tilePainter.fillRect(0, 0, 18, 18, invertColor ? invertedColor : color);
        tilePainter.end();
    }
}