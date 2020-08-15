#include "test.h"

.global test_func
.type test_func @function
test_func:
    mov $TESTER, %eax
    add $10, %eax
    ret
