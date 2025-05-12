/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpiensal <jpiensal@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 10:27:43 by jpiensal          #+#    #+#             */
/*   Updated: 2025/05/12 11:35:12 by jpiensal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static int	philosophers(t_master *master)
{
	pthread_t	*philo;

	philo = malloc(sizeof(pthread_t) * (master->total_philos + 1));
	if (!philo)
		return (philo_error(master, e_memory));
	if (create_threads(master, philo))
		return (-1);
	master->begin_program = get_current_time(master);
	if (!master->begin_program)
		return (philo_error(master, e_gettime));
	if (join_threads(master, philo))
		return (-1);
	free(philo);
	return (0);
}

static t_philo	init_philo(t_master *master)
{
	static int	id = 1;
	t_philo		philo;

	philo.id = id++;
	philo.eat_count = master->times_to_eat;
	philo.eaten = 0;
	philo.is_eating = false;
	return (philo);
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
	master->philo_arr = malloc(sizeof(t_philo) * (master->total_philos));
	if (!master->philo_arr)
		return (philo_error(master, e_memory));
	master->is_eaten = master->total_philos;
	master->philos_started = 0;
	master->is_dead = false;
	master->error = false;
	master->is_finished = false;
	master->begin_program = 0;
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
	int			i;

	if (input_check(--argc, ++argv))
		return (philo_error(&master, e_input));
	if (init_master(&master, argc, argv))
		return (EXIT_FAILURE);
	if (init_locks(&master))
		return (EXIT_FAILURE);
	i = 0;
	while (i < master.total_philos)
		master.philo_arr[i++] = init_philo(&master);
	exit_status = philosophers(&master);
	if (destroy_locks(&master))
	{
		free(master.forks);
		return (EXIT_FAILURE);
	}
	free(master.forks);
	free(master.philo_arr);
	return (exit_status);
}
