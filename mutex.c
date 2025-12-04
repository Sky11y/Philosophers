/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpiensal <jpiensal@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 15:29:04 by jpiensal          #+#    #+#             */
/*   Updated: 2025/05/26 11:48:11 by jpiensal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static int	destroy_failed_locks(t_master *master, int no_of_inits, int is_all);

int	init_locks(t_master *master, int i)
{
	master->forks = malloc(sizeof(pthread_mutex_t) * (master->total_philos));
	if (!master->forks)
		return (philo_error(master, e_memory));
	if (pthread_mutex_init(&master->print_lock, NULL))
		return (philo_error(master, e_lock));
	if (pthread_mutex_init(&master->time_lock, NULL))
	{
		destroy_failed_locks(master, 0, 0);
		return (philo_error(master, e_lock));
	}
	while (i < master->total_philos)
	{
		if (pthread_mutex_init(&master->forks[i], NULL))
		{
			destroy_failed_locks(master, i + 1, 1);
			return (philo_error(master, e_lock));
		}
		if (pthread_mutex_init(&master->philo_arr[i++].self_lock, NULL))
		{
			destroy_failed_locks(master, i + 1, 2);
			return (philo_error(master, e_lock));
		}
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
		if (pthread_mutex_destroy(&master->forks[i]))
			return (philo_error(master, e_unlock));
		if (pthread_mutex_destroy(&master->philo_arr[i++].self_lock))
			return (philo_error(master, e_unlock));
	}
	return (0);
}

static int	destroy_mutexes1(t_master *master, int no_of_inits)
{
	int	i;

	i = 0;
	while (i + 1 < no_of_inits)
	{
		if (pthread_mutex_destroy(&master->forks[i]))
			return (-1);
		if (pthread_mutex_destroy(&master->philo_arr[i++].self_lock))
			return (-1);
	}
	return (0);
}

static int	destroy_mutexes2(t_master *master, int no_of_inits)
{
	int	i;

	i = 0;
	while (i < no_of_inits)
	{
		if (pthread_mutex_destroy(&master->forks[i]))
			return (-1);
		if (i + 1 == no_of_inits)
			break ;
		if (pthread_mutex_destroy(&master->philo_arr[i++].self_lock))
			return (-1);
	}
	return (0);
}

static int	destroy_failed_locks(t_master *master, int no_of_inits, int is_all)
{
	int	i;

	if (pthread_mutex_destroy(&master->print_lock))
		return (philo_error(master, e_unlock));
	if (is_all > 0)
	{
		if (pthread_mutex_destroy(&master->time_lock))
			return (philo_error(master, e_unlock));
	}
	i = 0;
	if (is_all == 1)
	{
		if (destroy_mutexes1(master, no_of_inits))
			return (philo_error(master, e_unlock));
	}
	else if (is_all == 2)
	{
		if (destroy_mutexes2(master, no_of_inits))
			return (philo_error(master, e_unlock));
	}
	return (0);
}
