#pragma once
#include <QObject>
#include <QMap>
#include <memory>
#include "define/info.h"
using namespace std;

#if defined(RemindConfigDLL_LIBRARY)
#  define REMINDCONFIGEXPORTDLL Q_DECL_EXPORT
#else
#  define REMINDCONFIGEXPORTDLL Q_DECL_IMPORT
#endif

class WidgetConfig;
class REMINDCONFIGEXPORTDLL RemindConfig : public QObject {
    Q_OBJECT
public:
    void ConfigEditShow();
    shared_ptr<InfoDeviceNodes> ReadDeviceConfig(const QString &path);
    bool SaveDeviceConfig(const shared_ptr<InfoDeviceNodes> &info, const QString &path);
    bool ReadTopologyConfig(const QString &path, QMap<uint64_t, shared_ptr<InfoDeviceTopology>> &id2info);
    bool SaveTopologyConfig(const QMap<uint64_t, shared_ptr<InfoDeviceTopology>> &id2info, const QString &path);
private:
    WidgetConfig *m_widget = nullptr;
};
