#pragma once
#include <QMainWindow>
#include <QPushButton>
#include <QTextBrowser>
#include <QComboBox>
#include <QCheckBox>
#include <QTimer>
#include <QLineEdit>
#include <QLabel>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include "interface/RemindCommunicationStack.h"
#include "CommunicationUtils/BlockingQueue.hpp"
#include "CommunicationUtils/RemindCustomizedMessage.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void Init();
private:
    void uploadQueue();
    void recvQueue();
    bool loadTopology(const QString &path_top, const QString &path_nodes);
    void initNodeStatus();
    void setNodeOnline(uint64_t bid);
    void setNodeOffline(uint64_t bid);
    void showMessage(int level, string msg);
private slots:
    void slotAction();
    void slotShowMessage(const QString &msg);
    void slotTimeoutUpload();
    void slotTimeoutRecv();
    void slotRefreshStatus();
    void slotOriginBidChange(const QString &bid);
    void slotCheckUpload(bool c);
private:
    QPushButton *m_btnStart = nullptr;
    QPushButton *m_btnStop = nullptr;
    RemindCommunicationStack *m_lune = nullptr;
    QTextBrowser *m_browser = nullptr;
    QTimer *m_timer_upload = nullptr;
    QTimer *m_timer_recv = nullptr;
    QTimer *m_timer_status = nullptr;
    QMap<uint64_t, RemindMessageQueue *> m_bid2outputQueue;
    QMap<uint64_t, RemindMessageQueue *> m_bid2InputQueue;
    QMap<uint64_t, shared_ptr<InfoDeviceTopology>> m_bid2top;
    QComboBox *m_cbBid_origin = nullptr;
    QComboBox *m_cbBid_target = nullptr;
    QCheckBox *m_chUpload = nullptr;
    QCheckBox *m_chRecv = nullptr;
    QByteArray m_test_data;
    QLineEdit *m_leInterval = nullptr;
    QMap<uint64_t, QLabel *> m_bid2status;
    QVBoxLayout *m_vlay_main = nullptr;
    QList<RemindCustomizedMessage> m_msgList;
    QMap<QCheckBox*, bool> m_checkbox2enable;
    QVBoxLayout *m_vlay_checktargets = nullptr;
    int m_upload_count = 1;
};
