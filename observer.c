/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   observer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpiensal <jpiensal@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 15:26:54 by jpiensal          #+#    #+#             */
/*   Updated: 2025/05/26 12:56:39 by jpiensal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	observe_loop(t_master *master, unsigned int timestamp, int i,
		int eat_count)
{
	while (!master->error && master->is_eaten)
	{
		pthread_mutex_lock(&master->philo_arr[i].self_lock);
		eat_count = master->philo_arr[i].eat_count;
		pthread_mutex_unlock(&master->philo_arr[i].self_lock);
		if (eat_count == 0)
		{
			if (++i == master->total_philos)
				i = 0;
			continue ;
		}
		pthread_mutex_lock(&master->time_lock);
		timestamp = get_current_time(master);
		pthread_mutex_unlock(&master->time_lock);
		if (timestamp - master->philo_arr[i].eaten >= master->time_to_die)
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
	if (master->total_philos == 1)
		return (NULL);
	while (master->philos_started < master->total_philos
		&& master->error == false)
		continue ;
	if (master->error == false)
		observe_loop(master, 0, 0, -1);
	return (NULL);
}
