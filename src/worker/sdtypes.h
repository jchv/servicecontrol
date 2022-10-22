#pragma once

#include <qglobal.h>
#include <QtDBus/QDBusObjectPath>

struct ImportTransfer {
    quint32 id;
    QString operation;
    QString remoteFile;
    QString localMachineImageName;
    qreal progress;
    QDBusObjectPath path;
};
Q_DECLARE_METATYPE(ImportTransfer)
typedef QList<ImportTransfer> ImportTransferList;
Q_DECLARE_METATYPE(ImportTransferList)
