/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpiensal <jpiensal@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 10:27:43 by jpiensal          #+#    #+#             */
/*   Updated: 2025/04/29 15:56:34 by jpiensal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static int	init_locks(t_master *master)
{
	int	i;

	i = 0;
	if (pthread_mutex_init(&master->print_lock, NULL))
		return (philo_error(master, e_lock));
	if (pthread_mutex_init(&master->init_lock, NULL))
		return (philo_error(master, e_lock));
	master->forks = malloc(sizeof(pthread_mutex_t) * (master->total_philos));
	if (!master->forks)
		return (philo_error(master, e_memory));
	while (i < master->total_philos)
	{
		if (pthread_mutex_init(&master->forks[i++], NULL))
			return (philo_error(master, e_lock));
	}
	return (0);
}

static int	destroy_locks(t_master *master)
{
	int	i;

	i = 0;
	if (pthread_mutex_destroy(&master->print_lock))
		return (philo_error(master, e_unlock));
	if (pthread_mutex_destroy(&master->init_lock))
		return (philo_error(master, e_unlock));
	while (i < master->total_philos)
	{
		if (pthread_mutex_destroy(&master->forks[i++]))
		{
			printf("forklock, %d\n", i);
			return (philo_error(master, e_unlock));
		}
	}
	return (0);
}

static int	init_master(t_master *master, int argc, char **argv)
{
	master->total_philos = philo_atoi(*argv++);
	master->time_to_die = philo_atoi(*argv++);
	master->time_to_eat = philo_atoi(*argv++);
	master->time_to_sleep = philo_atoi(*argv++);
	if (argc == 5)
		master->times_to_eat = philo_atoi(*argv);
	else
		master->times_to_eat = -1;
	if (!master->total_philos || !master->time_to_die || !master->time_to_eat
		|| !master->time_to_sleep || !master->times_to_eat)
		return (philo_error(master, e_create_master));
	if (master->time_to_eat + master->time_to_sleep > master->time_to_die)
		master->time_to_think = 0;
	else
		master->time_to_think = (master->time_to_die
				- (master->time_to_eat + master->time_to_sleep)) / 2;
	master->philo_ids = 1;
	master->philo_arr = malloc(sizeof(t_philo) * (master->total_philos + 1));
	if (!master->philo_arr)
		return (philo_error(master, e_memory));
	master->philo_arr[master->total_philos] = NULL;
	master->begin_program = 0;
	master->is_dead = false;
	master->is_eaten = false;
	master->error = false;
	master->observe = false;
	return (0);
}

static int	input_check(int argc, char **argv)
{
	size_t	i;

	if (argc != 4 && argc != 5)
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
	int			exit_status;

	if (input_check(--argc, ++argv))
		return (philo_error(&master, e_input));
	if (init_master(&master, argc, argv))
		return (EXIT_FAILURE);
	if (init_locks(&master))
		return (EXIT_FAILURE);
	exit_status = philosophers(&master, 0);
	if (destroy_locks(&master))
	{
		free(master.forks);
		return (EXIT_FAILURE);
	}
	free(master.forks);
	free(master.philo_arr);
	return (exit_status);
}
