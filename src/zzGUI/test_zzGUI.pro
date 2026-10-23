QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    ZZConfigWidget/zzconfigwidget.cpp \
    ZZConfigWidget/zzoneparamwidget.cpp \
    ZZConfigWidget/zzprocessthread.cpp \
    ZZLogWidget/zzlogmessage.cpp \
    ZZLogWidget/zzlogwidget.cpp \
    ZZThumWidget/HThumbnailList.cpp \
    ZZThumWidget/LitImgItemWidget.cpp \
    ZZThumWidget/VThumbnailList.cpp \
    ZZViewWidget/customgraphicsview.cpp \
    ZZViewWidget/customimageitem.cpp \
    ZZViewWidget/customimageview.cpp \
    main.cpp \
    mainwindow.cpp \
    zzlistener.cpp

HEADERS += \
    ZZConfigWidget/ImageConvert.h \
    ZZConfigWidget/zzconfigwidget.h \
    ZZConfigWidget/zzoneparamwidget.h \
    ZZConfigWidget/zzprocessthread.h \
    ZZLogWidget/zzlogmessage.h \
    ZZLogWidget/zzlogwidget.h \
    ZZThumWidget/HThumbnailList.h \
    ZZThumWidget/LitImgItemWidget.h \
    ZZThumWidget/VThumbnailList.h \
    ZZViewWidget/customgraphicsview.h \
    ZZViewWidget/customimageitem.h \
    ZZViewWidget/customimageview.h \
    mainwindow.h \
    zzlistener.h

#添加翻译文件
TRANSLATIONS += language_ch.ts

#配置opencv库
INCLUDEPATH += C:/opencv/build/include
LIBS += C:/opencv/build/x64/vc15/lib/opencv_world460d.lib


#配置我们自己实现的光度立体算法库
INCLUDEPATH += $$PWD/../PhotometricStereo

LIBS += -L$$PWD/../PhotometricStereo -lPhotometricStereoDLL


# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    gg.qrc
