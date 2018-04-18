#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

void vTask1( void *pvParameters )
{
    for ( ; ; ) {
        for(int i=0 ; i<5000000 ; i++ ) {
            printf("%s\n", "Task 1 is running" );
        }
        taskYIELD();
    }
}

void vTask2( void *pvParameters )
{
    for ( ; ; ) {
        for(int i=0 ; i<10000000 ; i++ ) {
            printf("%s\n", "Task 2 is running" );
        }
        taskYIELD();
    }
}

void app_main( void )
{
    xTaskCreatePinnedToCore( vTask1, "Task 1", 2000, NULL, 1, NULL, 1 );
    xTaskCreatePinnedToCore( vTask2, "Task 2", 2000, NULL, 1, NULL, 1 );
    vTaskDelete(NULL);
}

