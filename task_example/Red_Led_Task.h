#ifndef __RED_LED_TASK_H
#define __RED_LED_TASK_H

#include "standart_library.h"
#include "stm32f4xx.h"
#include "delay.h"

extern void* RED_LED_TASK;
void Red_Led_Task_Manager();
bool Red_Led_Task_ConCheck();
void Red_Led_Task_Init();











#endif