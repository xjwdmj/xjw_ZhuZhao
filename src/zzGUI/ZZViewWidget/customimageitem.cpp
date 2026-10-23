#include "customimageitem.h"
#include <QGraphicsSceneHoverEvent>

CustomImageItem::CustomImageItem(QGraphicsItem* parent)
    : QGraphicsPixmapItem(parent)
{
    // 让图元能够接收鼠标悬停事件
    this->setAcceptHoverEvents(true);
}

void CustomImageItem::hoverMoveEvent(QGraphicsSceneHoverEvent* event)
{
    // 1. 获取鼠标在图像上的坐标
    QPointF mousePosition = event->pos();
    int x = mousePosition.x();
    int y = mousePosition.y();

    // 2. 边界检查（防止鼠标移出图片外时越界）
    if (x < 0)
        x = 0;
    if (y < 0)
        y = 0;

    // 3. 获取该像素的 RGB 值
    int R, G, B;
    pixmap().toImage().pixelColor(x, y).getRgb(&R, &G, &B);

    // 4. 拼接信息字符串
    QString InfoVal = QString(" W:%1,H:%2 | X:%3,Y:%4 | R:%5,G:%6,B:%7")
                          .arg(QString::number(w))
                          .arg(QString::number(h))
                          .arg(QString::number(x))
                          .arg(QString::number(y))
                          .arg(QString::number(R))
                          .arg(QString::number(G))
                          .arg(QString::number(B));
    // 5. 发出信号
    emit RGBValue(InfoVal);
}
