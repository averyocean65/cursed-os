#ifndef H_FONT_DRAWING
#define H_FONT_DRAWING

#include "../string.h"

#include "fonts.h"
#include "../graphics.h"

void draw_char(struct limine_framebuffer *framebuffer, char character, unsigned char *font, int char_size, uint32_t color, uint16_t x, uint16_t y) {
    unsigned char *glyph;

    // Get the font glyph based on font and char_size
    glyph = font + (character * char_size);

    // Draw the character on the framebuffer at the specified position
    unsigned int row, col;
    for (row = 0; row < char_size; row++) {
        for (col = 0; col < char_size; col++) {
            if ((glyph[row] >> (char_size - 1 - col)) & 0x01) {
                // Set the pixel to white
                draw_pixel(framebuffer, x + col, y + row, color);
            }
        }
    }
}

void draw_string(struct limine_framebuffer *framebuffer, const char *str, unsigned char *font, int char_size, int char_spacing, uint32_t color, uint16_t x, uint16_t y) {
    unsigned int strLength = strlen(str);
    unsigned int charWidth = char_size;
    unsigned int charHeight = char_size;

    uint16_t cx = x;
    uint16_t cy = y;

    // Draw each character of the string
    for (unsigned int i = 0; i < strLength; i++) {
        char character = str[i];
        if(character == '\n') {
            cx = x;
            cy += charHeight;
            continue;
        }

        draw_char(framebuffer, character, font, char_size, color, cx, cy);

        // Move to the next character position with custom spacing
        cx += charWidth + char_spacing;
    }
}

void draw_string_8x16(struct limine_framebuffer *framebuffer, const char *str, uint32_t color, uint16_t x, uint16_t y) {
    draw_string(framebuffer, str, g_8x16_font, CHAR_SIZE_8x16, -8, color, x, y);
}

void draw_string_8x8(struct limine_framebuffer *framebuffer, const char *str, uint32_t color, uint16_t x, uint16_t y) {
    draw_string(framebuffer, str, g_8x8_font, CHAR_SIZE_8x8, 0, color, x, y);
}

#endif