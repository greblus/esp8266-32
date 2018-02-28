#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

/* Declare a variable that is used to hold the handle of Task 2. */
TaskHandle_t xTask2Handle = NULL;

void vTask1( void *pvParameters )
{
	UBaseType_t uxPriority;
	uxPriority = uxTaskPriorityGet( NULL );
	for( ;; )
	{
		printf("%s\n", "Task 1 is running" );
		printf("%s\n", "About to raise the Task 2 priority" );
		vTaskPrioritySet( xTask2Handle, ( uxPriority + 1 ) );
	}
}

void vTask2( void *pvParameters )
{
	UBaseType_t uxPriority;
	uxPriority = uxTaskPriorityGet( NULL );
	for( ;; )
	{
		printf("%s\n", "Task 2 is running" );
		printf("%s\n", "About to lower the Task 2 priority" );
		vTaskPrioritySet( NULL, ( uxPriority - 2 ) );
	}
}

int app_main( void )
{
	xTaskCreate( vTask1, "Task 1", 1000, NULL, 2, NULL );
	xTaskCreate( vTask2, "Task 2", 1000, NULL, 1, &xTask2Handle );
	for( ;; );
}

