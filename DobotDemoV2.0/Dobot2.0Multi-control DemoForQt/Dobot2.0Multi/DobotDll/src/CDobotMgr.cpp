#include "CDobotMgr.h"
#include <QDebug>

CDobotMgr::CDobotMgr():
    QObject(qApp)
{
    m_currentDobotKey = 0;
    m_searchDobotId = -1;
}

CDobotMgr::~CDobotMgr()
{
    QHash<int, DobotItem *>::const_iterator hash = m_dobotHash.constBegin();
    while (hash != m_dobotHash.constEnd()) {
          DobotItem *item = hash.value();
          delete item->dobot;
          delete item;
          hash++;
    }
    m_idleDobotQueue.clear();
    m_dobotHash.clear();
}

CDobot *CDobotMgr::getDobotSearchInstance()
{
    // thread safty
    if(m_searchDobotId < 0){
        m_searchDobotId = newDobotInstance(DOBOTWORKTYPE_SEARCH);
    }

    return getDobotInstance(m_searchDobotId);
}

CDobot *CDobotMgr::getDobotInstance(int id, int *outId)
{
    if(id < 0){
        id = newDobotInstance(DOBOTWORKTYPE_NORMAL);
    }
    DobotItem *item = m_dobotHash.value(id, NULL);
    if(item){
        if(outId != NULL){
            *outId = id;
        }
        return item->dobot;
    }
    return NULL;
}

int CDobotMgr::newDobotInstance(DobotWorkType type)
{
    int id = 0;

    // check idle queue
    {
        QMutexLocker locker(&m_queueMutex);
        if(m_idleDobotQueue.size() > 0){
            DobotItem *item = NULL;
            if(type == DOBOTWORKTYPE_SEARCH){
                item = m_idleDobotQueue.head();
                item->status = DOBOTWORKSTATUS_IDLE;
            }else{
                item = m_idleDobotQueue.dequeue();
                item->status = DOBOTWORKTYPE_OCCUPY;
            }
            item->type = type;
            return item->id;
        }
    }

    // get key
    {
        QMutexLocker locker(&m_keyMutex);
        id = m_currentDobotKey;
        m_currentDobotKey++;
    }

    DobotItem* item =  new DobotItem();
    CDobot *dobot = new CDobot(this);
    item->dobot = dobot;
    item->id = id;
    item->type = type;
    if(type == DOBOTWORKTYPE_SEARCH){
        item->status = DOBOTWORKSTATUS_IDLE;
        // insert idle queue
        {
            QMutexLocker locker(&m_queueMutex);
            m_idleDobotQueue.enqueue(item);
        }
    }else{
        item->status = DOBOTWORKTYPE_OCCUPY;
    }
    m_dobotHash.insert(item->id, item);
    return item->id;
}

void CDobotMgr::delDobotInstance(int id)
{
    DobotItem *item = m_dobotHash.value(id, NULL);
    if(item != NULL){
        item->status = DOBOTWORKSTATUS_IDLE;
        // delete from idle queue
        {
            QMutexLocker locker(&m_queueMutex);
            m_idleDobotQueue.enqueue(item);
        }
    }
}

CDobotMgr *CDobotMgr::m_instance = 0;
CDobotMgr *CDobotMgr::instance(void)
{
    static QMutex mutex;
    if (!m_instance) {
        QMutexLocker locker(&mutex);
        if (!m_instance){
            if (qApp == 0) {
                // In case when used in non-Qt Appliction!
                int argc = 0;
                char **argv = 0;
                new QCoreApplication(argc, argv);
            }
            m_instance = new CDobotMgr();
        }
    }

    return m_instance;
}
