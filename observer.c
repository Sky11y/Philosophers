/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   observer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpiensal <jpiensal@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 15:26:54 by jpiensal          #+#    #+#             */
/*   Updated: 2025/05/13 15:13:41 by jpiensal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

/*static void	observe_loop(t_master *master, unsigned int timestamp, int i)
{
	while (!master->error && master->is_eaten)
	{
		if (master->philo_arr[i].eat_count == 0)
		{
			if (++i == master->total_philos)
				i = 0;
			continue ;
		}
		pthread_mutex_lock(&master->time_lock);
		timestamp = get_current_time(master);
		pthread_mutex_unlock(&master->time_lock);
		if (master->philo_arr[i].is_eating == false && \
				timestamp - master->philo_arr[i].eaten >= master->time_to_die)
		{
			print(master, i + 1, e_die);
			break ;
		}
		if (++i == master->total_philos)
			i = 0;
	}
}

void	*observer(void *arg)
{
	t_master		*master;

	master = (t_master *)arg;
	while (master->philos_started < master->total_philos)
		continue ;
	observe_loop(master, 0, 0);
	master->is_finished = true;
	return (NULL);
}*/

static void	observe_loop(t_master *master, t_philo *philo)
{
	unsigned int	timestamp;

	while (!master->error && !master->is_dead)
	{
		pthread_mutex_lock(&master->time_lock);
		timestamp = get_current_time(master);
		pthread_mutex_unlock(&master->time_lock);
		if (philo->is_eating == false && timestamp - philo->eaten >= philo->time_to_die)
		{
			print(master, philo->id, e_die);
			break ;
		}
	}
}

void	*observe(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	observe_loop(philo->data, philo);
	philo->data->is_eaten--;
	return (NULL);
}
