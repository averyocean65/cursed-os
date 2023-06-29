#include <stdint.h>
#include <stddef.h>
#include <limine.h>

#include "graphics.h"
#include "text/drawing.h"

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

    // Title
    char* title = "The CURSED OS";
    draw_string_8x16(framebuffer, title, 0xFFFFFF, framebuffer->width/2 - (strlen(title)*8), 0);

    // Quotes
    draw_string_8x16(framebuffer, "nya meow mrrp :3\n-rooot :3", 0xF900AA, 50, 50);
    draw_string_8x16(framebuffer, "HANDS OFF MY BBG\n-GangstaCat", 0x35CBC8, 400, 70);
    draw_string_8x16(framebuffer, "I am the bbg in question\n-Loafie", 0xA74B1D, 486, 70+64);
    draw_string_8x16(framebuffer, "Do you want a banana? Peel it down and go mmmmmmm\n-banana song, a cult classic", 0xE4CC22, 400, 200);
    draw_string_8x16(framebuffer, "KILL YOURSELF\n-Avery/Winter", 0xCE3351, 172, 200);
    
    // We're done, just hang...
    hcf();
}