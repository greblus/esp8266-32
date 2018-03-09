#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"

static QueueHandle_t xQueue1 = NULL, xQueue2 = NULL;
static QueueSetHandle_t xQueueSet = NULL;

void vSenderTask1( void *pvParameters )
{
	const TickType_t xBlockTime = pdMS_TO_TICKS( 100 );
	const char * const pcMessage = "Message from vSenderTask1\n";
	for( ;; )
	{
		/* Block for 100ms. */
		vTaskDelay( xBlockTime );
		xQueueSend( xQueue1, &pcMessage, 0 );
	}
}

void vSenderTask2( void *pvParameters )
{
	const TickType_t xBlockTime = pdMS_TO_TICKS( 200 );
	const char * const pcMessage = "Message from vSenderTask2\n";

	for( ;; )
	{
		/* Block for 200ms. */
		vTaskDelay( xBlockTime );
		xQueueSend( xQueue2, &pcMessage, 0 );
	}
}

void vReceiverTask( void *pvParameters )
{
	QueueHandle_t xQueueThatContainsData;
	char *pcReceivedString;
	for( ;; )
	{
		/* Block on the queue set to wait for one of the queues in the set to contain data.
		Cast the QueueSetMemberHandle_t value returned from xQueueSelectFromSet() to a
		QueueHandle_t, as it is known all the members of the set are queues (the queue set
		does not contain any semaphores). */
		xQueueThatContainsData = ( QueueHandle_t ) xQueueSelectFromSet( xQueueSet, portMAX_DELAY );
		/* An indefinite block time was used when reading from the queue set, so
		xQueueSelectFromSet() will not have returned unless one of the queues in the set
		contained data, and xQueueThatContainsData cannot be NULL. Read from the queue. It
		is not necessary to specify a block time because it is known the queue contains
		data. The block time is set to 0. */
		xQueueReceive( xQueueThatContainsData, &pcReceivedString, 0 );

        printf("%s\n", pcReceivedString);
        fflush(stdout);
	}
}

int app_main( void )
{
	xQueue1 = xQueueCreate( 1, sizeof( char * ) );
	xQueue2 = xQueueCreate( 1, sizeof( char * ) );
	xQueueSet = xQueueCreateSet( 1 * 2 );

	xQueueAddToSet( xQueue1, xQueueSet );
	xQueueAddToSet( xQueue2, xQueueSet );

	xTaskCreate( vSenderTask1, "Sender1", 1000, NULL, 1, NULL );
	xTaskCreate( vSenderTask2, "Sender2", 1000, NULL, 1, NULL );
	xTaskCreate( vReceiverTask, "Receiver", 1000, NULL, 2, NULL );

	vTaskDelete( NULL );
	return 0;

}
