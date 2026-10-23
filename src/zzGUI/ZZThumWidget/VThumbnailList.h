#ifndef VTHUMBNAILLIST_H
#define VTHUMBNAILLIST_H

#include <QListWidget>
#include <QWidget>
class VThumbnailList : public QWidget {
    Q_OBJECT
public:
    explicit VThumbnailList(QWidget* parent = nullptr);
    bool InitWidget();

    // 添加单张图像（从 QImage）
    void addImage(QImage& qImage);

    // 添加单张图像（从文件路径）
    void addImage(const QString& strPath);

    // 批量添加图像
    void addImages(QList<QImage>& qImages);

    // 清空所有图像
    void clearAllImages();

    // 获取当前选中的图像
    QImage getCurrentImage();

signals:
    // 选中图片改变时，发出这个信号通知外面
    void SigSelectImageChanged(QImage& qImage);

protected slots:
    // 当 QListWidget 选中行变化时，自动触发这个函数
    void OnCurrentRowChanged(int nCurRow);

private:
    QListWidget* m_pListWidget;
    QList<QImage> m_listImage;
};

#endif // VTHUMBNAILLIST_H
