#include <QLabel>
#include <QDateTime>
#include <QCoreApplication>
#include <QFile>
#include <QPicture>
#include "mainwindow.h"
#include "Logger.h"
#include "define/info.h"
#include "interface/RemindConfig.h"
#include <QDir>
#include <QFile>
#include <DiagnosisInfo.h>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
}

MainWindow::~MainWindow() {
}

void MainWindow::Init() {
    m_vlay_main = new QVBoxLayout();
    auto hlay_contrl = new QHBoxLayout();
    m_cbBid_origin = new QComboBox();
    //m_cbBid_target = new QComboBox();
    m_vlay_checktargets = new QVBoxLayout();
    m_leInterval = new QLineEdit();
    m_chRecv = new QCheckBox("recv test");
    m_chUpload = new QCheckBox("upload test");
    m_btnStart = new QPushButton("start");
    m_leInterval->setText("1000");
    connect(m_cbBid_origin, &QComboBox::currentTextChanged, this, &MainWindow::slotOriginBidChange);
    connect(m_btnStart, &QPushButton::clicked, this, &MainWindow::slotAction);
    connect(m_chUpload, &QCheckBox::clicked, this, &MainWindow::slotCheckUpload);
    m_btnStart->setMaximumWidth(1000);
    m_chUpload->setChecked(true);
    m_chRecv->setChecked(true);
    hlay_contrl->addWidget(new QLabel("origin id:"));
    hlay_contrl->addWidget(m_cbBid_origin);
    hlay_contrl->addWidget(new QLabel("target id:"));
    hlay_contrl->addLayout(m_vlay_checktargets);
    hlay_contrl->addStretch();
    hlay_contrl->addWidget(new QLabel("upload interval(ms):"));
    hlay_contrl->addWidget(m_leInterval);
    hlay_contrl->addWidget(m_chUpload);
    hlay_contrl->addWidget(m_chRecv);
    hlay_contrl->addWidget(m_btnStart);
    m_vlay_main->addLayout(hlay_contrl);

    auto w = new QWidget();
    w->setLayout(m_vlay_main);
    this->setCentralWidget(w);
    this->resize(1000, 800);
    m_lune = new RemindCommunicationStack();
    //connect(m_lune, &RemindCommunicationStack::sigMessage, this, &MainWindow::slotShowMessage);
    m_lune->RegisterMessageFunc(std::bind(&MainWindow::callbackMessage, this, std::placeholders::_1));
    QString path_device = QCoreApplication::applicationDirPath() + "/config/device_config.xml";
    QString path_top = QCoreApplication::applicationDirPath() + "/config/topology_config.xml";
    if (QFile::exists(path_device) && QFile::exists(path_top)) {
        m_lune->LoadConfig(path_device.toStdString(), path_top.toStdString());
    }

    m_timer_upload = new QTimer();
    m_timer_recv = new QTimer();
    m_timer_status = new QTimer();
    connect(m_timer_upload, &QTimer::timeout, this, &MainWindow::slotTimeoutUpload);
    connect(m_timer_recv, &QTimer::timeout, this, &MainWindow::slotTimeoutRecv);
    connect(m_timer_status, &QTimer::timeout, this, &MainWindow::slotRefreshStatus);
    connect(this, &MainWindow::sigMessage, this, &MainWindow::slotShowMessage);
    m_timer_status->setInterval(1000);
    m_timer_recv->setInterval(10);
    loadTopology(path_top, path_device);
    initNodeStatus();
    m_browser = new QTextBrowser();
    m_browser->setLineWrapMode(QTextBrowser::NoWrap);
    m_browser->document()->setMaximumBlockCount(1000);
    m_vlay_main->addWidget(m_browser);

    QByteArray ary;
    ary.append("123");
    QString str = ary;

    int code = ary.mid(0, 1).toUInt();
    slotShowMessage(QString("code:%1").arg(code));
    //qDebug() << "code:" << code;
    Logger::setLogPath(QDir::toNativeSeparators(QCoreApplication::applicationDirPath() + "/log/"), "remind_test");
    qInstallMessageHandler(Logger::outputMessage);
}

