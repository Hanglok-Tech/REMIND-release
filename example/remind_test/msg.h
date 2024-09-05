#pragma once
#include <QObject>

class MsgGlobal : public QObject {
    Q_OBJECT
public:
    static MsgGlobal *Inst() {
        static MsgGlobal m;
        return &m;
    }

signals:
    void sigShowMessage(const QString &msg);

};
