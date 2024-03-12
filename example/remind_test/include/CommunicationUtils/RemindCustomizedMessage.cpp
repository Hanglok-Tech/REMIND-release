#include "RemindCustomizedMessage.h"


/**
 * @brief RemindCustomizedMessage::RemindCustomizedMessage
 * @param messageId
 * @param targetId
 * @param originId
 * @param timestampes
 * @param DLC
 */
RemindCustomizedMessage::RemindCustomizedMessage(uint64_t messageId,
                                               uint32_t targetId,
                                               uint32_t originId,
                                               uint64_t  timestampes)
    : RemindMessage(messageId, targetId, originId, timestampes, 0)
{

}

//! -------------------------------------------------------------------------------------------------------------------------
//!
//! \brief RemindCustomizedMessage::~RemindCustomizedMessage
//!
RemindCustomizedMessage::~RemindCustomizedMessage()
{
}

//! -------------------------------------------------------------------------------------------------------------------------
//!
//! \brief RemindCustomizedMessage::get_message_body
//! \return
//!
const QByteArray& RemindCustomizedMessage::body() const {
    return message_body;
}

//! -------------------------------------------------------------------------------------------------------------------------
//!
//! \brief RemindCustomizedMessage::print
//!
void RemindCustomizedMessage::print(){
    qDebug()<<"RemindCustomizedMessage:"<<this->message_body[0]<<this->message_body[1]<<this->message_body[2]<<this->message_body[3]<<this->message_body[4]<<this->message_body[5]<<this->message_body[6]<<this->message_body[7]<<this->message_body[8]<<this->message_body[9];
}

//! -------------------------------------------------------------------------------------------------------------------------
//!
//! \brief RemindCustomizedMessage::append_uint8
//! \param uint8
//!
void RemindCustomizedMessage::appendUInt8(uint8_t v){
    //qDebug()<<this->index<<v;
    this->message_body.append(v);
    setDLC(message_body.size());
}

//! --------------------------------------------------------------------------------------------------------------------------
//!
//! \brief append_uint16
//! \param v
//!
void RemindCustomizedMessage::appendUInt16(uint16_t v){
    this->message_body.append(uint8_t((0xff00&v)>>8));
    this->message_body.append(uint8_t(0x00ff&v));
    setDLC(message_body.size());
}

//! --------------------------------------------------------------------------------------------------------------------------
//!
//! \brief RemindCustomizedMessage::append_uint32
//! \param v
//!
void RemindCustomizedMessage::appendUInt32(uint32_t v){
    this->message_body.append(uint8_t((0xff000000&v)>>24));
    this->message_body.append(uint8_t((0x00ff0000&v)>>16));
    this->message_body.append(uint8_t((0x0000ff00&v)>>8));
    this->message_body.append(uint8_t( 0x000000ff&v));
    setDLC(message_body.size());
}

//! --------------------------------------------------------------------------------------------------------------------------
//!
//! \brief RemindCustomizedMessage::append_uint64
//! \param v
//!
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

void RemindCustomizedMessage::append(const QByteArray &data)
{
    message_body.append(data);
    setDLC(message_body.size());
}

void RemindCustomizedMessage::append(const uint8_t *data, int len)
{
    message_body.append((const char*)data, len);
    setDLC(message_body.size());
}
