#pragma once

#include "RemindMessage.h"


class REMIND_EXPORT RemindCustomizedMessage : public RemindMessage
{

public:
    void appendUInt8(uint8_t v);
    void appendUInt16(uint16_t v);
    void appendUInt32(uint32_t v);
    void appendUInt64(uint64_t v);
    void append(const QByteArray& data);
    void append(const uint8_t* data, int len);

//    void append_bool(bool v);
//    void append_float(float v);
//    void append_double(double v);

    const QByteArray& body() const;
    void print();

private:
    QByteArray message_body;

public:
    RemindCustomizedMessage(uint64_t messageId, uint32_t targetId, uint32_t originId, uint64_t timestampes = 0);
    ~RemindCustomizedMessage();
};

