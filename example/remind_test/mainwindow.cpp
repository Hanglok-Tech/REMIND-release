#include <QLabel>
#include <QDateTime>
#include <QCoreApplication>
#include <QFile>
#include <QPicture>
#include "mainwindow.h"
#include "define/info.h"
#include "interface/RemindConfig.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{

}

MainWindow::~MainWindow()
{
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
    connect(m_lune, &RemindCommunicationStack::sigMessage, this, &MainWindow::slotShowMessage);
    m_lune->RegisterMsgFunc(std::bind(&MainWindow::showMessage, this, std::placeholders::_1, std::placeholders::_2));
    QString path_device = QCoreApplication::applicationDirPath() + "/config/device_config.xml";
    QString path_top = QCoreApplication::applicationDirPath() + "/config/topology_config.xml";
    if (QFile::exists(path_device) && QFile::exists(path_top)) {
        m_lune->LoadConfig(path_device, path_top);
    }

    m_timer_upload = new QTimer();
    m_timer_recv = new QTimer();
    m_timer_status = new QTimer();
    connect(m_timer_upload, &QTimer::timeout, this, &MainWindow::slotTimeoutUpload);
    connect(m_timer_recv, &QTimer::timeout, this, &MainWindow::slotTimeoutRecv);
    connect(m_timer_status, &QTimer::timeout, this, &MainWindow::slotRefreshStatus);
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
}

void MainWindow::initNodeStatus() {
    auto hlay = new QHBoxLayout();
    for (auto &top : m_bid2top) {
        auto status = new QLabel();
        m_bid2status[top->bid] = status;
        hlay->addWidget(new QLabel(top->name + ":\n" + QString::number(top->bid)));
        hlay->addWidget(status);
        hlay->addStretch(10);
        setNodeOffline(top->bid);
    }
    m_vlay_main->addLayout(hlay);
}

void MainWindow::setNodeOnline(uint64_t bid) {
    if (m_bid2status.contains(bid)) {
        QPixmap p(":/icon/online.png");
        m_bid2status[bid]->setPixmap(p);
    }
}

void MainWindow::setNodeOffline(uint64_t bid) {
    if (m_bid2status.contains(bid)) {
        QPixmap p(":/icon/outline.png");
        m_bid2status[bid]->setPixmap(p);
    }
}

