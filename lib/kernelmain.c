#include "serial.h"
#include "types.h"
#include "asm.h"
#include "io.h"

int kernelmain() {
  clear_screen_and_draw();

  clear_screen();

  setup_serial(COM1_BASE_ADDR);

  uint32_t position = 0;
  while(1) {
    char input = serial_read(COM1_BASE_ADDR);
    write_letter_to_screen(input, position);
    move_cursor(position + 1);
    position++;
  }
  return 0;
}
