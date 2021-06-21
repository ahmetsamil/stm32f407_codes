#ifndef __TIME_MANAGEMENT_H
#define __TIME_MANAGEMENT_H

/*************************************************************************
*@Author:AHMET SAMIL BILGIN
*@Name	:Task Management Library
*@Explanation:
-The purpose of this library is to make the code more modular and make it easier
to add and remove later.It allows us to do the tasks that occur in a certain period more regularly.


**************************************************************************/



#include "standart_library.h" // stdint.h,stdbool.h,stdlib.h Librarys.
#define MAX_TIME_TASK (32)	  // you can change max time task here.


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
