#include <QCoreApplication>
#include <QFile>
#include <QIODevice>
#include <QDataStream>

#ifdef Q_OS_WIN
#include <QWinEventNotifier>
#include <windows.h>
#else
#include <QSocketNotifier>
#endif

#include <src/worker/proto.capnp.h>
#include <capnp/message.h>
#include <capnp/serialize-packed.h>

int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);

    QFile stdin, stdout;
#ifdef Q_OS_WIN
    stdin.open(GetStdHandle(STD_INPUT_HANDLE), QIODevice::OpenMode(QIODevice::ReadOnly));
    stdout.open(GetStdHandle(STD_OUTPUT_HANDLE), QIODevice::OpenMode(QIODevice::WriteOnly));
#else
    stdin.open(0, QIODevice::OpenMode(QIODevice::ReadOnly));
    stdout.open(1, QIODevice::OpenMode(QIODevice::WriteOnly));
#endif

    QDataStream input(&stdin);
    QDataStream output(&stdout);

#ifdef Q_OS_WIN
    QWinEventNotifier notifier(GetStdHandle(STD_INPUT_HANDLE));
    QObject::connect(&notifier, &QWinEventNotifier::activated,
#else
    QSocketNotifier notifier(0, QSocketNotifier::Read);
    QObject::connect(&notifier, &QSocketNotifier::activated,
#endif
    [&]() {
        ::capnp::PackedFdMessageReader reader(0);
        auto command = reader.getRoot<Command>();

        // TODO: execute command here

        ::capnp::MallocMessageBuilder builder;
        auto response = builder.initRoot<Response>();
        ::capnp::writePackedMessageToFd(0, builder);
    });

    return app.exec();
}

