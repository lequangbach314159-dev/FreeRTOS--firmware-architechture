| Supported Targets | ESP32 | ESP32-C2 | ESP32-C3 | ESP32-C5 | ESP32-C6 | ESP32-C61 | ESP32-H2 | ESP32-H21 | ESP32-P4 | ESP32-S2 | ESP32-S3 |
| ----------------- | ----- | -------- | -------- | -------- | -------- | --------- | -------- | --------- | -------- | -------- | -------- |

## Overview

### Main Features
- UART communication (TX/RX)
- FreeRTOS multitasking
- Non-blocking UART handling
- Real-time task scheduling

### RTOS Concepts Demonstrated
- Task creation using `xTaskCreate()`
- Task delay using `vTaskDelay()`
- Concurrent execution of UART send and receive tasks
- Separation of communication logic into independent tasks

---

## How It Works

- **UART TX Task**
  - Periodically sends data through UART
  - Uses `uart_write_bytes()` to transmit messages
  - Runs continuously with a delay using `vTaskDelay()`

- **UART RX Task**
  - Listens for incoming UART data
  - Uses `uart_read_bytes()` to receive data
  - Prints received data to the serial monitor

Both tasks are scheduled by the **FreeRTOS kernel**, allowing simultaneous send and receive operations.


## How to Use Example

Before project configuration and build, be sure to set the correct chip target using `idf.py set-target <chip_name>`.

### Hardware 

* An ESP32 development board
* A USB cable for power supply and programming
* UART connection

See [Development Boards](https://www.espressif.com/en/products/devkits) for more information about it.

## Example Output

This output shows successful bidirectional UART communication handled by FreeRTOS tasks.

```text
ESP1 đã gửi: hello esp32
ESP2 nhận: hello esp32
ESP2 đã gửi lại cho ESP1: ESP2 đã nhận và gửi lại!
ESP1 đã gửi: hello esp32
ESP2 nhận: hello esp32
ESP2 đã gửi lại cho ESP1: ESP2 đã nhận và gửi lại!
```

## Applications

* UART communication with sensors
* ESP32 ↔ ESP32 communication
* ESP32 ↔ PC (Serial Monitor)
* Learning and practicing FreeRTOS multitasking

## Troubleshooting

* Check TX/RX wiring
* Ensure correct UART port and pins
* Verify baud rate settings
* Make sure both UART tasks are running
