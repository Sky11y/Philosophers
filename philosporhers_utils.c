#include "philosophers.h"

int	philo_atoi(char *nbr)
{
	int	ret;
	int	i;

	i = 0;
	ret = 0;
	while (nbr[i])
	{
		ret = ret * 10 + (int)(nbr[i] - '0');
		i++;
	}
	return (ret);
}

int	check_input(int argc, char **argv)
{
	short	i;
	short	j;

	i = 1;
	while (i < argc)
	{
		if (argv[i][0] == '\0' || argv[i][0] == '0')
			return (-1);
		j = 0;
		while (argv[i][j])
		{
			if (argv[i][j] > '9' || argv[i][j] < '0')
				return (-1);
			j++;
		}
		i++;
	}
	return (0);
}

