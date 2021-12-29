#include <Arduino.h>

void wire_setup(bool is_master, int slave_addr);
void wire_sendMsg(uint16_t value, int slave_addr);
void wire_registerCallback(void (*callback)(uint16_t value));