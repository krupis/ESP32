#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "stdint.h"
#include "stdio.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"



enum e_thermostat_state
{
    INITIAL,
    TASK1,
    TASK2,
	TASK3,
    MAX_STATES
};


class Controller
{
    private://only accesible for class
        int test1;
        e_thermostat_state new_state;
        e_thermostat_state old_state;
        TaskHandle_t main_task_handle;
        TaskHandle_t secondary_task_handle;
        

    public: 
    //accesible outside class
        Controller();                                                   // INIT OBJECT
        void begin();
        void State_change_handle(e_thermostat_state state);


        static void task1(void* parameters)
        {
            Controller* controller = (Controller*)parameters;         
            for(;;)
            {   
                printf("test 1 =%i\n",controller->test1);
                printf("hello from task 1\n");
                vTaskDelay(1000/portTICK_RATE_MS);
            }
        }


        static void task2(void* parameters)
        {
            
            Controller* controller = (Controller*)parameters;
            for(;;)
            {   
                printf("hello from task 2\n");
                controller->test1 ++;
                printf("test 1 inside task2 = %i \n",controller->test1);
                vTaskDelay(1000/portTICK_RATE_MS);
                if(controller->test1 >= 10){
                    controller->test1 = 0;
                    controller->State_change_handle(TASK1);
                }
            }
        }



        
        //static void normal_operation_task(void *argument);                                 // DECLARE DEFAULT THERMOSTAT STATES AND VARS       
};




#endif