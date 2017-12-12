#ifndef DOBOTDLL_H
#define DOBOTDLL_H

#include "dobotdll_global.h"
#include "DobotType.h"

extern "C" DOBOTDLLSHARED_EXPORT int DobotExec(void);

extern "C" DOBOTDLLSHARED_EXPORT int SearchDobot(char *dobotNameList, uint32_t maxLen);
extern "C" DOBOTDLLSHARED_EXPORT int ConnectDobot(const char *portName, uint32_t baudrate, char *fwType, char *version, int *dobotId);
extern "C" DOBOTDLLSHARED_EXPORT int DisconnectDobot(int dobotId);

extern "C" DOBOTDLLSHARED_EXPORT int SetCmdTimeout(int dobotId, uint32_t cmdTimeout);

// Device information
extern "C" DOBOTDLLSHARED_EXPORT int SetDeviceSN(int dobotId, const char *deviceSN);
extern "C" DOBOTDLLSHARED_EXPORT int GetDeviceSN(int dobotId, char *deviceSN, uint32_t maxLen);

extern "C" DOBOTDLLSHARED_EXPORT int SetDeviceName(int dobotId, const char *deviceName);
extern "C" DOBOTDLLSHARED_EXPORT int GetDeviceName(int dobotId, char *deviceName, uint32_t maxLen);

extern "C" DOBOTDLLSHARED_EXPORT int GetDeviceVersion(int dobotId, uint8_t *majorVersion, uint8_t *minorVersion, uint8_t *revision);

// Pose and Kinematics parameters are automatically get
extern "C" DOBOTDLLSHARED_EXPORT int GetPose(int dobotId, Pose *pose);
extern "C" DOBOTDLLSHARED_EXPORT int GetPoseEx(int dobotId, Pose *pose);
extern "C" DOBOTDLLSHARED_EXPORT int ResetPose(int dobotId, bool manual, float rearArmAngle, float frontArmAngle);
extern "C" DOBOTDLLSHARED_EXPORT int GetKinematics(int dobotId, Kinematics *kinematics);

// Alarms
extern "C" DOBOTDLLSHARED_EXPORT int GetAlarmsState(int dobotId, uint8_t *alarmsState, uint32_t *len, uint32_t maxLen);
extern "C" DOBOTDLLSHARED_EXPORT int ClearAllAlarmsState(int dobotId);

// HOME
extern "C" DOBOTDLLSHARED_EXPORT int SetHOMEParams(int dobotId, HOMEParams *homeParams, bool isQueued, uint64_t *queuedCmdIndex);
extern "C" DOBOTDLLSHARED_EXPORT int GetHOMEParams(int dobotId, HOMEParams *homeParams);

extern "C" DOBOTDLLSHARED_EXPORT int SetHOMECmd(int dobotId, HOMECmd *homeCmd, bool isQueued, uint64_t *queuedCmdIndex);

// Handheld teach
extern "C" DOBOTDLLSHARED_EXPORT int SetHHTTrigMode(int dobotId, HHTTrigMode hhtTrigMode);
extern "C" DOBOTDLLSHARED_EXPORT int GetHHTTrigMode(int dobotId, HHTTrigMode *hhtTrigMode);

extern "C" DOBOTDLLSHARED_EXPORT int SetHHTTrigOutputEnabled(int dobotId, bool isEnabled);
extern "C" DOBOTDLLSHARED_EXPORT int GetHHTTrigOutputEnabled(int dobotId, bool *isEnabled);

extern "C" DOBOTDLLSHARED_EXPORT int GetHHTTrigOutput(int dobotId, bool *isTriggered);

// EndEffector
extern "C" DOBOTDLLSHARED_EXPORT int SetEndEffectorParams(int dobotId, EndEffectorParams *endEffectorParams, bool isQueued, uint64_t *queuedCmdIndex);
extern "C" DOBOTDLLSHARED_EXPORT int GetEndEffectorParams(int dobotId, EndEffectorParams *endEffectorParams);

