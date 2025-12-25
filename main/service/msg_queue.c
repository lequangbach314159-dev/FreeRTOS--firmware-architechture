#include "msg_queue.h"
#include "freertos/FreeRTOS.h"
#include "freertos/queue.h"
#include "freertos/semphr.h"
#include "esp_log.h"
#include "esp_random.h"
#include <string.h>

#define MSG_QUEUE_LEN 8
#define MSG_MAX_LEN 64

static QueueHandle_t msg_queue = NULL;
static SemaphoreHandle_t queue_mutex = NULL;

static void send_task1(void *pvParameter) {
    int cnt = 1;
    char msg[MSG_MAX_LEN];
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
    char msg[MSG_MAX_LEN];
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

static void receive_task(void *pvParameter) {
    char msg[MSG_MAX_LEN];
    while (1) {
        if (msg_queue_receive(msg, sizeof(msg)) == pdPASS) {
            ESP_LOGI("UART", "Received: %s", msg);
        }
    }
}

void msg_queue_init(void) {
    msg_queue = xQueueCreate(MSG_QUEUE_LEN, MSG_MAX_LEN);
    queue_mutex = xSemaphoreCreateMutex();
    xTaskCreate(send_task1, "send_task1", 2048, NULL, 5, NULL);
    xTaskCreate(send_task2, "send_task2", 2048, NULL, 5, NULL);
    xTaskCreate(receive_task, "receive_task", 2048, NULL, 5, NULL);
}

int msg_queue_send(const char *msg) {
    if (xSemaphoreTake(queue_mutex, portMAX_DELAY)) {
        int ret = xQueueSend(msg_queue, msg, pdMS_TO_TICKS(100));
        xSemaphoreGive(queue_mutex);
        return ret;
    }
    return 0;
}

int msg_queue_receive(char *buf, size_t len) {
    if (xSemaphoreTake(queue_mutex, portMAX_DELAY)) {
        int ret = xQueueReceive(msg_queue, buf, pdMS_TO_TICKS(1000));
        xSemaphoreGive(queue_mutex);
        return ret;
    }
    return 0;
}
