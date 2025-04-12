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
	pthread_t	*philo;
	size_t		i;

	philo = malloc(sizeof(pthread_t) * master->total_philos);
	if (!philo)
		return (philo_error(e_memory));
	i = 0;
	while (i < master->total_philos)
	{
		if (pthread_create(&philo[i], NULL, create_philo, (void *)master))
			return (philo_error(e_create_philo));
		i++;
	}
	i = 0;
	while (i < master->total_philos)
	{
		if (pthread_join(philo[i], NULL))
			return (philo_error(e_join));
		i++;
	}
	free(philo);
	return (0);
}

static int	init_locks(t_master *master)
{
	int	i;

	i = 0;
	if (pthreat_mutex_init(master->eat_lock, NULL))
		return (philo_error(e_lock);
	if (pthreat_mutex_init(master->sleep_lock, NULL))
		return (philo_error(e_lock);
	if (pthreat_mutex_init(master->die_lock, NULL))
		return (philo_error(e_lock);
	while (master->forks[i])
	{
		if (pthread_mutex_init(master->forks[i++], NULL))
			return (philo_error(e_lock));
	}
	return (0);
}

static int	init_master(t_master *master, char **argv)
{
	int i;

	i = 0;
	master->total_philos = philo_atoi(*argv++);
	master->philo_ids = 1;
	master->is_dead = false;
	master->time_to_die = philo_atoi(*argv++);
	master->time_to_eat = philo_atoi(*argv++);
	master->time_to_sleep = philo_atoi(*argv);
	if (!master->total_philos || !master->time_to_die
			|| !master->time_to_eat || !master->time_to_sleep)
		return (philo_error(e_create_master));
	master->forks = malloc(sizeof(pthread_mutex_t) * (master->total_philos));
	if (!master->forks)
		return (philo_error(e_memory));
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
		return (EXIT_FAILURE);
	if (init_locks(&master))
		return (EXIT_FAILURE);
	philosophers(&master);
	printf("%d %d %d %d\n", master.total_philos,  master.time_to_die, master.time_to_eat, master.time_to_sleep);
	free(master.forks);
	return (0);
}
