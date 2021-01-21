#include <stdlib.h>

static void 
xtoa(unsigned long val, char *buf, unsigned radix, int negative) {
    char *p;
    char *firstdig;
    char temp;
    unsigned digval;

    p = buf;

    if (negative) {
        // Negative, so output '-' and negate
        *p++ = '-';
        val = (unsigned long)(-(long) val);
    }

    // Save pointer to first digit
    firstdig = p;

    do {
        digval = (unsigned) (val % radix);
        val /= radix;

        // Convert to ascii and store
        if (digval > 9) {
            *p++ = (char) (digval - 10 + 'a');
        } else {
            *p++ = (char) (digval + '0');
        }
    } while (val > 0);

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

char *
itoa(int val, char *buf, int radix) {
    if (radix == 10 && val < 0) {
        xtoa((unsigned long) val, buf, radix, 1);
    } else {
        xtoa((unsigned long)(unsigned int) val, buf, radix, 0);
    }
    return buf;
}

/*
char *
itoa(int value, char * str, int base) 
{
    char *rc;
    char *ptr;
    char *low;
    // Check for supported base.
    if ((base < 2) || (base > 36)) 
    {
        *str = '\0';
        return str;
    }
    rc = ptr = str;
    
	// Set '-' for negative decimals.
    if ((value < 0) && (base == 10))
    {
        *ptr++ = '-';
    }
	
    // Remember where the numbers start.
    low = ptr;
	
    // The actual conversion.
    do 
    {
        // Modulo is negative for negative value. This trick makes abs() unnecessary.
        *ptr++ = "zyxwvutsrqponmlkjihgfedcba9876543210123456789abcdefghijklmnopqrstuvwxyz"[35 + value % base];
        value /= base;
    } while ( value );
	
    // Terminating the char *
    *ptr-- = '\0';
	
    // Invert the numbers.
    while (low < ptr) 
    {
        char tmp = *low;
        *low++ = *ptr;
        *ptr-- = tmp;
    }
    return (rc);
}
*/