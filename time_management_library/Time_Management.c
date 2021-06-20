#include "Time_Management.h"
#include "main.h"

void*  Add_Task(void (*f_manager)(void),uint64_t time_periode,void (*f_init)(void),uint8_t priority);
void  Arrest_Task (Time_Task_Table_t* Task_Address);
void  Continue_Task(Time_Task_Table_t*  Task_Address);
void  Arrest_All_Task(void);
void Time_Management_Interface_Init(void);
void Task_Table_Init(void);

Time_Interface_t Time_Interface;
Time_Task_Table_t Time_Task_Table[MAX_TIME_TASK]; 

void Time_Management_Interface_Init()
{
	Time_Interface.Add_Task=Add_Task;
	Time_Interface.Arrest_Task=Arrest_Task;
	Time_Interface.Continue_Task=Continue_Task;
	Time_Interface.Arrest_All_Task=Arrest_All_Task;
	
	Task_Table_Init();
	
}	

void Task_Table_Init(void)
{
	uint8_t cnt;
	for(cnt=0;cnt<MAX_TIME_TASK;cnt++)
	{
		Time_Task_Table[cnt].Last_Entry=0;
		Time_Task_Table[cnt].Time_Periode=0;
		Time_Task_Table[cnt].Task_Manager=NULL;
		Time_Task_Table[cnt].time_task_status=deactive;
	}	
}	

void* Add_Task (void (*f_manager)(void),uint64_t time_periode,void (*f_init)(void),uint8_t priority)
{
	Time_Task_Table[priority].Time_Periode=time_periode;
	Time_Task_Table[priority].Task_Manager=f_manager;
	Time_Task_Table[priority].time_task_status=active;
	Time_Task_Table[priority].Task_Init=f_init;
	if(*f_init !=NULL)
		Time_Task_Table[priority].Task_Init();
	

}

void  Arrest_Task (Time_Task_Table_t* Task_Address)
{
	Task_Address->time_task_status=deactive;
}	
void  Continue_Task(Time_Task_Table_t*  Task_Address)
{
	Task_Address->time_task_status=active;
}	

void Arrest_All_Task(void)
{
	uint8_t cnt;
	
	for(cnt=0;cnt<MAX_TIME_TASK;cnt++)
	{
		if(Time_Task_Table[cnt].time_task_status==active)
		{
			Time_Task_Table[cnt].time_task_status=deactive;
		}	
	}	
}	

void Run_Time_Management(void)
{
	uint8_t cnt;
	while(1)
	{
		for(cnt=0;cnt<MAX_TIME_TASK;cnt++)
		{
			if(Time_Task_Table[cnt].time_task_status==active)
			{
				if(Time_Task_Table[cnt].Time_Periode<(Local_Time-Time_Task_Table[cnt].Last_Entry))
				{
					Time_Task_Table[cnt].Task_Manager();
					Time_Task_Table[cnt].Last_Entry=Local_Time;
				}	
			}	
		}	
	}
}	

