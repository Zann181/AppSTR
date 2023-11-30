#include "temperature_sensor.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

// Definición de la cola para enviar valores ADC
//QueueHandle_t adc_queue;

// En temperature_sensor.c
QueueHandle_t adc_queue = NULL; // Inicialización de la variable global


// Inicialización del ADC
void adc_init() {
    // Configuración de ADC 
    adc1_config_width(ADC_BIT);
    adc1_config_channel_atten(ADC_CHANNEL, ADC_ATTEN);

    // Calibración del ADC (opcional si se requiere calibración)
    esp_adc_cal_characteristics_t *adc_chars = calloc(1, sizeof(esp_adc_cal_characteristics_t));
    esp_adc_cal_characterize(ADC_UNIT_2, ADC_ATTEN, ADC_BIT, DEFAULT_VREF, adc_chars);
}

// Tarea para leer la temperatura
void read_temperature_task(void *pvParameter) {
    adc_init();
    const float maxVoltage = 3.3; // Asumiendo un máximo de 3.3V para el ADC
    const uint32_t maxValueADC = 4095; // 12 bits ADC

    while (1) {
        uint32_t adc_value;
        const int num_div = 100;
        adc_value = adc1_get_raw(ADC_CHANNEL);
        // Convertir el voltaje a temperatura
        float temperature = (adc_value/num_div)+4;

        xQueueSend(adc_queue, &temperature, portMAX_DELAY);
        //printf("Temperatura: %.2f°C\n", temperature);

        // Esperar 1 segundo antes de la próxima lectura
        vTaskDelay(pdMS_TO_TICKS(2000));
    }
}

void start_temperature_read_task() {
    xTaskCreate(read_temperature_task, "read_temperature_task", 2048, NULL, 5, NULL);
}

