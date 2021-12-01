#include "qqoiimageioplugin.h"

#define QOI_IMPLEMENTATION
#define QOI_MALLOC(sz) (unsigned char *)malloc(sz)
#define QOI_FREE(p)    (unsigned char *)free(p)

#include "qio.h"

#include <QtCore/QDebug>

class QQOIImageIOHandler : public QImageIOHandler
{
public:
    bool canRead() const override;
    bool read(QImage *image) override;
};

bool QQOIImageIOHandler::canRead() const
{
    if (!device())
        return false;
    return device()->bytesAvailable() > 0;
}

bool QQOIImageIOHandler::read(QImage *image)
{
    auto data = device()->readAll();
    int size = data.length();
    qoi_desc spec {};
    void *decoded = qoi_decode(data.constData(), size, &spec, 4);
    if (!decoded)
        return false;

    *image = QImage(spec.width, spec.height, QImage::Format_ARGB32);

    auto p = static_cast<unsigned char *>(decoded);
    for (unsigned int y = 0; y < spec.height; y++) {
        auto *l = reinterpret_cast<unsigned int *>(image->scanLine(y));
        for (unsigned int x = 0; x < spec.width; x++) {
            const auto r = *p++;
            const auto g = *p++;
            const auto b = *p++;
            const auto a = *p++;
            *l++ = qRgba(r, g, b, a);
        }
    }
    free(decoded);
    return true;
}

QQOIImageIOPlugin::QQOIImageIOPlugin(QObject *parent)
    : QImageIOPlugin(parent)
{}

QImageIOPlugin::Capabilities QQOIImageIOPlugin::capabilities(QIODevice *device, const QByteArray &format) const
{
    QImageIOPlugin::Capabilities ret;
    if (format == "qoi") {
        if (device) {
            if (device->isReadable())
                ret |= QImageIOPlugin::CanRead;
        } else {
            ret |= QImageIOPlugin::CanRead;
        }
    }
    return ret;
}

QImageIOHandler *QQOIImageIOPlugin::create(QIODevice *device, const QByteArray &format) const
{
    auto ret = new QQOIImageIOHandler;
    ret->setDevice(device);
    ret->setFormat(format);
    return ret;
}
