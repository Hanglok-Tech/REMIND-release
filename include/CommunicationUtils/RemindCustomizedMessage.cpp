#include "RemindCustomizedMessage.h"

RemindCustomizedMessage::RemindCustomizedMessage(uint64_t messageId,
                                               uint32_t targetId,
                                               uint32_t originId,
                                               uint64_t  timestampes)
    : RemindMessage(messageId, targetId, originId, timestampes, 0)
{

}

RemindCustomizedMessage::~RemindCustomizedMessage()
{
}

const CByteArray& RemindCustomizedMessage::body() const {
    return message_body;
}

void RemindCustomizedMessage::print(){
    qDebug()<<"RemindCustomizedMessage:"<<this->message_body.at(0)<<this->message_body.at(1)<<this->message_body.at(2)<<this->message_body.at(3)<<this->message_body.at(4)<<this->message_body.at(5)<<this->message_body.at(6)<<this->message_body.at(7)<<this->message_body.at(8)<<this->message_body.at(9);
}

void RemindCustomizedMessage::appendUInt8(uint8_t v){
    //qDebug()<<this->index<<v;
    this->message_body.append(v);
    setDLC(message_body.size());
}

void RemindCustomizedMessage::appendUInt16(uint16_t v){
    this->message_body.append(uint8_t((0xff00&v)>>8));
    this->message_body.append(uint8_t(0x00ff&v));
    setDLC(message_body.size());
}

void RemindCustomizedMessage::appendUInt32(uint32_t v){
    this->message_body.append(uint8_t((0xff000000&v)>>24));
    this->message_body.append(uint8_t((0x00ff0000&v)>>16));
    this->message_body.append(uint8_t((0x0000ff00&v)>>8));
    this->message_body.append(uint8_t( 0x000000ff&v));
    setDLC(message_body.size());
}

void RemindCustomizedMessage::appendUInt64(uint64_t v){
    this->message_body.append(uint8_t((0xff00000000000000&v)>>56));
    this->message_body.append(uint8_t((0x00ff000000000000&v)>>48));
    this->message_body.append(uint8_t((0x0000ff0000000000&v)>>40));
    this->message_body.append(uint8_t((0x000000ff00000000&v)>>32));
    this->message_body.append(uint8_t((0x00000000ff000000&v)>>24));
    this->message_body.append(uint8_t((0x0000000000ff0000&v)>>16));
    this->message_body.append(uint8_t((0x000000000000ff00&v)>>8));
    this->message_body.append(uint8_t( 0x00000000000000ff&v));
    setDLC(message_body.size());
}

//void RemindCustomizedMessage::append(const QByteArray &data)
//{
//    message_body.append(data.data());
//    setDLC(message_body.size());
//}

void RemindCustomizedMessage::append(const uint8_t *data, int len) {
    message_body.append(data, len);
    setDLC(message_body.size());
}

void RemindCustomizedMessage::append(const char *data, int len) {
    message_body.append(data, len);
    setDLC(message_body.size());
}
