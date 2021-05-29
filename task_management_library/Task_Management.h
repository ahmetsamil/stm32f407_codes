#ifndef __TASK_MANAGEMENT_H
#define __TASK_MANAGEMENT_H

/*********************************
*@Author:AHMET SAMIL BILGIN
*@Name	:Task Management Library
*@Explanation:
-The purpose of this library is to make the code more modular and make it easier
to add and remove later.

**********************************/


#include "standart_library.h"
#define MAX_NUMBER_TASK 32


typedef enum
{
	active=1,
	deactive=0	
}task_status_t;	

typedef struct
{
	void (*Task_Manager)(void);
	bool (*Task_Cond)(void);
	
	uint8_t priority;
	task_status_t task_status;
	
}Task_Table_t;	

typedef struct
{
	void* (*Add_Task)(void (*f_manager)(void),bool (*f_cond)(void),void (*f_init)(void),uint8_t priority);
	void (*Arrest_Task)(Task_Table_t* Task_Address);
	void (*Continue_Task)(Task_Table_t*  Task_Address);
	void (*Arrest_All_Task)(void);
}Task_Interface_t;

extern  Task_Interface_t Task_Interface;
void Start_Task_Management(void);
void Init_Task_Interface(void);

#endif
