/*
 * SystemProtocol.h
 *
 *  Created on: Aug 17, 2021
 *      Author: tonkovic.ig
 */

#ifndef __SYSTEM_PROTOCOL_H
#define __SYSTEM_PROTOCOL_H

#ifdef __cplusplus
extern "C" {
#endif

#include "stdint.h"
#include "stdio.h"
#include "string.h"
#include "driver/adc.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "Controller.h"



#define COMMAND_LINE_MAX_SIZE 1024 // Modem and system uart max command size (Max chars in one command line)
extern Controller controller;



bool ParseSystemCmd(char *line, uint16_t cmd_size);
void SystemUART_Task(void *argument);

#ifdef __cplusplus
}
#endif

#endif /* __SYSTEM_PROTOCOL_H */