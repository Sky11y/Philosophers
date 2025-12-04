/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpiensal <jpiensal@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 10:27:43 by jpiensal          #+#    #+#             */
/*   Updated: 2025/05/22 16:31:07 by jpiensal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static int	clean_up(t_master *master, int exit_value);

static int	philosophers(t_master *master)
{
	if (create_threads(master))
		return (-1);
	return (0);
}

static int	input_check(int argc, char **argv)
{
	size_t	i;

	if (argc < 4 || argc > 5)
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
		return (1);
	i = 0;
	while (i < master.total_philos)
		master.philo_arr[i++] = init_philo(&master);
	if (init_locks(&master, 0))
		return (clean_up(&master, 2));
	exit_status = philosophers(&master);
	if (destroy_locks(&master))
		return (clean_up(&master, 3));
	clean_up(&master, 0);
	return (exit_status);
}

static int	clean_up(t_master *master, int exit_value)
{
	if (master->philo_arr)
		free(master->philo_arr);
	if (master->forks)
		free(master->forks);
	return (exit_value);
}
