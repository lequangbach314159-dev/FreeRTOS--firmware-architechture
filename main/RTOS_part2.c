/*
 * @file RTOS.c
 * @author Your Name
 * @date 2025-08-17
 * @brief ESP32 FreeRTOS LED blink example following CMU C Coding Standard.
 *
 * This file demonstrates independent blinking of two LEDs using FreeRTOS task and timer.
 * LED1 blinks using a timer (on 0.5s, off 1s), LED2 blinks using a task (on 0.4s, off 0.6s).
 */
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/semphr.h"
#include "freertos/queue.h"
#include "driver/gpio.h"
#include "esp_log.h"
#include "sdkconfig.h"
#include "esp_timer.h"
#include "esp_random.h"
#include "hardware/uart_hw.h"
#include "service/msg_queue.h"

void app_main(void)
{
    uart_hw_init();
    msg_queue_init();
    // Application layer chỉ khởi tạo service/hardware, không gọi trực tiếp các task
    while (1) {
        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
} /* end app_main */

