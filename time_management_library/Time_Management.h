#ifndef __TIME_MANAGEMENT_H
#define __TIME_MANAGEMENT_H


#include "standart_library.h"

#define MAX_TIME_TASK (32)


typedef enum
{
	active=1,
	deactive=0	
}time_task_status_t;	

typedef struct
{
	void (*Task_Manager)(void);
	void (*Task_Init) (void);
	uint64_t Last_Entry;
	uint64_t Time_Periode;
	time_task_status_t time_task_status;
}Time_Task_Table_t;	


typedef struct
{
	void* (*Add_Task)(void (*f_manager)(void),uint64_t time_periode,void (*f_init)(void),uint8_t priority);
	void  (*Arrest_Task)(Time_Task_Table_t* Task_Address);
	void  (*Continue_Task)(Time_Task_Table_t* Task_Address);
	void  (*Arrest_All_Task)(void);

}Time_Interface_t;


extern Time_Interface_t Time_Interface;
void Run_Time_Management(void);
void Time_Management_Interface_Init();



#endif