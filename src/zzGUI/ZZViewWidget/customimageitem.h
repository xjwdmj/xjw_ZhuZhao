#ifndef CUSTOMIMAGEITEM_H
#define CUSTOMIMAGEITEM_H

#include <QGraphicsPixmapItem>
#include <QObject>

class CustomImageItem : public QObject, public QGraphicsPixmapItem {
    Q_OBJECT
public:
    explicit CustomImageItem(QGraphicsItem* parent = nullptr);

protected:
    virtual void hoverMoveEvent(QGraphicsSceneHoverEvent* event) override;

signals:
    void RGBValue(QString InfoVal);

public:
    int w = 0;
    int h = 0;
};

#endif // CUSTOMIMAGEITEM_H
