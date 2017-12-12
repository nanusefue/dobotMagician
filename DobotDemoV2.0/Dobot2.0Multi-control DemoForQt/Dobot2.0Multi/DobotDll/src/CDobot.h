#ifndef CDOBOT_H
#define CDOBOT_H

#include "CDobotConnector.h"
#include "CDobotProtocol.h"
#include "CDobotCommunicator.h"

class QCoreApplication;

class CDobot : public QObject
{
    Q_OBJECT
public:
    CDobot(QObject *parent = 0);
     ~CDobot();
    void exec(void);

public:
    CDobotConnector *connector;
    QThread *connectorTargetThread;
    CDobotProtocol *protocol;
    QThread *protocolTargetThread;
    CDobotCommunicator *communicator;
    QThread *communicatorTargetThread;
};

#endif // CDOBOT_H
