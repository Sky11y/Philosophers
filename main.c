/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpiensal <jpiensal@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 10:27:43 by jpiensal          #+#    #+#             */
/*   Updated: 2025/05/14 11:17:18 by jpiensal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static int	philosophers(t_master *master)
{
	if (create_threads(master))
		return (-1);
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
