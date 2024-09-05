#pragma once
#include "RemindMessageQueue.h"

#if defined(REMINDCOMDLL_LIBRARY)
    #define REMINDCOMEXPORTDLL Q_DECL_EXPORT
#else
    #define REMINDCOMEXPORTDLL Q_DECL_IMPORT
#endif

class HanglokDevice;
struct InfoDeviceNodes;
struct InfoDeviceTopology;

class REMINDCOMEXPORTDLL RemindCommunicationStack {
public:
    RemindCommunicationStack();

    ~RemindCommunicationStack() {}
    //common
    bool LoadConfig(const std::string &device_path, const std::string &topology_path);

    void SetPatientSession(const std::string &patient_id, const std::string &session_id);

    bool Init(uint64_t bid = 0);

    bool Launch();

    bool Terminate();

    RemindMessageQueue *GetOutputQueue(uint64_t bid = 0);//send data queue

    RemindMessageQueue *GetInputQueue(uint64_t bid = 0);//recv data queue

    RemindMessageQueue *DefineInputQueue(const std::string &queue_name,
                                         const std::string &exchange,
                                         const std::string &rout_key,
                                         bool no_msg_header = false);

    RemindMessageQueue *DefineOutputQueue(const std::string &queue_name,
                                          const std::string &exchange,
                                          const std::string &rout_key,
                                          bool no_msg_header = false);

    bool GetDeviceStatus(std::map<uint64_t, std::string> &status);

    bool GetDeviceStatus(uint64_t bid, std::string &status);

    void SetCurrentDeviceStatus(const std::string &status);

    void RegisterMessageFunc(const std::function<void(std::string &)> msg_callback);

    //create base info
    std::string GetCurrentNodeName();

    uint64_t GetCurrentNodeId();
    //name to id
    std::map<std::string, uint64_t> GetNodeConnectList();

    std::shared_ptr<InfoDeviceNodes> GetNodeConfig();
private:
    bool initConfig();

    void callbackMessage(std::string msg);

private:
    bool m_is_init = false;
    bool m_isLoadConfig = false;
    bool m_isRunning = false;
    std::string m_patientId = "12345678";
    std::string m_sessionId = "1";
    std::function<void(std::string &)> m_messageCallback = nullptr;
    std::shared_ptr<InfoDeviceNodes> m_info = nullptr;
    std::shared_ptr<HanglokDevice> m_device = nullptr;
    std::map<uint64_t, std::shared_ptr<InfoDeviceTopology>> m_id2topology;
    std::mutex m_mutex;
};

