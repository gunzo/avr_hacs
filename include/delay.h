#include <stdint.h>

#ifndef MICRO_SEC_CLK_DIV 
/**
 * @brief Divisor for the clock to get a microsecond.
 *
 * This value contains the divisor by witch the system clock must be divided to
 * get one micorsecond. The default value is 10, but can be overritten by the
 * user to adapt to different conditions. Overriding is done by redifining
 * MICRO_SEC_CLK_DIV with the desiered value.
 *
 */
#define MICRO_SEC_CLK_DIV 10 
#endif
