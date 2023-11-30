#include "uart_temperature.h"
#include "driver/uart.h"
#include <string.h>
#include <stdio.h>
#include "temperature_sensor.h"



#define UART_NUM UART_NUM_0
#define TX_PIN 1
#define RX_PIN 3


extern QueueHandle_t adc_queue; // Declaración de la cola externa
bool print_temperature = true; // Variable global para controlar la impresión




void uart_printer_init() {
    uart_config_t uart_config = {
        .baud_rate = 115200,
        .data_bits = UART_DATA_8_BITS,
        .parity    = UART_PARITY_DISABLE,
        .stop_bits = UART_STOP_BITS_1,
        .flow_ctrl = UART_HW_FLOWCTRL_DISABLE
    };
    uart_param_config(UART_NUM, &uart_config);
    uart_set_pin(UART_NUM, TX_PIN, RX_PIN, UART_PIN_NO_CHANGE, UART_PIN_NO_CHANGE);
    uart_driver_install(UART_NUM, 256, 0, 0, NULL, 0);
}




void uart_printer_task() {
    char buffer[50]; // Aumenta el tamaño del búfer si es necesario

    while (1) {
        float temperature;

        if (xQueueReceive(adc_queue, &temperature, portMAX_DELAY)) {
            if (print_temperature) {
                // Si la impresión está habilitada, imprime la temperatura
                snprintf(buffer, sizeof(buffer), "Temperatura: %.2f°C\r\n", temperature);
                uart_write_bytes(UART_NUM, buffer, strlen(buffer));
            }
        }

        vTaskDelay(2000 / portTICK_PERIOD_MS); // Espera 2 segundos
    }
}

