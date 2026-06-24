#pragma once

#include "types.h"

#define COM1_BASE_ADDR                  0x3F8
#define COM2_BASE_ADDR                  0x2F8

#define SERIAL_DATA_PORT(addr)          (addr)
#define SERIAL_INTERRUPT_PORT(addr)     (addr + 1)
#define SERIAL_FIFO_CMD_PORT(addr)      (addr + 2)
#define SERIAL_LINE_CMD_PORT(addr)      (addr + 3)
#define SERIAL_MODEM_CMD_PORT(addr)     (addr + 4)
#define SERIAL_LINE_STATUS_PORT(addr)   (addr + 5)
#define SERIAL_MODEM_STATUS_PORT(addr)  (addr + 6)


void setup_serial(uint16_t com);
void serial_write_string(uint16_t com, const char *buf, uint32_t len);
void serial_write(uint16_t com, uint16_t data);
int8_t is_read_buffer_ready(uint16_t com);
char serial_read(uint16_t com);
