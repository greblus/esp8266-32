#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

void vTaskFunction( void *pvParameters )
{
	char *pcTaskName;
	/* The string to print out is passed in via the parameter. Cast this to a
	character pointer. */
	pcTaskName = ( char * ) pvParameters;
	for( ;; )
	{
		/* Print out the name of this task. */
		printf("%s on core %i\n", pcTaskName, xPortGetCoreID());
		// each task has it's own slice of CPU time which is not interrupted/preempted
	}
}

/* Define the strings that will be passed in as the task parameters. These are
defined const and not on the stack to ensure they remain valid when the tasks are
executing. */
static const char *pcTextForTask1 = "Task 1 is running";
static const char *pcTextForTask2 = "Task 2 is running";

void app_main()
{
	xTaskCreatePinnedToCore( vTaskFunction, "Task 1", 2000, (void*)pcTextForTask1, 1, NULL, 0); //1st CPU
	xTaskCreatePinnedToCore( vTaskFunction, "Task 2", 2000, (void*)pcTextForTask2, 1, NULL, 1); //2nd CPU
	
   	vTaskDelete(NULL);
}
