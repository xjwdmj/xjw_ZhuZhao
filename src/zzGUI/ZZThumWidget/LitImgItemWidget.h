#ifndef LITIMGITEMWIDGET_H
#define LITIMGITEMWIDGET_H

#include <QImage>
#include <QWidget>
class LitImgItemWidget : public QWidget {
    Q_OBJECT
public:
    explicit LitImgItemWidget(QWidget* parent = nullptr);

    void setImage(QImage& qimage);

protected:
    virtual void paintEvent(QPaintEvent* event) override;

private:
    QImage m_qImg;
};

#endif // LITIMGITEMWIDGET_H
