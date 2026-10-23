#include "LitImgItemWidget.h"

#include <QImage>
#include <QPainter>
#include <QPixmap>

LitImgItemWidget::LitImgItemWidget(QWidget* parent)
    : QWidget { parent }
{
    this->setFocusPolicy(Qt::StrongFocus);
}

void LitImgItemWidget::setImage(QImage& qimage)
{
    m_qImg = qimage;
    update();
}
void LitImgItemWidget::paintEvent(QPaintEvent* event)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    int nWidth = this->width();
    int nHeight = this->height();

    if (m_qImg.isNull()) {
        m_qImg = QImage("C:\\Users\\Lenovo\\Desktop\\qt\\test_zzGUI\\ZZThumWidget\\nullImg.png");
    }

    QPixmap tempPixmap = QPixmap::fromImage(m_qImg);

    painter.drawPixmap(2, 2, nWidth - 4, nHeight - 4, tempPixmap);

    QPen pen;
    pen.setColor(QColor(this->hasFocus() ? Qt::red : Qt::black));
    pen.setWidth(4);
    painter.setPen(pen);

    painter.drawRect(QRect(2, 2, nWidth - 4, nHeight - 4));
}