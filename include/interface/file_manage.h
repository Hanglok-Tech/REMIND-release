#pragma once
#include <QObject>
#include "define/info.h"
#include "RemindGlobal.h"
#include "info_file_manage.h"

class FileUpload;
class FileDown;
class REMINDEXPORTDLL FileManage : public QObject {
    Q_OBJECT
public:
    explicit FileManage(const std::shared_ptr<InfoDeviceNodes> &info);

    ~FileManage();

    void SetPatientSession(const QString &patient_id, const QString &session_id);

    //upload file
    bool SynUpload(const QString &file_path, QString &file_id, QString &err_msg);//同步

    bool AsynUpload(const QString &file_path, QString &file_id, const std::function<void(InfoUploadStatus &)> &status_callback);//异步

    //down file
    bool SynDown(const QString &file_id, const QString &save_path, const QString &save_name, QString &err_msg);//同步

    bool AsynDown(const QString &file_id, const QString &save_path, const QString &save_name, const std::function<void(InfoDownStatus &)> &status_callback);//异步

    //delete file
    bool FileDelete(const QString &file_id, QString &err_msg);

private:
    std::string m_patient_id;
    std::string m_session_id;
    std::shared_ptr<InfoDeviceNodes> m_info = nullptr;
    std::shared_ptr<FileUpload> m_uploader = nullptr;
    std::shared_ptr<FileDown> m_down = nullptr;
};
