#include "DobotDll.h"
#include "dobotdll_global.h"
#include "CDobot.h"
#include "CDobotMgr.h"
#include <QThread>
#include <QCoreApplication>
#include <QDebug>

int DobotExec(void)
{
    CDobotMgr::instance()->getDobotSearchInstance()->exec();

    return 0;
}

int SearchDobot(char *dobotNameList, uint32_t maxLen)
{
    QScopedPointer<bool> isFinished(new bool);
    QScopedPointer<int> result(new int);

    *isFinished = false;
    *result = 0;

    QMetaObject::invokeMethod(CDobotMgr::instance()->getDobotSearchInstance()->connector,
                              "searchDobot",
                              Qt::QueuedConnection,
                              Q_ARG(void *, (void *)&(*isFinished)),
                              Q_ARG(void *, (void *)&(*result)),
                              Q_ARG(void *, (void *)dobotNameList),
                              Q_ARG(unsigned int, maxLen));

    while (*isFinished == false) {
        QCoreApplication::processEvents(QEventLoop::AllEvents, 5);
    }
    return *result;
}

int ConnectDobot(const char *portName, uint32_t baudrate, char *fwType, char *version, int *dobotId)
{
    QScopedPointer<bool> isFinished(new bool);
    QScopedPointer<int> result(new int);
    CDobot *dobot = NULL;
    *isFinished = false;
    *result = 0;
    int id = -1;

    if((dobot = CDobotMgr::instance()->getDobotInstance(-1, &id)) == NULL){
        return *result;
    }

    QMetaObject::invokeMethod(dobot->connector,
                              "connectDobot",
                              Qt::QueuedConnection,
                              Q_ARG(void *, (void *)&(*isFinished)),
                              Q_ARG(void *, (void *)&(*result)),
                              Q_ARG(void *, (void *)portName),
                              Q_ARG(unsigned int, baudrate),
                              Q_ARG(void *, (void *)fwType),
                              Q_ARG(void *, (void *)version));

    while (*isFinished == false) {
        QCoreApplication::processEvents(QEventLoop::AllEvents, 5);
    }

    if(*result != DobotConnect_NoError){
        CDobotMgr::instance()->delDobotInstance(id);
        id = -1;
    }
    qDebug() << "ConnectDobot id" << id;
    if (dobotId) {
        *dobotId = id;
    }
    return *result;
}

int DisconnectDobot(int dobotId)
{
    QScopedPointer<bool> isFinished(new bool);
    QScopedPointer<int> result(new int);
    CDobot *dobot = NULL;

    *isFinished = false;
    *result = 0;

    if((dobot = CDobotMgr::instance()->getDobotInstance(dobotId)) == NULL){
        return *result;
    }

    QMetaObject::invokeMethod(dobot->connector,
                              "disconnectDobot",
                              Qt::QueuedConnection,
                              Q_ARG(void *, (void *)&(*isFinished)),
                              Q_ARG(void *, (void *)&(*result)));

    while (*isFinished == false) {
        QCoreApplication::processEvents(QEventLoop::AllEvents, 5);
    }
    CDobotMgr::instance()->delDobotInstance(dobotId);
    return *result;
}

int SetCmdTimeout(int dobotId, unsigned int cmdTimeout)
{
    QScopedPointer<bool> isFinished(new bool);
    QScopedPointer<int> result(new int);
    CDobot *dobot = NULL;

    *isFinished = false;
    *result = 0;

    if((dobot = CDobotMgr::instance()->getDobotInstance(dobotId)) == NULL){
        return *result;
    }

    QMetaObject::invokeMethod(dobot->communicator,
                              "setCmdTimeout",
                              Qt::QueuedConnection,
                              Q_ARG(void *, (void *)&(*isFinished)),
                              Q_ARG(void *, (void *)&(*result)),
                              Q_ARG(unsigned int, cmdTimeout));
    while (*isFinished == false) {
        QCoreApplication::processEvents(QEventLoop::AllEvents, 5);
    }
    return *result;
}

#define WAIT_CMD_EXECUTION(dobotId)                                     \
QScopedPointer<bool> isFinished(new bool);                              \
QScopedPointer<int> result(new int);                                    \
CDobot *dobot = NULL;                                                   \
                                                                        \
*isFinished = false;                                                    \
*result = 0;                                                            \
                                                                        \
if((dobot = CDobotMgr::instance()->getDobotInstance(dobotId)) == NULL){ \
    return *result;                                                     \
}                                                                       \
                                                                        \
QMetaObject::invokeMethod(dobot->communicator,                          \
                          "insertMessage",                              \
                          Qt::QueuedConnection,                         \
                          Q_ARG(void *, (void *)isFinished.data()),     \
                          Q_ARG(void *, (void *)result.data()),         \
                          Q_ARG(void *, (void *)message.data()));       \
while (*isFinished == false) {                                          \
    QCoreApplication::processEvents(QEventLoop::AllEvents, 5);          \
}

/*********************************************************************************************************
** Device information
*********************************************************************************************************/
int SetDeviceSN(int dobotId, const char *deviceSN)
{
    // 0. Parameter checking
    if (deviceSN == NULL) {
        return DobotCommunicate_InvalidParams;
    }

    // 1.Send the message
    QScopedPointer<Message> message(new Message);

    message.data()->id = ProtocolDeviceSN;
    message.data()->rw = 1;
    message.data()->isQueued = false;
    strcpy((char *)message.data()->params, (const char *)deviceSN);
    message.data()->paramsLen = strlen(deviceSN) + 1;

    // 2.Wait for command execution
    WAIT_CMD_EXECUTION(dobotId);

    // 3.The result
    return *result;
}

int GetDeviceSN(int dobotId, char *deviceSN, uint32_t maxLen)
{
    // 0. Parameter checking
    if (deviceSN == NULL ||
        maxLen == 0) {
        return DobotCommunicate_InvalidParams;
    }

    // 1.Send the message
    QScopedPointer<Message> message(new Message);

    message.data()->id = ProtocolDeviceSN;
    message.data()->rw = 0;
    message.data()->isQueued = false;
    message.data()->paramsLen = 0;

    // 2.Wait for command execution
    WAIT_CMD_EXECUTION(dobotId);

    // 3. The result
    uint32_t len = strlen((const char *)&message.data()->params[0]);
    if (len < maxLen) {
        strcpy(deviceSN, (const char *)&message.data()->params[0]);
    } else {
        memcpy(deviceSN, (const char *)&message.data()->params[0], maxLen - 1);
        deviceSN[maxLen - 1] = 0;
    }

    return *result;
}

int SetDeviceName(int dobotId, const char *deviceName)
{
    // 0. Parameter checking
    if (deviceName == NULL) {
        return DobotCommunicate_InvalidParams;
    }

    // 1.Send the message
    QScopedPointer<Message> message(new Message);

    message.data()->id = ProtocolDeviceName;
    message.data()->rw = 1;
    message.data()->isQueued = false;
    strcpy((char *)message.data()->params, deviceName);
    message.data()->paramsLen = strlen(deviceName) + 1;

    // 2.Wait for command execution
    WAIT_CMD_EXECUTION(dobotId);

    // 3.The result
    return *result;
}

int GetDeviceName(int dobotId, char *deviceName, uint32_t maxLen)
{
    // 0. Parameter checking
    if (deviceName == NULL ||
        maxLen == 0) {
        return DobotCommunicate_InvalidParams;
    }

    // 1.Send the message
    QScopedPointer<Message> message(new Message);

    message.data()->id = ProtocolDeviceName;
    message.data()->rw = 0;
    message.data()->isQueued = false;
    message.data()->paramsLen = 0;

    // 2.Wait for command execution
    WAIT_CMD_EXECUTION(dobotId);

    // 3. The result
    uint32_t len = strlen((const char *)&message.data()->params[0]);
    if (len < maxLen) {
        strcpy(deviceName, (const char *)&message.data()->params[0]);
    } else {
        memcpy(deviceName, (const char *)&message.data()->params[0], maxLen - 1);
        deviceName[maxLen - 1] = 0;
    }

    return *result;
}

int GetDeviceVersion(int dobotId, uint8_t *majorVersion, uint8_t *minorVersion, uint8_t *revision)
{
    // 0. Parameter checking
    if (majorVersion == NULL ||
        minorVersion == NULL ||
        revision == NULL) {
        return DobotCommunicate_InvalidParams;
    }

    // 1.Send the message
    QScopedPointer<Message> message(new Message);

    message.data()->id = ProtocolDeviceVersion;
    message.data()->rw = 0;
    message.data()->isQueued = false;
    message.data()->paramsLen = 0;

    // 2.Wait for command execution
    WAIT_CMD_EXECUTION(dobotId);

    // 3. The result
    *majorVersion = message.data()->params[0];
    *minorVersion = message.data()->params[1];
    *revision = message.data()->params[2];

    return *result;
}

/*********************************************************************************************************
** Pose & Kinematics
*********************************************************************************************************/
int GetPose(int dobotId, Pose *pose)
{
    // 0. Parameter checking
    if (pose == NULL) {
        return DobotCommunicate_InvalidParams;
    }

    // 1.Send the message
    QScopedPointer<Message> message(new Message);

    message.data()->id = ProtocolGetPose;
    message.data()->rw = 0;
    message.data()->isQueued = false;
    message.data()->paramsLen = 0;

    // 2.Wait for command execution
    WAIT_CMD_EXECUTION(dobotId);

    // 3.The result
    memcpy(pose, &message.data()->params[0], sizeof(Pose));

    return *result;
}

