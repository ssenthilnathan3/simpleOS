#include "types.h"
#include "serial.h"
#include "asm.h"

void setup_serial(uint16_t com) {
  // disable interrupts
  outb(SERIAL_INTERRUPT_PORT(com), 0x00);

  // set baudrate with divisor of 1
  uint16_t divisor = 1;

  outb(SERIAL_LINE_CMD_PORT(com), 0x80);
  outb(SERIAL_DATA_PORT(com), divisor & 0x00FF);
  outb(SERIAL_DATA_PORT(com) + 1, (divisor >> 8) & 0x00FF);

  // configure line for frame buffer layout of 8N1
  outb(SERIAL_LINE_CMD_PORT(com), 0x03);

  // configure fifo
  outb(SERIAL_FIFO_CMD_PORT(com), 0xC7);

  // configure modem
  outb(SERIAL_MODEM_CMD_PORT(com), 0x03);
}

int8_t is_transmit_buffer_empty(uint16_t com) {
  return (inb(SERIAL_LINE_CMD_PORT(com) & 0x20) == 0x20);
}

int8_t is_read_buffer_ready(uint16_t com) {
  return (inb(SERIAL_LINE_STATUS_PORT(com)) & 0x01) == 0x01;
}

char serial_read(uint16_t com) {
    while (!is_read_buffer_ready(com)) {}
    return inb(SERIAL_DATA_PORT(com));
}

void serial_write(uint16_t com, uint16_t data) {
  while (is_transmit_buffer_empty(com)) {}
  outb(SERIAL_DATA_PORT(com), data);
}

void serial_write_string(uint16_t com, const char *buf, uint32_t len) {
  for (uint32_t i = 0; i < len; i++) {
    serial_write(com, buf[i]);
  }
}
