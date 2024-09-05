#pragma once
#include <QObject>
#include <memory>
#include "type_operative.h"
#include "info_operative_point.h"
using namespace std;

struct InfoNeedle {
    QString id;
    QString needleNo;
    QList<shared_ptr<InfoPoint3D>> points;
    uint32_t pointCount;
    XPACK(O(id, needleNo, points, pointCount));
};

struct InfoOperativeLesion {
    QString id;
    QString digitalBodyId;
    uint32_t needleCount;
    QList<shared_ptr<InfoNeedle>> needlesInfo;
    QString tumor_no;
    QString sessionId;
    XPACK(O(id, digitalBodyId, needleCount, needlesInfo, tumor_no, sessionId));
};