extern "C" DOBOTDLLSHARED_EXPORT int SetEndEffectorLaser(int dobotId, bool enableCtrl, bool on, bool isQueued, uint64_t *queuedCmdIndex);
extern "C" DOBOTDLLSHARED_EXPORT int GetEndEffectorLaser(int dobotId, bool *isCtrlEnabled, bool *isOn);

extern "C" DOBOTDLLSHARED_EXPORT int SetEndEffectorSuctionCup(int dobotId, bool enableCtrl, bool suck, bool isQueued, uint64_t *queuedCmdIndex);
extern "C" DOBOTDLLSHARED_EXPORT int GetEndEffectorSuctionCup(int dobotId, bool *isCtrlEnabled, bool *isSucked);

extern "C" DOBOTDLLSHARED_EXPORT int SetEndEffectorGripper(int dobotId, bool enableCtrl, bool grip, bool isQueued, uint64_t *queuedCmdIndex);
extern "C" DOBOTDLLSHARED_EXPORT int GetEndEffectorGripper(int dobotId, bool *isCtrlEnabled, bool *isGripped);

// Arm orientation
extern "C" DOBOTDLLSHARED_EXPORT int SetArmOrientation(int dobotId, ArmOrientation armOrientation, bool isQueued, uint64_t *queuedCmdIndex);
extern "C" DOBOTDLLSHARED_EXPORT int GetArmOrientation(int dobotId, ArmOrientation *armOrientation);

// JOG functions
extern "C" DOBOTDLLSHARED_EXPORT int SetJOGJointParams(int dobotId, JOGJointParams *jointJogParams, bool isQueued, uint64_t *queuedCmdIndex);
extern "C" DOBOTDLLSHARED_EXPORT int GetJOGJointParams(int dobotId, JOGJointParams *jointJogParams);

extern "C" DOBOTDLLSHARED_EXPORT int SetJOGCoordinateParams(int dobotId, JOGCoordinateParams *coordinateJogParams, bool isQueued, uint64_t *queuedCmdIndex);
extern "C" DOBOTDLLSHARED_EXPORT int GetJOGCoordinateParams(int dobotId, JOGCoordinateParams *coordinateJogParams);

extern "C" DOBOTDLLSHARED_EXPORT int SetJOGCommonParams(int dobotId, JOGCommonParams *jogCommonParams, bool isQueued, uint64_t *queuedCmdIndex);
extern "C" DOBOTDLLSHARED_EXPORT int GetJOGCommonParams(int dobotId, JOGCommonParams *jogCommonParams);
extern "C" DOBOTDLLSHARED_EXPORT int SetJOGCmd(int dobotId, JOGCmd *jogCmd, bool isQueued, uint64_t *queuedCmdIndex);

// PTP functions
extern "C" DOBOTDLLSHARED_EXPORT int SetPTPJointParams(int dobotId, PTPJointParams *ptpJointParams, bool isQueued, uint64_t *queuedCmdIndex);
extern "C" DOBOTDLLSHARED_EXPORT int GetPTPJointParams(int dobotId, PTPJointParams *ptpJointParams);
extern "C" DOBOTDLLSHARED_EXPORT int SetPTPCoordinateParams(int dobotId, PTPCoordinateParams *ptpCoordinateParams, bool isQueued, uint64_t *queuedCmdIndex);
extern "C" DOBOTDLLSHARED_EXPORT int GetPTPCoordinateParams(int dobotId, PTPCoordinateParams *ptpCoordinateParams);
extern "C" DOBOTDLLSHARED_EXPORT int SetPTPJumpParams(int dobotId, PTPJumpParams *ptpJumpParams, bool isQueued, uint64_t *queuedCmdIndex);
extern "C" DOBOTDLLSHARED_EXPORT int GetPTPJumpParams(int dobotId, PTPJumpParams *ptpJumpParams);
extern "C" DOBOTDLLSHARED_EXPORT int SetPTPCommonParams(int dobotId, PTPCommonParams *ptpCommonParams, bool isQueued, uint64_t *queuedCmdIndex);
extern "C" DOBOTDLLSHARED_EXPORT int GetPTPCommonParams(int dobotId, PTPCommonParams *ptpCommonParams);

