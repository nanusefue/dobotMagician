#ifndef DOBOTDLL_H
#define DOBOTDLL_H

#include "DobotType.h"

extern "C"  int DobotExec(void);

extern "C"  int SearchDobot(char *dobotNameList, uint32_t maxLen);
extern "C"  int ConnectDobot(const char *portName, uint32_t baudrate, char *fwType, char *version, int *dobotId);
extern "C"  int DisconnectDobot(int dobotId);

extern "C"  int SetCmdTimeout(int dobotId, uint32_t cmdTimeout);

// Device information
extern "C"  int SetDeviceSN(int dobotId, const char *deviceSN);
extern "C"  int GetDeviceSN(int dobotId, char *deviceSN, uint32_t maxLen);

extern "C"  int SetDeviceName(int dobotId, const char *deviceName);
extern "C"  int GetDeviceName(int dobotId, char *deviceName, uint32_t maxLen);

extern "C"  int GetDeviceVersion(int dobotId, uint8_t *majorVersion, uint8_t *minorVersion, uint8_t *revision);

// Pose and Kinematics parameters are automatically get
extern "C"  int GetPose(int dobotId, Pose *pose);
extern "C"  int GetPoseEx(int dobotId, Pose *pose);
extern "C"  int ResetPose(int dobotId, bool manual, float rearArmAngle, float frontArmAngle);
extern "C"  int GetKinematics(int dobotId, Kinematics *kinematics);

// Alarms
extern "C"  int GetAlarmsState(int dobotId, uint8_t *alarmsState, uint32_t *len, uint32_t maxLen);
extern "C"  int ClearAllAlarmsState(int dobotId);

// HOME
extern "C"  int SetHOMEParams(int dobotId, HOMEParams *homeParams, bool isQueued, uint64_t *queuedCmdIndex);
extern "C"  int GetHOMEParams(int dobotId, HOMEParams *homeParams);

extern "C"  int SetHOMECmd(int dobotId, HOMECmd *homeCmd, bool isQueued, uint64_t *queuedCmdIndex);

// Handheld teach
extern "C"  int SetHHTTrigMode(int dobotId, HHTTrigMode hhtTrigMode);
extern "C"  int GetHHTTrigMode(int dobotId, HHTTrigMode *hhtTrigMode);

extern "C"  int SetHHTTrigOutputEnabled(int dobotId, bool isEnabled);
extern "C"  int GetHHTTrigOutputEnabled(int dobotId, bool *isEnabled);

extern "C"  int GetHHTTrigOutput(int dobotId, bool *isTriggered);

// EndEffector
extern "C"  int SetEndEffectorParams(int dobotId, EndEffectorParams *endEffectorParams, bool isQueued, uint64_t *queuedCmdIndex);
extern "C"  int GetEndEffectorParams(int dobotId, EndEffectorParams *endEffectorParams);

extern "C"  int SetEndEffectorLaser(int dobotId, bool enableCtrl, bool on, bool isQueued, uint64_t *queuedCmdIndex);
extern "C"  int GetEndEffectorLaser(int dobotId, bool *isCtrlEnabled, bool *isOn);

extern "C"  int SetEndEffectorSuctionCup(int dobotId, bool enableCtrl, bool suck, bool isQueued, uint64_t *queuedCmdIndex);
extern "C"  int GetEndEffectorSuctionCup(int dobotId, bool *isCtrlEnabled, bool *isSucked);

extern "C"  int SetEndEffectorGripper(int dobotId, bool enableCtrl, bool grip, bool isQueued, uint64_t *queuedCmdIndex);
extern "C"  int GetEndEffectorGripper(int dobotId, bool *isCtrlEnabled, bool *isGripped);

// Arm orientation
extern "C"  int SetArmOrientation(int dobotId, ArmOrientation armOrientation, bool isQueued, uint64_t *queuedCmdIndex);
extern "C"  int GetArmOrientation(int dobotId, ArmOrientation *armOrientation);

// JOG functions
extern "C"  int SetJOGJointParams(int dobotId, JOGJointParams *jointJogParams, bool isQueued, uint64_t *queuedCmdIndex);
extern "C"  int GetJOGJointParams(int dobotId, JOGJointParams *jointJogParams);

extern "C"  int SetJOGCoordinateParams(int dobotId, JOGCoordinateParams *coordinateJogParams, bool isQueued, uint64_t *queuedCmdIndex);
extern "C"  int GetJOGCoordinateParams(int dobotId, JOGCoordinateParams *coordinateJogParams);

extern "C"  int SetJOGCommonParams(int dobotId, JOGCommonParams *jogCommonParams, bool isQueued, uint64_t *queuedCmdIndex);
extern "C"  int GetJOGCommonParams(int dobotId, JOGCommonParams *jogCommonParams);
extern "C"  int SetJOGCmd(int dobotId, JOGCmd *jogCmd, bool isQueued, uint64_t *queuedCmdIndex);

// PTP functions
extern "C"  int SetPTPJointParams(int dobotId, PTPJointParams *ptpJointParams, bool isQueued, uint64_t *queuedCmdIndex);
extern "C"  int GetPTPJointParams(int dobotId, PTPJointParams *ptpJointParams);
extern "C"  int SetPTPCoordinateParams(int dobotId, PTPCoordinateParams *ptpCoordinateParams, bool isQueued, uint64_t *queuedCmdIndex);
extern "C"  int GetPTPCoordinateParams(int dobotId, PTPCoordinateParams *ptpCoordinateParams);
extern "C"  int SetPTPJumpParams(int dobotId, PTPJumpParams *ptpJumpParams, bool isQueued, uint64_t *queuedCmdIndex);
extern "C"  int GetPTPJumpParams(int dobotId, PTPJumpParams *ptpJumpParams);
extern "C"  int SetPTPCommonParams(int dobotId, PTPCommonParams *ptpCommonParams, bool isQueued, uint64_t *queuedCmdIndex);
extern "C"  int GetPTPCommonParams(int dobotId, PTPCommonParams *ptpCommonParams);