int ResetPose(int dobotId, bool manual, float rearArmAngle, float frontArmAngle)
{
    // 0. Parameter checking

    // 1.Send the message
    QScopedPointer<Message> message(new Message);
    message.data()->rw = 1;
    message.data()->isQueued = false;
    message.data()->id = ProtocolResetPose;

    message.data()->params[0] = manual;
    memcpy(&message.data()->params[1], &rearArmAngle, sizeof(float));
    memcpy(&message.data()->params[1 + sizeof(float)], &frontArmAngle, sizeof(float));

    message.data()->paramsLen = 1 + 2 * sizeof(float);

    // 2.Wait for command execution
    WAIT_CMD_EXECUTION(dobotId);

    // 3. The result
    return *result;
}

int GetKinematics(int dobotId, Kinematics *kinematics)
{
    // 0. Parameter checking
    if (kinematics == NULL) {
        return DobotCommunicate_InvalidParams;
    }

    // 1.Send the message
    QScopedPointer<Message> message(new Message);

    message.data()->id = ProtocolGetKinematics;
    message.data()->rw = 0;
    message.data()->isQueued = false;
    message.data()->paramsLen = 0;

    // 2.Wait for command execution
    WAIT_CMD_EXECUTION(dobotId);

    // 3.The result
    memcpy(kinematics, &message.data()->params[0], sizeof(Kinematics));

    return *result;
}

/*********************************************************************************************************
** Alarms
*********************************************************************************************************/

int GetAlarmsState(int dobotId, uint8_t *alarmsState, uint32_t *len, unsigned int maxLen)
{
    // 0. Parameter checking
    if (alarmsState == NULL ||
        len == NULL ||
        maxLen == 0) {
        return DobotCommunicate_InvalidParams;
    }

    // 1.Send the message
    QScopedPointer<Message> message(new Message);

    message.data()->id = ProtocolAlarmsState;
    message.data()->rw = 0;
    message.data()->isQueued = false;
    message.data()->paramsLen = 0;

    // 2.Wait for command execution
    WAIT_CMD_EXECUTION(dobotId);

    // 3.The result
    *len = message.data()->paramsLen;
    memcpy(alarmsState, &message.data()->params[0], *len > maxLen ? maxLen : *len);

    return *result;
}

int ClearAllAlarmsState(int dobotId)
{
    // 0. Parameter checking

    // 1.Send the message
    QScopedPointer<Message> message(new Message);

    message.data()->id = ProtocolAlarmsState;
    message.data()->rw = 1;
    message.data()->isQueued = false;
    message.data()->paramsLen = 0;

    // 2.Wait for command execution
    WAIT_CMD_EXECUTION(dobotId);

    // 3. The result
    return *result;
}

/*********************************************************************************************************
** HOME
*********************************************************************************************************/
int SetHOMEParams(int dobotId, HOMEParams *homeParams, bool isQueued, uint64_t *queuedCmdIndex)
{
    // 0. Parameter checking
    if (homeParams == NULL) {
        return DobotCommunicate_InvalidParams;
    }

    // 1.Send the message
    QScopedPointer<Message> message(new Message);

    message.data()->id = ProtocolHOMEParams;
    message.data()->rw = 1;
    message.data()->isQueued = isQueued;
    memcpy(&message.data()->params[0], homeParams, sizeof(HOMEParams));
    message.data()->paramsLen = sizeof(HOMEParams);

    // 2.Wait for command execution
    WAIT_CMD_EXECUTION(dobotId);

    // 3.The result
    if (isQueued && queuedCmdIndex) {
        memcpy(queuedCmdIndex, &message.data()->params[0], sizeof(uint64_t));
    }

    return *result;
}

int GetHOMEParams(int dobotId, HOMEParams *homeParams)
{
    // 0. Parameter checking
    if (homeParams == NULL) {
        return DobotCommunicate_InvalidParams;
    }

    // 1.Send the message
    QScopedPointer<Message> message(new Message);

    message.data()->id = ProtocolHOMEParams;
    message.data()->rw = 0;
    message.data()->isQueued = false;
    message.data()->paramsLen = 0;

    // 2.Wait for command execution
    WAIT_CMD_EXECUTION(dobotId);

    // 3.The result
    memcpy(homeParams, &message.data()->params[0], sizeof(HOMEParams));

    return *result;
}

int SetHOMECmd(int dobotId, HOMECmd *homeCmd, bool isQueued, uint64_t *queuedCmdIndex)
{
    // 0. Parameter checking
    if (homeCmd == NULL) {
        return DobotCommunicate_InvalidParams;
    }

    // 1.Send the message
    QScopedPointer<Message> message(new Message);

    message.data()->id = ProtocolHOMECmd;
    message.data()->rw = 1;
    message.data()->isQueued = isQueued;
    memcpy(&message.data()->params[0], homeCmd, sizeof(HOMECmd));
    message.data()->paramsLen = sizeof(HOMECmd);

    // 2.Wait for command execution
    WAIT_CMD_EXECUTION(dobotId);

    // 3.The result
    if (isQueued && queuedCmdIndex) {
        memcpy(queuedCmdIndex, &message.data()->params[0], sizeof(uint64_t));
    }

    return *result;
}

/*********************************************************************************************************
** HHT
*********************************************************************************************************/

int SetHHTTrigMode(int dobotId, HHTTrigMode hhtTrigMode)
{
    // 0. Parameter checking

    // 1.Send the message
    QScopedPointer<Message> message(new Message);

    message.data()->id = ProtocolHHTTrigMode;
    message.data()->rw = 1;
    message.data()->isQueued = false;
    message.data()->params[0] = hhtTrigMode;
    message.data()->paramsLen = 1;

    // 2.Wait for command execution
    WAIT_CMD_EXECUTION(dobotId);

    // 3.The result
    return *result;
}

int GetHHTTrigMode(int dobotId, HHTTrigMode *hhtTrigMode)
{
    // 0. Parameter checking
    if (hhtTrigMode == NULL) {
        return DobotCommunicate_InvalidParams;
    }

    // 1.Send the message
    QScopedPointer<Message> message(new Message);

    message.data()->id = ProtocolHHTTrigMode;
    message.data()->rw = 0;
    message.data()->isQueued = false;
    message.data()->paramsLen = 0;

    // 2.Wait for command execution
    WAIT_CMD_EXECUTION(dobotId);

    // 3.The result
    *hhtTrigMode = (HHTTrigMode)message.data()->params[0];

    return *result;
}

int SetHHTTrigOutputEnabled(int dobotId, bool isEnabled)
{
    // 0. Parameter checking

    // 1.Send the message
    QScopedPointer<Message> message(new Message);

    message.data()->id = ProtocolHHTTrigOutputEnabled;
    message.data()->rw = 1;
    message.data()->isQueued = false;
    message.data()->params[0] = isEnabled;
    message.data()->paramsLen = 1;

    // 2.Wait for command execution
    WAIT_CMD_EXECUTION(dobotId);

    // 3.The result
    return *result;
}

int GetHHTTrigOutputEnabled(int dobotId, bool *isEnabled )
{
    // 0. Parameter checking
    if (isEnabled == NULL) {
        return DobotCommunicate_InvalidParams;
    }

    // 1.Send the message
    QScopedPointer<Message> message(new Message);

    message.data()->id = ProtocolHHTTrigOutputEnabled;
    message.data()->rw = 0;
    message.data()->isQueued = false;
    message.data()->paramsLen = 0;

    // 2.Wait for command execution
    WAIT_CMD_EXECUTION(dobotId);

    // 3.The result
    *isEnabled = message.data()->params[0];

    return *result;
}

int GetHHTTrigOutput(int dobotId, bool *isTriggered)
{
    // 0. Parameter checking
    if (isTriggered == NULL) {
        return DobotCommunicate_InvalidParams;
    }

    // 1.Send the message
    QScopedPointer<Message> message(new Message);

    message.data()->id = ProtocolHHTTrigOutput;
    message.data()->rw = 0;
    message.data()->isQueued = false;
    message.data()->paramsLen = 0;

    // 2.Wait for command execution
    WAIT_CMD_EXECUTION(dobotId);

    // 3.The result
    *isTriggered = message.data()->params[0];

    return *result;
}

/*********************************************************************************************************
** End effector
*********************************************************************************************************/

int SetEndEffectorParams(int dobotId, EndEffectorParams *endEffectorParams, bool isQueued, uint64_t *queuedCmdIndex)
{
    // 0. Parameter checking
    if (endEffectorParams == NULL) {
        return DobotCommunicate_InvalidParams;
    }

    // 1.Send the message
    QScopedPointer<Message> message(new Message);

    message.data()->id = ProtocolEndEffectorParams;
    message.data()->rw = 1;
    message.data()->isQueued = isQueued;
    memcpy(&message.data()->params[0], endEffectorParams, sizeof(EndEffectorParams));
    message.data()->paramsLen = sizeof(EndEffectorParams);

    // 2.Wait for command execution
    WAIT_CMD_EXECUTION(dobotId);

    // 3.The result
    if (isQueued && queuedCmdIndex) {
        memcpy(queuedCmdIndex, &message.data()->params[0], sizeof(uint64_t));
    }

    return *result;
}

