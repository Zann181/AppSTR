idf_component_register(SRCS "button_handler.c" "rgb_led2.c" "rgb_led.c" "wifi_app.c" "http_server.c" "main.c" "temperature_sensor.c" "uart_temperature.c"
                    INCLUDE_DIRS "."
                    EMBED_FILES webpage/app.css webpage/app.js webpage/favicon.ico webpage/index.html webpage/jquery-3.3.1.min.js)
