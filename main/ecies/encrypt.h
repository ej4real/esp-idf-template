
#ifndef _ENCRYPT_H_
#define _ENCRYPT_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/event_groups.h"
#include "esp_system.h"

#include <errno.h>

#include "../main/ecies/ecc.h"

void data_encrypt(uint8_t data);//[static 8]);

#ifdef __cplusplus
}
#endif

#endif /* _ENCRYPT_H_ */
