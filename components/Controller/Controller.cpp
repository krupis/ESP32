
#include "Controller.h"

Controller::Controller(){
    printf("Thermostat object created \n");
}

void Controller::begin(){
    this->test1 = 0;
    this->old_state = INITIAL;
    this->new_state = INITIAL;
    this->main_task_handle = NULL;
    printf("Start the task1 \n");
    this->State_change_handle(TASK2);
}

void Controller::State_change_handle(e_thermostat_state state)
{
    this-> new_state = state;
    if(this-> old_state != this-> new_state ){ // if the new state is different than current state, delete the task
        printf("different state, delete the previous task \n");
        if (this ->main_task_handle != NULL){
            vTaskDelete(this ->main_task_handle);
        }
        printf("PROGRAM STUCK \n");
    }
    else
    {
        printf("same task \n"); // the same task is set, dont do anything
        return;
    }
        
    switch(this->new_state) 
    {   
        case TASK1:
            printf("NEW STATE = MODE1 \n");
            this-> old_state = TASK1;
            xTaskCreate(task1,"MODE1",10000,this,1,&this->main_task_handle); // receiving commands from main uart
            break;

        case TASK2:
            printf("NEW STATE = MODE2\n");
            this-> old_state = TASK2;
            xTaskCreate(task2,"MODE2",10000,this,1,&this->main_task_handle); // receiving commands from main uart
            break;

        default:
            printf("state not recognised \n");
    }
}






