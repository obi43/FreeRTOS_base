#include <stdio.h>
#include "pico/stdlib.h"
#include "pico/platform.h"

#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"

#ifdef PICO_W
#include "pico/cyw43_arch.h"
#endif

#ifndef PICO_W 
const uint LED_PIN = 1;
#endif

SemaphoreHandle_t  xSemaphore; // The semaphore handle

// The LED task. It blinks the LED, thats all.
void led_task(void *arg)
{   
    int onOff=0;

#ifndef PICO_W 
    gpio_init(LED_PIN);
    gpio_set_dir(LED_PIN, GPIO_OUT);  
#endif

    while(1)
        {
#ifdef PICO_W  
        cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, onOff);
#else
        gpio_put(LED_PIN, onOff); 
#endif
        onOff = !onOff;
        vTaskDelay(1000);
        }
}


// Prints a message to the console and informs about the task number
void hello_task(void *arg)
{
    int taskNumber = (int)arg;



    while(1)
    {
        // Take the semaphore, if it is not available then wait for 10 ticks
        if( xSemaphoreTake( xSemaphore, ( TickType_t ) 10 ) == pdTRUE )
        {
            printf("Hello, world from task %d, and core %d!\n", taskNumber, get_core_num() );
            vTaskDelay(1000);
            xSemaphoreGive( xSemaphore );
        }
        else
        {
            printf("Task %d could not take the semaphore\n", taskNumber);
        }
    
        printf("Hello, world from task %d, and core %d!\n", taskNumber, get_core_num() );
        vTaskDelay(2000);
    }
}

int main()
{
    stdio_init_all();

    #ifdef PICO_W  
        if (cyw43_arch_init())
        {   // Fatal error not able to continue
            goto fatalError;
        }
    #endif

    // Attempt to create the semaphore
    xSemaphore = xSemaphoreCreateBinary();
    if (xSemaphore == NULL)
    {
        // There was insufficient FreeRTOS heap available for the semaphore to be created successfully
        printf("Failed to create semaphore\n");
        goto fatalError;
    }

    xTaskCreate(led_task, "ledTask", configMINIMAL_STACK_SIZE, NULL, 1, NULL);
    xTaskCreate(hello_task, "hellowTask", configMINIMAL_STACK_SIZE, (void*)1, 1, NULL);
    xTaskCreate(hello_task, "hellowTask", configMINIMAL_STACK_SIZE, (void*)2, 1, NULL);

    vTaskStartScheduler();

    // We shall newer ratch this point, but if we do then stay in an endless loop
    fatalError:
        for (;;)
            ;

}
