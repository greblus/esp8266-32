#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

unsigned long cnt1 = 0, cnt2 = 0, cnt3 = 0;
static const char *pcTextForTask1 = "Task 1 is running";
static const char *pcTextForTask2 = "Task 2 is running";
static const char *pcTextForTask3 = "Task 3 is running";

void vTaskFunction( void *pvParameters )
{
	char *pcTaskName;
	/* The string to print out is passed in via the parameter. Cast this to a
	character pointer. */
	pcTaskName = ( char * ) pvParameters;
	for( ;; )
	{
		if (pcTaskName == pcTextForTask1)
				cnt1++;
		if (pcTaskName == pcTextForTask2)
				cnt2++;
		if (pcTaskName == pcTextForTask3)
				cnt3++;

		printf("%s on core %i. Stats: t1: %lu t2: %lu t3: %lu\n", pcTaskName, xPortGetCoreID(), cnt1, cnt2, cnt3);
		fflush(stdout);
	
		vTaskDelay(20/portTICK_PERIOD_MS); // interestingly, if you make the delay smaller than 20ms it'll 
										   // move tasks between CPU cores, if it's 20ms, they'll run on core 1
										   // and if delay is too small, some tasks will cpu-starve the others
	}
}


void app_main()
{
	xTaskCreate( vTaskFunction, "Task 1", 2000, (void*)pcTextForTask1, 1, NULL );
	xTaskCreate( vTaskFunction, "Task 2", 2000, (void*)pcTextForTask2, 1, NULL );
	xTaskCreate( vTaskFunction, "Task 3", 2000, (void*)pcTextForTask3, 1, NULL );
	
   	vTaskDelete(NULL); 
}