int GetEndEffectorParams(int dobotId, EndEffectorParams *endEffectorParams)
{
    // 0. Parameter checking
    if (endEffectorParams == NULL) {
        return DobotCommunicate_InvalidParams;
    }

    // 1.Send the message
    QScopedPointer<Message> message(new Message);

    message.data()->id = ProtocolEndEffectorParams;
    message.data()->rw = 0;
    message.data()->isQueued = false;
    message.data()->paramsLen = 0;

    // 2.Wait for command execution
    WAIT_CMD_EXECUTION(dobotId);

    // 3. The result
    memcpy(endEffectorParams, &message.data()->params[0], sizeof(EndEffectorParams));

    return *result;
}

int SetEndEffectorLaser(int dobotId, bool enableCtrl, bool on, bool isQueued, uint64_t *queuedCmdIndex)
{
    // 0. Parameter checking

    // 1.Send the message
    QScopedPointer<Message> message(new Message);

    message.data()->id = ProtocolEndEffectorLaser;
    message.data()->rw = 1;
    message.data()->isQueued = isQueued;
    message.data()->params[0] = enableCtrl;
    message.data()->params[1] = on;
    message.data()->paramsLen = 2;

    // 2.Wait for command execution
    WAIT_CMD_EXECUTION(dobotId);

    // 3.The result
    if (isQueued && queuedCmdIndex) {
        memcpy(queuedCmdIndex, &message.data()->params[0], sizeof(uint64_t));
    }

    return *result;
}

int GetEndEffectorLaser(int dobotId, bool *isCtrlEnabled, bool *isOn)
{
    // 0. Parameter checking
    if (isCtrlEnabled == NULL ||
        isOn == NULL) {
        return DobotCommunicate_InvalidParams;
    }

    // 1.Send the message
    QScopedPointer<Message> message(new Message);

    message.data()->id = ProtocolEndEffectorLaser;
    message.data()->rw = 0;
    message.data()->isQueued = false;
    message.data()->paramsLen = 0;

    // 2.Wait for command execution
    WAIT_CMD_EXECUTION(dobotId);

    // 3. The result
    *isCtrlEnabled = message.data()->params[0];
    *isOn = message.data()->params[1];

    return *result;
}

int SetEndEffectorSuctionCup(int dobotId, bool enableCtrl, bool suck, bool isQueued, uint64_t *queuedCmdIndex)
{
    // 0. Parameter checking

    // 1.Send the message
    QScopedPointer<Message> message(new Message);

    message.data()->id = ProtocolEndEffectorSuctionCup;
    message.data()->rw = 1;
    message.data()->isQueued = isQueued;
    message.data()->params[0] = enableCtrl;
    message.data()->params[1] = suck;
    message.data()->paramsLen = 2;

    // 2.Wait for command execution
    WAIT_CMD_EXECUTION(dobotId);

    // 3.The result
    if (isQueued && queuedCmdIndex) {
        memcpy(queuedCmdIndex, &message.data()->params[0], sizeof(uint64_t));
    }

    return *result;
}

int GetEndEffectorSuctionCup(int dobotId, bool *isCtrlEnabled, bool *isSucked)
{
    // 0. Parameter checking
    if (isCtrlEnabled == NULL ||
        isSucked == NULL) {
        return DobotCommunicate_InvalidParams;
    }

    // 1.Send the message
    QScopedPointer<Message> message(new Message);

    message.data()->id = ProtocolEndEffectorSuctionCup;
    message.data()->rw = 0;
    message.data()->isQueued = false;
    message.data()->paramsLen = 0;

    // 2.Wait for command execution
    WAIT_CMD_EXECUTION(dobotId);

    // 3. The result
    *isCtrlEnabled = message.data()->params[0];
    *isSucked = message.data()->params[1];

    return *result;
}

int SetEndEffectorGripper(int dobotId, bool enableCtrl, bool grip, bool isQueued, uint64_t *queuedCmdIndex)
{
    // 0. Parameter checking

    // 1.Send the message
    QScopedPointer<Message> message(new Message);

    message.data()->id = ProtocolEndEffectorGripper;
    message.data()->rw = 1;
    message.data()->isQueued = isQueued;
    message.data()->params[0] = enableCtrl;
    message.data()->params[1] = grip;
    message.data()->paramsLen = 2;

    // 2.Wait for command execution
    WAIT_CMD_EXECUTION(dobotId);

    // 3.The result
    if (isQueued && queuedCmdIndex) {
        memcpy(queuedCmdIndex, &message.data()->params[0], sizeof(uint64_t));
    }

    return *result;
}

int GetEndEffectorGripper(int dobotId, bool *isCtrlEnabled, bool *isGripped)
{
    // 0. Parameter checking
    if (isCtrlEnabled == NULL ||
        isGripped == NULL) {
        return DobotCommunicate_InvalidParams;
    }

    // 1.Send the message
    QScopedPointer<Message> message(new Message);

    message.data()->id = ProtocolEndEffectorGripper;
    message.data()->rw = 0;
    message.data()->isQueued = false;
    message.data()->paramsLen = 0;

    // 2.Wait for command execution
    WAIT_CMD_EXECUTION(dobotId);

    // 3. The result
    *isCtrlEnabled = message.data()->params[0];
    *isGripped = message.data()->params[1];

    return *result;
}

/*********************************************************************************************************
** Arm orientation
*********************************************************************************************************/

int SetArmOrientation(int dobotId, ArmOrientation armOrientation, bool isQueued, uint64_t *queuedCmdIndex)
{
    // 0. Parameter checking

    // 1.Send the message
    QScopedPointer<Message> message(new Message);

    message.data()->id = ProtocolArmOrientation;
    message.data()->rw = 1;
    message.data()->isQueued = isQueued;
    message.data()->params[0] = armOrientation;
    message.data()->paramsLen = 1;

    // 2.Wait for command execution
    WAIT_CMD_EXECUTION(dobotId);

    // 3.The result
    if (isQueued && queuedCmdIndex) {
        memcpy(queuedCmdIndex, &message.data()->params[0], sizeof(uint64_t));
    }

    return *result;
}

int GetArmOrientation(int dobotId, ArmOrientation *armOrientation)
{
    // 0. Parameter checking
    if (armOrientation == NULL) {
        return DobotCommunicate_InvalidParams;
    }

    // 1.Send the message
    QScopedPointer<Message> message(new Message);

    message.data()->id = ProtocolArmOrientation;
    message.data()->rw = 0;
    message.data()->isQueued = false;
    message.data()->paramsLen = 0;

    // 2.Wait for command execution
    WAIT_CMD_EXECUTION(dobotId);

    // 3.The result
    *armOrientation = (ArmOrientation)message.data()->params[0];

    return *result;
}

/*********************************************************************************************************
** JOG
*********************************************************************************************************/

int SetJOGJointParams(int dobotId, JOGJointParams *jogJointParams, bool isQueued, uint64_t *queuedCmdIndex)
{
    // 0. Parameter checking
    if (jogJointParams == NULL) {
        return DobotCommunicate_InvalidParams;
    }

    // 1.Send the message
    QScopedPointer<Message> message(new Message);

    message.data()->id = ProtocolJOGJointParams;
    message.data()->rw = 1;
    message.data()->isQueued = isQueued;
    memcpy(&message.data()->params[0], jogJointParams, sizeof(JOGJointParams));
    message.data()->paramsLen = sizeof(JOGJointParams);


    // 2.Wait for command execution
    WAIT_CMD_EXECUTION(dobotId);

    // 3.The result
    if (isQueued && queuedCmdIndex) {
        memcpy(queuedCmdIndex, &message.data()->params[0], sizeof(uint64_t));
    }

    return *result;
}

int GetJOGJointParams(int dobotId, JOGJointParams *jogJointParams)
{
    // 0. Parameter checking
    if (jogJointParams == NULL) {
        return DobotCommunicate_InvalidParams;
    }

    // 1.Send the message
    QScopedPointer<Message> message(new Message);

    message.data()->id = ProtocolJOGJointParams;
    message.data()->rw = 0;
    message.data()->isQueued = false;
    message.data()->paramsLen = 0;

    // 2.Wait for command execution
    WAIT_CMD_EXECUTION(dobotId);

    // 3.The result
    memcpy(jogJointParams, &message.data()->params[0], sizeof(JOGJointParams));

    return *result;
}

int SetJOGCoordinateParams(int dobotId, JOGCoordinateParams *jogCoordinateParams, bool isQueued, uint64_t *queuedCmdIndex)
{
    // 0. Parameter checking
    if (jogCoordinateParams == NULL) {
        return DobotCommunicate_InvalidParams;
    }

    // 1.Send the message
    QScopedPointer<Message> message(new Message);

    message.data()->id = ProtocolJOGCoordinateParams;
    message.data()->rw = 1;
    message.data()->isQueued = isQueued;
    memcpy(&message.data()->params[0], jogCoordinateParams, sizeof(JOGCoordinateParams));
    message.data()->paramsLen = sizeof(JOGCoordinateParams);

    // 2.Wait for command execution
    WAIT_CMD_EXECUTION(dobotId);

    // 3.The result
    if (isQueued && queuedCmdIndex) {
        memcpy(queuedCmdIndex, &message.data()->params[0], sizeof(uint64_t));
    }
    return *result;
}

