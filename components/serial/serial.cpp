#include "serial.h"




bool ParseSystemCmd(char *line, uint16_t cmd_size)
{
if (!strcmp("task1", line))
	{
		printf("task1 selected\r\n");
		controller.State_change_handle(MODE1);
		return true;
	}
	if (!strcmp("task2", line))
	{
		printf("task2 selected\r\n");
		controller.State_change_handle(MODE2);
		return true;
	}

	if (!strcmp("task3", line))
	{
		printf("task3 selected\r\n");
		controller.State_change_handle(MODE3);
		return true;
	}


if (!strcmp("ping", line))
	{
		printf("pong\r\n");
		return true;
	}

if (!strcmp("mrst", line))
	{
		printf("Restarting modem\r\n");
		//ModemPowerON();
		return true;
	}	

if (!strcmp("adc", line))
	{
		uint32_t reading =  adc1_get_raw(ADC1_CHANNEL_7);
        printf("ADC RAW: %d\r\n", reading);
		return true;
	}

    printf("System cmd not found: %s\r\n", line);
	return false;

}

void SystemUART_Task(void *argument)
{
  unsigned int char_received=EOF;
  unsigned int char_counter=0;
  char command_line[COMMAND_LINE_MAX_SIZE];
  for (;;)
  	{
    
    while (char_received == EOF)
        {
          char_received=getchar(); 
		  vTaskDelay(10/portTICK_RATE_MS);;
        }

				char c = (char)char_received;

				//if ((c == '\n') || (c == '\r')) { // End of line reached
				if (c == '\n') // End of line reached
				{ 
					command_line[char_counter] = 0; // Set string termination character.
					ParseSystemCmd(command_line, char_counter); // Line is complete. Execute it!
					char_counter = 0;
          char_received=EOF;
				}
				else
				{
					if (c <= ' ')
					{

					}
					else
							if (char_counter >= (COMMAND_LINE_MAX_SIZE - 1))
							{
								// Detect line buffer overflow. Report error and reset line buffer.
								char_counter = 0;

							}
							else
								if ((c >= 'A') && (c <= 'Z'))
								{ // Upcase lowercase
									command_line[char_counter++] = c - 'A' + 'a';
								}
								else
								{
									command_line[char_counter++] = c;
								}
				}

        char_received=EOF;

  }

}