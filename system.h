#ifndef _system_h
#define _system_h
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif
uint32_t system_ticks();
void setup();
void loop();
#ifdef __cplusplus
}
#endif
#endif
