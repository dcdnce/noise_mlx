#include "noise.h"

float	lerp(const float lo, const float hi, const float t) {
	return (lo * (1 - t) + hi * t);
}

int	ft_atoi(const char *nptr)
{
	int	nb;
	int	sign;
	int	i;

	nb = 0;
	sign = 1;
	i = 0;
	while (nptr[i] == 32 || nptr[i] == '\t' || nptr[i] == '\n'
		|| nptr[i] == '\v' || nptr[i] == '\f' || nptr[i] == '\r')
		i++;
	if (nptr[i] == '-')
	{
		sign = -1;
		i++;
	}
	else if (nptr[i] == '+')
		i++;
	while (nptr[i] && (nptr[i] >= '0' && nptr[i] <= '9'))
	{
		nb *= 10;
		nb += nptr[i] - '0';
		i++;
	}
	return (nb * sign);
}
