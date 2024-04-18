#ifndef _system_h
#define _system_h
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif
uint32_t system_ticks();
void system_set_hse_72mhz_clock();
void system_init();
#ifdef __cplusplus
}
#endif
#endif
