#pragma once
#include <QObject>
#include <QMap>
#include <QPoint>
#include <string>
#include <memory>
#include <QMetaType>
using namespace std;

struct InfoRabbitMq {
    int port;
    QString ip;
    QString user;
    QString password;
    QString vhost;
    QString type;
};

struct InfoDevice {
    uint64_t bid;
    QString name;
    QString ip;
    int port;
};

struct InfoHeartBeat {
    int interval;
    QString ip;
    int port;
    QString rout;
};

struct InfoDeviceTopology {
    uint64_t bid;
    QString name;
    QList<uint64_t> connects; //bid
    QPoint pos = QPoint(0, 0);
    bool storage_message = true;
    //QString exchange;
    //QString rout; //routing key
};

struct InfoService {
    QString ip;
    int port;
    QString node_content;
    QString data_content;
    QString file_content;
};

struct InfoDeviceNodes {
    shared_ptr<InfoRabbitMq> rabbitmq = nullptr;
    shared_ptr<InfoService> service = nullptr;
    QMap<uint64_t, shared_ptr<InfoDevice>> id2infoDevices;
    shared_ptr<InfoHeartBeat> heartbeat = nullptr;
    QString patient_id;
    QString session_id;
    uint64_t cur_bid;
    shared_ptr<InfoDeviceTopology> cur_top = nullptr;
    QList<shared_ptr<InfoDeviceTopology>> connect_tops;
};

struct InfoOperation {
    QString patient_name;
    QString patient_id;
    QString session_id;
};

