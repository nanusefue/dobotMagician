import threading
import DobotDllType as dType
from PyQt4.QtCore import *
from PyQt4.QtGui import *

CON_STR = {
    dType.DobotConnect.DobotConnect_NoError:  "DobotConnect_NoError",
    dType.DobotConnect.DobotConnect_NotFound: "DobotConnect_NotFound",
    dType.DobotConnect.DobotConnect_Occupied: "DobotConnect_Occupied"}

#Load Dll
api = dType.load()

#Connect Dobot
state = dType.ConnectDobot(api, "", 115200)[0]
print("Connect status:",CON_STR[state])

if (state == dType.DobotConnect.DobotConnect_NoError):

    #Clean Command Queued
    dType.SetQueuedCmdClear(api)

    #Async Motion Params Setting
    dType.SetHOMEParams(api, 250, 0, 0,0,isQueued = 1)
   # dType.SetPTPJointParams(api, 200, 200, 200, 200, 200, 200, 200, 200, isQueued = 1)
   # dType.SetPTPCommonParams(api, 100, 100, isQueued = 1)

    #Async Home
    dType.SetHOMECmd(api, temp = 0, isQueued = 1)

    cPoint=[250,-110,-60,0]
    tPoint=[220,-110,-55,0]
    _cPoint=[220,-110,-60,0]
    _tPoint=[250,-110,-55,0]
    
    lastIndex = dType.SetPTPCmd(api, dType.PTPMode.PTPMOVLXYZMode, 250,0,0,0, isQueued = 1)[0]
    lastIndex = dType.SetPTPCmd(api, dType.PTPMode.PTPMOVLXYZMode, 250,-110,10,0, isQueued = 1)[0]
    lastIndex = dType.SetPTPCmd(api, dType.PTPMode.PTPMOVLXYZMode, 250,-110,-55,0, isQueued = 1)[0]
    lastIndex = dType.SetARCCmd(api,cPoint,tPoint, isQueued = 1)[0]
    lastIndex = dType.SetARCCmd(api,_cPoint,_tPoint, isQueued = 1)[0]
    print lastIndex


    #Async PTP Motion
#    for i in range(0, 5):
#        if i % 2 == 0:
#            offset = 50
#        else:
#            offset = -50
#        lastIndex = dType.SetPTPCmd(api, dType.PTPMode.PTPMOVLXYZMode, 200 + offset, offset, offset, offset, isQueued = 1)[0]

    #Start to Execute Command Queued
    dType.SetQueuedCmdStartExec(api)

    #Wait for Executing Last Command 
    while lastIndex > dType.GetQueuedCmdCurrentIndex(api)[0]:
        dType.dSleep(100)

    #Stop to Execute Command Queued
    dType.SetQueuedCmdStopExec(api)

#Disconnect Dobot
dType.DisconnectDobot(api)
