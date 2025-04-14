/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpiensal <jpiensal@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 16:23:16 by jpiensal          #+#    #+#             */
/*   Updated: 2025/04/14 17:09:49 by jpiensal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static int	init_philo(t_philo *philo, t_master *master)
{
	philo->id = master->philo_ids++;
	philo->wait_forks = exchange_current_time();
	if (!philo->wait_forks)
		return (philo_error(e_create_philo));
	philo->got_forks = 0;
	return (0);
}

static void	*create_philo(void *arg)
{
	t_master	*master;
	t_philo		philo;

	master = (t_master *)arg;
	if (init_philo(&philo, master))
	{
		philo_error(e_create_philo);
		return (NULL);
	}
	while (!master->is_dead && !master->error)
	{
		take_forks(master, &philo);
		if (philo.got_forks - philo.wait_forks > master->time_to_die * 1000)
		{
			die(master, &philo);
			return (NULL);
		}
		print(master, &philo, e_eat);
		usleep(master->time_to_eat * 1000);
		release_forks(master, &philo);
		print(master, &philo, e_sleep);
		usleep(master->time_to_sleep * 1000);
		print(master, &philo, e_think);
		usleep(master->time_to_think * 1000);
	}
	return (NULL);
}

int	philosophers(t_master *master)
{
	pthread_t	*philo;
	int			i;

	philo = malloc(sizeof(pthread_t) * master->total_philos);
	if (!philo)
		return (philo_error(e_memory));
	i = 0;
	while (i < master->total_philos)
	{
		if (pthread_create(&philo[i], NULL, create_philo, (void *)master))
			return (philo_error(e_create_philo));
		i++;
	}
	i = 0;
	while (i < master->total_philos)
	{
		if (pthread_join(philo[i], NULL))
			return (philo_error(e_join));
		i++;
	}
	free(philo);
	return (0);
}
