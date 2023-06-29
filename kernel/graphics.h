#ifndef H_GRAPHICS
#define H_GRAPHICS

#include <limine.h>
#include <stdint.h>

#include "math.h"

uint32_t make_color(uint8_t r, uint8_t g, uint8_t b) {
    uint32_t color = 0;
    color |= ((uint32_t)r) << 16; // Shift red value to the leftmost 8 bits
    color |= ((uint32_t)g) << 8;  // Shift green value to the middle 8 bits
    color |= (uint32_t)b;         // Assign blue value to the rightmost 8 bits

    return color;
}


void draw_pixel(struct limine_framebuffer *framebuffer, uint16_t x, uint16_t y, uint32_t color) {
    uint32_t* fb_ptr = framebuffer->address;
    fb_ptr[x + (y * framebuffer->width)] = color;
}

void draw_line(struct limine_framebuffer *framebuffer, uint16_t sx, uint16_t sy, uint16_t ex, uint16_t ey, uint32_t color) {
    int16_t dx = abs(ex - sx); // Calculate the absolute difference in x-coordinates
    int16_t dy = abs(ey - sy); // Calculate the absolute difference in y-coordinates
    int16_t sx2 = (sx < ex) ? 1 : -1; // Determine the sign of the x-increment
    int16_t sy2 = (sy < ey) ? 1 : -1; // Determine the sign of the y-increment
    int16_t err = (dx > dy ? dx : -dy) / 2; // Determine the initial error value

    while (1) {
        draw_pixel(framebuffer, sx, sy, color); // Plot the pixel at the current coordinates

        if (sx == ex && sy == ey) // Check if the end point has been reached
            break;

        int16_t e2 = err; // Store the previous error value

        if (e2 > -dx) {
            err -= dy; // Update the error value based on the difference in y-coordinates
            sx += sx2; // Increment the x-coordinate
        }

        if (e2 < dy) {
            err += dx; // Update the error value based on the difference in x-coordinates
            sy += sy2; // Increment the y-coordinate
        }
    }
}

void draw_rect(struct limine_framebuffer *framebuffer, uint16_t x, uint16_t y, uint16_t width, uint16_t height, uint32_t color) {
    draw_line(framebuffer, x, y, x + width - 1, y, color); // Top side
    draw_line(framebuffer, x, y, x, y + height - 1, color); // Left side
    draw_line(framebuffer, x + width - 1, y, x + width - 1, y + height - 1, color); // Right side
    draw_line(framebuffer, x, y + height - 1, x + width - 1, y + height - 1, color); // Bottom side
}

void draw_rect_filled(struct limine_framebuffer *framebuffer, uint16_t x, uint16_t y, uint16_t width, uint16_t height, uint32_t color) {
    // Y
    for(uint16_t cy = y; cy < y + height; cy++) {
        
        // X
        for(uint16_t cx = x; cx < x + width; cx++) {
            draw_pixel(framebuffer, cx, cy, color);
        }
    }
}

void draw_rect_filled_outline(struct limine_framebuffer *framebuffer, uint16_t x, uint16_t y, uint16_t width, uint16_t height, uint32_t outlineColor, uint32_t innerColor) {
    draw_rect_filled(framebuffer, x, y, width, height, innerColor);
    draw_rect       (framebuffer, x, y, width, height, outlineColor);
}

void clear_screen(struct limine_framebuffer *framebuffer, uint32_t color) {
    draw_rect_filled(framebuffer, 0, 0, framebuffer->width, framebuffer->height, color);
}

#endif