/*
 * rgb_led2.c
 *
 *  Created on: Oct 11, 2021
 *      Author: kjagu
 */

#include <stdbool.h>

#include "driver/ledc.h"
#include "rgb_led2.h"

// Array de configuración para el segundo LED RGB
ledc_info_t2 ledc_ch2[RGB_LED_CHANNEL_NUM2];

// Variable para el manejo de la inicialización de PWM
bool g_pwm_init_handle2 = false;

// Inicialización de los ajustes del segundo LED RGB por canal
static void rgb_led_pwm_init2(void) {
	int rgb_ch;

	// Configuración para el color rojo
	ledc_ch2[0].channel		= LEDC_CHANNEL_3;  // Usa canales diferentes a los del primer LED
	ledc_ch2[0].gpio		= RGB_LED2_RED_GPIO;
	ledc_ch2[0].mode		= LEDC_HIGH_SPEED_MODE;
	ledc_ch2[0].timer_index	= LEDC_TIMER_1;  // Puede ser el mismo timer o uno diferente

	// Configuración para el color verde
	ledc_ch2[1].channel		= LEDC_CHANNEL_4;
	ledc_ch2[1].gpio		= RGB_LED2_GREEN_GPIO;
	ledc_ch2[1].mode		= LEDC_HIGH_SPEED_MODE;
	ledc_ch2[1].timer_index	= LEDC_TIMER_1;

	// Configuración para el color azul
	ledc_ch2[2].channel		= LEDC_CHANNEL_5;
	ledc_ch2[2].gpio		= RGB_LED2_BLUE_GPIO;
	ledc_ch2[2].mode		= LEDC_HIGH_SPEED_MODE;
	ledc_ch2[2].timer_index	= LEDC_TIMER_1;

	// Configuración del temporizador
	ledc_timer_config_t ledc_timer2 = {
		.duty_resolution	= LEDC_TIMER_8_BIT,
		.freq_hz			= 100,
		.speed_mode			= LEDC_HIGH_SPEED_MODE,
		.timer_num			= LEDC_TIMER_1
	};
	ledc_timer_config(&ledc_timer2);

	// Configuración de los canales
	for (rgb_ch = 0; rgb_ch < RGB_LED_CHANNEL_NUM2; rgb_ch++) {
		ledc_channel_config_t ledc_channel2 = {
			.channel	= ledc_ch2[rgb_ch].channel,
			.duty		= 0,
			.hpoint		= 0,
			.gpio_num	= ledc_ch2[rgb_ch].gpio,
			.intr_type	= LEDC_INTR_DISABLE,
			.speed_mode = ledc_ch2[rgb_ch].mode,
			.timer_sel	= ledc_ch2[rgb_ch].timer_index,
		};
		ledc_channel_config(&ledc_channel2);
	}

	g_pwm_init_handle2 = true;
}

// Establece el color del segundo LED RGB
void rgb_led_set_color2(uint8_t red, uint8_t green, uint8_t blue) {
	ledc_set_duty(ledc_ch2[0].mode, ledc_ch2[0].channel, red);
	ledc_update_duty(ledc_ch2[0].mode, ledc_ch2[0].channel);

	ledc_set_duty(ledc_ch2[1].mode, ledc_ch2[1].channel, green);
	ledc_update_duty(ledc_ch2[1].mode, ledc_ch2[1].channel);

	ledc_set_duty(ledc_ch2[2].mode, ledc_ch2[2].channel, blue);
	ledc_update_duty(ledc_ch2[2].mode, ledc_ch2[2].channel);
}

// Funciones específicas para el segundo LED RGB
void rgb_led_wifi_app_started2(void) {
	if (!g_pwm_init_handle2) {
		rgb_led_pwm_init2();
	}
	rgb_led_set_color2(255, 102, 255);
}

void rgb_led_http_server_started2(void) {
	if (!g_pwm_init_handle2) {
		rgb_led_pwm_init2();
	}
	rgb_led_set_color2(204, 255, 51);
}

void rgb_led_wifi_connected2(void) {
	if (!g_pwm_init_handle2) {
		rgb_led_pwm_init2();
	}
	rgb_led_set_color2(0, 255, 153);
}

