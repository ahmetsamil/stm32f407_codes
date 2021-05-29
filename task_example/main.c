#include "stm32f4xx.h"
#include "standart_library.h"
#include "delay.h"
#include "Task_Management.h"
#include "Red_led_Task.h"


int main()
{
	Init_Task_Interface();
	Task_Interface.Add_Task(Red_Led_Task_Manager,Red_Led_Task_ConCheck,Red_Led_Task_Init,0);
	Start_Task_Management();			 
}	