void MainWindow::initNodeStatus() {
    auto hlay = new QHBoxLayout();
    for (auto &top : m_bid2top) {
        auto status = new QLabel();
        m_bid2status[top.second->bid] = status;
        hlay->addWidget(new QLabel(QString("%1:\n%2").arg(top.second->name.c_str()).arg(top.second->bid)));
        hlay->addWidget(status);
        hlay->addStretch(10);
        setNodeOffline(top.second->bid);
    }
    m_vlay_main->addLayout(hlay);
}

void MainWindow::setNodeOnline(uint64_t bid) {
    if (m_bid2status.count(bid)) {
        QPixmap p(":/icon/online.png");
        m_bid2status[bid]->setPixmap(p);
    }
}

void MainWindow::setNodeOffline(uint64_t bid) {
    if (m_bid2status.count(bid)) {
        QPixmap p(":/icon/outline.png");
        m_bid2status[bid]->setPixmap(p);
    }
}

void MainWindow::slotRefreshStatus() {
    for (auto &top : m_bid2top) {
        std::string s;
        auto id = top.second->bid;
        if (m_bid2status.count(id)) {
            auto ret = m_lune->GetDeviceStatus(id, s);
            //slotShowMessage(QString("get status, id:%1, status:%2, ret:%3").arg(id).arg(s.c_str()).arg(ret));
            if (ret) {
                if (s == "a") {
                    setNodeOnline(id);
                } else {
                    setNodeOffline(id);
                }
            } else {
                setNodeOffline(id);
            }
        }

    }
}

void MainWindow::slotCheckUpload(bool c) {
    if (m_chUpload->isChecked()) {
        m_cbBid_origin->setEnabled(true);
        m_vlay_checktargets->setEnabled(true);
    } else {
        m_cbBid_origin->setEnabled(false);
        m_vlay_checktargets->setEnabled(false);
    }
}

bool MainWindow::loadTopology(const QString &path_top, const QString &path_nodes) {
    auto config = std::make_shared<RemindConfig>();
    if (!config->ReadTopologyConfig(path_top, m_bid2top)) {
        slotShowMessage("load topology config fail!");
        return false;
    }
    auto info = config->ReadDeviceConfig(path_nodes);
    if (info == nullptr) {
        slotShowMessage("load device node config fail!");
        return false;
    }
    auto id2device = info->id2infoDevices;
    for (auto &top : m_bid2top) {
        if (id2device.count(top.second->bid)) {
            top.second->name = id2device[top.second->bid]->name;
        }
    }
    m_cbBid_origin->clear();
    m_checkbox2enable.clear();
    for (auto &top : m_bid2top) {
        m_cbBid_origin->addItem(QString::number(top.second->bid));
        auto box = new QCheckBox(QString::number(top.second->bid));
        m_checkbox2enable[box] = false;
        m_vlay_checktargets->addWidget(box);
    }
    if (!m_bid2top.empty()) {
        slotOriginBidChange(QString::number(m_bid2top.begin()->second->bid));
    }
    return true;
}

void MainWindow::slotOriginBidChange(const QString &bid) {
    uint64_t id = bid.toULongLong();
    if (m_bid2top.count(id)) {
        auto connects = m_bid2top[id]->connects;
        if (connects.empty()) {
            return;
        }
        for (auto it = m_checkbox2enable.begin(); it != m_checkbox2enable.end(); it++) {
            auto check = it->first;
            auto id = check->text().toULongLong();
            auto is_exist = false;
            for (auto &l : connects) {
                if (l == id) {
                    is_exist = true;
                    break;
                }
            }
            if (is_exist) {
                m_checkbox2enable[check] = true;
                check->show();
            } else {
                m_checkbox2enable[check] = false;
                check->hide();
            }
        }
    }
}

