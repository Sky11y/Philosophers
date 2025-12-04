/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpiensal <jpiensal@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 11:50:58 by jpiensal          #+#    #+#             */
/*   Updated: 2025/05/20 12:40:47 by jpiensal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

t_philo	init_philo(t_master *master)
{
	static int	id = 1;
	t_philo		philo;

	philo.data = master;
	philo.thread = 0;
	philo.id = id++;
	if (philo.id == master->total_philos)
		philo.r_fork = 0;
	else
		philo.r_fork = philo.id;
	philo.l_fork = philo.id - 1;
	philo.eat_count = master->times_to_eat;
	philo.eaten = 0;
	return (philo);
}

static int	init_thinking_time(t_master *data)
{
	if (data->total_philos == 0)
		return (1);
	if (data->time_to_die == 0)
		return (1);
	if (data->time_to_eat == 0)
		return (1);
	if (data->time_to_sleep == 0)
		return (1);
	if (data->times_to_eat == 0)
		return (1);
	if (data->time_to_sleep + data->time_to_eat < data->time_to_die)
	{
		data->time_to_think = (data->time_to_die
				- (data->time_to_sleep + data->time_to_eat)) / 2;
	}
	else
		data->time_to_think = 0;
	return (0);
}

int	init_master(t_master *master, int argc, char **argv)
{
	master->total_philos = philo_atoi(*argv++);
	master->time_to_die = philo_atoi(*argv++);
	master->time_to_eat = philo_atoi(*argv++);
	master->time_to_sleep = philo_atoi(*argv++);
	if (argc == 5)
		master->times_to_eat = philo_atoi(*argv);
	else
		master->times_to_eat = -1;
	if (init_thinking_time(master))
		return (philo_error(master, e_create_master));
	master->philo_arr = malloc(sizeof(t_philo) * (master->total_philos));
	if (!master->philo_arr)
		return (philo_error(master, e_memory));
	master->is_eaten = master->total_philos;
	master->philos_started = 0;
	master->is_dead = false;
	master->error = false;
	master->begin_program = 0;
	return (0);
}
