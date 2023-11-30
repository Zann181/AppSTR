/*
 * rgb_led2.h
 *
 *  Created on: Oct 11, 2021
 *      Author: kjagu
 */

#ifndef MAIN_RGB_LED2_H_
#define MAIN_RGB_LED2_H_

#include <stdint.h>

// RGB LED2 GPIOs
#define RGB_LED2_RED_GPIO       22  // Ejemplo: Cambia estos números GPIO según tu configuración
#define RGB_LED2_GREEN_GPIO     23
#define RGB_LED2_BLUE_GPIO      32

// RGB LED2 color mix channels
#define RGB_LED_CHANNEL_NUM2    3

// RGB LED2 configuration
typedef struct {
    int channel;
    int gpio;
    int mode;
    int timer_index;
} ledc_info_t2;

// Funciones para la segunda instancia de RGB LED
void rgb_led_wifi_app_started2(void);
void rgb_led_http_server_started2(void);
void rgb_led_wifi_connected2(void);
void rgb_led_set_color2(uint8_t red, uint8_t green, uint8_t blue);

#endif /* MAIN_RGB_LED2_H_ */
