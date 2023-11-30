#ifndef TEMPERATURE_SENSOR_H
#define TEMPERATURE_SENSOR_H

#include <driver/adc.h>
#include <esp_adc_cal.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"


extern QueueHandle_t adc_queue; // Declaración de la variable global

#define ADC_CHANNEL ADC1_CHANNEL_6  // GPIO34 en ESP32
#define ADC_ATTEN ADC_ATTEN_DB_0    //ATENUACION 
#define ADC_BIT ADC_WIDTH_BIT_12    //BITS
#define DEFAULT_VREF 1100           // Use adc2_vref_to_gpio() para medir el voltaje de referencia del sistema


// Prototipos de funciones
void adc_init();
void read_temperature_task(void *pvParameter);
void start_temperature_read_task();

// Inicializa el ADC y UART para la lectura de temperatura
void temperature_sensor_init();


#endif // TEMPERATURE_SENSOR_H
