#pragma once
#include <QObject>

struct InfoDown {
    QString save_path = "";
    QString save_file_name;
    QString file_id;
    QString service_ip;
    int service_port;
    QString content;
};
Q_DECLARE_METATYPE(InfoDown);

struct InfoDownStatus {
    QString m_file_id;
    bool m_finish = false;
    bool m_result = false;
    QString m_error = "";
    double m_down_percent = 0;
    void SetStatus(bool finish, bool result, const QString &error, double down_percent) {
        m_finish = finish;
        m_result = result;
        m_error = error;
        m_down_percent = down_percent;
    }
};
Q_DECLARE_METATYPE(InfoDownStatus);

struct InfoUpload {
    QString file_path = "";
    QString file_name;
    QString file_type;
    QString equipment_id;
    QString patient_id;
    QString session_id;
    QString service_ip;
    int service_port;
    QString content;
};
Q_DECLARE_METATYPE(InfoUpload);

struct InfoUploadStatus {
    QString m_file_name;
    QString m_file_id;
    bool m_finish = false;
    bool m_result = false;
    QString m_error = "";
    double m_upload_percent = 0;

    void SetStatus(bool finish, bool result, const QString &error, double upload_percent) {
        m_finish = finish;
        m_result = result;
        m_error = error;
        if(upload_percent != 0) {
            m_upload_percent = upload_percent;
        }
    }
};
Q_DECLARE_METATYPE(InfoUploadStatus);