extern "C" DOBOTDLLSHARED_EXPORT int SetPTPCmd(int dobotId, PTPCmd *ptpCmd, bool isQueued, uint64_t *queuedCmdIndex);

// CP functions
extern "C" DOBOTDLLSHARED_EXPORT int SetCPParams(int dobotId, CPParams *cpParams, bool isQueued, uint64_t *queuedCmdIndex);
extern "C" DOBOTDLLSHARED_EXPORT int GetCPParams(int dobotId, CPParams *cpParams);
extern "C" DOBOTDLLSHARED_EXPORT int SetCPCmd(int dobotId, CPCmd *cpCmd, bool isQueued, uint64_t *queuedCmdIndex);
extern "C" DOBOTDLLSHARED_EXPORT int SetCPLECmd(int dobotId, CPCmd *cpCmd, bool isQueued, uint64_t *queuedCmdIndex);

// ARC
extern "C" DOBOTDLLSHARED_EXPORT int SetARCParams(int dobotId, ARCParams *arcParams, bool isQueued, uint64_t *queuedCmdIndex);
extern "C" DOBOTDLLSHARED_EXPORT int GetARCParams(int dobotId, ARCParams *arcParams);
extern "C" DOBOTDLLSHARED_EXPORT int SetARCCmd(int dobotId, ARCCmd *arcCmd, bool isQueued, uint64_t *queuedCmdIndex);

// WAIT
extern "C" DOBOTDLLSHARED_EXPORT int SetWAITCmd(int dobotId, WAITCmd *waitCmd, bool isQueued, uint64_t *queuedCmdIndex);

// TRIG
extern "C" DOBOTDLLSHARED_EXPORT int SetTRIGCmd(int dobotId, TRIGCmd *trigCmd, bool isQueued, uint64_t *queuedCmdIndex);

// EIO
extern "C" DOBOTDLLSHARED_EXPORT int SetIOMultiplexing(int dobotId, IOMultiplexing *ioMultiplexing, bool isQueued, uint64_t *queuedCmdIndex);
extern "C" DOBOTDLLSHARED_EXPORT int GetIOMultiplexing(int dobotId, IOMultiplexing *ioMultiplexing);

extern "C" DOBOTDLLSHARED_EXPORT int SetIODO(int dobotId, IODO *ioDO, bool isQueued, uint64_t *queuedCmdIndex);
extern "C" DOBOTDLLSHARED_EXPORT int GetIODO(int dobotId, IODO *ioDO);

extern "C" DOBOTDLLSHARED_EXPORT int SetIOPWM(int dobotId, IOPWM *ioPWM, bool isQueued, uint64_t *queuedCmdIndex);
extern "C" DOBOTDLLSHARED_EXPORT int GetIOPWM(int dobotId, IOPWM *ioPWM);

extern "C" DOBOTDLLSHARED_EXPORT int GetIODI(int dobotId, IODI *ioDI);
extern "C" DOBOTDLLSHARED_EXPORT int GetIOADC(int dobotId, IOADC *ioADC);

extern "C" DOBOTDLLSHARED_EXPORT int SetEMotor(int dobotId, EMotor *eMotor, bool isQueued, uint64_t *queuedCmdIndex);

// CAL
extern "C" DOBOTDLLSHARED_EXPORT int SetAngleSensorStaticError(int dobotId, float rearArmAngleError, float frontArmAngleError);
extern "C" DOBOTDLLSHARED_EXPORT int GetAngleSensorStaticError(int dobotId, float *rearArmAngleError, float *frontArmAngleError);
extern "C" DOBOTDLLSHARED_EXPORT int SetAngleSensorCoef(int dobotId, float rearArmAngleCoef, float frontArmAngleCoef);
extern "C" DOBOTDLLSHARED_EXPORT int GetAngleSensorCoef(int dobotId, float *rearArmAngleCoef, float *frontArmAngleCoef);

