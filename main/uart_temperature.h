// uart_temperature.h

#ifndef UART_TEMPERATURE_H
#define UART_TEMPERATURE_H

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"


extern bool print_temperature;


void uart_printer_init(void);
void uart_printer_task(void);


#endif // UART_TEMPERATURE_H