int GetJOGCoordinateParams(int dobotId, JOGCoordinateParams *jogCoordinateParams)
{
    // 0. Parameter checking
    if (jogCoordinateParams == NULL) {
        return DobotCommunicate_InvalidParams;
    }

    // 1.Send the message
    QScopedPointer<Message> message(new Message);

    message.data()->id = ProtocolJOGCoordinateParams;
    message.data()->rw = 0;
    message.data()->isQueued = false;
    message.data()->paramsLen = 0;

    // 2.Wait for command execution
    WAIT_CMD_EXECUTION(dobotId);

    // 3.The result
    memcpy(jogCoordinateParams, &message.data()->params[0], sizeof(JOGCoordinateParams));

    return *result;
}

int SetJOGCommonParams(int dobotId, JOGCommonParams *jogCommonParams, bool isQueued, uint64_t *queuedCmdIndex)
{
    // 0. Parameter checking
    if (jogCommonParams == NULL) {
        return DobotCommunicate_InvalidParams;
    }

    // 1.Send the message
    QScopedPointer<Message> message(new Message);

    message.data()->id = ProtocolJOGCommonParams;
    message.data()->rw = 1;
    message.data()->isQueued = isQueued;
    memcpy(&message.data()->params[0], jogCommonParams, sizeof(JOGCommonParams));
    message.data()->paramsLen = sizeof(JOGCommonParams);

    // 2.Wait for command execution
    WAIT_CMD_EXECUTION(dobotId);

    // 3.The result
    if (isQueued && queuedCmdIndex) {
        memcpy(queuedCmdIndex, &message.data()->params[0], sizeof(uint64_t));
    }

    return *result;
}

int GetJOGCommonParams(int dobotId, JOGCommonParams *jogCommonParams)
{
    // 0. Parameter checking
    if (jogCommonParams == NULL) {
        return DobotCommunicate_InvalidParams;
    }

    // 1.Send the message
    QScopedPointer<Message> message(new Message);

    message.data()->id = ProtocolJOGCommonParams;
    message.data()->rw = 0;
    message.data()->isQueued = false;
    message.data()->paramsLen = 0;

    // 2.Wait for command execution
    WAIT_CMD_EXECUTION(dobotId);

    // 3.The result
    memcpy(jogCommonParams, &message.data()->params[0], sizeof(JOGCommonParams));

    return *result;
}

int SetJOGCmd(int dobotId, JOGCmd *jogCmd, bool isQueued, uint64_t *queuedCmdIndex)
{
    static bool isJointJog = false;

    // 0. Parameter checking
    if (jogCmd == NULL) {
        return DobotCommunicate_InvalidParams;
    }

    // 1.Send the message
    QScopedPointer<Message> message(new Message);

    if (jogCmd->cmd != JogIdle) {
        isJointJog = jogCmd->isJoint;
    }
    message.data()->id = ProtocolJOGCmd;
    message.data()->rw = 1;
    message.data()->isQueued = isQueued;

    message.data()->params[0] = isJointJog;
    message.data()->params[1] = jogCmd->cmd;
    message.data()->paramsLen = 2;

    // 2.Wait for command execution
    WAIT_CMD_EXECUTION(dobotId);

    // 3.The result
    if (isQueued && queuedCmdIndex) {
        memcpy(queuedCmdIndex, &message.data()->params[0], sizeof(uint64_t));
    }
    return *result;
}

/*********************************************************************************************************
** PTP
*********************************************************************************************************/

int SetPTPJointParams(int dobotId, PTPJointParams *ptpJointParams, bool isQueued, uint64_t *queuedCmdIndex)
{
    // 0. Parameter checking
    if (ptpJointParams == NULL) {
        return DobotCommunicate_InvalidParams;
    }

    // 1.Send the message
    QScopedPointer<Message> message(new Message);

    message.data()->id = ProtocolPTPJointParams;
    message.data()->rw = 1;
    message.data()->isQueued = isQueued;
    memcpy(&message.data()->params[0], ptpJointParams, sizeof(PTPJointParams));
    message.data()->paramsLen = sizeof(PTPJointParams);


    // 2.Wait for command execution
    WAIT_CMD_EXECUTION(dobotId);

    // 3.The result
    if (isQueued && queuedCmdIndex) {
        memcpy(queuedCmdIndex, &message.data()->params[0], sizeof(uint64_t));
    }

    return *result;
}

int GetPTPJointParams(int dobotId, PTPJointParams *ptpJointParams)
{
    // 0. Parameter checking
    if (ptpJointParams == NULL) {
        return DobotCommunicate_InvalidParams;
    }

    // 1.Send the message
    QScopedPointer<Message> message(new Message);

    message.data()->id = ProtocolPTPJointParams;
    message.data()->rw = 0;
    message.data()->isQueued = false;
    message.data()->paramsLen = 0;

    // 2.Wait for command execution
    WAIT_CMD_EXECUTION(dobotId);

    // 3.The result
    memcpy(ptpJointParams, &message.data()->params[0], sizeof(PTPJointParams));

    return *result;
}

int SetPTPCoordinateParams(int dobotId, PTPCoordinateParams *ptpCoordinateParams, bool isQueued, uint64_t *queuedCmdIndex)
{
    // 0. Parameter checking
    if (ptpCoordinateParams == NULL) {
        return DobotCommunicate_InvalidParams;
    }

    // 1.Send the message
    QScopedPointer<Message> message(new Message);

    message.data()->id = ProtocolPTPCoordinateParams;
    message.data()->rw = 1;
    message.data()->isQueued = isQueued;
    memcpy(&message.data()->params[0], ptpCoordinateParams, sizeof(PTPCoordinateParams));
    message.data()->paramsLen = sizeof(PTPCoordinateParams);

    // 2.Wait for command execution
    WAIT_CMD_EXECUTION(dobotId);

    // 3.The result
    if (isQueued && queuedCmdIndex) {
        memcpy(queuedCmdIndex, &message.data()->params[0], sizeof(uint64_t));
    }

    return *result;
}

int GetPTPCoordinateParams(int dobotId, PTPCoordinateParams *ptpCoordinateParams)
{
    // 0. Parameter checking
    if (ptpCoordinateParams == NULL) {
        return DobotCommunicate_InvalidParams;
    }

    // 1.Send the message
    QScopedPointer<Message> message(new Message);

    message.data()->id = ProtocolPTPCoordinateParams;
    message.data()->rw = 0;
    message.data()->isQueued = false;
    message.data()->paramsLen = 0;

    // 2.Wait for command execution
    WAIT_CMD_EXECUTION(dobotId);

    // 3.The result
    memcpy(ptpCoordinateParams, &message.data()->params[0], sizeof(PTPCoordinateParams));

    return *result;
}

int SetPTPJumpParams(int dobotId, PTPJumpParams *ptpJumpParams, bool isQueued, uint64_t *queuedCmdIndex)
{
    // 0. Parameter checking
    if (ptpJumpParams == NULL) {
        return DobotCommunicate_InvalidParams;
    }

    // 1.Send the message
    QScopedPointer<Message> message(new Message);

    message.data()->id = ProtocolPTPJumpParams;
    message.data()->rw = 1;
    message.data()->isQueued = isQueued;
    memcpy(&message.data()->params[0], ptpJumpParams, sizeof(PTPJumpParams));
    message.data()->paramsLen = sizeof(PTPJumpParams);

    // 2.Wait for command execution
    WAIT_CMD_EXECUTION(dobotId);

    // 3.The result
    if (isQueued && queuedCmdIndex) {
        memcpy(queuedCmdIndex, &message.data()->params[0], sizeof(uint64_t));
    }

    return *result;
}

int GetPTPJumpParams(int dobotId, PTPJumpParams *ptpJumpParams)
{
    // 0. Parameter checking
    if (ptpJumpParams == NULL) {
        return DobotCommunicate_InvalidParams;
    }

    // 1.Send the message
    QScopedPointer<Message> message(new Message);

    message.data()->id = ProtocolPTPJumpParams;
    message.data()->rw = 0;
    message.data()->isQueued = false;
    message.data()->paramsLen = 0;

    // 2.Wait for command execution
    WAIT_CMD_EXECUTION(dobotId);

    // 3.The result
    memcpy(ptpJumpParams, &message.data()->params[0], sizeof(PTPJumpParams));

    return *result;
}

int SetPTPCommonParams(int dobotId, PTPCommonParams *ptpCommonParams, bool isQueued, uint64_t *queuedCmdIndex)
{
    // 0. Parameter checking
    if (ptpCommonParams == NULL) {
        return DobotCommunicate_InvalidParams;
    }

    // 1.Send the message
    QScopedPointer<Message> message(new Message);

    message.data()->id = ProtocolPTPCommonParams;
    message.data()->rw = 1;
    message.data()->isQueued = isQueued;
    memcpy(&message.data()->params[0], ptpCommonParams, sizeof(PTPCommonParams));
    message.data()->paramsLen = sizeof(PTPCommonParams);

    // 2.Wait for command execution
    WAIT_CMD_EXECUTION(dobotId);

    // 3.The result
    if (isQueued && queuedCmdIndex) {
        memcpy(queuedCmdIndex, &message.data()->params[0], sizeof(uint64_t));
    }

    return *result;
}

