#include "RemindMessage.h"


/**
 * @brief RemindMessage::RemindMessage
 * @param messageId
 * @param targetId
 * @param timestampes
 * @param DLC
 */
RemindMessage::RemindMessage(uint64_t messageId, uint32_t targetId, uint32_t originId, uint64_t timestampes, uint32_t DLC)
{
    this->messageId = messageId;
    this->targetId = targetId;
    this->originId = originId;
    this->timestamp = timestampes;
    this->DLC = DLC;
}

//! ------------------------------------------------------------------------------------------------------------
//!
//! \brief RemindMessage::~RemindMessage
//!
RemindMessage::~RemindMessage(){

}

//! ----------------------------------------------------------------------
//!
//! \brief RemindMessage::getOrigineId
//! \return
//!
uint32_t RemindMessage::getOriginId() const {
    return this->originId;
}

//!
//! \brief RemindMessage::setOriginId
//! \param originId
//!
void RemindMessage::setOriginId(uint32_t originId){
    this->originId  = originId;
}

//! ---------------------------------------------------------------------
//!
//! \brief RemindMessage::printHeader
//!
void RemindMessage::printHeader(){
    qDebug()<<"header"<<this->messageId<<this->targetId<<this->timestamp<<this->DLC;
}

//! ---------------------------------------------------------------------
//!
//! \brief RemindMessage::init
//!
void RemindMessage::init(){
    this->messageId = 0;
    this->targetId = 0;
    this->timestamp = 0;
    this->DLC = 0;
}

//! ----------------------------------------------------------------------
//!
//! \brief RemindMessage::set_message_id
//! \param message_id
//!
void RemindMessage::setMessageId(uint64_t  message_id){
    this->messageId = message_id;
}

//! ----------------------------------------------------------------------
//!
//! \brief RemindMessage::getMessageType
//! \return
//!
//uint32_t RemindMessage::getMessageType(){
//    return uint32_t(this->messageId % (2**32));
//}

//! ----------------------------------------------------------------------
//!
//! \brief RemindMessage::set_target_id
//! \param target_id
//!
void RemindMessage::setTargetId(uint32_t target_id){
    this->targetId = target_id;
}

void RemindMessage::setDLC(uint32_t dlc)
{
    DLC = dlc;
}

//! ----------------------------------------------------------------------
//!
//! \brief RemindMessage::getCustomerizedMessageId
//! \return
//!
uint32_t RemindMessage:: getCustomerizedMessageId() const {
    return this->messageId % (uint64_t)pow(256, 4);
}

//! ----------------------------------------------------------------------
//!
//! \brief RemindMessage::getDeviceClass
//! \return 3bits from 29-31
//!
uint8_t RemindMessage:: getDeviceClass() const {
    return uint8_t(this->getOriginId()/(256*256*256*32));
}

//! ----------------------------------------------------------------------
//!
//! \brief RemindMessage::getManufacture
//! \return 14bits for 15-28
//!
uint32_t RemindMessage:: getManufacture() const {
    return uint32_t((this->getOriginId() % (256*256*256*32)) / (256*128));
}

//! ----------------------------------------------------------------------
//!
//! \brief RemindMessage::getDeviceType
//! \return 6bits from 9-14
//!
uint8_t RemindMessage:: getDeviceType() const {
    return uint8_t((this->getOriginId() % (256*128)) / (256*2));

}

//! ----------------------------------------------------------------------
//!
//! \brief RemindMessage::getDeviceVision
//! \return 6bits from 3-8
//!
uint8_t RemindMessage:: getDeviceVision() const {
    return uint8_t((this->getOriginId() % (256*2)) /8);

}

//! ----------------------------------------------------------------------
//!
//! \brief RemindMessage::getDeviceIndex
//! \return 3bits for 0-2
//!
uint8_t RemindMessage:: getDeviceIndex() const {
    return uint32_t(this->getOriginId()%8);

}

//! ----------------------------------------------------------------------
//!
//! \brief RemindMessage::get_message_id
//! \return
//!
uint64_t RemindMessage::getMessageId() const {
    return this->messageId;
}

//! ----------------------------------------------------------------------
//!
//! \brief RemindMessage::get_target_id
//! \return
//!
uint32_t RemindMessage::getTargetId() const {
    return this->targetId;
}

//! ----------------------------------------------------------------------
//!
//! \brief RemindMessage::getTimestampes
//! \return
//!
uint64_t RemindMessage::getTimestamp() const {
    return this->timestamp;
}

//! ----------------------------------------------------------------------
//!
//! \brief RemindMessage::getDLC
//! \return
//!
uint32_t RemindMessage::getDLC() const {
    return this->DLC;
}
