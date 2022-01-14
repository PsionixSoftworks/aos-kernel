#include <string.h>
#include <math/math-util.h>

static void
reverse(char *str, int len)
{
	int i = 0, j = len - 1, tmp;
	while (i < j)
	{
		tmp = str[i];
		str[i] = str[j];
		str[j] = tmp;
		i++;
		j--;
	}
}

static int
int_to_str(int x, char str[], int d)
{
	int i = 0;
	while (x)
	{
		str[i++] = (x % 10) + '0';
		x = x / 10;
	}

	while (i < d)
		str[i++] = '0';
	
	reverse(str, i);
	str[i] = '\0';
	return i;
}

void
ftoa(double n, char *res, int after)
{
	int ipart = (int)n;

	double fpart = n - (double)ipart;

	int i = int_to_str(ipart, res, 0);

	if (after != 0)
	{
		res[i] = '.';
		fpart = fpart * pow(10, after);

		int_to_str((int)fpart, res + i + 1, after);
	}
}
