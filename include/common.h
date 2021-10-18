/* Include common headers in one file so that it's easier to import modules
 * that are used frequently. This will eliminate unnecessary lines of code
 * and repititious code.
 * 
 * Useful for headers that require the C Standard library.
 *   
 */

#ifndef _COMMON_H
#define _COMMON_H

/* When the adamantinw header is needed */
#include <adamantine/adamantine.h>

#include <string.h>
#include <macros.h>
#include <assert.h>
#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>

#ifndef SYSTEM_TYPES_DEFINED
#define SYSTEM_TYPES_DEFINED    1
#include <system/types.h>
#endif

#if !defined(__cplusplus)
#include <stdbool.h>
#endif

#endif