int GetPTPCommonParams(int dobotId, PTPCommonParams *ptpCommonParams)
{
    // 0. Parameter checking
    if (ptpCommonParams == NULL) {
        return DobotCommunicate_InvalidParams;
    }

    // 1.Send the message
    QScopedPointer<Message> message(new Message);

    message.data()->id = ProtocolPTPCommonParams;
    message.data()->rw = 0;
    message.data()->isQueued = false;
    message.data()->paramsLen = 0;

    // 2.Wait for command execution
    WAIT_CMD_EXECUTION(dobotId);

    // 3.The result
    memcpy(ptpCommonParams, &message.data()->params[0], sizeof(PTPCommonParams));

    return *result;
}

int SetPTPCmd(int dobotId, PTPCmd *ptpCmd, bool isQueued, uint64_t *queuedCmdIndex)
{
    // 0. Parameter checking
    if (ptpCmd == NULL) {
        return DobotCommunicate_InvalidParams;
    }

   // 1.Send the message
    QScopedPointer<Message> message(new Message);

    message.data()->id = ProtocolPTPCmd;
    message.data()->rw = 1;
    message.data()->isQueued = isQueued;
    memcpy(&message.data()->params[0], ptpCmd, sizeof(PTPCmd));
    message.data()->paramsLen = sizeof(PTPCmd);

    // 2.Wait for command execution
    WAIT_CMD_EXECUTION(dobotId);

    // 3.The result
    if (isQueued && queuedCmdIndex) {
        memcpy(queuedCmdIndex, &message.data()->params[0], sizeof(uint64_t));
    }

    return *result;
}

/*********************************************************************************************************
** CP
*********************************************************************************************************/
int SetCPParams(int dobotId, CPParams *cpParams, bool isQueued, uint64_t *queuedCmdIndex)
{
    // 0. Parameter checking
    if (cpParams == NULL) {
        return DobotCommunicate_InvalidParams;
    }

    // 1.Send the message
    QScopedPointer<Message> message(new Message);

    message.data()->id = ProtocolCPParams;
    message.data()->rw = 1;
    message.data()->isQueued = isQueued;
    memcpy(&message.data()->params[0], cpParams, sizeof(CPParams));
    message.data()->paramsLen = sizeof(CPParams);

    // 2.Wait for command execution
    WAIT_CMD_EXECUTION(dobotId);

    // 3.The result
    if (isQueued && queuedCmdIndex) {
        memcpy(queuedCmdIndex, &message.data()->params[0], sizeof(uint64_t));
    }

    return *result;
}

int GetCPParams(int dobotId, CPParams *cpParams)
{
    // 0. Parameter checking
    if (cpParams == NULL) {
        return DobotCommunicate_InvalidParams;
    }

    // 1.Send the message
    QScopedPointer<Message> message(new Message);

    message.data()->id = ProtocolCPParams;
    message.data()->rw = 0;
    message.data()->isQueued = false;
    message.data()->paramsLen = 0;

    // 2.Wait for command execution
    WAIT_CMD_EXECUTION(dobotId);

    // 3.The result
    memcpy(cpParams, &message.data()->params[0], sizeof(CPParams));

    return *result;
}

int SetCPCmd(int dobotId, CPCmd *cpCmd, bool isQueued, uint64_t *queuedCmdIndex)
{
    // 0. Parameter checking
    if (cpCmd == NULL) {
        return DobotCommunicate_InvalidParams;
    }

    // 1.Send the message
    QScopedPointer<Message> message(new Message);

    message.data()->id = ProtocolCPCmd;
    message.data()->rw = 1;
    message.data()->isQueued = isQueued;
    memcpy(&message.data()->params[0], cpCmd, sizeof(CPCmd));
    message.data()->paramsLen = sizeof(CPCmd);

    // 2.Wait for command execution
    WAIT_CMD_EXECUTION(dobotId);

    // 3.The result
    if (isQueued && queuedCmdIndex) {
        memcpy(queuedCmdIndex, &message.data()->params[0], sizeof(uint64_t));
    }

    return *result;
}

int SetCPLECmd(int dobotId, CPCmd *cpCmd, bool isQueued, uint64_t *queuedCmdIndex)
{
    // 0. Parameter checking
    if (cpCmd == NULL) {
        return DobotCommunicate_InvalidParams;
    }

    // 1.Send the message
    QScopedPointer<Message> message(new Message);

    message.data()->id = ProtocolCPLECmd;
    message.data()->rw = 1;
    message.data()->isQueued = isQueued;
    memcpy(&message.data()->params[0], cpCmd, sizeof(CPCmd));
    message.data()->paramsLen = sizeof(CPCmd);

    // 2.Wait for command execution
    WAIT_CMD_EXECUTION(dobotId);

    // 3.The result
    if (isQueued && queuedCmdIndex) {
        memcpy(queuedCmdIndex, &message.data()->params[0], sizeof(uint64_t));
    }

    return *result;
}

/*********************************************************************************************************
** ARC
*********************************************************************************************************/

int SetARCParams(int dobotId, ARCParams *arcParams, bool isQueued, uint64_t *queuedCmdIndex)
{
    // 0. Parameter checking
    if (arcParams == NULL) {
        return DobotCommunicate_InvalidParams;
    }

    // 1.Send the message
    QScopedPointer<Message> message(new Message);

    message.data()->id = ProtocolARCParams;
    message.data()->rw = 1;
    message.data()->isQueued = isQueued;
    memcpy(&message.data()->params[0], arcParams, sizeof(ARCParams));
    message.data()->paramsLen = sizeof(ARCParams);

    // 2.Wait for command execution
    WAIT_CMD_EXECUTION(dobotId);

    // 3.The result
    if (isQueued && queuedCmdIndex) {
        memcpy(queuedCmdIndex, &message.data()->params[0], sizeof(uint64_t));
    }

    return *result;
}

int GetARCParams(int dobotId, ARCParams *arcParams)
{
    // 0. Parameter checking
    if (arcParams == NULL) {
        return DobotCommunicate_InvalidParams;
    }

    // 1.Send the message
    QScopedPointer<Message> message(new Message);

    message.data()->id = ProtocolARCParams;
    message.data()->rw = 0;
    message.data()->isQueued = false;
    message.data()->paramsLen = 0;

    // 2.Wait for command execution
    WAIT_CMD_EXECUTION(dobotId);

    // 3.The result
    memcpy(arcParams, &message.data()->params[0], sizeof(ARCParams));

    return *result;
}

int SetARCCmd(int dobotId, ARCCmd *arcCmd, bool isQueued, uint64_t *queuedCmdIndex)
{
    // 0. Parameter checking
    if (arcCmd == NULL) {
        return DobotCommunicate_InvalidParams;
    }

    // 1.Send the message
    QScopedPointer<Message> message(new Message);

    message.data()->id = ProtocolARCCmd;
    message.data()->rw = 1;
    message.data()->isQueued = isQueued;
    memcpy(&message.data()->params[0], arcCmd, sizeof(ARCCmd));
    message.data()->paramsLen = sizeof(ARCCmd);

    // 2.Wait for command execution
    WAIT_CMD_EXECUTION(dobotId);

    // 3.The result
    if (isQueued && queuedCmdIndex) {
        memcpy(queuedCmdIndex, &message.data()->params[0], sizeof(uint64_t));
    }

    return *result;
}

/*********************************************************************************************************
** WAIT
*********************************************************************************************************/

int SetWAITCmd(int dobotId, WAITCmd *waitCmd, bool isQueued, uint64_t *queuedCmdIndex)
{
    // 0. Parameter checking
    if (waitCmd == NULL) {
        return DobotCommunicate_InvalidParams;
    }

    // 1.Send the message
    QScopedPointer<Message> message(new Message);

    message.data()->id = ProtocolWAITCmd;
    message.data()->rw = 1;
    message.data()->isQueued = isQueued;
    memcpy(&message.data()->params[0], waitCmd, sizeof(WAITCmd));
    message.data()->paramsLen = sizeof(WAITCmd);

    // 2.Wait for command execution
    WAIT_CMD_EXECUTION(dobotId);

    // 3.The result
    if (isQueued && queuedCmdIndex) {
        memcpy(queuedCmdIndex, &message.data()->params[0], sizeof(uint64_t));
    }

    return *result;
}

/*********************************************************************************************************
** TRIG
*********************************************************************************************************/

int SetTRIGCmd(int dobotId, TRIGCmd *trigCmd, bool isQueued, uint64_t *queuedCmdIndex)
{
    // 0. Parameter checking
    if (trigCmd == NULL) {
        return DobotCommunicate_InvalidParams;
    }

    // 1.Send the message
    QScopedPointer<Message> message(new Message);

    message.data()->id = ProtocolTRIGCmd;
    message.data()->rw = 1;
    message.data()->isQueued = isQueued;
    memcpy(&message.data()->params[0], trigCmd, sizeof(TRIGCmd));
    message.data()->paramsLen = sizeof(TRIGCmd);

    // 2.Wait for command execution
    WAIT_CMD_EXECUTION(dobotId);

    // 3.The result
    if (isQueued && queuedCmdIndex) {
        memcpy(queuedCmdIndex, &message.data()->params[0], sizeof(uint64_t));
    }

    return *result;
}

