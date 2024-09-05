#pragma once
#include <list>
#include <vector>
#include <map>
#include <string>
#include <memory>
// using namespace std;

struct InfoRabbitMq {
    int port;
    std::string ip;
    std::string user;
    std::string password;
    std::string vhost;
    std::string type;
};

struct InfoDevice {
    uint64_t bid;
    std::string name;
    std::string ip;
    int port;
};

struct InfoHeartBeat {
    int interval;
    std::string ip;
    int port;
    std::string rout;
};

struct InfoDefineQueue {
    std::string queue_name;
    std::string exchange;
    std::string rout_key;
    bool no_msg_header = false;
};

struct InfoDeviceTopology {
    uint64_t bid;
    std::string name;
    std::list<uint64_t> connects; //bid
    std::vector<float> pos = {0, 0};
    bool storage_message = true;
    //QString exchange;
    //QString rout; //routing key
};

struct InfoService {
    std::string ip;
    int port;
    std::string node_content;
    std::string data_content;
    std::string file_content;
};

struct InfoDeviceNodes {
    std::shared_ptr<InfoRabbitMq> rabbitmq = nullptr;
    std::shared_ptr<InfoService> service = nullptr;
    std::map<uint64_t, std::shared_ptr<InfoDevice>> id2infoDevices;
    std::shared_ptr<InfoHeartBeat> heartbeat = nullptr;
    std::string patient_id;
    std::string session_id;
    uint64_t cur_bid;
    std::shared_ptr<InfoDeviceTopology> cur_top = nullptr;
    std::list<std::shared_ptr<InfoDeviceTopology>> connect_tops;
};

struct InfoOperation {
    std::string patient_name;
    std::string patient_id;
    std::string session_id;
};

