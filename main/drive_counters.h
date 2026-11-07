#pragma once
#include "ssd1681_fast.h"

/* DRIVE_PLANES bit planes count pulses (up to 2^planes - 1) independently for 32
 * pixels at once. Four planes: internal SRAM 25 KB, including the target image;
 * each extra plane adds 5 KB. */
#ifndef DRIVE_PLANES
#define DRIVE_PLANES 4
#endif
#define DRIVE_WORDS (SSD1681_FRAME_BYTES / sizeof(uint32_t))
typedef struct {
    uint32_t target[DRIVE_WORDS], count[DRIVE_PLANES][DRIVE_WORDS];
    unsigned pending_pixels;
} drive_counters_t;

void drive_counters_seed(drive_counters_t *c, const uint8_t *clean);
unsigned drive_counters_prepare(drive_counters_t *c, const uint8_t *target,
                               unsigned black_pulses, unsigned white_pulses,
                               uint8_t *black, uint8_t *white);
/* Consume only successfully delivered masks, before the next prepare. */
void drive_counters_complete(drive_counters_t *c, const uint8_t *black, const uint8_t *white);
