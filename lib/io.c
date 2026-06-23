#include "types.h"
#include "io.h"
#include "asm.h"

void write_letter_to_framebuffer(uint8_t letter, uint8_t row, uint8_t col, uint8_t text_color, uint8_t bg_color) {
  volatile uint16_t *framebuffer = (volatile uint16_t*) FRAME_BUFFER;

  uint16_t letter_framebuffer = (0x00FF & letter);
  uint16_t bg_color_framebuffer = (0x000F & bg_color) << 12;
  uint16_t text_color_framebuffer = (0x00F & text_color) << 8;

  framebuffer[col + row*80] = letter_framebuffer | text_color_framebuffer | bg_color_framebuffer;
}

void move_cursor(uint16_t pos) {
  uint8_t pos_low_byte = pos & 0x00FF;
  uint8_t pos_high_byte = (pos >> 8) & 0x00FF;

  outb(CRTC_CMD_PORT, CURSOR_POS_HIGH_BYTE_CMD);
  outb(CRTC_DATA_PORT, pos_high_byte);
  outb(CRTC_CMD_PORT, CURSOR_POS_LOW_BYTE_CMD);
  outb(CRTC_DATA_PORT, pos_low_byte);
}

void scroll(uint16_t row) {
  uint16_t pos = 80*row;
  uint16_t pos_low_byte = pos & 0x00FF;
  uint16_t pos_high_byte = (pos >> 8) & 0x00FF;

  outb(CRTC_CMD_PORT, SCREEN_START_POS_HIGH_BYTE_CMD);
  outb(CRTC_DATA_PORT, pos_high_byte);
  outb(CRTC_CMD_PORT, SCREEN_START_POS_LOW_BYTE_CMD);
  outb(CRTC_DATA_PORT, pos_low_byte);
}

void write_letter_to_screen(const char c, uint16_t pos) {
  write_letter_to_framebuffer(c, 0, pos, WHITE, BLACK);
}

void write_to_screen(const char *buf, uint16_t len) {
  for (int i = 0; i < len; i++) {
    write_letter_to_framebuffer(buf[i], 0, i, WHITE, BLACK);
  }
  move_cursor(len);
}

void clear_screen(void) {
    for (int row = 0; row < 25; row++) {
      for (int col = 0; col < 80; col++) {
        write_letter_to_framebuffer(' ', row, col, WHITE, BLACK);
      }
    }
  }
