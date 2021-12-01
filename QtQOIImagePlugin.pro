TEMPLATE = lib
QT = gui
CONFIG += plugin
DEFINES += QOI_NO_STDIO

SOURCES += \
    qqoiimageioplugin.cpp

HEADERS += \
    qqoiimageioplugin.h \
    qio.h

DISTFILES += QtQOIImagePlugin.json

# Default rules for deployment.
unix {
    target.path = $$[QT_INSTALL_PLUGINS]/imageformats
}
!isEmpty(target.path): INSTALLS += target
