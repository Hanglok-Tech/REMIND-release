#pragma once
#include <QDebug>
#include <math.h>
#include "RemindGlobal.h"

class REMIND_EXPORT RemindMessage {
public:

    void init();
    void printHeader();

    void setMessageId(uint64_t  messageId);
    void setTargetId(uint32_t targetId);
    void setTimestamp(uint64_t  timestamp);
    void setDLC(uint32_t dlc);

    void setOriginId(uint32_t originId);
    uint32_t getOriginId() const;

    uint64_t  getMessageId() const;
    uint32_t getTargetId() const;
    uint64_t  getTimestamp() const;
    uint32_t getDLC() const;
    uint32_t getMessageType() const;

    uint32_t getCustomerizedMessageId() const;
    uint8_t getDeviceClass() const;

    uint32_t getManufacture() const;
    uint8_t getDeviceType() const;
    uint8_t getDeviceVision() const;
    uint8_t getDeviceIndex() const;

private:
    uint64_t messageId;         //! 64 bits
    uint32_t targetId;          //! 32 bits
    uint32_t originId;          //! 32 bits
    uint64_t timestamp;         //! 64 bits
    uint32_t DLC;               //! 32 bits

public:
    RemindMessage(uint64_t messageId, uint32_t targetId, uint32_t originId, uint64_t timestamp, uint32_t DLC);
    ~RemindMessage();
};

