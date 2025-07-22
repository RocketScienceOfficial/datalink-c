#ifndef _DATALINK__H
#define _DATALINK__H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

#define DATALINK_MAGIC_SERIAL 0x7E
#define DATALINK_MAGIC_RADIO 0x5A

typedef enum datalink_message_type
{
    DATALINK_MESSAGE_TELEMETRY_DATA_OBC,
    DATALINK_MESSAGE_TELEMETRY_DATA_OBC_WITH_RESPONSE,
    DATALINK_MESSAGE_TELEMETRY_DATA_GCS,
    DATALINK_MESSAGE_TELEMETRY_RESPONSE,
    DATALINK_MESSAGE_OBC_APP_EKF_TRANSMIT_START,
    DATALINK_MESSAGE_OBC_APP_EKF_TRANSMIT_END,
    DATALINK_MESSAGE_OBC_APP_EKF_DATA,
    DATALINK_MESSAGE_DATA_SAVED_CHUNK,
    DATALINK_MESSAGE_DATA_SAVED_SIZE,
    DATALINK_MESSAGE_DATA_REQUEST_READ,
    DATALINK_MESSAGE_DATA_FINISH_READ,
    DATALINK_MESSAGE_DATA_REQUEST_CLEAR,
    DATALINK_MESSAGE_DATA_PROGRESS_CLEAR,
    DATALINK_MESSAGE_DATA_FINISH_CLEAR,
    DATALINK_MESSAGE_DATA_REQUEST_RECOVERY,
    DATALINK_MESSAGE_DATA_FINISH_RECOVERY,
    DATALINK_MESSAGE_IGN_REQUEST_TEST,
    DATALINK_MESSAGE_IGN_FINISH_TEST,
    DATALINK_MESSAGE_CONFIG_GET,
    DATALINK_MESSAGE_CONFIG_GET_ACK,
    DATALINK_MESSAGE_CONFIG_SET,
    DATALINK_MESSAGE_CONFIG_SET_ACK,
    DATALINK_MESSAGE_RADIO_MODULE_TX_DONE,
    DATALINK_MESSAGE_NONE,
} datalink_message_type_t;

typedef enum datalink_options_sm_state
{
    DATALINK_OPTIONS_SM_STATE_STANDING = 0,
    DATALINK_OPTIONS_SM_STATE_ACCELERATING = 1,
    DATALINK_OPTIONS_SM_STATE_FREE_FLIGHT = 2,
    DATALINK_OPTIONS_SM_STATE_FREE_FALL = 3,
    DATALINK_OPTIONS_SM_STATE_LANDED = 4,
} datalink_options_sm_state_t;

typedef enum datalink_flags_telemetry_data_control_flags
{
    DATALINK_FLAGS_TELEMETRY_DATA_CONTROL_ARM_ENABLED = 1 << 0,
    DATALINK_FLAGS_TELEMETRY_DATA_CONTROL_3V3_ENABLED = 1 << 1,
    DATALINK_FLAGS_TELEMETRY_DATA_CONTROL_5V_ENABLED = 1 << 2,
    DATALINK_FLAGS_TELEMETRY_DATA_CONTROL_VBAT_ENABLED = 1 << 3,
    DATALINK_FLAGS_TELEMETRY_DATA_CONTROL_IGN_1 = 1 << 4,
    DATALINK_FLAGS_TELEMETRY_DATA_CONTROL_IGN_2 = 1 << 5,
    DATALINK_FLAGS_TELEMETRY_DATA_CONTROL_IGN_3 = 1 << 6,
    DATALINK_FLAGS_TELEMETRY_DATA_CONTROL_IGN_4 = 1 << 7,
} datalink_flags_telemetry_data_control_flags_t;

typedef enum datalink_flags_telemetry_response_control_flags
{
    DATALINK_FLAGS_TELEMETRY_RESPONSE_CONTROL_ARM_ENABLED = 1 << 0,
    DATALINK_FLAGS_TELEMETRY_RESPONSE_CONTROL_3V3_ENABLED = 1 << 1,
    DATALINK_FLAGS_TELEMETRY_RESPONSE_CONTROL_5V_ENABLED = 1 << 2,
    DATALINK_FLAGS_TELEMETRY_RESPONSE_CONTROL_VBAT_ENABLED = 1 << 3,
} datalink_flags_telemetry_response_control_flags_t;

typedef enum datalink_flags_ign
{
    DATALINK_FLAGS_IGN_1_CONT = 1 << 0,
    DATALINK_FLAGS_IGN_2_CONT = 1 << 1,
    DATALINK_FLAGS_IGN_3_CONT = 1 << 2,
    DATALINK_FLAGS_IGN_4_CONT = 1 << 3,
    DATALINK_FLAGS_IGN_1_STATE = 1 << 4,
    DATALINK_FLAGS_IGN_2_STATE = 1 << 5,
    DATALINK_FLAGS_IGN_3_STATE = 1 << 6,
    DATALINK_FLAGS_IGN_4_STATE = 1 << 7,
} datalink_flags_ign_t;

