#include "libft.h"
#include <ctype.h>
#include <stdlib.h>

double	ft_atof(const char *str)
{
	double	result;
	double	fraction;
	int		sign;
	int		i;
	double	divisor;

	result = 0.0;
	fraction = 0.0;
	sign = 1;
	i = 0;
	while (isspace(str[i]))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (isdigit(str[i]))
	{
		result = result * 10 + (str[i] - '0');
		i++;
	}
	if (str[i] == '.')
	{
		i++;
		divisor = 10.0;
		while (isdigit(str[i]))
		{
			fraction += (str[i] - '0') / divisor;
			divisor *= 10.0;
			i++;
		}
	}
	return (sign * (result + fraction));
}
