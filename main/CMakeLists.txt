idf_component_register(SRCS "RTOS_part2_esp1.c" "RTOS_part2.c"
                       INCLUDE_DIRS "."
                       PRIV_REQUIRES esp_driver_uart esp_timer esp_driver_gpio)
