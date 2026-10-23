#ifndef CUSTOMGRAPHICSVIEW_H
#define CUSTOMGRAPHICSVIEW_H

#include <QGraphicsView>
#include <QImage>
#include <QLabel>

class CustomImageItem;
class CustomGraphicsView : public QGraphicsView {
    Q_OBJECT
public:
    explicit CustomGraphicsView(QWidget* parent = nullptr);

    bool InitWidget();
    void SetImage(const QImage& image);

protected:
    // 重写事件函数
    virtual void wheelEvent(QWheelEvent* event) override;
    virtual void mouseDoubleClickEvent(QMouseEvent* event) override;
    virtual void resizeEvent(QResizeEvent* event) override;
    virtual void paintEvent(QPaintEvent* event) override;

private slots:
    void onCenter(); // 居中显示
    void onZoom(float fScaleFavtor); // 缩放

private:
    void fitFrame(); // 自适应大小
    void setBackground(bool enables = true, bool invertColor = false);
    // 设置背景

private:
    double m_dZoomValue = 1; // 记录当前缩放比例

    QGraphicsScene* m_pScene; // 场景
    CustomImageItem* m_pImageItem; // 图像图元

    QWidget* m_pPosInfoWidget; // 底部信息栏容器
    QLabel* m_pPosInfoLabel; // 显示鼠标位置的标签

    QPixmap m_Image; // 当前显示的图
    QImage m_qImage;
    QPixmap m_tilePixmap = QPixmap(36, 36); // 棋盘格背景图
};

#endif // CUSTOMGRAPHICSVIEW_H
