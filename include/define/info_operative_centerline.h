#pragma once
#include "info_operative_point.h"

struct InfoCenterLine {
    QString id;
    QString sessionId;
    QList<InfoPoint3D> points;
    XPACK(O(points));
};
