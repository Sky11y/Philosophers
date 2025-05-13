/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpiensal <jpiensal@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 15:29:04 by jpiensal          #+#    #+#             */
/*   Updated: 2025/05/13 12:53:36 by jpiensal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	init_locks(t_master *master)
{
	int	i;

	if (pthread_mutex_init(&master->print_lock, NULL))
		return (philo_error(master, e_lock));
	if (pthread_mutex_init(&master->time_lock, NULL))
		return (philo_error(master, e_lock));
	master->forks = malloc(sizeof(pthread_mutex_t) * (master->total_philos));
	if (!master->forks)
		return (philo_error(master, e_memory));
	i = 0;
	while (i < master->total_philos)
	{
		if (pthread_mutex_init(&master->forks[i++], NULL))
			return (philo_error(master, e_lock));
	}
	return (0);
}

int	destroy_locks(t_master *master)
{
	int	i;

	if (pthread_mutex_destroy(&master->print_lock))
		return (philo_error(master, e_unlock));
	if (pthread_mutex_destroy(&master->time_lock))
		return (philo_error(master, e_unlock));
	i = 0;
	while (i < master->total_philos)
	{
		if (pthread_mutex_destroy(&master->forks[i++]))
			return (philo_error(master, e_unlock));
	}
	return (0);
}