typedef struct __attribute__((__packed__)) datalink_frame_telemetry_data_obc
{
    float qw;
    float qx;
    float qy;
    float qz;
    uint16_t velocity_kmh;
    uint16_t batteryVoltage100;
    uint8_t batteryPercentage;
    double lat;
    double lon;
    uint16_t alt;
    uint8_t state;
    uint8_t controlFlags;
} datalink_frame_telemetry_data_obc_t;

typedef struct __attribute__((__packed__)) datalink_frame_telemetry_data_gcs
{
    float qw;
    float qx;
    float qy;
    float qz;
    uint16_t velocity_kmh;
    uint16_t batteryVoltage100;
    uint8_t batteryPercentage;
    double lat;
    double lon;
    uint16_t alt;
    uint8_t state;
    uint8_t controlFlags;
    uint8_t signalStrengthNeg;
    uint8_t packetLossPercentage;
} datalink_frame_telemetry_data_gcs_t;

typedef struct __attribute__((__packed__)) datalink_frame_telemetry_response
{
    uint8_t controlFlags;
} datalink_frame_telemetry_response_t;

typedef struct __attribute__((__packed__)) datalink_frame_obc_app_ekf_data
{
    float qw;
    float qx;
    float qy;
    float qz;
    float positionN;
    float positionE;
    float positionD;
    float velocityN;
    float velocityE;
    float velocityD;
    float accelerationN;
    float accelerationE;
    float accelerationD;
} datalink_frame_obc_app_ekf_data_t;

typedef struct __attribute__((__packed__)) datalink_frame_data_saved_chunk
{
    uint16_t dt;
    float accX;
    float accY;
    float accZ;
    float velN;
    float velE;
    float velD;
    float posN;
    float posE;
    float posD;
    float qw;
    float qx;
    float qy;
    float qz;
    double lat;
    double lon;
    double alt;
    uint16_t pressure;
    uint8_t smState;
    uint16_t batteryVoltage100;
    uint8_t ignFlags;
    uint8_t gpsData;
} datalink_frame_data_saved_chunk_t;

typedef struct __attribute__((__packed__)) datalink_frame_data_acs_saved_chunk
{
    uint16_t dt;
    float accX;
    float accY;
    float accZ;
    float velN;
    float velE;
    float velD;
    float posN;
    float posE;
    float posD;
    float qw;
    float qx;
    float qy;
    float qz;
    double lat;
    double lon;
    double alt;
    uint16_t pressure;
    int16_t angleSetpoint10;
    int16_t pidRoll10;
    int8_t servoAngle10;
    uint8_t smState;
    uint16_t batteryVoltage100;
    uint8_t gpsData;
} datalink_frame_data_acs_saved_chunk_t;

typedef struct __attribute__((__packed__)) datalink_frame_data_saved_size
{
    uint32_t size;
} datalink_frame_data_saved_size_t;

typedef struct __attribute__((__packed__)) datalink_frame_data_progress_clear
{
    uint8_t percentage;
} datalink_frame_data_progress_clear_t;

typedef struct __attribute__((__packed__)) datalink_frame_ign_request_test
{
    uint8_t ignNum;
} datalink_frame_ign_request_test_t;

typedef struct __attribute__((__packed__)) datalink_frame_config_get
{
    uint16_t mainHeight;
    uint8_t malfunctionSpeed;
} datalink_frame_config_get_t;

typedef struct __attribute__((__packed__)) datalink_frame_config_set
{
    uint16_t mainHeight;
    uint8_t malfunctionSpeed;
} datalink_frame_config_set_t;

typedef struct datalink_frame_structure_serial
{
    uint8_t magic_serial;
    uint8_t msgId;
    uint8_t len;
    uint8_t payload[255];
    uint16_t crc;
} datalink_frame_structure_serial_t;

typedef struct datalink_frame_structure_radio
{
    uint8_t magic_radio;
    uint8_t seq;
    uint8_t srcId;
    uint8_t destId;
    uint8_t msgId;
    uint8_t len;
    uint8_t payload[255];
    uint16_t crc;
} datalink_frame_structure_radio_t;

int datalink_serialize_frame_serial(const datalink_frame_structure_serial_t *frame, uint8_t *buffer, int *len);
int datalink_serialize_frame_radio(const datalink_frame_structure_radio_t *frame, uint8_t *buffer, int *len);
int datalink_deserialize_frame_serial(datalink_frame_structure_serial_t *frame, const uint8_t *buffer, int len);
int datalink_deserialize_frame_radio(datalink_frame_structure_radio_t *frame, const uint8_t *buffer, int len);

#ifdef __cplusplus
}
#endif

#endif