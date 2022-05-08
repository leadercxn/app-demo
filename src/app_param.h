#ifndef APP_PARAM_H__
#define APP_PARAM_H__

#include "stdint.h"
#include "stdbool.h"

typedef struct
{
    uint32_t magic_word;
    uint16_t crc16;
    uint8_t  flag;

    uint32_t fw_version;
    uint32_t hw_version;
} app_param_t;

extern app_param_t g_app_param;

#endif
