#ifndef ZZLOGWIDGET_H
#define ZZLOGWIDGET_H

#include <QObject>
#include <QPushButton>
#include <QTextBrowser>
#include <QWidget>

class ZZLogWidget : public QWidget {
    Q_OBJECT
public:
    explicit ZZLogWidget(QWidget* parent = nullptr);

protected:
    bool InitWidget(); // 初始化界面

private:
    void OnClearBtnClicked(); // 清空按钮点击
    void OnHelperBtnClicked(); // 帮助按钮点击

private:
    QPushButton* m_pClearBtn; // 清空按钮
    QPushButton* m_pHelperBtn; // 帮助按钮
    QTextBrowser* m_pLogTextBrowser; // 日志显示框
};

#endif // ZZLOGWIDGET_H