void MainWindow::slotAction() {
    m_start_timeshpe = QDateTime::currentSecsSinceEpoch();
    QString patient_id = "remind_comunication_test";
    QString session_id = QDateTime::currentDateTime().toString("MM-dd-HHmmss");
    QString test_path = "test/2m.log";
    QFile file(test_path);
    if (file.open(QIODevice::ReadOnly)) {
        m_test_data = file.readAll();
        file.close();
    }
    uint64_t origin_id = m_cbBid_origin->currentText().toULongLong();
    //QString target_id = m_cbBid_target->currentText();
    if (origin_id == 0) {
        slotShowMessage("origin id or target id is empty!");
        return;
    }
    int interval = m_leInterval->text().toUInt();
    if (interval > 0) {
        m_timer_upload->setInterval(interval);
    } else {
        m_timer_upload->setInterval(100);
    }
    if (m_lune != nullptr) {
        if (m_btnStart->text() == "start") {
            m_lune->SetPatientSession(patient_id.toStdString(), session_id.toStdString());
            if (!m_lune->Init(origin_id)) {
                slotShowMessage("init fail!");
                return;
            }
//            if (m_chRecv->isChecked()) {
//                m_define_inQueue = m_lune->DefineInputQueue("test_queue", "text_exchane", "test_rout_key");
//            }
//            if (m_chUpload->isChecked()) {
//                m_define_outQueue = m_lune->DefineOutputQueue("test_queue", "text_exchane", "test_rout_key");
//                m_segment_request_queue = m_lune->DefineOutputQueue("AlgorithmRequest", "hanglok.algorithm.ex", "AlgorithmRequest");
//            }
            m_lune->SetCurrentDeviceStatus(CommonNodeStatus::Active);
            if (!m_lune->Launch()) {
                slotShowMessage("start fail!");
                return;
            }
            m_timer_upload->start();
            m_timer_recv->start();
            m_timer_status->start();
            m_btnStart->setText("stop");
        } else if (m_btnStart->text() == "stop") {
            m_lune->Terminate();
            m_timer_upload->stop();
            m_timer_recv->stop();
            m_timer_status->stop();
            m_btnStart->setText("start");
            setNodeOffline(m_cbBid_origin->currentText().toULongLong());
        }
    }
    //recvQueueProcess();
}

void MainWindow::slotTimeoutUpload() {
    if (m_chUpload->isChecked()) {
        uploadQueue();
    }
}

void MainWindow::slotTimeoutRecv() {
    if (m_chRecv->isChecked()) {
        recvQueueProcess();
    }
}

void MainWindow::uploadQueue() {
    if (m_bid2outputQueue.empty()) {
        if (m_checkbox2enable.empty()) {
            return;
        }
        for (auto it = m_checkbox2enable.begin(); it != m_checkbox2enable.end(); it++) {
            auto bid = it->first->text().toULongLong();
            auto check = it->first;
            if (it->second == false || check->isChecked() == false) {
                continue;
            }
            if (bid == 0) {
                slotShowMessage("bid = 0");
                continue;
            }
            auto q = m_lune->GetOutputQueue(bid);
            if (q == nullptr) {
                slotShowMessage(QString("get id:%1 output queue fail!").arg(bid));
                continue;
            }
            m_bid2outputQueue[bid] = q;
        }
    }
    uint64_t origin_id = m_cbBid_origin->currentText().toULongLong();
    for (auto it = m_bid2outputQueue.begin(); it != m_bid2outputQueue.end(); it++) {
        uint64_t target_id = it->first;
        if (origin_id == target_id) {
            continue;
        }
        auto queue = it->second;
        QByteArray bd = "123456789123456789123456789123456789";//getSendData();
        uint64_t timeshpe = QDateTime::currentMSecsSinceEpoch();
        uint64_t message_id = timeshpe + origin_id;
        auto msg = new RemindCustomizedMessage(message_id, target_id, origin_id, timeshpe);
        msg->append(bd.data(), bd.length());
        queue->push(msg);
    }
    if (m_define_outQueue != nullptr) {
        QByteArray bd = getSendData();
        uint64_t timeshpe = QDateTime::currentMSecsSinceEpoch();
        uint64_t message_id = timeshpe + origin_id + 1;
        auto msg = new RemindCustomizedMessage(message_id, 1008, origin_id, timeshpe);
        msg->append(bd.data(), bd.length());
        m_define_outQueue->push(msg);
    }

    if (m_segment_request_queue != nullptr) {
        std::string msg = "12345678";
        int64_t timeshpe = QDateTime::currentMSecsSinceEpoch();
        int64_t message_id = timeshpe + origin_id;
        auto remind_msg = new RemindCustomizedMessage(message_id, 1008, origin_id, timeshpe);
        remind_msg->append(msg.data(), msg.length());
        m_segment_request_queue->push(remind_msg);
    }
}

