#ifndef _ADAMANTINE_STDDEF_H
#define _ADAMANTINE_STDDEF_H       1

/* Check if 'NULL' was previously defined */
#ifndef NULL
#ifdef __cplusplus							// If it wasn't and we're using C
#define NULL		0						// just define it as '0'
#else										// otherwise,
#define NULL			((void *)0)			// define it as a null void ptr
#endif
#endif

#endif  // !_ADAMANTINE_STDDEF_H