extern "C"  int SetPTPCmd(int dobotId, PTPCmd *ptpCmd, bool isQueued, uint64_t *queuedCmdIndex);

// CP functions
extern "C"  int SetCPParams(int dobotId, CPParams *cpParams, bool isQueued, uint64_t *queuedCmdIndex);
extern "C"  int GetCPParams(int dobotId, CPParams *cpParams);
extern "C"  int SetCPCmd(int dobotId, CPCmd *cpCmd, bool isQueued, uint64_t *queuedCmdIndex);
extern "C"  int SetCPLECmd(int dobotId, CPCmd *cpCmd, bool isQueued, uint64_t *queuedCmdIndex);

// ARC
extern "C"  int SetARCParams(int dobotId, ARCParams *arcParams, bool isQueued, uint64_t *queuedCmdIndex);
extern "C"  int GetARCParams(int dobotId, ARCParams *arcParams);
extern "C"  int SetARCCmd(int dobotId, ARCCmd *arcCmd, bool isQueued, uint64_t *queuedCmdIndex);

// WAIT
extern "C"  int SetWAITCmd(int dobotId, WAITCmd *waitCmd, bool isQueued, uint64_t *queuedCmdIndex);

// TRIG
extern "C"  int SetTRIGCmd(int dobotId, TRIGCmd *trigCmd, bool isQueued, uint64_t *queuedCmdIndex);

// EIO
extern "C"  int SetIOMultiplexing(int dobotId, IOMultiplexing *ioMultiplexing, bool isQueued, uint64_t *queuedCmdIndex);
extern "C"  int GetIOMultiplexing(int dobotId, IOMultiplexing *ioMultiplexing);

extern "C"  int SetIODO(int dobotId, IODO *ioDO, bool isQueued, uint64_t *queuedCmdIndex);
extern "C"  int GetIODO(int dobotId, IODO *ioDO);

extern "C"  int SetIOPWM(int dobotId, IOPWM *ioPWM, bool isQueued, uint64_t *queuedCmdIndex);
extern "C"  int GetIOPWM(int dobotId, IOPWM *ioPWM);

extern "C"  int GetIODI(int dobotId, IODI *ioDI);
extern "C"  int GetIOADC(int dobotId, IOADC *ioADC);

extern "C"  int SetEMotor(int dobotId, EMotor *eMotor, bool isQueued, uint64_t *queuedCmdIndex);

// CAL
extern "C"  int SetAngleSensorStaticError(int dobotId, float rearArmAngleError, float frontArmAngleError);
extern "C"  int GetAngleSensorStaticError(int dobotId, float *rearArmAngleError, float *frontArmAngleError);
extern "C"  int SetAngleSensorCoef(int dobotId, float rearArmAngleCoef, float frontArmAngleCoef);
extern "C"  int GetAngleSensorCoef(int dobotId, float *rearArmAngleCoef, float *frontArmAngleCoef);

extern "C"  int SetBaseDecoderStaticError(int dobotId, float baseDecoderError);
extern "C"  int GetBaseDecoderStaticError(int dobotId, float *baseDecoderError);

// WIFI
extern "C"  int SetWIFIConfigMode(int dobotId, bool enable);
extern "C"  int GetWIFIConfigMode(int dobotId, bool *isEnabled);
extern "C"  int SetWIFISSID(int dobotId, const char *ssid);
extern "C"  int GetWIFISSID(int dobotId, char *ssid, uint32_t maxLen);
extern "C"  int SetWIFIPassword(int dobotId, const char *password);
extern "C"  int GetWIFIPassword(int dobotId, char *password, uint32_t maxLen);
extern "C"  int SetWIFIIPAddress(int dobotId, WIFIIPAddress *wifiIPAddress);
extern "C"  int GetWIFIIPAddress(int dobotId, WIFIIPAddress *wifiIPAddress);
extern "C"  int SetWIFINetmask(int dobotId, WIFINetmask *wifiNetmask);
extern "C"  int GetWIFINetmask(int dobotId, WIFINetmask *wifiNetmask);
extern "C"  int SetWIFIGateway(int dobotId, WIFIGateway *wifiGateway);
extern "C"  int GetWIFIGateway(int dobotId, WIFIGateway *wifiGateway);
extern "C"  int SetWIFIDNS(int dobotId, WIFIDNS *wifiDNS);
extern "C"  int GetWIFIDNS(int dobotId, WIFIDNS *wifiDNS);
extern "C"  int GetWIFIConnectStatus(int dobotId, bool *isConnected);

// TEST
extern "C"  int GetUserParams(int dobotId, UserParams *userParams);
extern "C"  int GetPTPTime(int dobotId, PTPCmd *ptpCmd, uint32_t *ptpTime);

// Queued command
extern "C"  int SetQueuedCmdStartExec(int dobotId);
extern "C"  int SetQueuedCmdStopExec(int dobotId);
extern "C"  int SetQueuedCmdForceStopExec(int dobotId);
extern "C"  int SetQueuedCmdStartDownload(int dobotId, uint32_t totalLoop, uint32_t linePerLoop);
extern "C"  int SetQueuedCmdStopDownload(int dobotId);
extern "C"  int SetQueuedCmdClear(int dobotId);
extern "C"  int GetQueuedCmdCurrentIndex(int dobotId, uint64_t *queuedCmdCurrentIndex);

#endif // DOBOTDLL_H