QByteArray MainWindow::getSendData() {
    int64_t current_timeshpe = QDateTime::currentSecsSinceEpoch();
    int space_time = current_timeshpe - m_start_timeshpe;
    int x = space_time / 60;
    QByteArray data;
    int len = x * 1024 * 50;
    if (len == 0) {
        len = 1024;
    }
    if (len > m_test_data.length()) {
        data = m_test_data;
        m_start_timeshpe = current_timeshpe;
    } else {
        data = m_test_data.mid(0, len);
    }

    return data;
}

void MainWindow::recvQueue() {
    //while (true) {
        for (auto it = m_bid2InputQueue.begin(); it != m_bid2InputQueue.end(); it++) {
            auto input_queue = it->second;
            if (input_queue == nullptr || input_queue->getLen() == 0) {
                continue;
            }
            auto msg = input_queue->popFront();
            uint64_t current_timeshpe = QDateTime::currentMSecsSinceEpoch();
            uint64_t cost_time = current_timeshpe - msg->getTimestamp();
            //cost_times(msg->getOriginId(), msg->body().length(), cost_time);
            //QString text = QString("data origin id:%1 recv<--- data lenght:%2  message id:%3 cost time for producer:%4 ms").arg(msg->getOriginId()).arg(msg->body().length()).arg(msg->getTargetId()).arg(cost_time);
            //emit sigMessage(text);
            delete msg;
            //QByteArray body;

            //body.setRawData((char*)msg->body().toStdString().c_str(), msg->body().length());
            //QString text = QString("origin id:%1 <---, message_id:%2, lenght:%3").arg(msg.getOriginId()).arg(msg.getMessageId()).arg(msg.getLen());
            //slotShowMessage(text);
        }
        if (m_define_inQueue != nullptr && m_define_inQueue->getLen() > 0) {
            auto msg = m_define_inQueue->popFront();
            uint64_t current_timeshpe = QDateTime::currentMSecsSinceEpoch();
            uint64_t cost_time = current_timeshpe - msg->getTimestamp();
            delete msg;
        }
       // std::this_thread::sleep_for(std::chrono::milliseconds(10));
    //}
}

void MainWindow::recvQueueProcess() {
    if (m_bid2InputQueue.empty()) {
        auto bid = m_cbBid_origin->currentText().toULongLong();
        if (!m_bid2top.count(bid)) {
            slotShowMessage(("recvQueue origin bid:" + QString::number(bid) + "is not exist!"));
            return;
        }
        auto connects = m_bid2top[bid]->connects;
        if (connects.empty()) {
            slotShowMessage("recvQueue connect bid is empty!");
            return;
        }
        for (auto &i : connects) {
            m_bid2InputQueue[i] = m_lune->GetInputQueue(i);
        }
    }
    recvQueue();
//    std::thread th(std::bind(&MainWindow::recvQueue, this));
//    th.detach();

}

void MainWindow::cost_times(uint64_t id, int size, uint64_t cost_time) {
    if (m_recv_current_size != size) {
        for (auto it = m_id2costtimes.begin(); it != m_id2costtimes.end(); it++) {
            auto id = it->first;
            auto times = it->second;
            uint64_t time_count = 0;
            for (auto &t : times) {
                time_count += t;
            }
            uint64_t avg_time = time_count / times.size();
            qDebug() << "time_count:" << time_count;
            qDebug() << "time size:" << times.size();
            QString text = QString("id %1 , size:%2kb,  avg time:%3").arg(id).arg(int(m_recv_current_size / 1024)).arg(avg_time);
            slotShowMessage(text);
        }
        m_id2costtimes.clear();
    }
    if (m_id2costtimes.count(id)) {
        m_id2costtimes[id].push_back(cost_time);
    } else {
        std::vector<int64_t> ts;
        ts.push_back(cost_time);
        m_id2costtimes[id] = ts;
    }

    m_recv_current_size = size;
}

void MainWindow::callbackMessage(std::string msg) {
    emit sigMessage(msg.c_str());
}

void MainWindow::slotShowMessage(QString msg) {
    if (m_browser == nullptr) {
        return;
    }
    auto text = QString("[%2] %3").arg(QDateTime::currentDateTime().toString("HH:mm:ss zzz")).arg(msg);
    m_browser->append(text);
    m_browser->setFont(QFont("宋体", 12));
    qDebug() << msg;
}
