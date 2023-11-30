/**
 * Application entry point.
 */

#include "nvs_flash.h"

#include "wifi_app.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "button_handler.h"

#include "temperature_sensor.h"
#include "uart_temperature.h"
#include "freertos/queue.h"


void app_main(void)
{

	  // Inicializa el manejador de botón
    button_handler_init();

    // Crea la tarea del manejador del botón
    xTaskCreate(button_handler_task, "button_handler_task", 2048, NULL, 5, NULL);


    // Initialize NVS
	esp_err_t ret = nvs_flash_init();
	if (ret == ESP_ERR_NVS_NO_FREE_PAGES || ret == ESP_ERR_NVS_NEW_VERSION_FOUND)
	{
		ESP_ERROR_CHECK(nvs_flash_erase());
		ret = nvs_flash_init();
	}
	ESP_ERROR_CHECK(ret);

	// Start Wifi
	wifi_app_start();

	// Creación de la cola para los datos de temperatura
    adc_queue = xQueueCreate(10, sizeof(float));
    if (adc_queue == NULL) {
        printf("Error al crear la cola\n");
        return;
    }

    // Creación y lanzamiento de la tarea para leer la temperatura
    xTaskCreate(read_temperature_task, "read_temperature_task", 2048, NULL, 5, NULL);

	//uart_printer_init();
    //xTaskCreate(uart_printer_task, "uart_printer_task", 2048, NULL, 10, NULL);

}

