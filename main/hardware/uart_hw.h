#pragma once
void uart_hw_init(void);
void uart_hw_send(const char *msg);
int uart_hw_receive(char *buf, size_t len);
