#pragma once
#include <QObject>
#include <vector>
#include "xpack.h"
using namespace std;

struct InfoPreoperative {
    vector<QString> m_ctSourceIds;
    vector<QString> m_ctResultIds;
    vector<QString> m_digitalBodyIds;
    vector<QString> m_seedDistributeIds;//去除
    vector<QString> m_needlePathIds;//改为介入路径
};

struct InfoIntraOperative {
    QString m_ultrasound;
    QString m_opticalVision;
    QString m_control;
    QString m_feedback;
};

struct InfoPostOperative {
    vector<QString> m_reference;
};

struct InfoSession {
    QString id;
    QString admissionNo;
    uint32_t admissionCount;
    uint64_t admissionTime;
    QString bedNo;
    QString archiater;
    QString secondDr;
    QString thirdDr;
    QString symptom;
    //InfoPreoperative m_preoperativeInfo;
    //InfoIntraOperative m_intraoperativeInfo;
    //InfoPostOperative m_postoperativeInfo;
    XPACK(O(id, admissionNo, admissionCount, admissionTime, bedNo, archiater, secondDr, thirdDr, symptom));
};
