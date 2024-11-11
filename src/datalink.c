#include "datalink.h"
#include <string.h>

static int _safe_copy(uint8_t *buffer, int *bufferOffset, int bufferLen, const uint8_t *src, int srcLen);
static uint16_t _crc16_ccitt_calculate(const uint8_t *data, int length);
static uint16_t _crc16_mcrf4xx_calculate(const uint8_t *data, int length);

int datalink_serialize_frame_serial(const datalink_frame_structure_serial_t *frame, uint8_t *buffer, int *len)
{
    int bufferOffset = 0;

    if (*len >= 3)
    {
        buffer[0] = DATALINK_MAGIC_SERIAL;
        buffer[1] = frame->msgId;
        buffer[2] = frame->len;

        bufferOffset += 3;
    }
    else
    {
        return 0;
    }

    if (!_safe_copy(buffer, &bufferOffset, *len, frame->payload, frame->len))
    {
        return 0;
    }

    uint16_t crc = _crc16_mcrf4xx_calculate(buffer, bufferOffset);

    if (!_safe_copy(buffer, &bufferOffset, *len, (const uint8_t *)&crc, 2))
    {
        return 0;
    }

    *len = bufferOffset;

    return 1;
}

int datalink_serialize_frame_radio(const datalink_frame_structure_radio_t *frame, uint8_t *buffer, int *len)
{
    int bufferOffset = 0;

    if (*len >= 6)
    {
        buffer[0] = DATALINK_MAGIC_RADIO;
        buffer[1] = frame->seq;
        buffer[2] = frame->srcId;
        buffer[3] = frame->destId;
        buffer[4] = frame->msgId;
        buffer[5] = frame->len;

        bufferOffset += 6;
    }
    else
    {
        return 0;
    }

    if (!_safe_copy(buffer, &bufferOffset, *len, frame->payload, frame->len))
    {
        return 0;
    }

    uint16_t crc = _crc16_mcrf4xx_calculate(buffer, bufferOffset);

    if (!_safe_copy(buffer, &bufferOffset, *len, (const uint8_t *)&crc, 2))
    {
        return 0;
    }

    *len = bufferOffset;

    return 1;
}

int datalink_deserialize_frame_serial(datalink_frame_structure_serial_t *frame, const uint8_t *buffer, int len)
{
    if (len < 5)
    {
        return 0;
    }

    frame->magic_serial = buffer[0];

    if (frame->magic_serial != DATALINK_MAGIC_SERIAL)
    {
        return 0;
    }

    memcpy(&frame->crc, buffer + len - 2, 2);

    uint16_t crc = _crc16_mcrf4xx_calculate(buffer, len - 2);

    if (frame->crc != crc)
    {
        return 0;
    }

    frame->msgId = buffer[1];

    if (frame->msgId >= DATALINK_MESSAGE_NONE)
    {
        return 0;
    }

    frame->len = buffer[2];

    if (frame->len != len - 5)
    {
        return 0;
    }

    if (frame->len > 0)
    {
        memcpy(frame->payload, buffer + 3, frame->len);
    }

    return 1;
}

int datalink_deserialize_frame_radio(datalink_frame_structure_radio_t *frame, const uint8_t *buffer, int len)
{
    if (len < 8)
    {
        return 0;
    }

    frame->magic_radio = buffer[0];

    if (frame->magic_radio != DATALINK_MAGIC_RADIO)
    {
        return 0;
    }

    memcpy(&frame->crc, buffer + len - 2, 2);

    uint16_t crc = _crc16_mcrf4xx_calculate(buffer, len - 2);

    if (frame->crc != crc)
    {
        return 0;
    }

    frame->seq = buffer[1];
    frame->srcId = buffer[2];
    frame->destId = buffer[3];
    frame->msgId = buffer[4];

    if (frame->msgId >= DATALINK_MESSAGE_NONE)
    {
        return 0;
    }

    frame->len = buffer[5];

    if (frame->len != len - 8)
    {
        return 0;
    }

    if (frame->len > 0)
    {
        memcpy(frame->payload, buffer + 6, frame->len);
    }

    return 1;
}

static int _safe_copy(uint8_t *buffer, int *bufferOffset, int bufferLen, const uint8_t *src, int srcLen)
{
    if (srcLen + *bufferOffset <= bufferLen)
    {
        if (srcLen > 0)
        {
            memcpy(buffer + *bufferOffset, src, srcLen);

            *bufferOffset += srcLen;
        }

        return 1;
    }
    else
    {
        return 0;
    }
}

/**
 * REF: https://stackoverflow.com/a/23726131/14697550
 * REF: https://www.lammertbies.nl/comm/info/crc-calculation
 */
static uint16_t _crc16_ccitt_calculate(const uint8_t *data, int length)
{
    uint16_t crc = 0xFFFF;
    uint8_t x;

    while (length--)
    {
        x = crc >> 8 ^ *data++;
        x ^= x >> 4;
        crc = (crc << 8) ^ ((uint16_t)(x << 12)) ^ ((uint16_t)(x << 5)) ^ ((uint16_t)x);
    }

    return crc;
}

/**
 * REF: https://gist.github.com/aurelj/270bb8af82f65fa645c1
 */
static uint16_t _crc16_mcrf4xx_calculate(const uint8_t *data, int length)
{
    uint16_t crc = 0xFFFF;
    uint8_t t;
    uint8_t L;

    while (length--)
    {
        crc ^= *data++;
        L = crc ^ (crc << 4);
        t = (L << 3) | (L >> 5);
        L ^= (t & 0x07);
        t = (t & 0xF8) ^ (((t << 1) | (t >> 7)) & 0x0F) ^ (uint8_t)(crc >> 8);
        crc = (L << 8) | t;
    }

    return crc;
}