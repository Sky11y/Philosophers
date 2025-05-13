/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpiensal <jpiensal@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 11:50:58 by jpiensal          #+#    #+#             */
/*   Updated: 2025/05/13 12:45:53 by jpiensal         ###   ########.fr       */
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
	philo.time_to_die = master->time_to_die;
	philo.time_to_eat = master->time_to_eat;
	philo.time_to_sleep = master->time_to_sleep;
	philo.is_eating = false;
	return (philo);
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
