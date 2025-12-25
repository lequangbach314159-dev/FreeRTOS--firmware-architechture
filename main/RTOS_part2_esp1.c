#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/uart.h"
#include "freertos/queue.h"
#include "freertos/semphr.h"

#define UART_PORT_NUM      UART_NUM_1
#define UART_TX_PIN        17
#define UART_RX_PIN        16
#define UART_BAUD_RATE     115200
#define UART_BUF_SIZE      1024

static void init_uart(void)
{
    const uart_config_t uart_config = {
        .baud_rate = UART_BAUD_RATE,
        .data_bits = UART_DATA_8_BITS,
        .parity    = UART_PARITY_DISABLE,
        .stop_bits = UART_STOP_BITS_1,
        .flow_ctrl = UART_HW_FLOWCTRL_DISABLE
    };
    uart_driver_install(UART_PORT_NUM, UART_BUF_SIZE, UART_BUF_SIZE, 0, NULL, 0);
    uart_param_config(UART_PORT_NUM, &uart_config);
    uart_set_pin(UART_PORT_NUM, UART_TX_PIN, UART_RX_PIN, UART_PIN_NO_CHANGE, UART_PIN_NO_CHANGE);
}

void esp1_task(void *pvParameter)
{
    const char *msg = "hello esp32\r\n";
    uint8_t rx_data[64];
    while (1) {
        uart_write_bytes(UART_PORT_NUM, msg, strlen(msg));
        printf("ESP1 đã gửi: %s\n", msg);
        int timeout = 2000; // ms
        int elapsed = 0;
        int received = 0;
        while (elapsed < timeout) {
            int len = uart_read_bytes(UART_PORT_NUM, rx_data, sizeof(rx_data)-1, pdMS_TO_TICKS(100));
            if (len > 0) {
                rx_data[len] = '\0';
                printf("ESP1 nhận phản hồi: %s\n", rx_data);
                received = 1;
                break;
            }
            elapsed += 100;
        }
        if (!received) {
            printf("ESP1: Timeout không nhận được phản hồi!\n");
        }
        vTaskDelay(pdMS_TO_TICKS(3000));
    }
}

void esp2_task(void *pvParameter)
{
    uint8_t rx_data[64];
    while (1) {
        int len = uart_read_bytes(UART_PORT_NUM, rx_data, sizeof(rx_data)-1, pdMS_TO_TICKS(1000));
        if (len > 0) {
            rx_data[len] = '\0';
            printf("ESP2 nhận: %s\n", rx_data);
            const char *response = "hi esp1\r\n";
            uart_write_bytes(UART_PORT_NUM, response, strlen(response));
            printf("ESP2 đã gửi phản hồi: %s\n", response);
        }
        vTaskDelay(pdMS_TO_TICKS(100));
    }
}

void app_main(void)
{
    init_uart();
    xTaskCreate(esp1_task, "esp1_task", 2048, NULL, 5, NULL);
    xTaskCreate(esp2_task, "esp2_task", 2048, NULL, 5, NULL);
}
