#include "sdtypes.h"
#include <QtDBus/QDBusArgument>

QDBusArgument& operator<<(QDBusArgument &argument, const ImportTransfer &object)
{
    argument.beginStructure();
    argument
        << object.id
        << object.operation
        << object.remoteFile
        << object.localMachineImageName
        << object.progress
        << object.path;
    argument.endStructure();
    return argument;
}

const QDBusArgument& operator>>(const QDBusArgument &argument, ImportTransfer &object)
{
    argument.beginStructure();
    argument
        >> object.id
        >> object.operation
        >> object.remoteFile
        >> object.localMachineImageName
        >> object.progress
        >> object.path;
    argument.endStructure();
    return argument;
}