/*********************************************************************************************************
** EIO
*********************************************************************************************************/

int SetIOMultiplexing(int dobotId, IOMultiplexing *ioMultiplexing, bool isQueued, uint64_t *queuedCmdIndex)
{
    // 0. Parameter checking
    if (ioMultiplexing == NULL) {
        return DobotCommunicate_InvalidParams;
    }

    // 1.Send the message
    QScopedPointer<Message> message(new Message);

    message.data()->id = ProtocolIOMultiplexing;
    message.data()->rw = 1;
    message.data()->isQueued = isQueued;
    memcpy(&message.data()->params[0], ioMultiplexing, sizeof(IOMultiplexing));
    message.data()->paramsLen = sizeof(IOMultiplexing);

    // 2.Wait for command execution
    WAIT_CMD_EXECUTION(dobotId);

    // 3.The result
    if (isQueued && queuedCmdIndex) {
        memcpy(queuedCmdIndex, &message.data()->params[0], sizeof(uint64_t));
    }

    return *result;
}

int GetIOMultiplexing(int dobotId, IOMultiplexing *ioMultiplexing)
{
    // 0. Parameter checking
    if (ioMultiplexing == NULL) {
        return DobotCommunicate_InvalidParams;
    }

    // 1.Send the message
    QScopedPointer<Message> message(new Message);

    message.data()->id = ProtocolIOMultiplexing;
    message.data()->rw = 0;
    message.data()->isQueued = false;
    memcpy(&message.data()->params[0], ioMultiplexing, sizeof(IOMultiplexing));
    message.data()->paramsLen = sizeof(IOMultiplexing);

    // 2.Wait for command execution
    WAIT_CMD_EXECUTION(dobotId);

    // 3.The result
    memcpy(ioMultiplexing, &message.data()->params[0], sizeof(IOMultiplexing));

    return *result;
}

int SetIODO(int dobotId, IODO *ioDO, bool isQueued, uint64_t *queuedCmdIndex)
{
    // 0. Parameter checking
    if (ioDO == NULL) {
        return DobotCommunicate_InvalidParams;
    }

    // 1.Send the message
    QScopedPointer<Message> message(new Message);

    message.data()->id = ProtocolIODO;
    message.data()->rw = 1;
    message.data()->isQueued = isQueued;
    memcpy(&message.data()->params[0], ioDO, sizeof(IODO));
    message.data()->paramsLen = sizeof(IODO);

    // 2.Wait for command execution
    WAIT_CMD_EXECUTION(dobotId);

    // 3.The result
    if (isQueued && queuedCmdIndex) {
        memcpy(queuedCmdIndex, &message.data()->params[0], sizeof(uint64_t));
    }

    return *result;
}

int GetIODO(int dobotId, IODO *ioDO)
{
    // 0. Parameter checking
    if (ioDO == NULL) {
        return DobotCommunicate_InvalidParams;
    }

    // 1.Send the message
    QScopedPointer<Message> message(new Message);

    message.data()->id = ProtocolIODO;
    message.data()->rw = 0;
    message.data()->isQueued = false;
    memcpy(&message.data()->params[0], ioDO, sizeof(IODO));
    message.data()->paramsLen = sizeof(IODO);

    // 2.Wait for command execution
    WAIT_CMD_EXECUTION(dobotId);

    // 3.The result
    memcpy(ioDO, &message.data()->params[0], sizeof(IODO));

    return *result;
}

int SetIOPWM(int dobotId, IOPWM *ioPWM, bool isQueued, uint64_t *queuedCmdIndex)
{
    // 0. Parameter checking
    if (ioPWM == NULL) {
        return DobotCommunicate_InvalidParams;
    }

    // 1.Send the message
    QScopedPointer<Message> message(new Message);

    message.data()->id = ProtocolIOPWM;
    message.data()->rw = 1;
    message.data()->isQueued = isQueued;
    memcpy(&message.data()->params[0], ioPWM, sizeof(IOPWM));
    message.data()->paramsLen = sizeof(IOPWM);

    // 2.Wait for command execution
    WAIT_CMD_EXECUTION(dobotId);

    // 3.The result
    if (isQueued && queuedCmdIndex) {
        memcpy(queuedCmdIndex, &message.data()->params[0], sizeof(uint64_t));
    }

    return *result;
}

int GetIOPWM(int dobotId, IOPWM *ioPWM)
{
    // 0. Parameter checking
    if (ioPWM == NULL) {
        return DobotCommunicate_InvalidParams;
    }

    // 1.Send the message
    QScopedPointer<Message> message(new Message);

    message.data()->id = ProtocolIOPWM;
    message.data()->rw = 0;
    message.data()->isQueued = false;
    memcpy(&message.data()->params[0], ioPWM, sizeof(IOPWM));
    message.data()->paramsLen = sizeof(IOPWM);

    // 2.Wait for command execution
    WAIT_CMD_EXECUTION(dobotId);

    // 3.The result
    memcpy(ioPWM, &message.data()->params[0], sizeof(IOPWM));

    return *result;
}

int GetIODI(int dobotId, IODI *ioDI)
{
    // 0. Parameter checking
    if (ioDI == NULL) {
        return DobotCommunicate_InvalidParams;
    }

    // 1.Send the message
    QScopedPointer<Message> message(new Message);

    message.data()->id = ProtocolIODI;
    message.data()->rw = 0;
    message.data()->isQueued = false;
    memcpy(&message.data()->params[0], ioDI, sizeof(IODI));
    message.data()->paramsLen = sizeof(IODI);

    // 2.Wait for command execution
    WAIT_CMD_EXECUTION(dobotId);

    // 3.The result
    memcpy(ioDI, &message.data()->params[0], sizeof(IODI));

    return *result;
}

int GetIOADC(int dobotId, IOADC *ioADC)
{
    // 0. Parameter checking
    if (ioADC == NULL) {
        return DobotCommunicate_InvalidParams;
    }

    // 1.Send the message
    QScopedPointer<Message> message(new Message);

    message.data()->id = ProtocolIOADC;
    message.data()->rw = 0;
    message.data()->isQueued = false;
    memcpy(&message.data()->params[0], ioADC, sizeof(IOADC));
    message.data()->paramsLen = sizeof(IOADC);

    // 2.Wait for command execution
    WAIT_CMD_EXECUTION(dobotId);

    // 3.The result
    memcpy(ioADC, &message.data()->params[0], sizeof(IOADC));

    return *result;
}

int SetEMotor(int dobotId, EMotor *eMotor, bool isQueued, uint64_t *queuedCmdIndex)
{
    // 0. Parameter checking
    if (eMotor == NULL) {
        return DobotCommunicate_InvalidParams;
    }

    // 1.Send the message
    QScopedPointer<Message> message(new Message);

    message.data()->id = ProtocolEMotor;
    message.data()->rw = 1;
    message.data()->isQueued = isQueued;
    memcpy(&message.data()->params[0], eMotor, sizeof(EMotor));
    message.data()->paramsLen = sizeof(EMotor);

    // 2.Wait for command execution
    WAIT_CMD_EXECUTION(dobotId);

    // 3.The result
    if (isQueued && queuedCmdIndex) {
        memcpy(queuedCmdIndex, &message.data()->params[0], sizeof(uint64_t));
    }

    return *result;
}

/*********************************************************************************************************
** CAL
*********************************************************************************************************/

int SetAngleSensorStaticError(int dobotId, float rearArmAngleError, float frontArmAngleError)
{
    // 0. Parameter checking

    // 1.Send the message
    QScopedPointer<Message> message(new Message);

    message.data()->id = ProtocolAngleSensorStaticError;
    message.data()->rw = 1;
    message.data()->isQueued = false;
    memcpy((void *)&message.data()->params[0], (void *)&rearArmAngleError, sizeof(float));
    memcpy((void *)&message.data()->params[sizeof(float)], (void *)&frontArmAngleError, sizeof(float));
    message.data()->paramsLen = 2 * sizeof(float);

    // 2.Wait for command execution
    WAIT_CMD_EXECUTION(dobotId);

    // 3.The result
    return *result;
}

int GetAngleSensorStaticError(int dobotId, float *rearArmAngleError, float *frontArmAngleError)
{
    // 0. Parameter checking
    if (rearArmAngleError == NULL ||
        frontArmAngleError == NULL) {
        return DobotCommunicate_InvalidParams;
    }

    // 1.Send the message
    QScopedPointer<Message> message(new Message);

    message.data()->id = ProtocolAngleSensorStaticError;
    message.data()->rw = 0;
    message.data()->isQueued = false;
    message.data()->paramsLen = 0;

    // 2.Wait for command execution
    WAIT_CMD_EXECUTION(dobotId);

    // 3.The result
    memcpy((void *)rearArmAngleError, &message.data()->params[0], sizeof(float));
    memcpy((void *)frontArmAngleError, &message.data()->params[sizeof(float)], sizeof(float));

    return *result;
}

