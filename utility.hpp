/**
 * @file utility.hpp
 * @brief Contains a few utility macros and typedefs.
 */

#ifndef QZ2304_UTILITY
#define QZ2304_UTILITY

#include <HCSR04.h>

#define REPEAT(n) for (uint8_t __i##__LINE__ = 0; __i##__LINE__ < n; __i##__LINE__++)
#define NONE -1

typedef UltraSonicDistanceSensor ultrasonic_sensor;

#endif  // QZ2304_UTILITY