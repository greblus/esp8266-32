#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

static const char *pcTextForTask1 = "Task 1 is running";
static const char *pcTextForTask2 = "Task 2 is running";
volatile uint32_t ulIdleCycleCount = 0UL;

void vTaskFunction( void *pvParameters )
{
	char *pcTaskName;
	pcTaskName = ( char * ) pvParameters;

	for( ;; )
	{
		printf("%s on core %i. Idle count: %i\n" , pcTaskName, xPortGetCoreID(), ulIdleCycleCount);
		fflush(stdout);

		vTaskDelay( pdMS_TO_TICKS( 100 ) );	
	}
}

void app_main()
{
	xTaskCreate( vTaskFunction, "Task 1", 2000, (void*)pcTextForTask1, 1, NULL );
	xTaskCreate( vTaskFunction, "Task 2", 2000, (void*)pcTextForTask2, 1, NULL );
}

void vApplicationIdleHook( void )
{
	ulIdleCycleCount++;
}
