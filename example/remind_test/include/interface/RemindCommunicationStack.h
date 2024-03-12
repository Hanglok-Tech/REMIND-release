#pragma once
#include <QObject>
#include <QMap>
#include <memory>
#include "RemindGlobal.h"
#include "RemindMessageQueue.h"
using namespace std;

class HanglokDevice;
struct InfoDeviceNodes;
struct InfoDeviceTopology;

class REMINDEXPORTDLL RemindCommunicationStack : public QObject {
    Q_OBJECT
public:
    RemindCommunicationStack();
    ~RemindCommunicationStack() {}
    //common
    bool LoadConfig(const QString &device_path, const QString &topology_path);
    void SetPatientSession(const QString &patient_id, const QString &session_id);
    //node communication
    bool Launch(uint64_t bid = 0);
    bool Terminate();
    RemindMessageQueue *GetOutputQueue(uint64_t bid = 0);//send data queue
    RemindMessageQueue *GetInputQueue(uint64_t bid = 0);//recv data queue
    bool GetDeviceStatus(QMap<uint64_t, QString> &status);
    bool GetDeviceStatus(uint64_t bid, QString &status);
    void RegisterMsgFunc(const std::function<void(int, string)> &msg_callback);

    //create base info
    QString GetCurrentNodeName();
    uint64_t GetCurrentNodeId();
    //name to id
    QMap<QString, uint64_t> GetNodeConnectList();
    shared_ptr<InfoDeviceNodes> GetNodeConfig();
private:
    bool initConfig();

signals:
    void sigMessage(const QString &msg);

private slots:
    void slotRecvMessage(const QString &msg);
private:
    bool m_isLoadConfig = false;
    bool m_isRunning = false;
    QString m_patientId;
    QString m_sessionId;
    std::function<void(int, string)> m_msg_callback = nullptr;
    shared_ptr<InfoDeviceNodes> m_info = nullptr;
    shared_ptr<HanglokDevice> m_device = nullptr;
    QMap<uint64_t, shared_ptr<InfoDeviceTopology>> m_id2topology;
};

