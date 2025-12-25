#include "send_task.h"
#include "service/msg_queue.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"
#include "esp_random.h"

static void send_task1(void *pvParameter) {
    int cnt = 1;
    char msg[64];
    while (1) {
        snprintf(msg, sizeof(msg), "Task 1 of Bach (cnt = %d)\r\n", cnt++);
        if (msg_queue_send(msg) == pdPASS) {
            ESP_LOGI("UART", "Task 1 queued: %s", msg);
        } else {
            ESP_LOGW("UART", "Queue full, Task 1 message lost");
        }
        uint32_t rand_delay = 500 + (esp_random() % 400);
        vTaskDelay(pdMS_TO_TICKS(rand_delay));
    }
}

static void send_task2(void *pvParameter) {
    int cnt = 1;
    char msg[64];
    while (1) {
        snprintf(msg, sizeof(msg), "Task 2 of Bach (cnt = %d)\r\n", cnt++);
        if (msg_queue_send(msg) == pdPASS) {
            ESP_LOGI("UART", "Task 2 queued: %s", msg);
        } else {
            ESP_LOGW("UART", "Queue full, Task 2 message lost");
        }
        uint32_t rand_delay = 500 + (esp_random() % 400);
        vTaskDelay(pdMS_TO_TICKS(rand_delay));
    }
}

void send_task1_start(void) {
    xTaskCreate(send_task1, "send_task1", 2048, NULL, 5, NULL);
}

void send_task2_start(void) {
    xTaskCreate(send_task2, "send_task2", 2048, NULL, 5, NULL);
}