int SetAngleSensorCoef(int dobotId, float rearArmAngleCoef, float frontArmAngleCoef)
{
    // 0. Parameter checking

    // 1.Send the message
    QScopedPointer<Message> message(new Message);

    message.data()->id = ProtocolAngleSensorCoef;
    message.data()->rw = 1;
    message.data()->isQueued = false;
    memcpy((void *)&message.data()->params[0], (void *)&rearArmAngleCoef, sizeof(float));
    memcpy((void *)&message.data()->params[sizeof(float)], (void *)&frontArmAngleCoef, sizeof(float));
    message.data()->paramsLen = 2 * sizeof(float);

    // 2.Wait for command execution
    WAIT_CMD_EXECUTION(dobotId);

    // 3.The result
    return *result;
}

int GetAngleSensorCoef(int dobotId, float *rearArmAngleCoef, float *frontArmAngleCoef)
{
    // 0. Parameter checking
    if (rearArmAngleCoef == NULL ||
        frontArmAngleCoef == NULL) {
        return DobotCommunicate_InvalidParams;
    }

    // 1.Send the message
    QScopedPointer<Message> message(new Message);

    message.data()->id = ProtocolAngleSensorCoef;
    message.data()->rw = 0;
    message.data()->isQueued = false;
    message.data()->paramsLen = 0;

    // 2.Wait for command execution
    WAIT_CMD_EXECUTION(dobotId);

    // 3.The result
    memcpy((void *)rearArmAngleCoef, &message.data()->params[0], sizeof(float));
    memcpy((void *)frontArmAngleCoef, &message.data()->params[sizeof(float)], sizeof(float));

    return *result;
}

int SetBaseDecoderStaticError(int dobotId, float baseDecoderError)
{
    // 0. Parameter checking

    // 1.Send the message
    QScopedPointer<Message> message(new Message);

    message.data()->id = ProtocolBaseDecoderStaticError;
    message.data()->rw = 1;
    message.data()->isQueued = false;
    memcpy((void *)&message.data()->params[0], (void *)&baseDecoderError, sizeof(float));
    message.data()->paramsLen = sizeof(float);

    // 2.Wait for command execution
    WAIT_CMD_EXECUTION(dobotId);

    // 3.The result
    return *result;
}

int GetBaseDecoderStaticError(int dobotId, float *baseDecoderError)
{
    // 0. Parameter checking
    if (baseDecoderError == NULL) {
        return DobotCommunicate_InvalidParams;
    }

    // 1.Send the message
    QScopedPointer<Message> message(new Message);

    message.data()->id = ProtocolBaseDecoderStaticError;
    message.data()->rw = 0;
    message.data()->isQueued = false;
    message.data()->paramsLen = 0;

    // 2.Wait for command execution
    WAIT_CMD_EXECUTION(dobotId);

    // 3.The result
    memcpy((void *)baseDecoderError, &message.data()->params[0], sizeof(float));

    return *result;
}

/*********************************************************************************************************
** WIFI
*********************************************************************************************************/
int SetWIFIConfigMode(int dobotId, bool enable)
{
    // 0. Parameter checking

    // 1.Send the message
    QScopedPointer<Message> message(new Message);

    message.data()->id = ProtocolWIFIConfigMode;
    message.data()->rw = 1;
    message.data()->isQueued = false;
    message.data()->params[0] = enable;
    message.data()->paramsLen = 1;

    // 2.Wait for command execution
    WAIT_CMD_EXECUTION(dobotId);

    // 3.The result
    return *result;
}

int GetWIFIConfigMode(int dobotId, bool *isEnabled)
{
    // 0. Parameter checking
    if (isEnabled == NULL) {
        return DobotCommunicate_InvalidParams;
    }

    // 1.Send the message
    QScopedPointer<Message> message(new Message);

    message.data()->id = ProtocolWIFIConfigMode;
    message.data()->rw = 0;
    message.data()->isQueued = false;
    message.data()->paramsLen = 0;

    // 2.Wait for command execution
    WAIT_CMD_EXECUTION(dobotId);

    // 3.The result
    *isEnabled = message.data()->params[0] != 0;
    return *result;
}

int SetWIFISSID(int dobotId, const char *ssid)
{
    // 0. Parameter checking
    if (ssid == NULL) {
        return DobotCommunicate_InvalidParams;
    }

    // 1.Send the message
    QScopedPointer<Message> message(new Message);

    message.data()->id = ProtocolWIFISSID;
    message.data()->rw = 1;
    message.data()->isQueued = false;
    strcpy((char *)&message.data()->params[0], ssid);
    message.data()->paramsLen = strlen(ssid) + 1;

    // 2.Wait for command execution
    WAIT_CMD_EXECUTION(dobotId);

    // 3.The result
    return *result;
}

int GetWIFISSID(int dobotId, char *ssid, uint32_t maxLen)
{
    // 0. Parameter checking
    if (ssid == NULL ||
        maxLen == 0) {
        return DobotCommunicate_InvalidParams;
    }

    // 1.Send the message
    QScopedPointer<Message> message(new Message);

    message.data()->id = ProtocolWIFISSID;
    message.data()->rw = 0;
    message.data()->isQueued = false;
    message.data()->paramsLen = 0;

    // 2.Wait for command execution
    WAIT_CMD_EXECUTION(dobotId);

    // 3.The result
    uint32_t len = strlen((const char *)&message.data()->params[0]);
    if (len < maxLen) {
        strcpy(ssid, (const char *)&message.data()->params[0]);
    } else {
        memcpy(ssid, (const char *)&message.data()->params[0], maxLen - 1);
        ssid[maxLen - 1] = 0;
    }

    return *result;
}

int SetWIFIPassword(int dobotId, const char *password)
{
    // 0. Parameter checking
    if (password == NULL) {
        return DobotCommunicate_InvalidParams;
    }

    // 1.Send the message
    QScopedPointer<Message> message(new Message);

    message.data()->id = ProtocolWIFIPassword;
    message.data()->rw = 1;
    message.data()->isQueued = false;
    strcpy((char *)&message.data()->params[0], password);
    message.data()->paramsLen = strlen(password) + 1;

    // 2.Wait for command execution
    WAIT_CMD_EXECUTION(dobotId);

    // 3.The result
    return *result;
}

int GetWIFIPassword(int dobotId, char *password, uint32_t maxLen)
{
    // 0. Parameter checking
    if (password == NULL ||
        maxLen == 0) {
        return DobotCommunicate_InvalidParams;
    }

    // 1.Send the message
    QScopedPointer<Message> message(new Message);

    message.data()->id = ProtocolWIFIPassword;
    message.data()->rw = 0;
    message.data()->isQueued = false;
    message.data()->paramsLen = 0;

    // 2.Wait for command execution
    WAIT_CMD_EXECUTION(dobotId);

    // 3.The result
    uint32_t len = strlen((const char *)&message.data()->params[0]);
    if (len < maxLen) {
        strcpy(password, (const char *)&message.data()->params[0]);
    } else {
        memcpy(password, (const char *)&message.data()->params[0], maxLen - 1);
        password[maxLen - 1] = 0;
    }

    return *result;
}

int SetWIFIIPAddress(int dobotId, WIFIIPAddress *wifiIPAddress)
{
    // 0. Parameter checking
    if (wifiIPAddress == NULL) {
        return DobotCommunicate_InvalidParams;
    }

    // 1.Send the message
    QScopedPointer<Message> message(new Message);

    message.data()->id = ProtocolWIFIIPAddress;
    message.data()->rw = 1;
    message.data()->isQueued = false;
    memcpy(&message.data()->params[0], wifiIPAddress, sizeof(WIFIIPAddress));
    message.data()->paramsLen = sizeof(WIFIIPAddress);

    // 2.Wait for command execution
    WAIT_CMD_EXECUTION(dobotId);

    // 3.The result
    return *result;
}

int GetWIFIIPAddress(int dobotId, WIFIIPAddress *wifiIPAddress)
{
    // 0. Parameter checking
    if (wifiIPAddress == NULL) {
        return DobotCommunicate_InvalidParams;
    }

    // 1.Send the message
    QScopedPointer<Message> message(new Message);

    message.data()->id = ProtocolWIFIIPAddress;
    message.data()->rw = 0;
    message.data()->isQueued = false;
    message.data()->paramsLen = 0;

    // 2.Wait for command execution
    WAIT_CMD_EXECUTION(dobotId);

    // 3.The result
    memcpy(wifiIPAddress, &message.data()->params[0], sizeof(WIFIIPAddress));

    return *result;
}

int SetWIFINetmask(int dobotId, WIFINetmask *wifiNetmask)
{
    // 0. Parameter checking
    if (wifiNetmask == NULL) {
        return DobotCommunicate_InvalidParams;
    }

    // 1.Send the message
    QScopedPointer<Message> message(new Message);

    message.data()->id = ProtocolWIFINetmask;
    message.data()->rw = 1;
    message.data()->isQueued = false;
    memcpy(&message.data()->params[0], wifiNetmask, sizeof(WIFINetmask));
    message.data()->paramsLen = sizeof(WIFINetmask);

    // 2.Wait for command execution
    WAIT_CMD_EXECUTION(dobotId);

    // 3.The result
    return *result;
}