extern "C" DOBOTDLLSHARED_EXPORT int SetBaseDecoderStaticError(int dobotId, float baseDecoderError);
extern "C" DOBOTDLLSHARED_EXPORT int GetBaseDecoderStaticError(int dobotId, float *baseDecoderError);

// WIFI
extern "C" DOBOTDLLSHARED_EXPORT int SetWIFIConfigMode(int dobotId, bool enable);
extern "C" DOBOTDLLSHARED_EXPORT int GetWIFIConfigMode(int dobotId, bool *isEnabled);
extern "C" DOBOTDLLSHARED_EXPORT int SetWIFISSID(int dobotId, const char *ssid);
extern "C" DOBOTDLLSHARED_EXPORT int GetWIFISSID(int dobotId, char *ssid, uint32_t maxLen);
extern "C" DOBOTDLLSHARED_EXPORT int SetWIFIPassword(int dobotId, const char *password);
extern "C" DOBOTDLLSHARED_EXPORT int GetWIFIPassword(int dobotId, char *password, uint32_t maxLen);
extern "C" DOBOTDLLSHARED_EXPORT int SetWIFIIPAddress(int dobotId, WIFIIPAddress *wifiIPAddress);
extern "C" DOBOTDLLSHARED_EXPORT int GetWIFIIPAddress(int dobotId, WIFIIPAddress *wifiIPAddress);
extern "C" DOBOTDLLSHARED_EXPORT int SetWIFINetmask(int dobotId, WIFINetmask *wifiNetmask);
extern "C" DOBOTDLLSHARED_EXPORT int GetWIFINetmask(int dobotId, WIFINetmask *wifiNetmask);
extern "C" DOBOTDLLSHARED_EXPORT int SetWIFIGateway(int dobotId, WIFIGateway *wifiGateway);
extern "C" DOBOTDLLSHARED_EXPORT int GetWIFIGateway(int dobotId, WIFIGateway *wifiGateway);
extern "C" DOBOTDLLSHARED_EXPORT int SetWIFIDNS(int dobotId, WIFIDNS *wifiDNS);
extern "C" DOBOTDLLSHARED_EXPORT int GetWIFIDNS(int dobotId, WIFIDNS *wifiDNS);
extern "C" DOBOTDLLSHARED_EXPORT int GetWIFIConnectStatus(int dobotId, bool *isConnected);

// TEST
extern "C" DOBOTDLLSHARED_EXPORT int GetUserParams(int dobotId, UserParams *userParams);
extern "C" DOBOTDLLSHARED_EXPORT int GetPTPTime(int dobotId, PTPCmd *ptpCmd, uint32_t *ptpTime);

// Queued command
extern "C" DOBOTDLLSHARED_EXPORT int SetQueuedCmdStartExec(int dobotId);
extern "C" DOBOTDLLSHARED_EXPORT int SetQueuedCmdStopExec(int dobotId);
extern "C" DOBOTDLLSHARED_EXPORT int SetQueuedCmdForceStopExec(int dobotId);
extern "C" DOBOTDLLSHARED_EXPORT int SetQueuedCmdStartDownload(int dobotId, uint32_t totalLoop, uint32_t linePerLoop);
extern "C" DOBOTDLLSHARED_EXPORT int SetQueuedCmdStopDownload(int dobotId);
extern "C" DOBOTDLLSHARED_EXPORT int SetQueuedCmdClear(int dobotId);
extern "C" DOBOTDLLSHARED_EXPORT int GetQueuedCmdCurrentIndex(int dobotId, uint64_t *queuedCmdCurrentIndex);

#endif // DOBOTDLL_H
