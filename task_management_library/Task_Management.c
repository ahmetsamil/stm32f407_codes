#include "task_management.h"

Task_Interface_t Task_Interface;
Task_Table_t Task_Table[MAX_NUMBER_TASK];
task_status_t task_status;


void* Add_Task(void (*f_manager)(void),bool (*f_cond)(void),void (*f_init)(void),uint8_t priority);
void Start_Task_Management(void);
static void Arrest_Task(Task_Table_t* Task_Address);
static void Continue_Task(Task_Table_t*  Task_Address);
static void Arrest_All_Task(void);

static void Init_Task_Table(void);

/**
*@brief :Init Task Interface Structure
**/
void Init_Task_Interface()
{
	Task_Interface.Add_Task=Add_Task;
	Task_Interface.Arrest_Task=Arrest_Task;
	Task_Interface.Continue_Task=Continue_Task;
	Task_Interface.Arrest_All_Task=Arrest_All_Task;
	Init_Task_Table();
}

/**
*@brief : Init Task Table.
**      - Resets task table. 
**/
static void Init_Task_Table()
{
	uint8_t cnt;
	for(cnt=0;cnt<MAX_NUMBER_TASK;cnt++)
  {
		Task_Table[cnt].Task_Manager=NULL;
		Task_Table[cnt].priority=0;
		Task_Table[cnt].task_status=deactive;
	}	
}


/**
  * @brief  Adds the tasks you have written
  * @param  f_manager: it is task running 
  *         f_cond   : condition is checked to see if it enters the task or not. 
						f_init   : before run task, init written task.if not enter NULL 
  * @retval return pointer.You may access this pointer.
  */
static void* Add_Task(void (*f_manager)(void),bool (*f_cond)(void),void (*f_init)(void),uint8_t priority)
{
	Task_Table_t* Task_Table_ptr;
	Task_Table_ptr=&Task_Table[priority];
	
	Task_Table[priority].Task_Cond=f_cond;
	Task_Table[priority].Task_Manager=f_manager;
	Task_Table[priority].priority=priority;
	Task_Table[priority].task_status=active;
	
	if(f_init !=false)
	{
		f_init();
	}	
	
	Task_Table_ptr=&Task_Table[priority];
	
	return Task_Table_ptr;

}	
/** 
  * @brief  Stop running task
  * @retval None
  */
static void Arrest_Task(Task_Table_t* Task_Address)
{
	Task_Address->task_status=deactive;
}	

/** 
  * @brief  Continue stopped task
  * @retval None
  */
static void Continue_Task(Task_Table_t* Task_Address)
{
	Task_Address->task_status=active;
}	

/** 
  * @brief  Stop all task
  * @retval None
  */
static void Arrest_All_Task()
{
	uint8_t cnt;
	for(cnt=0;cnt<MAX_NUMBER_TASK;cnt++)
	{
		Task_Table[cnt].task_status=deactive;
	}
}	

/** 
  * @brief  navigates through tasks.First it looks task cond.If check_function is return true then run task_manager. 
  * @retval None
  */

void Start_Task_Management()
{
	uint8_t cnt;
	Task_Table_t* Task_ptr;

	while(1)
	{
		for(cnt=0;cnt<MAX_NUMBER_TASK;cnt++)
		{
			Task_ptr=cnt+Task_Table;
				if(Task_Table[cnt].task_status == active)
				{
					if(Task_ptr->Task_Cond != NULL)
					{
						if(Task_ptr->Task_Cond() == true)
						{
							Task_ptr->Task_Manager();
						}	
					}		
				}	
			}
		}
}
