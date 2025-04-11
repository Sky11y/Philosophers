/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpiensal <jpiensal@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 10:27:43 by jpiensal          #+#    #+#             */
/*   Updated: 2025/04/11 17:37:27 by jpiensal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static int	philosophers(t_master *master)
{
	pthread_t	philo;
	
	if (pthread_create(&philo, NULL, create_philo, (void *)master))
		return (philo_error(e_create_philo));
	if (pthread_join(philo, NULL))
		return (philo_error(e_join));
	return (0);
}

static int	init_master(t_master *master, char **argv)
{
	master->philos = philo_atoi(*argv++);
	master->forks = master->philos + 1;
	master->time_to_die = philo_atoi(*argv++);
	master->time_to_eat = philo_atoi(*argv++);
	master->time_to_sleep = philo_atoi(*argv);
	if (!master->philos || !master->time_to_die
			|| !master->time_to_eat || !master->time_to_sleep)
		return (1);
	return (0);
}

static int	input_check(int	argc, char **argv)
{
	size_t	i;

	if (argc != 4)
		return (1);
	while (*argv)
	{
		i = 0;
		while ((*argv)[i])
		{
			if ((*argv)[i] >= '0' && (*argv)[i] <= '9')
				i++;
			else
				return (1);
		}
		argv++;
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_master	master;

	if (input_check(--argc, ++argv))
		return (philo_error(e_input));
	if (init_master(&master, argv))
		return (philo_error(e_input));
	philosophers(&master);
	printf("%d %d %d %d %d\n", master.philos, master.forks, master.time_to_die, master.time_to_eat, master.time_to_sleep);
	return (0);
}
