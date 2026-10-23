#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "zzlistener.h"

#include <QMainWindow>

class ZZConfigWidget; // 或者使用前置声明
class ZZLogWidget;
class HThumbnailList;
class LitImgItemWidget;
class VThumbnailList;
class CustomImageView;
class ZZProcessThread;

// 👈 多继承
class MainWindow : public QMainWindow, public ZZListener {
    Q_OBJECT

public:
    explicit MainWindow(QWidget* parent = nullptr);
    ~MainWindow() override;

    // 👇 重写接口，响应消息
    void RespondMessage(int message) override;

protected:
    void InitWidget();

protected slots:
    void OnProcessThreadFinished(); // 线程完成时自动被调用

private:
    ZZConfigWidget* m_pConfigWidget;

    ZZLogWidget* m_pLogWidget;

    HThumbnailList* m_pHThumList;

    VThumbnailList* m_pVThumList;

    CustomImageView* m_pImageView;

    ZZProcessThread* m_pRunProcess; // 线程对象
};
#endif // MAINWINDOW_H
