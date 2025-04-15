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
	philo->eat_count = master->times_to_eat;
	philo->got_forks = 0;
	philo->wait_forks = get_current_time();
	if (!philo->wait_forks)
		return (philo_error(master, e_gettime));
	return (0);
}

static void	master_loop(t_master *master, t_philo *philo)
{
	while (!master->is_dead && !master->error)
	{
		take_forks(master, philo);
		print(master, philo, e_gotfork);
		if (philo->got_forks - philo->wait_forks > master->time_to_die * 1000)
		{
			release_forks(master, philo);
			die(master, philo);
			return ;
		}
		print(master, philo, e_eat);
		usleep(master->time_to_eat * 1000);
		release_forks(master, philo);
		if (!philo->eat_count)
			return ;
		print(master, philo, e_sleep);
		usleep(master->time_to_sleep * 1000);
		print(master, philo, e_think);
		usleep(master->time_to_think * 1000);
	}
}

static void	*start_thread(void *arg)
{
	t_master	*master;
	t_philo		philo;

	master = (t_master *)arg;
	if (init_philo(&philo, master))
	{
		philo_error(master, e_create_philo);
		return (NULL);
	}
	if (master->total_philos == 1)
	{
		usleep(master->time_to_die * 1000);
		die(master, &philo);
		return (NULL);
	}
	master_loop(master, &philo);
	return (NULL);
}

int	philosophers(t_master *master, int count)
{
	pthread_t	*philo;

	philo = malloc(sizeof(pthread_t) * master->total_philos);
	if (!philo)
		return (philo_error(master, e_memory));
	while (count < master->total_philos)
	{
		if (pthread_create(&philo[count++], NULL, start_thread, (void *)master))
		{
			free(philo);
			return (philo_error(master, e_create_philo));
		}
	}
	while (count--)
	{
		if (pthread_join(philo[count], NULL))
		{
			free(philo);
			return (philo_error(master, e_join));
		}
	}
	free(philo);
	return (0);
}
