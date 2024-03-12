#pragma once
#include <QObject>
#include <QMap>
#include <memory>
#include "type_operative.h"
using namespace std;

#if defined(REMINDDATADLL_LIBRARY)
#  define REMINDEXPORTDLL Q_DECL_EXPORT
#else
#  define REMINDEXPORTDLL Q_DECL_IMPORT
#endif

class DataBase;
class FileManage;
class ModelPatient;
class ModelSession;
class WidgetConfig;
class ModelOperativeFile;
class ModelOperativeLesion;
class ModelOperativeCenterLine;
struct InfoDeviceNodes;
struct InfoDeviceTopology;
struct InfoPatient;
struct InfoSession;
struct InfoPreoperative;
struct InfoPostOperative;
struct InfoOperativeFile;
struct InfoOperativeLesion;
struct InfoCenterLine;
//enum TypeOperativeFile : int;
//enum TypeOperativeLesion : int;
class REMINDEXPORTDLL RemindData : public QObject {
    Q_OBJECT
public:
    RemindData() {}
    ~RemindData() {}
    //common
    bool LoadConfig(const QString &device_path, const QString &topology_path);
    void SetPatientSession(const QString &patient_id, const QString &session_id);
    //patient info
    bool GetPatientList(QList<shared_ptr<InfoPatient>> &list_patients, QString &err_msg);
    bool GetPatientById(const QString &id, shared_ptr<InfoPatient> &info_patient, QString &err_msg);
    bool GetPatientByCardId(const QString &card_id, shared_ptr<InfoPatient> &info_patient, QString &err_msg);
    bool CreatePatientInfo(const shared_ptr<InfoPatient> &info_patient, QString &err_msg);
    bool UpdatePatientInfo(const QString &id, const shared_ptr<InfoPatient> &info_patient, QString &err_msg);
    bool DeletePatientInfo(const QString &id, QString &err_msg);
    //session info
    bool GetSessionList(const QString &patient_id, QList<shared_ptr<InfoSession>> &list_sessions, QString &err_msg);
    bool GetSessionById(const QString &patient_id, const QString &id, shared_ptr<InfoSession> &info_sessions, QString &err_msg);
    bool CreateSessionInfo(const QString &patient_id, const shared_ptr<InfoSession> &info_session, QString &err_msg);
    bool UpdateSessionInfo(const QString &patient_id, const QString &id, const shared_ptr<InfoSession> &info_session, QString &err_msg);
    bool DeleteSessionInfo(const QString &patient_id, const QString &id, QString &err_msg);
    //operative file
    bool GetOperativeFileInfo(const TypeOperativeFile &file_type, QList<shared_ptr<InfoOperativeFile>> &out_files, QString &err_msg);
    bool GetOperativeFileInfoById(const TypeOperativeFile &file_type, const QString &input_fileId, shared_ptr<InfoOperativeFile> &out_file, QString &err_msg);
    bool GetOperativeFileInfoByFileName(const TypeOperativeFile &file_type, const QString &input_fileName, shared_ptr<InfoOperativeFile> &out_file, QString &err_msg);
    bool DownOperativeFileById(const TypeOperativeFile &file_type, const QString &file_id, const QString &save_path, const QString &file_name, const QString &file_suffix, QString &err_msg);
    bool CreateOperativeFileInfo(const TypeOperativeFile &file_type, const shared_ptr<InfoOperativeFile> &input_file, QString &err_msg);
    bool UpdateOperativeFileInfo(const TypeOperativeFile &file_type, const shared_ptr<InfoOperativeFile> &update_file, QString &err_msg);
    bool DeleteOperativeFileInfo(const TypeOperativeFile &file_type, const QString &input_fileId, QString &err_msg);
    //operative lesion
    bool GetLesionInfo(const TypeOperativeLesion &path_type, QList<shared_ptr<InfoOperativeLesion>> &out_lesions, QString &err_msg);
    bool GetLesionInfoById(const TypeOperativeLesion &lesion_type, const QString &input_lesionId, shared_ptr<InfoOperativeLesion> &out_lesion, QString &err_msg);
    bool CreateLesionInfo(const TypeOperativeLesion &lesion_type, const shared_ptr<InfoOperativeLesion> &input_lesion, QString &out_lesionId, QString &err_msg);
    bool UpdateLesionInfo(const TypeOperativeLesion &lesion_type, const shared_ptr<InfoOperativeLesion> &update_Lesion, QString &err_msg);
    bool DeleteLesionInfo(const TypeOperativeLesion &lesion_type, const QString &input_pathId, QString &err_msg);
    //operative centerline
    bool GetCenterLineInfo(QList<shared_ptr<InfoCenterLine>> &out_lines, QString &err_msg);
    bool GetCenterLineInfoById(const QString &input_lineId, shared_ptr<InfoCenterLine> &out_line, QString &err_msg);
    bool CreateCenterLineInfo(const shared_ptr<InfoCenterLine> &input_line, QString &out_lineId, QString &err_msg);
    bool UpdateCenterLineInfo(const shared_ptr<InfoCenterLine> &update_line, QString &err_msg);
    bool DeleteCenterLineInfo(const QString &input_lineId, QString &err_msg);

signals:
    void sigMessage(const QString &msg);

private:
    bool initConfig();
    bool initPatient();
    bool initSession();
    bool initOperativeFile();
    bool initOperativeLesion();
    bool initOperativeCenterline();
private:
    bool m_isLoadConfig = false;
    QString m_patientId;
    QString m_sessionId;
    shared_ptr<InfoDeviceNodes> m_info = nullptr;
    shared_ptr<DataBase> m_database = nullptr;
    shared_ptr<FileManage> m_fileManage = nullptr;
    QMap<uint64_t, shared_ptr<InfoDeviceTopology>> m_id2topology;
    shared_ptr<ModelPatient> m_patient = nullptr;
    shared_ptr<ModelSession> m_session = nullptr;
    shared_ptr<ModelOperativeFile> m_operative_file = nullptr;
    shared_ptr<ModelOperativeLesion> m_operative_lesion = nullptr;
    shared_ptr<ModelOperativeCenterLine> m_centerline = nullptr;
};

