#include "red_led_task.h"
volatile bool red_led_flag;
void* RED_LED_TASK=NULL;



void Red_Led_Task_Init()
{
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD,ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);
	GPIO_InitStructure.GPIO_Mode= GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15 ;
	GPIO_InitStructure.GPIO_OType =GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_Init(GPIOD, &GPIO_InitStructure);	
}	

bool Red_Led_Task_ConCheck()
{
	if(red_led_flag==true)
        return true;
	else
	    return false;
}	


void Red_Led_Task_Manager()
{
	GPIO_SetBits(GPIOD,GPIO_Pin_12);
	delay_ms(1000);
	GPIO_ResetBits(GPIOD,GPIO_Pin_12);
	delay_ms(1000);
}	

