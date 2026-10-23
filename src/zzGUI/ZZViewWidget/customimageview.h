#ifndef CUSTOMIMAGEVIEW_H
#define CUSTOMIMAGEVIEW_H

#include <QImage>
#include <QLabel>
#include <QWidget>

class CustomGraphicsView;
class CustomImageView : public QWidget {
    Q_OBJECT
public:
    explicit CustomImageView(QWidget* parent = nullptr);
    ~CustomImageView();

    bool InitWidget();
    void SetImage(QImage& qImage); // 设置图片

    // 获取当前图片
    const QImage& GetImage() const
    {
        return m_qImage;
    }

public slots:
    void OnSendImage(QImage& qImage); // 槽函数，接收信号

private:
    // void updateDisplay();

    CustomGraphicsView* m_pGraphicsView; // 内部真正的视图
    QImage m_qImage; // 当前显示的图
};

#endif // CUSTOMIMAGEVIEW_H
