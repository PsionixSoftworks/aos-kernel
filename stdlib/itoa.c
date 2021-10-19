#include <stdlib.h>

/* Convert integer to string internally */
static void 
xtoa(unsigned long _val, char *_buf, unsigned _radix, int _negative) {
    char *p;
    char *firstdig;
    char temp;
    unsigned dig_val;

    p = _buf;

    if (_negative) {
        // Negative, so output '-' and negate
        *p++ = '-';
        _val = (unsigned long)(-(long) _val);
    }

    // Save pointer to first digit
    firstdig = p;

    do {
        dig_val = (unsigned) (_val % _radix);
        _val /= _radix;

        // Convert to ascii and store
        if (dig_val > 9) {
            *p++ = (char) (dig_val - 10 + 'a');
        } else {
            *p++ = (char) (dig_val + '0');
        }
    } while (_val > 0);

    // We now have the digit of the number in the buffer, but in reverse
    // order.  Thus we reverse them now.

    *p-- = '\0';
    do {
        temp = *p;
        *p = *firstdig;
        *firstdig = temp;
        p--;
        firstdig++;
    } while (firstdig < p);
}

/* Convert integer to string */
char *
itoa(int _val, char *_buf, int _radix) {
    if (_radix == 10 && _val < 0) {
        xtoa((unsigned long) _val, _buf, _radix, 1);
    } else {
        xtoa((unsigned long)(unsigned int) _val, _buf, _radix, 0);
    }
    return _buf;
}
