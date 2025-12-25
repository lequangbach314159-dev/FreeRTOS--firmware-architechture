#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/uart.h"

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

void esp2_task(void *pvParameter)
{
    uint8_t rx_data[64];
    const char *reply = "esp2 da nhan va gui lai!\r\n";
    while (1) {
        int len = uart_read_bytes(UART_PORT_NUM, rx_data, sizeof(rx_data)-1, pdMS_TO_TICKS(500));
        if (len > 0) {
            rx_data[len] = '\0';
            printf("ESP2 đã nhận: %s\n", rx_data);
            uart_write_bytes(UART_PORT_NUM, reply, strlen(reply));
            printf("ESP2 đã gửi lại cho ESP1: %s\n", reply);
        }
        vTaskDelay(pdMS_TO_TICKS(100));
    }
}

void app_main(void)
{
    init_uart();
    xTaskCreate(esp2_task, "esp2_task", 2048, NULL, 5, NULL);
}
