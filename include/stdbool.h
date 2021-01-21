#ifndef _AOS_STDBOOL_H
#define _AOS_STDBOOL_H      1

#ifndef BOOLEAN_OPS
#ifndef FALSE
#define FALSE								0
#endif

#ifndef TRUE
#define TRUE								1
#endif
#endif

#if !defined(__cplusplus)
typedef enum { false, true } bool;
#endif

#endif  // !_AOS_STDBOOL_H
