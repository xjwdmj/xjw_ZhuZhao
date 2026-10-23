#ifndef ZZONEPARAMWIDGET_H
#define ZZONEPARAMWIDGET_H

#include <QDoubleSpinBox>
#include <QImage>
#include <QLabel>
#include <QPushButton>
#include <QWidget>

class ZZOneParamWidget : public QWidget {
    Q_OBJECT
public:
    explicit ZZOneParamWidget(QWidget* parent = nullptr);

    QImage GetQImage();
    float GetSlantAngle();
    float GetTiltAngle();

protected:
    void InitWidget();

protected slots:
    void OnSingLoadimageBtnClicked(bool clicked);

signals:

private:
    QLabel* m_pSlantLable;
    QDoubleSpinBox* m_pSlantSpinBox;

    QLabel* m_pTiltLable;
    QDoubleSpinBox* m_pTiltSpinBox;

    QPushButton* m_pLoadImageBtn;

    QImage m_pImage;
};

#endif // ZZONEPARAMWIDGET_H
