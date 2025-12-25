#pragma once
void msg_queue_init(void);
int msg_queue_send(const char *msg);
int msg_queue_receive(char *buf, size_t len);
