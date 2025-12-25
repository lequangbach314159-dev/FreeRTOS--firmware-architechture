#include "receive_task.h"
#include "service/msg_queue.h"
#include "hardware/uart_hw.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"

static void receive_task(void *pvParameter) {
    char msg[64];
    while (1) {
        if (msg_queue_receive(msg, sizeof(msg)) == pdPASS) {
            uart_hw_send(msg); // gửi ra UART nếu cần
            ESP_LOGI("UART", "Received: %s", msg);
        }
    }
}

void receive_task_start(void) {
    xTaskCreate(receive_task, "receive_task", 2048, NULL, 5, NULL);
}
