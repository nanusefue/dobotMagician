#ifndef CDOBOTMGR_H
#define CDOBOTMGR_H

#include "CDobot.h"
#include <QHash>
#include <QQueue>
#include <QObject>
#include <QMutex>
#include <QMutexLocker>
#include <QCoreApplication>

enum DobotWorkType{
    DOBOTWORKTYPE_SEARCH,
    DOBOTWORKTYPE_NORMAL
};

enum DobotWorkStatus{
    DOBOTWORKSTATUS_IDLE,
    DOBOTWORKTYPE_OCCUPY
};

struct DobotItem{
    int id;
    CDobot *dobot;
    DobotWorkType type;
    DobotWorkStatus status;
    char entry[20];
};

class CDobotMgr:public QObject
{
public:
    static CDobotMgr *instance(void);
    ~CDobotMgr();
    CDobot *getDobotSearchInstance();
    CDobot *getDobotInstance(int id, int *outId=NULL);
    void delDobotInstance(int id);

private:
    CDobotMgr();
    int newDobotInstance(DobotWorkType type);
    static CDobotMgr* m_instance;

    int m_currentDobotKey;
    int m_searchDobotId;
    QMutex m_queueMutex; //for m_idleDobotQueue
    QMutex m_keyMutex; // for m_currentDobotKey
    QHash<int, DobotItem *> m_dobotHash;
    QQueue<DobotItem *> m_idleDobotQueue;
};

#endif // CDOBOTMGR_H
