#pragma once
#include "CByteArray.h"
#include "RemindMessage.h"


class REMINDEXPORTDLL RemindCustomizedMessage : public RemindMessage
{
public:
    RemindCustomizedMessage(uint64_t messageId, uint32_t targetId, uint32_t originId, uint64_t timestampes = 0);
    ~RemindCustomizedMessage();

public:
    void appendUInt8(uint8_t v);
    void appendUInt16(uint16_t v);
    void appendUInt32(uint32_t v);
    void appendUInt64(uint64_t v);
    //void append(const QByteArray& data);
    void append(const uint8_t* data, int len);
    void append(const char* data, int len);

    const CByteArray& body() const;
    void print();

private:
    CByteArray message_body;
};

