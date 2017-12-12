#include "CDobot.h"
#include <QCoreApplication>
#include <QThread>

void CDobot::exec(void)
{
    if (qApp) {
        qApp->exec();
    }
}

CDobot::CDobot(QObject *parent)
    : QObject(parent)
{
    connector = new CDobotConnector();
    connectorTargetThread = new QThread();
    connectorTargetThread->start();
    connector->moveToThread(connectorTargetThread);
    connect(connectorTargetThread, &QThread::finished, connectorTargetThread, &QObject::deleteLater);
    QMetaObject::invokeMethod(connector, "onInit", Qt::BlockingQueuedConnection);

    protocol = new CDobotProtocol();
    protocolTargetThread = new QThread();
    protocolTargetThread->start();
    protocol->moveToThread(protocolTargetThread);
    connect(protocolTargetThread, &QThread::finished, protocolTargetThread, &QObject::deleteLater);
    QMetaObject::invokeMethod(protocol, "onInit", Qt::BlockingQueuedConnection);

    communicator = new CDobotCommunicator();
    communicatorTargetThread = new QThread();
    communicatorTargetThread->start();
    communicator->moveToThread(communicatorTargetThread);
    connect(communicatorTargetThread, &QThread::finished, communicatorTargetThread, &QObject::deleteLater);
    QMetaObject::invokeMethod(communicator, "onInit", Qt::BlockingQueuedConnection);

    connect(connector, SIGNAL(newConnectStatus(bool)), protocol, SLOT(onNewConnectStatus(bool)));
    connect(connector, SIGNAL(newConnectStatus(bool)), communicator, SLOT(onNewConnectStatus(bool)));

    connect(protocol, SIGNAL(bytesToWrite(const char*,qint64)), connector, SLOT(onBytesToWrite(const char*,qint64)));
    connect(connector, SIGNAL(bytesWritten()), protocol, SLOT(onBytesWritten()));
    connect(connector, SIGNAL(bytesReady(QByteArray)), protocol, SLOT(onBytesReady(QByteArray)));

    connect(communicator, SIGNAL(messageToSend(Message)), protocol, SLOT(sendMessage(Message)));
    connect(protocol, SIGNAL(messageReady(Message)), communicator, SLOT(onMessageReady(Message)));
}

CDobot::~CDobot()
{
    connectorTargetThread->exit();
    protocolTargetThread->exit();
    communicatorTargetThread->exit();
    delete connectorTargetThread;
    delete protocolTargetThread;
    delete communicatorTargetThread;
}
