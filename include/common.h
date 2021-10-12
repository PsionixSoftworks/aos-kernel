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
#ifdef _USES_ADAMANTINE
#include <adamantine/adamantine.h>
#endif

/* When memory and string functions are needed */
#ifdef _USES_STRING
#include <string.h>
#endif

#include <macros.h>
#include <assert.h>
#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>

#if !defined(__cplusplus)
#include <stdbool.h>
#endif

#endif