int GetWIFINetmask(int dobotId, WIFINetmask *wifiNetmask)
{
    // 0. Parameter checking
    if (wifiNetmask == NULL) {
        return DobotCommunicate_InvalidParams;
    }

    // 1.Send the message
    QScopedPointer<Message> message(new Message);

    message.data()->id = ProtocolWIFINetmask;
    message.data()->rw = 0;
    message.data()->isQueued = false;
    message.data()->paramsLen = 0;

    // 2.Wait for command execution
    WAIT_CMD_EXECUTION(dobotId);

    // 3.The result
    memcpy(wifiNetmask, &message.data()->params[0], sizeof(WIFINetmask));

    return *result;
}

int SetWIFIGateway(int dobotId, WIFIGateway *wifiGateway)
{
    // 0. Parameter checking
    if (wifiGateway == NULL) {
        return DobotCommunicate_InvalidParams;
    }

    // 1.Send the message
    QScopedPointer<Message> message(new Message);

    message.data()->id = ProtocolWIFIGateway;
    message.data()->rw = 1;
    message.data()->isQueued = false;
    memcpy(&message.data()->params[0], wifiGateway, sizeof(WIFIGateway));
    message.data()->paramsLen = sizeof(WIFIGateway);

    // 2.Wait for command execution
    WAIT_CMD_EXECUTION(dobotId);

    // 3.The result
    return *result;
}

int GetWIFIGateway(int dobotId, WIFIGateway *wifiGateway)
{
    // 0. Parameter checking
    if (wifiGateway == NULL) {
        return DobotCommunicate_InvalidParams;
    }

    // 1.Send the message
    QScopedPointer<Message> message(new Message);

    message.data()->id = ProtocolWIFIGateway;
    message.data()->rw = 0;
    message.data()->isQueued = false;
    message.data()->paramsLen = 0;

    // 2.Wait for command execution
    WAIT_CMD_EXECUTION(dobotId);

    // 3.The result
    memcpy(wifiGateway, &message.data()->params[0], sizeof(WIFIGateway));

    return *result;
}

int SetWIFIDNS(int dobotId, WIFIDNS *wifiDNS)
{
    // 0. Parameter checking
    if (wifiDNS == NULL) {
        return DobotCommunicate_InvalidParams;
    }

    // 1.Send the message
    QScopedPointer<Message> message(new Message);

    message.data()->id = ProtocolWIFIDNS;
    message.data()->rw = 1;
    message.data()->isQueued = false;
    memcpy(&message.data()->params[0], wifiDNS, sizeof(WIFIDNS));
    message.data()->paramsLen = sizeof(WIFIDNS);

    // 2.Wait for command execution
    WAIT_CMD_EXECUTION(dobotId);

    // 3.The result
    return *result;
}

int GetWIFIDNS(int dobotId, WIFIDNS *wifiDNS)
{
    // 0. Parameter checking
    if (wifiDNS == NULL) {
        return DobotCommunicate_InvalidParams;
    }

    // 1.Send the message
    QScopedPointer<Message> message(new Message);

    message.data()->id = ProtocolWIFIDNS;
    message.data()->rw = 0;
    message.data()->isQueued = false;
    message.data()->paramsLen = 0;

    // 2.Wait for command execution
    WAIT_CMD_EXECUTION(dobotId);

    // 3.The result
    memcpy(wifiDNS, &message.data()->params[0], sizeof(WIFIDNS));

    return *result;
}

int GetWIFIConnectStatus(int dobotId, bool *isConnected)
{
    // 0. Parameter checking
    if (isConnected == NULL) {
        return DobotCommunicate_InvalidParams;
    }

    // 1.Send the message
    QScopedPointer<Message> message(new Message);

    message.data()->id = ProtocolWIFIConnectStatus;
    message.data()->rw = 0;
    message.data()->isQueued = false;
    message.data()->paramsLen = 0;

    // 2.Wait for command execution
    WAIT_CMD_EXECUTION(dobotId);

    // 3.The result
    *isConnected = message.data()->params[0];

    return *result;
}

int GetUserParams(int dobotId, UserParams *userParams)
{
    // 0. Parameter checking
    if (userParams == NULL) {
        return DobotCommunicate_InvalidParams;
    }

    // 1.Send the message
    QScopedPointer<Message> message(new Message);

    message.data()->id = ProtocolUserParams;
    message.data()->rw = 0;
    message.data()->isQueued = false;
    message.data()->paramsLen = 0;

    // 2.Wait for command execution
    WAIT_CMD_EXECUTION(dobotId);

    // 3.The result
    memcpy(userParams, &message.data()->params[0], sizeof(UserParams));

    return *result;
}

int GetPTPTime(int dobotId, PTPCmd *ptpCmd, uint32_t *ptpTime)
{
    // 0. Parameter checking
    if (ptpCmd == NULL ||
        ptpTime == NULL) {
        return DobotCommunicate_InvalidParams;
    }

    // 1.Send the message
    QScopedPointer<Message> message(new Message);

    message.data()->id = ProtocolPTPTime;
    message.data()->rw = 0;
    message.data()->isQueued = false;
    memcpy(&message.data()->params[0], ptpCmd, sizeof(PTPCmd));
    message.data()->paramsLen = sizeof(PTPCmd);

    // 2.Wait for command execution
    WAIT_CMD_EXECUTION(dobotId);

    // 3.The result
    memcpy(ptpTime, &message.data()->params[0], sizeof(uint32_t));

    return *result;
}

/*********************************************************************************************************
** Queud command
*********************************************************************************************************/

int SetQueuedCmdStartExec(int dobotId)
{
    // 0. Parameter checking

    // 1.Send the message
    QScopedPointer<Message> message(new Message);

    message.data()->id = ProtocolQueuedCmdStartExec;
    message.data()->rw = 1;
    message.data()->isQueued = false;
    message.data()->paramsLen = 0;

    // 2.Wait for command execution
    WAIT_CMD_EXECUTION(dobotId);

    // 3.The result
    return *result;
}

int SetQueuedCmdStopExec(int dobotId)
{
    // 0. Parameter checking

    // 1.Send the message
    QScopedPointer<Message> message(new Message);

    message.data()->id = ProtocolQueuedCmdStopExec;
    message.data()->rw = 1;
    message.data()->isQueued = false;
    message.data()->paramsLen = 0;

    // 2.Wait for command execution
    WAIT_CMD_EXECUTION(dobotId);

    // 3.The result
    return *result;
}

int SetQueuedCmdForceStopExec(int dobotId)
{
    // 0. Parameter checking

    // 1.Send the message
    QScopedPointer<Message> message(new Message);

    message.data()->id = ProtocolQueuedCmdForceStopExec;
    message.data()->rw = 1;
    message.data()->isQueued = false;
    message.data()->paramsLen = 0;

    // 2.Wait for command execution
    WAIT_CMD_EXECUTION(dobotId);

    // 3.The result
    return *result;
}

int SetQueuedCmdStartDownload(int dobotId, uint32_t totalLoop, uint32_t linePerLoop)
{
    // 0. Parameter checking

    // 1.Send the message
    QScopedPointer<Message> message(new Message);

    message.data()->id = ProtocolQueuedCmdStartDownload;
    message.data()->rw = 1;
    message.data()->isQueued = false;
    memcpy(&message.data()->params[0], &totalLoop, sizeof(uint32_t));
    memcpy(&message.data()->params[4], &linePerLoop, sizeof(uint32_t));
    message.data()->paramsLen = 2 * sizeof(uint32_t);

    // 2.Wait for command execution
    WAIT_CMD_EXECUTION(dobotId);

    // 3.The result
    return *result;
}

int SetQueuedCmdStopDownload(int dobotId)
{
    // 0. Parameter checking

    // 1.Send the message
    QScopedPointer<Message> message(new Message);

    message.data()->id = ProtocolQueuedCmdStopDownload;
    message.data()->rw = 1;
    message.data()->isQueued = false;
    message.data()->paramsLen = 0;

    // 2.Wait for command execution
    WAIT_CMD_EXECUTION(dobotId);

    // 3.The result
    return *result;
}

int SetQueuedCmdClear(int dobotId)
{
    // 0. Parameter checking

    // 1.Send the message
    QScopedPointer<Message> message(new Message);

    message.data()->id = ProtocolQueuedCmdClear;
    message.data()->rw = 1;
    message.data()->isQueued = false;
    message.data()->paramsLen = 0;

    // 2.Wait for command execution
    WAIT_CMD_EXECUTION(dobotId);

    // 3.The result
    return *result;
}

int GetQueuedCmdCurrentIndex(int dobotId, uint64_t *queuedCmdCurrentIndex)
{
    // 0. Parameter checking
    if (queuedCmdCurrentIndex == NULL) {
        return DobotCommunicate_InvalidParams;
    }

    // 1.Send the message
    QScopedPointer<Message> message(new Message);

    message.data()->id = ProtocolQueuedCmdCurrentIndex;
    message.data()->rw = 0;
    message.data()->isQueued = false;
    message.data()->paramsLen = 0;

    // 2.Wait for command execution
    WAIT_CMD_EXECUTION(dobotId);

    // 3.The result
    memcpy(queuedCmdCurrentIndex, &message.data()->params[0], sizeof(uint64_t));

    return *result;
}
