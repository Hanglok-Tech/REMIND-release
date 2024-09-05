#pragma once
#include <string>
#include <QObject>
#include "RemindGlobal.h"

//TODO: 区分业务状态和健康状态
namespace CommonNodeStatus
{
    const std::string NotStarted = "not-started";
    const std::string Standby = "stand-by";
    const std::string Inactive = "i";
    const std::string Bussy = "busy";
    const std::string Active = "a";
    const std::string NodeException = "e";
}
namespace BuildinNodeException
{
    const std::string HeartBeatError = "HagHeartBeatError";
}

class REMINDEXPORTDLL NodeStatus{
public:
    NodeStatus();
    NodeStatus(std::string status, std::string common);
    std::string status = CommonNodeStatus::NotStarted;
    std::string common = "";
};
Q_DECLARE_METATYPE(NodeStatus);
