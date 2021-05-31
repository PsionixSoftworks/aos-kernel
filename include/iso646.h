#ifndef _ADAMANTINE_ISO646_H
#define _ADAMANTINE_ISO646_H       1

/* Check if 'OPS' is defined elsewhere */
#ifndef OPS
#define OPS												// If not, define it
#define and         &&									// And
#define and_eq      &=									// And equals
#define bitand      &									// Bitwise and
#define or          ||									// Or
#define or_eq       |=									// Or equals
#define bit_or      |									// Bitwise or
#define xor         ^									// Exclusive or
#define xor_eq      ^=									// Exclusive or equals
#define not         !									// Not
#define not_eq      !=									// Not equals
#define compl       ~									// ??
#endif	// !OPS
#endif  // !_ADAMANTINE_ISO646_H
