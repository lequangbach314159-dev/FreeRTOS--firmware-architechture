#include "uart_hw.h"
#include "driver/uart.h"
#include <string.h>

#define UART_PORT_NUM      UART_NUM_1
#define UART_TX_PIN        17
#define UART_RX_PIN        16
#define UART_BAUD_RATE     115200

static void uart_hw_config(void) {
    const uart_config_t uart_config = {
        .baud_rate = UART_BAUD_RATE,
        .data_bits = UART_DATA_8_BITS,
        .parity    = UART_PARITY_DISABLE,
        .stop_bits = UART_STOP_BITS_1,
        .flow_ctrl = UART_HW_FLOWCTRL_DISABLE
    };
    uart_driver_install(UART_PORT_NUM, 1024, 1024, 0, NULL, 0);
    uart_param_config(UART_PORT_NUM, &uart_config);
    uart_set_pin(UART_PORT_NUM, UART_TX_PIN, UART_RX_PIN, UART_PIN_NO_CHANGE, UART_PIN_NO_CHANGE);
}

void uart_hw_init(void) {
    uart_hw_config();
}

void uart_hw_send(const char *msg) {
    uart_write_bytes(UART_PORT_NUM, msg, strlen(msg));
}

int uart_hw_receive(char *buf, size_t len) {
    return uart_read_bytes(UART_PORT_NUM, (uint8_t *)buf, len, pdMS_TO_TICKS(100));
}
