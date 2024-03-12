#pragma once


//!--------------------------------------------------------------------------------------------------------------------------
//!                                        constant variable
//!--------------------------------------------------------------------------------------------------------------------------
#define HEADER_SIZE 28
#define DEBUG       0

//!--------------------------------------------------------------------------------------------------------------------------
//!                                        remind distributed device ID
//!--------------------------------------------------------------------------------------------------------------------------

// hand
#define NORMAN_ENDOVASCULAR_ROBOTIC_VERSION_1               0
#define HANGLOK_SGNIO_ROBOTIC_ARM_VERSION_1                 1
#define HANGLOK_SGNIP_ROBOTIC_ARM_VERSION_1                 2

// eye
#define SIEMENS_CBCT_ARCADIS_ORBIC_VERSION_1                536870912
#define NDI_MAGNETIC_SENSOR_VERSION_1                       536870913
#define HANGLOK_SGNIO_OTTM_VERSION_1                        536870914
#define HANGLOK_SGNIO_UIAM_VERSION_1                        536870915

// bran
#define SIAT_COCKPIT_VERSION_1                              1073741824
#define HANGLOK_SGNIO_INCM_VERSION_1                        1073741825


//!--------------------------------------------------------------------------------------------------------------------------
//!                                        real time session management
//!--------------------------------------------------------------------------------------------------------------------------
#define remind_SESSION_MANAGEMENT_HANDSHAKE_MESSAGE                                                  0
#define remind_SESSION_MANAGEMENT_HANDSHAKECOMMIT_MESSAGE                                            1
#define remind_SESSION_MANAGEMENT_CHANNELOPENNED_MESSAGE                                             2
#define remind_SESSION_MANAGEMENT_DISENGAGEMENT_MESSAGE                                              3
#define remind_SESSION_MANAGEMENT_DISENGAGEMENTCOMMIT_MESSAGE                                        4
#define remind_SESSION_MANAGEMENT_CHANNELCLOSED_MESSAGE                                              5

#define remind_SESSION_MANAGEMENT_REHANDSHAKE_MESSAGE                                               1048576
#define remind_SESSION_MANAGEMENT_REHANDSHAKECOMMIT_MESSAGE                                         1048577
#define remind_SESSION_MANAGEMENT_REOPENED_MESSAGE                                                  1048578

#define remind_SESSION_MANAGEMENT_HEARTBEAT_MESSAGE                                                  2097152
#define remind_SESSION_MANAGMENT_NTP_SYNCHRONIZATION_MESSAGE                                         2097153

#define remind_SESSION_MANAGEMENT_CLOSE_SYSTEM_MESSAGE                                               3145728
#define remind_SESSION_MANAGEMENT_OPEN_SYSTEM_MESSAGE                                                3145729
#define remind_SESSION_MANAGEMENT_FREEZE_SYSTEM_MESSAGE                                              3145730
#define remind_SESSION_MANAGEMENT_WAKEUP_SYSTEM_MESSAGE                                              3145731


//!--------------------------------------------------------------------------------------------------------------------------
//!                                       remind error
//!--------------------------------------------------------------------------------------------------------------------------

#define remind_ERROR_SUCCESS                                                                       0
#define remind_ERROR_LOCAL_CONNECTION_LOST                                                         1
#define remind_ERROR_PEER_SERVER_NOT_LAUNCHED                                                      2
#define remind_ERROR_PEER_CONNECTION_LOST                                                          4


//!--------------------------------------------------------------------------------------------------------------------------
//!                                        robotic system message set
//!--------------------------------------------------------------------------------------------------------------------------

/* message set for device MEDSIGHT_INTERVENTIONAL_VASCULAR_ROBOT_VERSION_1 */
#define NORMAN_ENDOVASCULAR_ROBOTIC_CONTROL_INSTRUCTION                     16777215


/************************* sensors information feedback ***************************/
#define NORMAN_ENDOVASCULAR_ROBOTIC_FEEDBACK_INFORMATION                     16777216
#define NORMAN_GUIDEWIRE_TIP_COORDINATE                                      16777217

