#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

TaskHandle_t h1, h2;

void vTaskFunction( void *pvParameters )
{
    char *pcTaskName;
    pcTaskName = ( char * ) pvParameters;
    for( ;; )
    {
        if (xTaskGetCurrentTaskHandle() == h1) {
            xTaskNotifyGive(h2);
          }
        else {
            xTaskNotifyGive(h1);
          }

        uint32_t nv = ulTaskNotifyTake(pdFALSE, pdMS_TO_TICKS(10));
        printf("%s status code: %i\n", pcTaskName, nv);
        fflush(stdout);
    }
}

static const char *pcTextForTask1 = "Task 1";
static const char *pcTextForTask2 = "Task 2";

void app_main()
{

    /*    Tasks notifications are not smp-safe and they are working but only on the 
          same CPU core  */                     

    //    xTaskCreate( vTaskFunction, "Task 1", 3000, (void*)pcTextForTask1, 1, &h1); 
    //    xTaskCreate( vTaskFunction, "Task 2", 3000, (void*)pcTextForTask2, 1, &h2); 

    xTaskCreatePinnedToCore( vTaskFunction, "Task 1", 3000, (void*)pcTextForTask1, 1, &h1, 0); 
    xTaskCreatePinnedToCore( vTaskFunction, "Task 2", 3000, (void*)pcTextForTask2, 1, &h2, 0); 

    vTaskDelete(NULL);
}
