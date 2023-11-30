// button_handler.h

#ifndef BUTTON_HANDLER_H
#define BUTTON_HANDLER_H

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

// Define el número de pin del botón
#define BUTTON_PIN GPIO_NUM_26
#define BUTTON_PIN2 GPIO_NUM_27
// Prototipo de la función de manejador de interrupción
void IRAM_ATTR button_isr_handler(void *arg);


// Prototipos de funciones
void button_handler_init(void);
void button_handler_task(void *pvParameter);


// Functions to get the press count for each button
int button1_get_press_count(void);
int button2_get_press_count(void);


#endif // BUTTON_HANDLER_H