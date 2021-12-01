#ifndef QQOIIMAGEIOPLUGIN_H
#define QQOIIMAGEIOPLUGIN_H

#include <QtGui/QImageIOPlugin>

class QQOIImageIOPlugin : public QImageIOPlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID QImageIOHandlerFactoryInterface_iid FILE "QtQOIImagePlugin.json")

public:
    explicit QQOIImageIOPlugin(QObject *parent = nullptr);

    QImageIOPlugin::Capabilities capabilities(QIODevice *device, const QByteArray &format) const override;
    QImageIOHandler *create(QIODevice *device, const QByteArray &format) const override;
};

#endif // QQOIIMAGEIOPLUGIN_H
