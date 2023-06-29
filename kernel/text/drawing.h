#ifndef H_FONT_DRAWING
#define H_FONT_DRAWING

#include "../string.h"

#include "fonts.h"
#include "../graphics.h"

void draw_char(struct limine_framebuffer *framebuffer, char character, unsigned char *font, int char_size, uint16_t x, uint16_t y) {
    unsigned char *glyph;

    // Get the font glyph based on font and char_size
    glyph = font + (character * char_size);

    // Draw the character on the framebuffer at the specified position
    unsigned int row, col;
    for (row = 0; row < char_size; row++) {
        for (col = 0; col < char_size; col++) {
            if ((glyph[row] >> (char_size - 1 - col)) & 0x01) {
                // Set the pixel to white
                draw_pixel(framebuffer, x + col, y + row, 0xFFFFFFFF);
            }
        }
    }
}

void draw_string(struct limine_framebuffer *framebuffer, const char *str, unsigned char *font, int char_size, uint16_t x, uint16_t y) {
    unsigned int strLength = strlen(str);
    unsigned int charWidth = char_size;

    // Draw each character of the string
    for (unsigned int i = 0; i < strLength; i++) {
        char character = str[i];
        draw_char(framebuffer, character, font, char_size, x, y);

        // Move to the next character position
        x += charWidth;
    }
}

#endif