void MainWindow::slotRefreshStatus() {
    for (auto &top : m_bid2top) {
        QString s;
        if (m_bid2status.contains(top->bid)) {
            if (m_lune->GetDeviceStatus(top->bid, s)) {
                qDebug() << "status:" << s;
                if (s == "a") {
                    setNodeOnline(top->bid);
                } else {
                    setNodeOffline(top->bid);
                }
            } else {
                setNodeOffline(top->bid);
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
    auto config = make_shared<RemindConfig>();
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
        if (id2device.contains(top->bid)) {
            top->name = id2device[top->bid]->name;
        }
    }
    m_cbBid_origin->clear();
    m_checkbox2enable.clear();
    for (auto &top : m_bid2top) {
        m_cbBid_origin->addItem(QString::number(top->bid));
        auto box = new QCheckBox(QString::number(top->bid));
        m_checkbox2enable[box] = false;
        m_vlay_checktargets->addWidget(box);
    }
    if (!m_bid2top.isEmpty()) {
        slotOriginBidChange(QString::number(m_bid2top.first()->bid));
    }
    return true;
}

void MainWindow::slotOriginBidChange(const QString &bid) {
    uint64_t id = bid.toULongLong();
    if (m_bid2top.contains(id)) {
        auto connects = m_bid2top[id]->connects;
        if (connects.isEmpty()) {
            return;
        }
        for (auto it = m_checkbox2enable.begin(); it != m_checkbox2enable.end(); it++) {
            auto check = it.key();
            auto id = check->text().toULongLong();
            if (connects.contains(id)) {
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
    QString patient_id = "d6c97b69-3c4c-42ae-8e6a-8eb2076022b0";
    QString session_id = "d77c08e3-f059-49cb-b3e4-54ccb98d7f4d";
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
            m_lune->SetPatientSession(patient_id, session_id);
            if (!m_lune->Launch(origin_id)) {
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
}

void MainWindow::slotTimeoutUpload() {
    if (m_chUpload->isChecked()) {
        uploadQueue();
    }
}

void MainWindow::slotTimeoutRecv() {
    if (m_chRecv->isChecked()) {
        recvQueue();
    }
}

void MainWindow::uploadQueue() {
    if (m_bid2outputQueue.isEmpty()) {
        if (m_checkbox2enable.isEmpty()) {
            return;
        }
        for (auto it = m_checkbox2enable.begin(); it != m_checkbox2enable.end(); it++) {
            auto bid = it.key()->text().toULongLong();
            auto check = it.key();
            if (it.value() == false || check->isChecked() == false) {
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
        uint64_t target_id = it.key();
        if (origin_id == target_id) {
            continue;
        }
        auto queue = it.value();
        QByteArray bd;
        if (!m_test_data.isEmpty()) {
            bd = m_test_data;
        } else {
            bd = "fdsfdsfsd1223555" + QDateTime::currentDateTime().toString("yyyyMMdd:HH:mm:ss zzz").toUtf8();
        }
        int len = 1024 * 2048;
        int64_t timeshpe = QDateTime::currentMSecsSinceEpoch();
        int64_t message_id = timeshpe + origin_id;
        //slotShowMessage(QString("origin timeshpe:%1").arg(timeshpe));
        auto msg = new RemindCustomizedMessage(message_id, target_id, origin_id, timeshpe);
        msg->append(bd);
        queue->push(msg);
        //m_msgList.push_back(msg);
        QString text = QString("origin id:%1 --->%2, message_id:%3, lenght:%4").arg(origin_id).arg(target_id).arg(msg->getMessageId()).arg(msg->body().length());
        //slotShowMessage(text);
    }
}

void MainWindow::recvQueue() {
    if (m_bid2InputQueue.isEmpty()) {
        auto bid = m_cbBid_origin->currentText().toULongLong();
        if (!m_bid2top.contains(bid)) {
            slotShowMessage("recvQueue origin bid:" + QString::number(bid) + "is not exist!");
            return;
        }
        auto connects = m_bid2top[bid]->connects;
        if (connects.isEmpty()) {
            slotShowMessage("recvQueue connect bid is empty!");
            return;
        }
        for (auto &i : connects) {
            m_bid2InputQueue[i] = m_lune->GetInputQueue(i);
        }
    }
    for (auto it = m_bid2InputQueue.begin(); it != m_bid2InputQueue.end(); it++) {
        auto input_queue = it.value();
        if (input_queue->getLen() == 0) {
            continue;
        }
        auto msg = input_queue->popFront();
        int64_t current_timeshpe = QDateTime::currentMSecsSinceEpoch();
        int64_t cost_time = current_timeshpe - msg->getTimestamp();
        //slotShowMessage(QString("input_queue len:%1").arg(input_queue->getLen()));
        slotShowMessage(QString("data origin id:%1 recv<--- data lenght:%2  message id:%3 cost time for producer:%4 ms").arg(msg->getOriginId()).arg(msg->body().length()).arg(msg->getTargetId()).arg(cost_time));
        delete msg;
    }
}

void MainWindow::slotShowMessage(const QString &msg) {
    if (m_browser == nullptr) {
        return;
    }
    auto text = QString("[%2] %3").arg(QDateTime::currentDateTime().toString("HH:mm:ss zzz")).arg(msg);
    m_browser->append(text);
    m_browser->setFont(QFont("宋体", 12));
    //Logger::Inst()->WriteLog(QtDebugMsg, msg);
}

void MainWindow::showMessage(int level, string msg) {

}
