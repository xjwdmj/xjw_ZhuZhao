#ifndef ZZCONFIGWIDGET_H
#define ZZCONFIGWIDGET_H

#include <QWidget>

#include <QLabel>
#include <QList>
#include <QPushButton>

class ZZOneParamWidget; // 前置声明
class ZZConfigWidget : public QWidget {
    Q_OBJECT
public:
    explicit ZZConfigWidget(QWidget* parent = nullptr);

    // 把所有面板已加载的图收集出来
    void GetLoadedImages(QList<QImage>& images);

    // 主线程需要能从配置面板里拿到图 + Slant + Tilt
    void GetPhotometricStereoParams(QList<QImage>& srcImages,
        QList<float>& Slants,
        QList<float>& Tilts);

protected:
    void InitWidget();

private:
    QLabel* m_pTitleLabel;
    QPushButton* m_pResBtn;
    QPushButton* m_pRunBtn;

    // ZZOneParamWidget* m_pOneParam;
    QList<ZZOneParamWidget*> m_pParamWidgetList;
signals:
};

#endif // ZZCONFIGWIDGET_H
