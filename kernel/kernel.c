#include <stdint.h>
#include <stddef.h>
#include <limine.h>

#include "graphics.h"

static volatile struct limine_framebuffer_request framebuffer_request = {
    .id = LIMINE_FRAMEBUFFER_REQUEST,
    .revision = 0
};

static void hcf(void) {
    asm("cli");

    for (;;) {
        asm ("hlt");
    }
}

// The following will be our kernel's entry point.
void _start(void) {
    // Ensure we got a framebuffer.
    if (framebuffer_request.response == NULL
     || framebuffer_request.response->framebuffer_count < 1) {
        hcf();
    }

    // Fetch the first framebuffer.
    struct limine_framebuffer *framebuffer = framebuffer_request.response->framebuffers[0];

    // Clear the screen
    clear_screen(framebuffer, 0x000000);
    
    // We're done, just hang...
    hcf();
}