#pragma once
#include <QObject>
#include "type_operative.h"
#include "xpack.h"

struct InfoOperativeFile {
    QString id;//return by save db
    //QString fileId;
    QString filePath;//must
    QString fileName;//must
    QString fileSuffix;//must 文件后缀
    QString md5;
    QString sessionId;
    XPACK(O(id, filePath, fileName, fileSuffix, md5, sessionId));
};

struct InfoImageResultFile : public InfoOperativeFile {
    QString imageSourceId;
    QString algType;
    XPACK(I(InfoOperativeFile), O(imageSourceId, algType));
};

struct InfoDigitalBodyFile : public InfoOperativeFile {
    QList<QString> cTIds;
    TypeBodyPart part;
    XPACK(I(InfoOperativeFile), O(cTIds, part));
};

struct InfoImageSourceFile : public InfoOperativeFile {
    TypeSourceImage sourceImageType;
    uint64_t scanTime;
    QString doctor;
    XPACK(I(InfoOperativeFile), O(sourceImageType, scanTime, doctor));
};

struct InfoPostReferenceFile : public InfoOperativeFile {
    QString imageSourceId;
    XPACK(I(InfoOperativeFile), O(imageSourceId));
};



