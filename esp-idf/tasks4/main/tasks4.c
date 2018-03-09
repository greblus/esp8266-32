#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

static const char *pcTextForTask1 = "DelayedUntil little pig is running";
static const char *pcTextForTask2 = "Periodic hog 1 is running";
static const char *pcTextForTask3 = "Periodic hog 2 is running";

void vDelayedUntil( void *pvParameters )
{
	char *pcTaskName;
	/* The string to print out is passed in via the parameter. Cast this to a
	character pointer. */
	pcTaskName = ( char * ) pvParameters;
	TickType_t xLastWakeTime;
	xLastWakeTime = xTaskGetTickCount();

	for( ;; )
	{
		printf("%s on core %i.\n", pcTaskName, xPortGetCoreID());
		fflush(stdout);

		vTaskDelayUntil( &xLastWakeTime, pdMS_TO_TICKS( 100 ) );	
	}
}

void vTaskFunction( void *pvParameters )
{
	char *pcTaskName;
	pcTaskName = ( char * ) pvParameters;

	for( ;; )
	{
		printf("%s on core %i.\n", pcTaskName, xPortGetCoreID());
		fflush(stdout);

	}
}
void app_main()
{
	xTaskCreate( vDelayedUntil, "Task 1", 2000, (void*)pcTextForTask1, 2, NULL );
	xTaskCreate( vTaskFunction, "Task 2", 2000, (void*)pcTextForTask2, 1, NULL );
	xTaskCreate( vTaskFunction, "Task 3", 2000, (void*)pcTextForTask3, 1, NULL );
	
  	vTaskDelete(NULL); 
}
